// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Game/EDirectionToGo.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCharInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEDIFFTALES_API ICharInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interfaces")
	void OnBombHit();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interfaces")
	void IncreaseTraceDistance();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interfaces")
	void GetCurrentDirection(EEDirectionToGo& OutCurrentDirection);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interfaces")
	void GetAiMiddleLocation(EEDirectionToGo InDirection, FVector& OutMiddleLocation, EEDirectionToGo& OutDirectionToGo);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interfaces")
	void GetLocationAtTraceAtFreeDirection(EEDirectionToGo Direction, FVector& Location, bool& bHit);
	
};
