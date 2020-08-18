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
	static void HAssetToggleExtrude(AHoudiniAssetActor* HoudiniAssetActor);
	
	UFUNCTION(BlueprintCallable, Category="Houdini Functions")
	static void HAssetAdvanceFrame(AHoudiniAssetActor* HoudiniAssetActor);
	UFUNCTION(BlueprintCallable, Category="Houdini Functions")
	static void HAssetSetFrame(AHoudiniAssetActor* HoudiniAssetActor, int frame);
	UFUNCTION(BlueprintCallable, Category="Houdini Functions")
	static int HAssetGetFrame(AHoudiniAssetActor* HoudiniAssetActor);

	UFUNCTION(BlueprintCallable, Category="Houdini Functions")
	static void HAssetAdvanceTime(AHoudiniAssetActor* HoudiniAssetActor, float dt);
	UFUNCTION(BlueprintCallable, Category="Houdini Functions")
	static float HAssetGetTime(AHoudiniAssetActor* HoudiniAssetActor);

	UFUNCTION(BlueprintCallable, Category="Houdini Functions")
	static FVector HAssetGetPos(AHoudiniAssetActor* HoudiniAssetActor);
	UFUNCTION(BlueprintCallable, Category="Houdini Functions")
	static void HAssetChangePos(AHoudiniAssetActor* HoudiniAssetActor, float dx=0, float dy=0, float dz=0);
	UFUNCTION(BlueprintCallable, Category="Houdini Functions")
	static void HAssetSetPos(AHoudiniAssetActor* HoudiniAssetActor, float x, float y, float z);
	UFUNCTION(BlueprintCallable, Category="Houdini Functions")
	static void HAssetSetRot(AHoudiniAssetActor* HoudiniAssetActor, float dx, float dy, float dz);

	UFUNCTION(BlueprintCallable, Category="Houdini Functions")
	static void HAssetSetTransform(AHoudiniAssetActor* HoudiniAssetActor, const FTransform& trans);

	UFUNCTION(BlueprintCallable, Category="Houdini Functions")
	static void HAssetCook(AHoudiniAssetActor* HoudiniAssetActor);
};
