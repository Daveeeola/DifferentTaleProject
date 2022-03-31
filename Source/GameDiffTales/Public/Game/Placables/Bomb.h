// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstanceProxy.h"
#include "Game/BombInterface.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS()
class GAMEDIFFTALES_API ABomb : public AActor, public IBombInterface
{
	GENERATED_BODY()

	protected:
	UPROPERTY(BlueprintReadOnly)
	FVector ActorScale;

	bool bBlockHit;

	UPROPERTY(BlueprintReadOnly)
	float TraceDistance;
	
public:	
	// Sets default values for this actor's properties
	ABomb();
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components")
	class USphereComponent* Sphere;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Components")
	class UStaticMeshComponent* BombMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	public:
	void SetTraceDistance(float Distance)
	{
		TraceDistance = Distance;
	}

	UFUNCTION(BlueprintCallable)
	void DetectDestructibleBlocksInAllDirection(float YawAngle, float Distance);
};
