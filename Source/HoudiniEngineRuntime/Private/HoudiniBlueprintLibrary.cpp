// Fill out your copyright notice in the Description page of Project Settings.


#include "HoudiniBlueprintLibrary.h"

UHoudiniAssetParameter* GetHParm(AHoudiniAssetActor* HoudiniAssetActor, const FString& ParmName)
{
    if (!FHoudiniEngineUtils::IsInitialized())
    {
        HOUDINI_LOG_MESSAGE(TEXT("Engine is not initializesd."));
        return nullptr;
    }
    if (!HoudiniAssetActor) return nullptr;

    UHoudiniAssetComponent* HAC = HoudiniAssetActor->GetHoudiniAssetComponent();
    if (!HAC) return nullptr;

    return HAC->FindParameter(ParmName);
}

void UHoudiniBlueprintLibrary::HAssetToggleExtrude(AHoudiniAssetActor* HoudiniAssetActor)
{
    HOUDINI_LOG_MESSAGE(TEXT("HAssetToggleExtrude Enter"));
    auto parm = GetHParm(HoudiniAssetActor, "extrude");
    if (parm == nullptr) return;

    if (auto ParamToggle = Cast<UHoudiniAssetParameterToggle>( parm )) {
        ECheckBoxState st = ParamToggle->IsChecked(0);

        if (st == ECheckBoxState::Checked) {
            st = ECheckBoxState::Unchecked;
        } else {
            st = ECheckBoxState::Checked;
        }
        ParamToggle->CheckStateChanged(st, 0);
    }
}

void UHoudiniBlueprintLibrary::HAssetAdvanceFrame(AHoudiniAssetActor* HoudiniAssetActor)
{
    HOUDINI_LOG_MESSAGE(TEXT("HAssetAdvanceFrame Enter"));
    auto parm = GetHParm(HoudiniAssetActor, "frame");
    if (parm == nullptr) return;

    if (auto ParamInt = Cast<UHoudiniAssetParameterInt>( parm )) {
        int frame = ParamInt->GetParameterValue(0, -1);
        HOUDINI_LOG_MESSAGE(TEXT("Sim frame number %d -> %d."), frame, frame + 1);

        ParamInt->SetValue(frame + 1, 0, true);
    }
}

void UHoudiniBlueprintLibrary::HAssetSetFrame(AHoudiniAssetActor* HoudiniAssetActor, int frame)
{
    HOUDINI_LOG_MESSAGE(TEXT("HAssetSetFrame Enter"));
    auto parm = GetHParm(HoudiniAssetActor, "frame");
    if (parm == nullptr) return;

    if (auto ParamInt = Cast<UHoudiniAssetParameterInt>( parm )) {
        ParamInt->SetValue(frame, 0, true);
    }
}

int UHoudiniBlueprintLibrary::HAssetGetFrame(AHoudiniAssetActor* HoudiniAssetActor)
{
    auto parm = GetHParm(HoudiniAssetActor, "frame");
    if (parm == nullptr) return -1;

    if (auto ParamInt = Cast<UHoudiniAssetParameterInt>( parm )) {
        int frame = ParamInt->GetParameterValue(0, -1);
        return frame;
    }
    return -1;
}

void UHoudiniBlueprintLibrary::HAssetAdvanceTime(AHoudiniAssetActor* HoudiniAssetActor, float dt)
{
    HOUDINI_LOG_MESSAGE(TEXT("HAssetAdvanceTime Enter"));
    auto parm = GetHParm(HoudiniAssetActor, "simtime");
    if (parm == nullptr) return;

    if (auto ParamFloat = Cast<UHoudiniAssetParameterFloat>( parm )) {
        float time = ParamFloat->GetParameterValue(0, -1);
        HOUDINI_LOG_MESSAGE(TEXT("Sim time %f."), time);

        ParamFloat->SetValue(time + dt, 0, true);
    }
}

float UHoudiniBlueprintLibrary::HAssetGetTime(AHoudiniAssetActor* HoudiniAssetActor)
{
    auto parm = GetHParm(HoudiniAssetActor, "simtime");
    if (parm == nullptr) return -1;

    if (auto ParamFloat = Cast<UHoudiniAssetParameterFloat>( parm )) {
        float time = ParamFloat->GetParameterValue(0, -1);
        return time;
    }
    return -1;
}

