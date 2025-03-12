// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextRenderComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponet"));
	
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComponent->SetCollisionProfileName("BlockAllDynamic");
	RootComponent = BoxComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetupAttachment(RootComponent);

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->SetupAttachment(RootComponent);
	RadialForceComponent->Radius = 250;
	RadialForceComponent->ImpulseStrength = 5300;
	RadialForceComponent->bImpulseVelChange = true;
	RadialForceComponent->bAutoActivate = false;
	RadialForceComponent->bIgnoreOwningActor = true;

	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextComponent"));
	TextComponent->SetupAttachment(RootComponent);
	TextComponent->SetRelativeLocation(FVector(0.0f, -10.0f, 40.0f));
	TextComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 180.0f));
	
	FuseTime = 3;

	SetReplicates(true);

}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();

	TextComponent->SetText(FText::AsNumber(FuseTime));

	MC_SetColor(FLinearColor::Green);
	
}

void ABomb::MC_SetColor_Implementation(FLinearColor Color)
{
	if (MeshComponent)
	{
		UMaterialInstanceDynamic* MatInst = MeshComponent->CreateAndSetMaterialInstanceDynamic(0);
		if (MatInst)
		{
			MatInst->SetVectorParameterValue("Color", Color);
		}
	}
	
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABomb::Use_Implementation()
//void ABomb::Use_Implementation(APlayerController* PC)
{
	if (HasAuthority())
	{
		MC_SetColor(FLinearColor::Red);

		UWorld* World = GetWorld();
		/*if (PC)
		{
			SetInstigator(PC->GetPawn());
		}*/
		
		if (World != nullptr)
		{
			World->GetTimerManager().SetTimer(TimerHandle_Fuse, this, &ABomb::CountDown, 1.0f, true);
		}
		
		
	}
}

void ABomb::PlayExplodeParticleEffect()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleFX1, GetActorLocation());
}

void ABomb::CountDown()
{
	MC_CountDown();
}

void ABomb::MC_CountDown_Implementation()
{
	FuseTime -= 1;
	TextComponent->SetText(FText::AsNumber(FuseTime));

	if (FuseTime == 0)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Fuse);
		OnExplode();
	}
}

void ABomb::OnExplode()
{
	PlayExplodeParticleEffect();
	RadialForceComponent->FireImpulse();
	UGameplayStatics::ApplyRadialDamage(this, 100, GetActorLocation(), 250, UDamageType::StaticClass(), TArray<AActor*>(), this, GetInstigatorController());

	Destroy();
}

