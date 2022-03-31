// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Placables/Bomb.h"

#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"
#include "Game/CharInterface.h"
#include "Game/DestructInterface.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BombMesh"));
	Sphere->SetWorldScale3D(FVector(2.5,2.5,2.5));
	Sphere->SetCollisionProfileName(FName("OverlapAll"));
	BombMesh->SetupAttachment(Sphere);
	BombMesh->SetWorldScale3D(FVector(0.6,0.6,0.6));
	BombMesh->SetCollisionProfileName(FName("BlockAll"));

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABomb::OnSphereOverlap);

}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();

	ActorScale = BombMesh->GetComponentScale();
	
}

void ABomb::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ABomb::DetectDestructibleBlocksInAllDirection(float YawAngle, float Distance)
{
	FVector StartLoc = GetActorLocation();
	FVector EndLoc;

	FRotator ActorRotation = GetActorRotation();
	FRotator CombineRot = UKismetMathLibrary::ComposeRotators(ActorRotation, FRotator(0.f,YawAngle,0.f));
	

	FVector Direction = FRotationMatrix(CombineRot).GetUnitAxis(EAxis::X);
	Direction = Direction * Distance;

	EndLoc = StartLoc + Direction;

	DrawDebugLine(GetWorld(),StartLoc,EndLoc,FColor::Green,false,5,2);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc,EndLoc,ECollisionChannel::ECC_Visibility,QueryParams))
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor Name: %s"),*(HitResult.Actor->GetName()) );
		if(HitResult.bBlockingHit)
		{
			if (HitResult.GetActor()->GetClass()->ImplementsInterface(UCharInterface::StaticClass()))
			{
				ICharInterface::Execute_OnBombHit(HitResult.GetActor());
			}
			
			if (HitResult.GetActor()->GetClass()->ImplementsInterface(UDestructInterface::StaticClass()))
			{
				IDestructInterface::Execute_Destroy(HitResult.GetActor());
			}

			
		}
		

		bBlockHit = true;
	}
}


