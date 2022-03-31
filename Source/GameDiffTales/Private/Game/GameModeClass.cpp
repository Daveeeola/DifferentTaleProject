// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameModeClass.h"


AGameModeClass::AGameModeClass()
{
	Lives = 2;
	TimeMin = 4;
	TimeSec = 0;
}

void AGameModeClass::BeginPlay()
{
	GetWorldTimerManager().SetTimer(TimerTimeHandle,this, &AGameModeClass::TimeDownEvent, 1.0,true,0.0 );
}

void AGameModeClass::ReduceLife()
{
	Lives = (Lives - 1)> 0 ? (Lives - 1) : 0;

	if(Lives <= 0)
	{
		//Get Player Controller
		//Get HUD - Game Over
	}
}

void AGameModeClass::TimeDownEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Timer Countdown"));
	
	TimeSec = TimeSec-1;
	if(TimeSec < 0 && TimeMin > 0)
	{
		TimeMin = TimeMin -1;
		TimeSec = 59;
	}

	if (TimeMin <= 0 && TimeSec < 0)
	{
		GetWorldTimerManager().ClearTimer(TimerTimeHandle);
		TimeMin = 0;
		TimeSec = 0;
		
		GameOverEvent();
	}
}

void AGameModeClass::AddScore_Implementation(int Amount)
{
	PlayerScore+=Amount;
}

void AGameModeClass::ReduceLive_Implementation()
{
	Lives = (Lives -1) > 0 ? (Lives -1) : 0;

	if(Lives <= 0)
	{
		GameOverEvent();
	}
}

void AGameModeClass::LoadHighScore_Implementation()
{
	
}

void AGameModeClass::GameOverEvent_Implementation()
{
	
}
