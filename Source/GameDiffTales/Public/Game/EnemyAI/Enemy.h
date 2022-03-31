// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Game/EDirectionToGo.h"
#include "CoreMinimal.h"
#include "Game/CharInterface.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class GAMEDIFFTALES_API AEnemy : public ACharacter, public ICharInterface
{
	GENERATED_BODY()

	protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Player Properties")
	TSoftObjectPtr <class ABlockoutToolsParent> BlockoutBox;
	
	
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category="Player Properties")
	float LevelWidthX;
	
	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category="Player Properties")
	float LevelWidthY;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category="Player Properties")
	float GridSize;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category="Player Properties")
	float NumberOfTileX;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category="Player Properties")
	float NumberTileY;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category="Player Properties")
	int32 Health;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category="Player Properties")
	float TraceDistance;

	UPROPERTY(BlueprintReadWrite, VisibleDefaultsOnly, Category="Player Properties")
	bool bBombOverlapped;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components")
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components")
	class UTextRenderComponent* ScoreText;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Properties")
	EEDirectionToGo DirectionToGo;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Properties")
	EEDirectionToGo CurrentDirection;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Properties")
	TArray<EEDirectionToGo> HitDirections;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Properties")
	TArray<EEDirectionToGo> Directions;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Properties")
	TArray<EEDirectionToGo> NotHitDirections;
	

public:
	// Sets default values for this character's properties
	AEnemy();

	UFUNCTION(BlueprintCallable)
	void InitializeVariables();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CheckForBlockage();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GetRandomSuitableDirection();

	UFUNCTION(BlueprintCallable)
	void GetObstaclesInAllDirection(float YawAngle, EEDirectionToGo Direction);

	UFUNCTION(BlueprintCallable)
	void GetBoxesInAllFourDirections(float YawAngle);

	UFUNCTION(BlueprintCallable)
	void LocationAtTraceAlongDirection(EEDirectionToGo Direction, float TraceLength, FVector& HitLocation, bool &bHit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnBombHit_Implementation() override;

	virtual void GetCurrentDirection_Implementation(EEDirectionToGo& OutCurrentDirection) override;

	virtual void GetAiMiddleLocation_Implementation(EEDirectionToGo InDirection, FVector& OutMiddleLocation, EEDirectionToGo& OutDirectionToGo) override;

	virtual void GetLocationAtTraceAtFreeDirection_Implementation(EEDirectionToGo Direction, FVector& Location, bool& bHit) override;
	
};
