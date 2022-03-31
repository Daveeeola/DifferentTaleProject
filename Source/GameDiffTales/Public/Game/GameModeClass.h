// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModeInterface.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeClass.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDIFFTALES_API AGameModeClass : public AGameModeBase, public IGameModeInterface
{
	GENERATED_BODY()

	public:

	AGameModeClass();
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Variables")
	int32 PlayerScore;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Variables")
	int32 Lives;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Variables")
	int32 HighScore;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Variables")
	int32 TimeMin;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Variables")
	int32 TimeSec;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Variables")
	FTimerHandle TimerTimeHandle;
	
	public:
	
	virtual void BeginPlay() override;

	void ReduceLife();

	UFUNCTION()
	void TimeDownEvent();

	virtual void AddScore_Implementation(int Amount) override;

	virtual void ReduceLive_Implementation() override;

	virtual void LoadHighScore_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GameOverEvent();
};
