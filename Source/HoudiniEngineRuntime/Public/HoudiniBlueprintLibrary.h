// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HoudiniAssetActor.h"
#include "HoudiniBlueprintLibrary.generated.h"


/**
 * 
 */
UCLASS()
class HOUDINIENGINERUNTIME_API UHoudiniBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category="Houdini Functions")
	static void MyFirstFunction(AHoudiniAssetActor* HoudiniAssetActor);
};
