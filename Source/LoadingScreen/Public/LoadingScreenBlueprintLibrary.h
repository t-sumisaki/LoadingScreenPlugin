// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LoadingScreenBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LOADINGSCREEN_API ULoadingScreenBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "LoadingScreen")
		static void PlayLoadingScreen(bool bPlayUntilStopped, float PlayTime);
	
	UFUNCTION(BlueprintCallable, Category = "LoadingScreen")
		static void StopLoadingScreen();
	
};
