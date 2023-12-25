// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu.h"

#include "Components/Button.h"
#include "MultiplayerSessionsSubsystem.h"

void UMenu::MenuSetup()
{
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

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
		MultiplayerSessionsSubsystem->CreateSession(4, FString("FreeForAll"));
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
