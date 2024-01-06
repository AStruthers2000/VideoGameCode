// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

UENUM()
enum ERaycastState
{
	FirstFrameOfSeeingInteractable,
	CurrentlyLookingAtInteractable,
	FirstFrameOfLookingAwayFromInteractable,
	NotLookingAtInteractable
};

constexpr ECollisionChannel InteractionTraceChannel = ECC_GameTraceChannel1;

UCLASS(Config=PlayerConfig)
class VIDEOGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/***** Input *****/
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartJump(const FInputActionValue& Value);
	void EndJump(const FInputActionValue& Value);
	void TryInteract(const FInputActionValue& Value);

	UFUNCTION(BlueprintImplementableEvent)
	void PrototypeInteract();

public:
	FORCEINLINE USpringArmComponent* GetPlayerSpringArm() const { return SpringArm; }
	FORCEINLINE UCameraComponent* GetPlayerCamera() const { return Camera; }

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float InteractDistance = 500.f;

	bool InteractTrace(FHitResult& OutHit) const;
	AActor* TryLookingAtInteractActor();
	void HandleCurrentLook(AActor* HitActor);

	bool IsLookingAtInteractable = false;

	UPROPERTY()
	AActor* InteractableInLookRange;

	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Variables", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<ERaycastState> LookState = NotLookingAtInteractable;
};
