// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadingScreenBlueprintLibrary.h"
#include "LoadingScreen.h"

ULoadingScreenBlueprintLibrary::ULoadingScreenBlueprintLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ULoadingScreenBlueprintLibrary::PlayLoadingScreen(bool bPlayUntilStopped, float PlayTime)
{
	UE_LOG(LogTemp, Log, TEXT("Play Loading Screen"));

	ILoadingScreenModule& LoadingScreenModule = ILoadingScreenModule::Get();
	LoadingScreenModule.StartInGameLoadingScreen(bPlayUntilStopped, PlayTime);
}

void ULoadingScreenBlueprintLibrary::StopLoadingScreen()
{
	UE_LOG(LogTemp, Log, TEXT("Stop Loading Screen"))
	ILoadingScreenModule& LoadingScreenModule = ILoadingScreenModule::Get();
	LoadingScreenModule.StopInGameLoadingScreen();
}