// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UMG.h"
#include "LoadingScreenSettings.generated.h"

/**
 * 
 */
UCLASS(config=Game, defaultconfig)
class LOADINGSCREEN_API ULoadingScreenSettings : public UObject
{
	GENERATED_BODY()
	
public:
	ULoadingScreenSettings(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, config, Category = "LoadingScreen", meta = (AllowedClasses = "Texture", EditCondition="!bOverrideByWidget"))
	FSoftObjectPath LoadingScreenTexture;

	UPROPERTY(EditAnywhere, config, Category = "LoadingScreen", meta = (EditCondition = "!bOverrideByWidget"))
		FVector2D TextureSize;

	UPROPERTY(EditAnywhere, config, Category = "LoadingScreen", meta = (EditCondition = "!bOverrideByWidget"))
		FLinearColor BackgroundTintColor;
};
