// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"
class USphereComponent;
UCLASS()
class BALLMAZE_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* PickupFX;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayEffects();

public:	
	
	void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	
};