FVector HAssetGetPos(AHoudiniAssetActor* HoudiniAssetActor)
{
    FVector ret;

    auto parm = GetHParm(HoudiniAssetActor, "extr_pos");
    if (parm == nullptr) return;

    if (auto ParamFloat = Cast<UHoudiniAssetParameterFloat>( parm )) {
        // Houdini y & z are flipped from UE4 y & z
        ret.X = ParamFloat->GetParameterValue(0, 0);
        ret.Y = ParamFloat->GetParameterValue(2, 0);
        ret.Z = ParamFloat->GetParameterValue(1, 0);
    }
    return ret;
}


void UHoudiniBlueprintLibrary::HAssetChangePos(AHoudiniAssetActor* HoudiniAssetActor, float dx, float dy, float dz)
{
    HOUDINI_LOG_MESSAGE(TEXT("HAssetChangePos Enter"));
    auto parm = GetHParm(HoudiniAssetActor, "extr_pos");
    if (parm == nullptr) return;

    if (auto ParamFloat = Cast<UHoudiniAssetParameterFloat>( parm )) {
        // Houdini y & z are flipped from UE4 y & z
        float x = ParamFloat->GetParameterValue(0, 0);
        float y = ParamFloat->GetParameterValue(2, 0);
        float z = ParamFloat->GetParameterValue(1, 0);

        ParamFloat->SetValue(x + dx, 0, false);
        ParamFloat->SetValue(y + dy, 2, false);
        ParamFloat->SetValue(z + dz, 1, true);
    }
}

void UHoudiniBlueprintLibrary::HAssetSetPos(AHoudiniAssetActor* HoudiniAssetActor, float x, float y, float z)
{
    HOUDINI_LOG_MESSAGE(TEXT("HAssetSetPos Enter"));
    auto parm = GetHParm(HoudiniAssetActor, "extr_pos");
    if (parm == nullptr) return;

    if (auto ParamFloat = Cast<UHoudiniAssetParameterFloat>( parm )) {
        ParamFloat->SetValue(x, 0, false);
        ParamFloat->SetValue(y, 2, false);
        ParamFloat->SetValue(z, 1, true);
    }
}

void UHoudiniBlueprintLibrary::HAssetSetRot(AHoudiniAssetActor* HoudiniAssetActor, float rx, float ry, float rz)
{
    HOUDINI_LOG_MESSAGE(TEXT("HAssetSetRot Enter"));
    auto parm = GetHParm(HoudiniAssetActor, "extr_rot");
    if (parm == nullptr) return;

    if (auto ParamFloat = Cast<UHoudiniAssetParameterFloat>( parm )) {
        ParamFloat->SetValue(rx, 0, false);
        ParamFloat->SetValue(ry, 2, false);
        ParamFloat->SetValue(rz, 1, true);
    }
}

void UHoudiniBlueprintLibrary::HAssetSetTransform(AHoudiniAssetActor* HoudiniAssetActor, const FTransform& trans)
{
    if (!HoudiniAssetActor) return;
    const FVector& loc = trans.GetLocation();
    const FVector& dir = trans.GetRotation().Euler();

    HAssetSetPos(HoudiniAssetActor, loc.X, loc.Y, loc.Z);
    HAssetSetRot(HoudiniAssetActor, dir.X, dir.Y, dir.Z);
}

// Others: extr_temp, extr_vel

void UHoudiniBlueprintLibrary::HAssetCook(AHoudiniAssetActor* HoudiniAssetActor)
{
    HOUDINI_LOG_MESSAGE(TEXT("HAssetCook Enter"));
    UHoudiniAssetComponent* HoudiniAssetComponent = HoudiniAssetActor->GetHoudiniAssetComponent();
    // auto parm = GetHParm(HoudiniAssetActor, "simtime");
    // if (parm == nullptr) return;

    // if (auto ParamFloat = Cast<UHoudiniAssetParameterFloat>( parm )) {
    //     float time = ParamFloat->GetParameterValue(0, -1);
    //     HoudiniAssetComponent->NotifyParameterChanged(ParamFloat);
    // }

    HoudiniAssetComponent->StartTaskAssetCookingManual();
}
