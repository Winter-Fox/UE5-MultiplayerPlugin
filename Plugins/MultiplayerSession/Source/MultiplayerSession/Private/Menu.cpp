// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"

#include "Components/Button.h"
#include "MultiplayerSessionsSubsystem.h"

void UMenu::MenuSetup(int32 NumverOfPublicconnections, FString TypeOfMatch)
{
	NumPublicConnections = NumverOfPublicconnections;
	MatchType = TypeOfMatch;

	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	SetIsFocusable(true);

	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (IsValid(PlayerController))
	{
		FInputModeUIOnly InputModedata;
		InputModedata.SetWidgetToFocus(TakeWidget());
		InputModedata.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(InputModedata);
		PlayerController->SetShowMouseCursor(true);
	}

	UGameInstance* GameInstance = GetGameInstance();
	if (IsValid(GameInstance))
	{
		MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubsystem>();
	}
}

bool UMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
	}
	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);
	}

	return true;
}

void UMenu::NativeDestruct()
{
	MenuTearDown();

	Super::NativeDestruct();
}

void UMenu::HostButtonClicked()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.0f,
			FColor::Yellow,
			TEXT("Host button clicked"));

	if (IsValid(MultiplayerSessionsSubsystem))
	{
		// TODO: remove hardcode
		MultiplayerSessionsSubsystem->CreateSession(NumPublicConnections, MatchType);
	}
}

void UMenu::JoinButtonClicked()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(
			-1,
			15.0f,
			FColor::Yellow,
			TEXT("Join button clicked"));

}

void UMenu::MenuTearDown()
{
	RemoveFromParent();

	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (IsValid(PlayerController))
	{
		FInputModeGameOnly InputModedata;
		PlayerController->SetInputMode(InputModedata);
		PlayerController->SetShowMouseCursor(false);
	}
}
