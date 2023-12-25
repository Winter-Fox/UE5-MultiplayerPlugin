// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "MultiplayerSessionsSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMultiplayerOnCreateSessionComplete, bool, bWasSucceful);

DEFINE_LOG_CATEGORY_STATIC(LogMultiplayerSessionsSubsystem, Log, All);

class FOnlineSessionSettings;

/**
 * Game subsystem to operate sessions functionality
 */
UCLASS()
class MULTIPLAYERSESSION_API UMultiplayerSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UMultiplayerSessionsSubsystem();

	//
	// To handle session functionality. Menu will call these
	//
	void CreateSession(int32 NumPublicConnections, FString MatchType);
	void FindSessions(int32 MaxSearchResults);
	void JoinSession(const FOnlineSessionSearchResult& SearchResult);
	void DestroySession();
	void StartSession();

	//
	// Delegates for the menu class to bind to
	//
	FMultiplayerOnCreateSessionComplete MultiplayerOnCreateSessionComplete;

protected:
	//
	//	Internal callbacks to the delegates we'll add to the Online Session interface delegate list
	// These don't have to be called outside of this class
	//
	void OnCreateSessionComplete(FName SessionName, bool bWassucceful);
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	void OnDestroySessionComplete(FName SessionName, bool bWassucceful);
	void OnStartSessionComplete(FName SessionName, bool bWassucceful);

private:
	IOnlineSessionPtr OnlineSessionInterface;
	TSharedPtr<FOnlineSessionSettings> LastSessionSettings;

	//
	// To add to the Online Session delegate list
	// We''l bind our internal callbacks to these
	//
	FOnCreateSessionCompleteDelegate  OnCreateSessionCompleteDelegate;
	FOnFindSessionsCompleteDelegate   OnFindSessionsCompleteDelegate;
	FOnJoinSessionCompleteDelegate    OnJoinSessionCompleteDelegate;
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;
	FOnStartSessionCompleteDelegate   OnStartSessionCompleteDelegate;

	FDelegateHandle CreateSessionCompleteHandle;
	FDelegateHandle FindSessionCompleteHandle;
	FDelegateHandle JoinSessionCompleteHandle;
	FDelegateHandle DestroySessionCompleteHandle;
	FDelegateHandle StartSessionCompleteHandle;
};
