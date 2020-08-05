// Fill out your copyright notice in the Description page of Project Settings.


#include "HoudiniBlueprintLibrary.h"

void UHoudiniBlueprintLibrary::HAssetToggleExtrude(AHoudiniAssetActor* HoudiniAssetActor)
{
    HOUDINI_LOG_MESSAGE(TEXT("HAssetToggleExtrude Enter"));
    if (!FHoudiniEngineUtils::IsInitialized())
    {
        HOUDINI_LOG_MESSAGE(TEXT("Engine is not initializesd."));
        return;
    }

    UHoudiniAssetComponent* HoudiniAssetComponent = HoudiniAssetActor->GetHoudiniAssetComponent();
    auto parm = HoudiniAssetComponent->FindParameter("extrude");
    if (parm == nullptr) return;

    // HOUDINI_LOG_MESSAGE(TEXT("Found the extrude parm: %s"), *parm->GetParameterName());

    if (auto ParamToggle = Cast<UHoudiniAssetParameterToggle>( parm )) {
        ECheckBoxState st = ParamToggle->IsChecked(0);

        if (st == ECheckBoxState::Checked) {
            st = ECheckBoxState::Unchecked;
            HOUDINI_LOG_MESSAGE(TEXT("Unchecking :("));
        } else {
            st = ECheckBoxState::Checked;
            HOUDINI_LOG_MESSAGE(TEXT("Checking :)"));
        }
        ParamToggle->CheckStateChanged(st, 0);

        HoudiniAssetComponent->StartTaskAssetCookingManual();
    }
}

void UHoudiniBlueprintLibrary::HAssetAdvanceFrame(AHoudiniAssetActor* HoudiniAssetActor)
{
    HOUDINI_LOG_MESSAGE(TEXT("HAssetAdvanceFrame Enter"));
    if (!FHoudiniEngineUtils::IsInitialized())
    {
        HOUDINI_LOG_MESSAGE(TEXT("Engine is not initializesd."));
        return;
    }

    UHoudiniAssetComponent* HoudiniAssetComponent = HoudiniAssetActor->GetHoudiniAssetComponent();
    auto parm = HoudiniAssetComponent->FindParameter("frame");
    if (parm == nullptr) return;

    if (auto ParamInt = Cast<UHoudiniAssetParameterInt>( parm )) {
        int frame = ParamInt->GetValue(0).GetValue();
        HOUDINI_LOG_MESSAGE(TEXT("Frame number %d."), frame);

        ParamInt->SetValue(frame + 1, 0, false);
        HoudiniAssetComponent->NotifyParameterChanged( ParamInt );
        HoudiniAssetComponent->StartTaskAssetCookingManual();
    }
}

int UHoudiniBlueprintLibrary::HAssetGetFrame(AHoudiniAssetActor* HoudiniAssetActor)
{
    if (!FHoudiniEngineUtils::IsInitialized())
    {
        HOUDINI_LOG_MESSAGE(TEXT("Engine is not initializesd."));
        return -1;
    }

    UHoudiniAssetComponent* HoudiniAssetComponent = HoudiniAssetActor->GetHoudiniAssetComponent();
    auto parm = HoudiniAssetComponent->FindParameter("frame");
    if (parm == nullptr) return -1;
    if (auto ParamInt = Cast<UHoudiniAssetParameterInt>( parm )) {
        int ret = ParamInt->GetValue(0).GetValue();
        HOUDINI_LOG_MESSAGE(TEXT("Frame number %d."), ret);
        return ret;
    }
    return -1;
}

