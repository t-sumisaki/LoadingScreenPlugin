// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "LoadingScreen.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MoviePlayer.h"
#include "SThrobber.h"
#include "LoadingScreenSettings.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"

#define LOCTEXT_NAMESPACE "FLoadingScreenModule"


struct FLoadingScreenBrush : public FSlateDynamicImageBrush, public FGCObject
{
	FLoadingScreenBrush(const FName InTextureName, const FVector2D& InImageSize)
		:FSlateDynamicImageBrush(InTextureName, InImageSize)
	{
		SetResourceObject(LoadObject<UObject>(NULL, *InTextureName.ToString()));
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector)
	{
		if (UObject * CachedResourceObject = GetResourceObject())
		{
			Collector.AddReferencedObject(CachedResourceObject);
		}
	}
};


class SLoadingScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLoadingScreen) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		const ULoadingScreenSettings* Settings = GetDefault<ULoadingScreenSettings>();
		static const FName LoadingScreenName(Settings->LoadingScreenTexture.GetAssetPathName());
		UE_LOG(LogTemp, Log, TEXT("Asset: %s"), *LoadingScreenName.ToString());

		LoadingScreenBrush = MakeShareable(new FLoadingScreenBrush(LoadingScreenName, Settings->TextureSize));


		FSlateBrush * BGBrush = new FSlateBrush();
		BGBrush->TintColor = Settings->BackgroundTintColor;

		ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SBorder)
				.BorderImage(BGBrush)
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SImage)
				.Image(LoadingScreenBrush.Get())
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.VAlign(VAlign_Bottom)
				.HAlign(HAlign_Right)
				.Padding(FMargin(10.0f))
				[
					SNew(SThrobber)
					.Visibility(this, &SLoadingScreen::GetLoadIndirectorVisibility)
				]
			]
		];
	}

	EVisibility GetLoadIndirectorVisibility() const
	{
		bool Vis = GetMoviePlayer()->IsLoadingFinished();
		return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;
	}

	TSharedPtr<FSlateDynamicImageBrush> LoadingScreenBrush;
};


class FLoadingScreenModule : public ILoadingScreenModule
{
public:
	virtual void StartupModule() override
	{
		RegisterSettings();

		if (IsMoviePlayerEnabled())
		{
			CreateScreen();
		}
	}

	virtual void ShutdownModule() override
	{
		if (UObjectInitialized())
		{
			UnregisterSettings();
		}
	}

	virtual bool SupportsDynamicReloading() override
	{
		return true;
	}

	virtual bool IsGameModule() const override
	{
		return true;
	}

	virtual void StartInGameLoadingScreen(bool bPlayerUntilStopped, float PlayTime) override
	{
		const ULoadingScreenSettings* Settings = GetDefault<ULoadingScreenSettings>();


		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = !bPlayerUntilStopped;
		LoadingScreen.bWaitForManualStop = bPlayerUntilStopped;
		LoadingScreen.bAllowEngineTick = bPlayerUntilStopped;
		LoadingScreen.MinimumLoadingScreenDisplayTime = PlayTime;
		LoadingScreen.WidgetLoadingScreen = SNew(SLoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}

	virtual void StopInGameLoadingScreen() override
	{
		GetMoviePlayer()->StopMovie();
	}

	virtual void CreateScreen()
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreen.MinimumLoadingScreenDisplayTime = 3.0f;
		LoadingScreen.WidgetLoadingScreen = SNew(SLoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}

private:
	bool HandleSettingsSaved()
	{
		ULoadingScreenSettings* Settings = GetMutableDefault<ULoadingScreenSettings>();
		bool ResaveSettings = false;

		if (ResaveSettings)
		{
			Settings->SaveConfig();
		}

		return true;
	}

	void RegisterSettings()
	{
		if (ISettingsModule * SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		{
			// Create category
			ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");

			// Register settings
			ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings("Project", "Plugins", "LoadingScreen",
				LOCTEXT("LoadingScreenSettingsName", "LoadingScreen"),
				LOCTEXT("LoadingScreenSettingsDescription", "Configure loading screen plug-in."),
				GetMutableDefault<ULoadingScreenSettings>()
			);

			if (SettingsSection.IsValid())
			{
				SettingsSection->OnModified().BindRaw(this, &FLoadingScreenModule::HandleSettingsSaved);
			}

		}
	}

	void UnregisterSettings()
	{
		if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		{
			SettingsModule->UnregisterSettings("Project", "Plugins", "LoadingScreen");
		}
	}
};



#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLoadingScreenModule, LoadingScreen)