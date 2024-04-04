// Copyright Aurora Laboratories

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VideoGame/Interfaces/DialogueInterface.h"
#include "VideoGame/Interfaces/InteractableActor.h"
#include "NPC.generated.h"

UCLASS()

class VIDEOGAME_API ANPC : public ACharacter, public IDialogueInterface, public IInteractableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//void Talk_Implementation() override;
	//virtual void Talk_Implementation() override;
	virtual void Interact_Implementation() override;
	virtual void Talk_Implementation() override;

};