void UHoudiniBlueprintLibrary::HAssetAdvanceTime(AHoudiniAssetActor* HoudiniAssetActor, float dt)
{
    HOUDINI_LOG_MESSAGE(TEXT("HAssetAdvanceTime Enter"));
    if (!FHoudiniEngineUtils::IsInitialized())
    {
        HOUDINI_LOG_MESSAGE(TEXT("Engine is not initializesd."));
        return;
    }

    UHoudiniAssetComponent* HoudiniAssetComponent = HoudiniAssetActor->GetHoudiniAssetComponent();
    auto parm = HoudiniAssetComponent->FindParameter("simtime");
    if (parm == nullptr) return;

    if (auto ParamFloat = Cast<UHoudiniAssetParameterFloat>( parm )) {
        float frame = ParamFloat->GetParameterValue(0, -1);
        HOUDINI_LOG_MESSAGE(TEXT("Sim time %f."), frame);

        ParamFloat->SetValue(frame + dt, 0, false);
        HoudiniAssetComponent->NotifyParameterChanged( ParamFloat );
        HoudiniAssetComponent->StartTaskAssetCookingManual();
    }
}

float UHoudiniBlueprintLibrary::HAssetGetTime(AHoudiniAssetActor* HoudiniAssetActor)
{
    if (!FHoudiniEngineUtils::IsInitialized())
    {
        HOUDINI_LOG_MESSAGE(TEXT("Engine is not initializesd."));
        return -1;
    }

    UHoudiniAssetComponent* HoudiniAssetComponent = HoudiniAssetActor->GetHoudiniAssetComponent();
    auto parm = HoudiniAssetComponent->FindParameter("frame");
    if (parm == nullptr) return -1;
    if (auto ParamFloat = Cast<UHoudiniAssetParameterFloat>( parm )) {
        float time = ParamFloat->GetParameterValue(0, -1);
        return time;
    }
    return -1;
}

void UHoudiniBlueprintLibrary::HAssetChangePos(AHoudiniAssetActor* HoudiniAssetActor, float dx, float dy, float dz)
{
    HOUDINI_LOG_MESSAGE(TEXT("HAssetChangePos Enter"));
    if (!FHoudiniEngineUtils::IsInitialized())
    {
        HOUDINI_LOG_MESSAGE(TEXT("Engine is not initializesd."));
        return;
    }

    UHoudiniAssetComponent* HoudiniAssetComponent = HoudiniAssetActor->GetHoudiniAssetComponent();
    auto parm = HoudiniAssetComponent->FindParameter("extr_pos");
    if (parm == nullptr) return;

    if (auto ParamFloat = Cast<UHoudiniAssetParameterFloat>( parm )) {
        // Houdini y & z are flipped from UE4 y & z
        float x = ParamFloat->GetParameterValue(0, 0);
        float y = ParamFloat->GetParameterValue(2, 0);
        float z = ParamFloat->GetParameterValue(1, 0);

        ParamFloat->SetValue(x + dx, 0, false);
        ParamFloat->SetValue(y + dy, 2, false);
        ParamFloat->SetValue(z + dz, 1, false);
        HoudiniAssetComponent->NotifyParameterChanged( ParamFloat );
        HoudiniAssetComponent->StartTaskAssetCookingManual();
    }
}

void UHoudiniBlueprintLibrary::HAssetSetPos(AHoudiniAssetActor* HoudiniAssetActor, float x, float y, float z)
{
    HOUDINI_LOG_MESSAGE(TEXT("HAssetChangePos Enter"));
    if (!FHoudiniEngineUtils::IsInitialized())
    {
        HOUDINI_LOG_MESSAGE(TEXT("Engine is not initializesd."));
        return;
    }

    UHoudiniAssetComponent* HoudiniAssetComponent = HoudiniAssetActor->GetHoudiniAssetComponent();
    auto parm = HoudiniAssetComponent->FindParameter("extr_pos");
    if (parm == nullptr) return;

    if (auto ParamFloat = Cast<UHoudiniAssetParameterFloat>( parm )) {
        ParamFloat->SetValue(x, 0, false);
        ParamFloat->SetValue(y, 2, false);
        ParamFloat->SetValue(z, 1, false);
        HoudiniAssetComponent->NotifyParameterChanged( ParamFloat );
        HoudiniAssetComponent->StartTaskAssetCookingManual();
    }
}

// Others: extr_temp, extr_vel
