// Fill out your copyright notice in the Description page of Project Setti.

#include "BallCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
ABallCharacter::ABallCharacter()
{
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> BallMesh(TEXT("/Game/Starter Content/Blueprints"));
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	Mesh1PComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball1"));
	Mesh1PComponent->GetStaticMesh();
	Mesh1PComponent->BodyInstance.SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	Mesh1PComponent->SetSimulatePhysics(true);
	Mesh1PComponent->SetLinearDamping(0.1f);
	Mesh1PComponent->SetAngularDamping(0.1f);
	Mesh1PComponent->BodyInstance.MassScale = 5.0f;
	Mesh1PComponent->BodyInstance.MaxAngularVelocity = 5000.0f;
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

	RollTorque = 5000000.0f;

}

// Called when the game starts or when spawned
void ABallCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABallCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABallCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABallCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABallCharacter::MoveRight);

}

void ABallCharacter::MoveForward(float Val)
{
	const FVector Torque = FVector(-1.f * Val * RollTorque, 0.f, 0.f);
	Mesh1PComponent->AddTorqueInRadians(Torque);
}

void ABallCharacter::MoveRight(float Val)
{
	const FVector Torque = FVector(0.f, Val * RollTorque, 0.f);
	Mesh1PComponent->AddTorqueInRadians(Torque);
}
