// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "IWebSocket.h"

#include "WebActor.generated.h"

USTRUCT(BlueprintType)
struct FCmdInterface
{
GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NMSAK2024")
	TArray<float> joint_targets;
};


UCLASS()
class NMSAK2024_API AWebActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWebActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ParseMsg(const FString& msg);

protected:

	TSharedPtr<IWebSocket> websocket;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCmdInterface cmd;

};
