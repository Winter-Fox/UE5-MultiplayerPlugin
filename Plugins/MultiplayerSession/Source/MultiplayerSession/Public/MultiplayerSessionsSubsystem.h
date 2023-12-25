// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MultiplayerSessionsSubsystem.generated.h"

/**
 * Game subsystem to operate sessions functionality
 */
UCLASS()
class MULTIPLAYERSESSION_API UMultiplayerSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UMultiplayerSessionsSubsystem();
protected:

private:
	IOnlineSessionPtr OnlineSessionInterface;
};
