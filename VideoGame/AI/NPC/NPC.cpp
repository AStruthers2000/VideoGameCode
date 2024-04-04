// Copyright Aurora Laboratories


#include "NPC.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::Interact_Implementation()
{
	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString(TEXT("interacting with npc")));
	if(Implements<UDialogueInterface>())
	{
		IDialogueInterface::Execute_Talk(this);
	}
}

void ANPC::Talk_Implementation()
{
	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString(TEXT("Yo from the NPC, nice conversation we are having")));
	IDialogueInterface::Talk_Implementation();
}



