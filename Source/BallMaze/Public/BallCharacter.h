// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BallCharacter.generated.h"
class UCameraComponent;

UCLASS()
class BALLMAZE_API ABallCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		UStaticMeshComponent* Mesh1PComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpringArm")
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		UCameraComponent* CameraComponent;

public:
	// Sets default values for this character's properties
	ABallCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles strafing movement, left and right */
	void MoveRight(float Val);


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Ball)
		float RollTorque;

public:
	/** Returns Mesh1P subobject **/
	UStaticMeshComponent* GetMesh1P() const { return Mesh1PComponent; }

	USpringArmComponent* GetSpringArm() const { return SpringArm; }

	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetThirdPersonCameraComponent() const { return CameraComponent; }

};
