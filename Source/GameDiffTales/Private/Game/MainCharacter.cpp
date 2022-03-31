// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MainCharacter.h"

#include "Components/BoxComponent.h"
#include "BlockoutToolsPlugin/Private/BlockoutToolsParent.h"
#include "Components/CapsuleComponent.h"
#include "Game/GameModeClass.h"
#include "Kismet/KismetMathLibrary.h"
#include "Game/EnemyAI/Enemy.h"
#include "Game/Placables/Bomb.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(GetRootComponent());
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(CollisionBox);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnCapsuleOverlap);

	TraceDistance = 200;
	
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(BlockoutBox)
	{
		UE_LOG(LogTemp, Warning, TEXT("BlockoutBox is Set"));
		
	}
	
	
}


// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainCharacter::MoveRight);
	
	PlayerInputComponent->BindAction(TEXT("DropBomb"), IE_Pressed, this, &AMainCharacter::DropBomb);

}

void AMainCharacter::InitializeVariables()
{
	NumberOfTileX = LevelWidthX/GridSize;
	NumberTileY = LevelWidthY/GridSize;
}

void AMainCharacter::MoveForward(float Value)
{
	
	if(Value != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f"), Value);

		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0,Rotation.Yaw,0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		this->AddMovementInput(Direction, Value);
	}
	
}

void AMainCharacter::MoveRight(float Value)
{
	
	if(Value != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f"), Value);
		
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0,Rotation.Yaw,0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		this->AddMovementInput(Direction, Value);
	}
	
}

void AMainCharacter::DropBomb()
{
	if(BombClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawned Bomb"));
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ABomb* SpawnedBomb = GetWorld()->SpawnActor<ABomb>(BombClass, GetBombSpawnLocation(),FRotator::ZeroRotator,SpawnParams);
		GetCapsuleComponent()->IgnoreActorWhenMoving(SpawnedBomb, true);
		SpawnedBomb->SetTraceDistance(TraceDistance);

		//Explode the bomb using Interface
		if(SpawnedBomb->GetClass()->ImplementsInterface(UBombInterface::StaticClass()))
		{
			IBombInterface::Execute_Explode(SpawnedBomb);
		}
	}
	
}

FVector AMainCharacter::GetBombSpawnLocation()
{
	if(BlockoutBox)
	{
		FVector BlockoutBoxLocaton = BlockoutBox->GetActorLocation();

		FVector Calc_Vector = GetActorLocation() - BlockoutBoxLocaton;
		Calc_Vector.Z = 0;

		Calc_Vector.X = Calc_Vector.X/GridSize;
		Calc_Vector.Y = Calc_Vector.Y/GridSize;
		
		float TruncVarX = ((FMath::TruncToInt(Calc_Vector.X)) + 0.5) * GridSize;
		float TruncVarY = ((FMath::TruncToInt(Calc_Vector.Y)) + 0.5) * GridSize;

		FVector Combine_Vec = FVector(TruncVarX,TruncVarY,GetActorLocation().Z);
	
		FVector SpawnLocation = BlockoutBoxLocaton + Combine_Vec;

		return SpawnLocation;
	}
	return (GetActorLocation());
}

void AMainCharacter::OnCapsuleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AEnemy* OverlappedEnemy = Cast<AEnemy>(OtherActor))
	{
		if (UGameplayStatics::GetGameMode(GetWorld())->GetClass()->ImplementsInterface(UGameModeInterface::StaticClass()))
		{
			IGameModeInterface::Execute_ReduceLive(UGameplayStatics::GetGameMode(GetWorld()));
			StaticMesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1.f,0.4f,0.f));
			GetWorldTimerManager().SetTimer(ColorChangeHandle, this,&AMainCharacter::ReturnColorToNormal , 0.4,false);
		}
	}
}

void AMainCharacter::ReturnColorToNormal()
{
	GetWorldTimerManager().ClearTimer(ColorChangeHandle);
	StaticMesh->SetVectorParameterValueOnMaterials(TEXT("Color"), FVector(1.f,1.f,1.f));
}


void AMainCharacter::OnBombHit_Implementation()
{
	if (UGameplayStatics::GetGameMode(GetWorld())->GetClass()->ImplementsInterface(UGameModeInterface::StaticClass()))
	{
		IGameModeInterface::Execute_ReduceLive(UGameplayStatics::GetGameMode(GetWorld()));
	}
}

void AMainCharacter::IncreaseTraceDistance_Implementation()
{
	TraceDistance = TraceDistance + 200;
}

void AMainCharacter::GetCurrentDirection_Implementation(EEDirectionToGo& OutCurrentDirection)
{
	
}

void AMainCharacter::GetAiMiddleLocation_Implementation(EEDirectionToGo InDirection, FVector& OutMiddleLocation, EEDirectionToGo& DirectionToGo)
{
	
}

