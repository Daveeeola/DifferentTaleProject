// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Placables/Block_Destructible.h"
#include "Game/Goodies.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ABlock_Destructible::ABlock_Destructible()
{
	bHasGoodies = false;
	bIsExitBlock = false;
	Color = FLinearColor(FVector(0.f,0.f,0.f));

}


void ABlock_Destructible::BeginPlay()
{
	Super::BeginPlay();
}



void ABlock_Destructible::Destroy_Implementation()
{
	if(ParticleSystem && Goodies)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ParticleSystem,GetActorLocation(),FRotator::ZeroRotator,FVector(1.f),true);
		if(bHasGoodies)
		{
			//Spawn Goodies Actor
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			GetWorld()->SpawnActor<AGoodies>(Goodies,GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
		}
			GetWorld()->DestroyActor(this);
	}

	
}

void ABlock_Destructible::HitAfterEnemyBombed_Implementation()
{
	BlockMesh->SetVectorParameterValueOnMaterials(TEXT("Color"),UKismetMathLibrary::Conv_LinearColorToVector(Color));
	bHasGoodies = true;

	
}
