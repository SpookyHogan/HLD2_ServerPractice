// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/SkeletalMeshComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DoorMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	RootComponent = DoorMesh;

	bReplicates = true;

	bDoorOpen = false;
}

void ADoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ADoor, bDoorOpen);
}


void ADoor::Multicast_DoorToggled_Implementation()
{
	if (bDoorOpen)
	{
		if (CloseAnimation)
		{
			DoorMesh->PlayAnimation(CloseAnimation, false);
		}
	}
	else
	{
		if (OpenAnimation)
		{
			DoorMesh->PlayAnimation(OpenAnimation, false);
		}
	}
	bDoorOpen = !bDoorOpen;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

//void ADoor::Use_Implementation(APlayerController* PC)
void ADoor::Use_Implementation()
{
	if (HasAuthority())
	{
		Multicast_DoorToggled();
	}
}