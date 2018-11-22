// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
	Mesh1PComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball1"));
	Mesh1PComponent->GetStaticMesh();
	Mesh1PComponent->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	Mesh1PComponent->SetSimulatePhysics(true);
	Mesh1PComponent->SetLinearDamping(0.1f);
	Mesh1PComponent->SetAngularDamping(0.1f);
	Mesh1PComponent->BodyInstance.MassScale = 3.5f;
	Mesh1PComponent->BodyInstance.MaxAngularVelocity = 500.0f;
	Mesh1PComponent->SetNotifyRigidBodyCollision(true);
	RootComponent = Mesh1PComponent;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bAbsoluteRotation = true; // Rotation of the ball should not affect rotation of boom
	SpringArm->RelativeRotation = FRotator(-45.f, 0.f, 0.f);
	SpringArm->TargetArmLength = 1200.f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 3.f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	CameraComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	RollTorque = 50000000.0f;

}

void AMyPawn::MoveForward(float Val)
{
	const FVector Torque = FVector(-1.f * Val * RollTorque, 0.f, 0.f);
	Mesh1PComponent->AddTorqueInRadians(Torque);
}

void AMyPawn::MoveRight(float Val)
{
	const FVector Torque = FVector(0.f, Val * RollTorque, 0.f);
	Mesh1PComponent->AddTorqueInRadians(Torque);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPawn::MoveRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPawn::MoveForward);
}

