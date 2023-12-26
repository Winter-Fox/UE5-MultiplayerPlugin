// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h" 

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GameState)
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(
				1,
				60.0f,
				FColor::Green,
				FString::Printf(TEXT("Number of players: %d"),
					NumberOfPlayers));

		APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>();
		if (GEngine && IsValid(PlayerState))
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.0f,
				FColor::Blue,
				FString::Printf(TEXT("%s has joined the game"),
					*PlayerState->GetPlayerName()));
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	if (GameState)
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(
				1,
				60.0f,
				FColor::Green,
				FString::Printf(TEXT("Number of players: %d"),
					NumberOfPlayers-1));

		APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>();
		if (GEngine && IsValid(PlayerState))
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.0f,
				FColor::Blue,
				FString::Printf(TEXT("%s has left the game"),
					*PlayerState->GetPlayerName()));
	}
}
