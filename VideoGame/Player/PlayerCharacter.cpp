#include "PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "VideoGame/Interfaces/InteractableActor.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	/** setting default character values. all of these can be adjusted in the character blueprint later **/
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()-> MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	//creating and configuring a spring arm component that follows behind the player
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bUsePawnControlRotation = true;

	//creating a camera attached to the spring arm
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Person Follow Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); //attaches camera to the end of the spring arm
	Camera->bUsePawnControlRotation = false;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add default input mapping context to enhanced input subsystem
	if(const APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

/***** Input *****/
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerCharacter::EndJump);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::TryInteract);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if(Controller == nullptr) return;
	
	const FVector2D MovementVector = Value.Get<FVector2D>();

	//we only care about the yaw of the rotation, since we will only want to rotate "left" and "right"
	const FRotator Rotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	FVector ForwardVector, RightVector, UpVector;
	FRotationMatrix(Rotation).GetUnitAxes(ForwardVector, RightVector, UpVector);

	AddMovementInput(ForwardVector, MovementVector.Y);
	AddMovementInput(RightVector, MovementVector.X);
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	if(Controller == nullptr) return;

	const FVector2D LookVector = Value.Get<FVector2D>();
	
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void APlayerCharacter::StartJump(const FInputActionValue& Value)
{
	Jump();
}

void APlayerCharacter::EndJump(const FInputActionValue& Value)
{
	StopJumping();
}

void APlayerCharacter::TryInteract(const FInputActionValue& Value)
{
	if(IsLookingAtInteractable && InteractableInLookRange)
	{
		IInteractableActor::Execute_Interact(InteractableInLookRange);
	}
}

bool APlayerCharacter::InteractTrace(FHitResult& OutHit, bool UseCameraForward = false) const
{
	const FVector Start = GetActorLocation();
	FVector TraceForward;
	if(UseCameraForward)
	{
		TraceForward = FVector(Camera->GetForwardVector().X, Camera->GetForwardVector().Y, 0.f);
	}
	else
	{
		TraceForward = FVector(GetActorForwardVector().X, GetActorForwardVector().Y, 0.f);
	}
	const float CapsuleRadius = GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector End = Start + TraceForward * InteractDistance;
	
	static const FName TraceName(TEXT("Interaction Trace"));
	FCollisionQueryParams Params(TraceName);
	Params.bReturnPhysicalMaterial = false;
	Params.bReturnFaceIndex = false;
	Params.AddIgnoredActor(this);
	Params.bTraceComplex = false;

	const UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
	check(World != nullptr);
	
	const bool bHit = World->SweepSingleByChannel(OutHit, Start, End, FQuat::Identity, InteractionTraceChannel, FCollisionShape::MakeSphere(CapsuleRadius), Params);
	return bHit;
}

AActor* APlayerCharacter::TryLookingAtInteractActor()
{
	AActor* HitActor = nullptr;
	FHitResult CameraHit, PlayerHit; 
	if(InteractTrace(CameraHit, true) || InteractTrace(PlayerHit, false))
	{
		FHitResult Hit = CameraHit.bBlockingHit ? CameraHit : PlayerHit;
		HitActor = Hit.GetActor();
		if((IsLookingAtInteractable = HitActor->Implements<UInteractableActor>()) == true)
		{
			if(LookState != CurrentlyLookingAtInteractable)
			{
				LookState = FirstFrameOfSeeingInteractable;
			}
		}
	}
	else
	{
		if(LookState != NotLookingAtInteractable)
		{
			LookState = FirstFrameOfLookingAwayFromInteractable;
		}
	}

	return HitActor;
}

void APlayerCharacter::HandleCurrentLook(AActor* HitActor)
{
	switch (LookState) {
	case FirstFrameOfSeeingInteractable:
		InteractableInLookRange = HitActor;
		IInteractableActor::Execute_SetVisibility_InteractUI(InteractableInLookRange, true);
		LookState = CurrentlyLookingAtInteractable;
		break;
		
	case CurrentlyLookingAtInteractable:
		break;
		
	case FirstFrameOfLookingAwayFromInteractable:
		IInteractableActor::Execute_SetVisibility_InteractUI(InteractableInLookRange, false);
		IsLookingAtInteractable = false;
		InteractableInLookRange = nullptr;
		LookState = NotLookingAtInteractable;
		break;
		
	case NotLookingAtInteractable:
		break;
	default: break;
	}
}

/***** No more input *****/

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	HandleCurrentLook(TryLookingAtInteractActor());
}

