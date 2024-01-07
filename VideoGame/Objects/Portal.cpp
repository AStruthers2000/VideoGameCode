#include "Portal.h"

#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "VideoGame/UI/InteractionWidgetParent.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Temporary Portal Mesh"));
	TimerWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Portal Clock Timer Widget"));
	TimerWidget->SetupAttachment(Mesh);
	TimerWidget->SetWidgetSpace(EWidgetSpace::Screen);
	
	
	//mesh->SetCollisionProfileName()
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

	check(TimerWidgetClass != nullptr);
	
	TimerWidget->SetWidgetClass(TimerWidgetClass);
	TimerWidget->SetVisibility(false);

	if(LevelToLoad.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("%s doesn't have a valid level to load"), *GetActorNameOrLabel());
	}
}

void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PortalLoadLevelTimerHandle.IsValid())
	{
		const float TimeRemaining = GetWorld()->GetTimerManager().GetTimerRemaining(PortalLoadLevelTimerHandle);

		const auto WidgetObject = TimerWidget->GetUserWidgetObject();
		const auto PortalTimer = Cast<UInteractionWidgetParent>(WidgetObject);
		if(PortalTimer != nullptr)
		{
			PortalTimer->UpdateTimerText(TimeRemaining);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Portal timer is null"));
		}
	}
}

void APortal::Interact_Implementation()
{
	if(LevelToLoad.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("Player tried interacting with portal %s, which has no valid level to load"), *GetActorNameOrLabel());
		return;
	}
	
	if(!PortalLoadLevelTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(
			PortalLoadLevelTimerHandle,
			this,
			&APortal::OnTimerComplete_LoadLevel,
			FMath::Max(LevelLoadingTime, 0.001f),
			false);

		TimerWidget->SetVisibility(true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("This portal is already activated"));
	}
}

void APortal::OnTimerComplete_LoadLevel()
{
	PortalLoadLevelTimerHandle.Invalidate();
	
	const UObject* WorldContextObject = this;
	UGameplayStatics::OpenLevelBySoftObjectPtr(WorldContextObject, LevelToLoad, true);
}

