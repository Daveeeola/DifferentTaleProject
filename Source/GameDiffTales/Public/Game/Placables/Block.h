// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

UCLASS()
class GAMEDIFFTALES_API ABlock : public AActor
{
	GENERATED_BODY()
	public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class UStaticMeshComponent* BlockMesh;

	UPROPERTY(VisibleAnywhere,  Category="Components")
	class USceneComponent* DefaultSceneRoot;
	
	
public:	
	// Sets default values for this actor's properties
	ABlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

};
