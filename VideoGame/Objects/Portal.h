// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VideoGame/Interfaces/InteractableActor.h"
#include "Portal.generated.h"

UCLASS()
class VIDEOGAME_API APortal : public AActor, public IInteractableActor
{
	GENERATED_BODY()
	
public:	
	APortal();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Geometry", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mesh;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:	
	//InteractableActor interface
	virtual void Interact_Implementation() override;
};

