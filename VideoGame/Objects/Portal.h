// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VideoGame/Interfaces/InteractableActor.h"
#include "Portal.generated.h"

class UWidgetComponent;

UCLASS()
class VIDEOGAME_API APortal : public AActor, public IInteractableActor
{
	GENERATED_BODY()
	
public:	
	APortal();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Geometry", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:	
	//InteractableActor interface
	virtual void Interact_Implementation() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Portal Functionality", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UWorld> LevelToLoad;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Portal Functionality", meta = (AllowPrivateAccess = "true"))
	float LevelLoadingTime;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "Portal Functionality", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* TimerWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Portal Functionality", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> TimerWidgetClass;
	

	FTimerHandle PortalLoadLevelTimerHandle;
	void OnTimerComplete_LoadLevel();
};

