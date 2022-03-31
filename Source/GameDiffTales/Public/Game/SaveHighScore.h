// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveHighScore.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDIFFTALES_API USaveHighScore : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	int32 HighScore;
	
};
