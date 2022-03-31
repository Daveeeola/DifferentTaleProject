// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/DestructInterface.h"
#include "Game/Placables/Block.h"
#include "Block_Destructible.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDIFFTALES_API ABlock_Destructible : public ABlock, public IDestructInterface
{
	GENERATED_BODY()

public:
	ABlock_Destructible();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Variables")
	bool bIsExitBlock;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Variables")
	TSubclassOf<class AGoodies> Goodies;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Variables")
	bool bHasGoodies;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Variables")
	FLinearColor Color;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category="Variables")
	class UParticleSystem* ParticleSystem;



	public:
	//Methods

	virtual void BeginPlay() override;

	virtual void Destroy_Implementation() override;

	virtual void HitAfterEnemyBombed_Implementation() override;

};
