// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterTypes.h"
#include "G_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class BH_01_API UG_AnimInstance : public UAnimInstance 
{
	GENERATED_BODY() 
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float Deltatime) override;


	UPROPERTY(BlueprintReadOnly)
	class AGreystoneCharacter* GreystoneCharacter;

	UPROPERTY(BlueprintReadOnly)
	class UCharacterMovementComponent* GreystoneCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsFalling;

    UPROPERTY(BlueprintReadOnly, Category = "Movement | Character State")
	ECharacterState CharacterState;
	UPROPERTY(BlueprintReadOnly, Category = "Action State")
	EActionState ActionState;
	UPROPERTY(BlueprintReadOnly, Category = Movement)
		TEnumAsByte<EDeathPose> DeathPose;
};
