// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Goodies.generated.h"

UCLASS()
class GAMEDIFFTALES_API AGoodies : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Components")
	class USceneComponent* SceneComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Components")
	class UStaticMeshComponent* Sphere;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Components")
	class USphereComponent* Sphere1;
	// Sets default values for this actor's properties
	AGoodies();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:
	void OnOverlapSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
