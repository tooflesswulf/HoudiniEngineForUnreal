// Fill out your copyright notice in the Description page of Project Settings.


#include "HoudiniBlueprintLibrary.h"

void UHoudiniBlueprintLibrary::MyFirstFunction(AHoudiniAssetActor* HoudiniAssetActor)
{
    HOUDINI_LOG_MESSAGE(TEXT("Hi! Entering!"));

    UHoudiniAssetComponent* HoudiniAssetComponent = HoudiniAssetActor->GetHoudiniAssetComponent();
    auto parm = HoudiniAssetComponent->FindParameter("extrude");
    if (parm == nullptr) return;

    HOUDINI_LOG_MESSAGE(TEXT("Found the extrude parm: %s"), *parm->GetParameterName());

    if (auto ParamToggle = Cast<UHoudiniAssetParameterToggle>( parm )) {
        ECheckBoxState st = ParamToggle->IsChecked(0);

        if (st == ECheckBoxState::Checked)
        {
            ParamToggle->CheckStateChanged(ECheckBoxState::Unchecked, 0);
            HOUDINI_LOG_MESSAGE(TEXT("Unchecking :("));
        }
        else
        {
            ParamToggle->CheckStateChanged(ECheckBoxState::Checked, 0);
            HOUDINI_LOG_MESSAGE(TEXT("Checking :)"));
        }

        // if( HAPI_RESULT_SUCCESS != FHoudiniApi::CookNode( FHoudiniEngine::Get().GetSession(), ConnectedAssetId, nullptr ) )
        // {
        //     Success = false;
        // }
    }
}
