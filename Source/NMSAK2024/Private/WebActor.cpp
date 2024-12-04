// Fill out your copyright notice in the Description page of Project Settings.


#include "WebActor.h"
#include "WebSocketsModule.h"
#include "JsonUtilities.h"

// Sets default values
AWebActor::AWebActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWebActor::BeginPlay()
{
	Super::BeginPlay();

	if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		FModuleManager::Get().LoadModule("WebSockets");
	}

	cmd.x = 0;
	cmd.y = 0;
	cmd.z = 0;


	this->websocket = FWebSocketsModule::Get().CreateWebSocket("ws://127.0.0.1:8000");
	
	this->websocket->OnConnected().AddLambda([]()
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Connected.");
		});

	/* Connection error */
	this->websocket->OnConnectionError().AddLambda([](const FString& Error)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Error);
		}
	);

	/* Disconnected */
	this->websocket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, bWasClean ? FColor::Green : FColor::Red, "Connection closed " + Reason);
		}
	);

	/* On message */
	this->websocket->OnMessage().AddLambda([this](const FString& Msg)
		{
			this->ParseMsg(Msg);
		}
	);

	this->websocket->Connect();

}

// Called every frame
void AWebActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWebActor::ParseMsg(const FString& msg)
{
	FJsonObjectConverter::JsonObjectStringToUStruct(msg, &cmd);
}

