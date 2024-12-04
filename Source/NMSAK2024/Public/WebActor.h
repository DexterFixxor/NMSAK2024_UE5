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
	float x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NMSAK2024")
	float y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NMSAK2024")
	float z;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NMSAK2024")
	float qx;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NMSAK2024")
	float qy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NMSAK2024")
	float qz;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NMSAK2024")
	float theta;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NMSAK2024")
	FCmdInterface cmd;

};
