// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EDirectionToGo.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EEDirectionToGo : uint8
{
  EET_Up UMETA(DisplayName = "Up"),
	EET_Down UMETA(DisplayName = "Down"),
	EET_Left UMETA(DisplayName = "Left"),
	EET_Right UMETA(DisplayName = "Right")
};

