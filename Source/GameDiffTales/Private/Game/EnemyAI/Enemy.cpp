// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EnemyAI/Enemy.h"

#include "DrawDebugHelpers.h"
#include "Game/DestructInterface.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());


	TraceDistance = 200.f;
}

void AEnemy::InitializeVariables()
{
	NumberOfTileX = LevelWidthX/GridSize;
	NumberTileY = LevelWidthY/GridSize;
}

void AEnemy::CheckForBlockage_Implementation()
{
	
}


void AEnemy::GetRandomSuitableDirection_Implementation()
{
	
}

void AEnemy::GetObstaclesInAllDirection(float YawAngle, EEDirectionToGo Direction)
{
	FVector StartLoc = GetActorLocation();
	FVector EndLoc;

	FRotator ActorRotation = GetActorRotation();
	FRotator CombineRot = UKismetMathLibrary::ComposeRotators(ActorRotation, FRotator(0.f,YawAngle,0.f));
	

	FVector Directiona = FRotationMatrix(CombineRot).GetUnitAxis(EAxis::X);
	Directiona = Directiona * TraceDistance;

	EndLoc = StartLoc + Directiona;

	DrawDebugLine(GetWorld(),StartLoc,EndLoc,FColor::Green,false,5,2);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc,EndLoc,ECollisionChannel::ECC_Visibility,QueryParams))
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor Name: %s"),*(HitResult.Actor->GetName()) );
		if(HitResult.bBlockingHit)
		{
			HitDirections.AddUnique(Direction);
	
		}
	}
}

void AEnemy::GetBoxesInAllFourDirections(float YawAngle)
{
	FVector StartLoc = GetActorLocation();
	FVector EndLoc;

	FRotator ActorRotation = GetActorRotation();
	FRotator CombineRot = UKismetMathLibrary::ComposeRotators(ActorRotation, FRotator(0.f,YawAngle,0.f));
	

	FVector Directiona = FRotationMatrix(CombineRot).GetUnitAxis(EAxis::X);
	Directiona = Directiona * TraceDistance;

	EndLoc = StartLoc + Directiona;

	DrawDebugLine(GetWorld(),StartLoc,EndLoc,FColor::Green,false,5,2);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc,EndLoc,ECollisionChannel::ECC_Visibility,QueryParams))
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor Name: %s"),*(HitResult.Actor->GetName()) );
		if (HitResult.GetActor()->GetClass()->ImplementsInterface(UDestructInterface::StaticClass()))
		{
			IDestructInterface::Execute_HitAfterEnemyBombed(HitResult.GetActor());
		}
	}
	

	
}


void AEnemy::LocationAtTraceAlongDirection(EEDirectionToGo Direction, float TraceLength, FVector& HitLocation, bool &bHit)
{
	FVector StartLoc = GetActorLocation();
	FVector EndLoc;

	FRotator ActorRotation = GetActorRotation();

	float YawAngle = 0.f;

	if(Direction == EEDirectionToGo::EET_Up)
	{
		YawAngle = 0.0f;
	}

	else if (Direction == EEDirectionToGo::EET_Down)
	{
		YawAngle = 180.f;
	}

	else if (Direction == EEDirectionToGo::EET_Left)
	{
		YawAngle = 270.f;
	}

	else if (Direction == EEDirectionToGo::EET_Right)
	{
		YawAngle = 90.f;
	}

	UE_LOG(LogTemp, Warning, TEXT("Value: %f"), YawAngle);
	
	FRotator CombineRot = UKismetMathLibrary::ComposeRotators(ActorRotation, FRotator(0.f,YawAngle,0.f));
	

	FVector Directiona = FRotationMatrix(CombineRot).GetUnitAxis(EAxis::X);
	Directiona = Directiona * TraceLength;

	EndLoc = StartLoc + Directiona;

	DrawDebugLine(GetWorld(),StartLoc,EndLoc,FColor::Green,false,5,2);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc,EndLoc,ECollisionChannel::ECC_Visibility,QueryParams))
	{
		if(HitResult.bBlockingHit)
		{
			HitLocation = HitResult.Location;
			bHit = true;
		}
	}

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnBombHit_Implementation()
{
	
}

void AEnemy::GetCurrentDirection_Implementation(EEDirectionToGo& OutCurrentDirection)
{
	
}

void AEnemy::GetAiMiddleLocation_Implementation(EEDirectionToGo InDirection, FVector& OutMiddleLocation, EEDirectionToGo& OutDirectionToGo)
{
	
}

void AEnemy::GetLocationAtTraceAtFreeDirection_Implementation(EEDirectionToGo Direction, FVector& Location, bool& bHit)
{
	
}

