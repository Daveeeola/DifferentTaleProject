// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Goodies.h"

#include "Components/SphereComponent.h"
#include "Game/MainCharacter.h"

// Sets default values
AGoodies::AGoodies()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

	Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere1"));
	Sphere1->SetupAttachment(GetRootComponent());

	Sphere1->OnComponentBeginOverlap.AddDynamic(this,&AGoodies::OnOverlapSphere);

}

// Called when the game starts or when spawned
void AGoodies::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGoodies::OnOverlapSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AMainCharacter* MyChar = Cast<AMainCharacter>(OtherActor))
	{
		if(MyChar->GetClass()->ImplementsInterface(UCharInterface::StaticClass()))
		{
			ICharInterface::Execute_IncreaseTraceDistance(MyChar);
		}

		GetWorld()->DestroyActor(this);
	}
}


