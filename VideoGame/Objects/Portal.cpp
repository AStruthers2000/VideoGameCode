#include "Portal.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = false;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Temporary Portal Mesh"));
	//mesh->SetCollisionProfileName()
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	
}

void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortal::Interact_Implementation()
{
	//UE_LOG(LogTemp, Display, TEXT("I am a portal that is being interacted with"));
	if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, TEXT("I am a portal that is being interacted with!"));
}

