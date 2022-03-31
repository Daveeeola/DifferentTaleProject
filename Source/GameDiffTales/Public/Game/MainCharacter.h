// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharInterface.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class GAMEDIFFTALES_API AMainCharacter : public ACharacter, public ICharInterface
{
	GENERATED_BODY()

	protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Player Properties")
	TSoftObjectPtr <class ABlockoutToolsParent> BlockoutBox;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Bomb")
	TSubclassOf<class ABomb> BombClass;
	
	
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

	public:
	UPROPERTY(VisibleDefaultsOnly, Category="Components")
	class UBoxComponent* CollisionBox;

	UPROPERTY(VisibleDefaultsOnly, Category="Components")
	class UStaticMeshComponent* StaticMesh;

	FTimerHandle ColorChangeHandle;
	
	
public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void InitializeVariables();

	void MoveForward(float Value);

	void MoveRight(float Value);

	UFUNCTION(BlueprintCallable)
	void DropBomb();

	FVector GetBombSpawnLocation();
	UFUNCTION()
	void OnCapsuleOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	void ReturnColorToNormal();
	
	//Interfaces;
	virtual void OnBombHit_Implementation() override;

	virtual void IncreaseTraceDistance_Implementation() override;

	virtual void GetCurrentDirection_Implementation(EEDirectionToGo& OutCurrentDirection) override;

	virtual void GetAiMiddleLocation_Implementation(EEDirectionToGo InDirection, FVector& OutMiddleLocation, EEDirectionToGo& DirectionToGo) override;

	
};

