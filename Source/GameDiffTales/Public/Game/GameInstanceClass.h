// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstanceClass.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDIFFTALES_API UGameInstanceClass : public UGameInstance
{
	GENERATED_BODY()
	
	public:

	UGameInstanceClass();
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 HighScore;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FString SavedGame;
	
};
