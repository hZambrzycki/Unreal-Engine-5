// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/G_AnimInstance.h"
#include "Characters/GreystoneCharacter.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UG_AnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	GreystoneCharacter = Cast<AGreystoneCharacter>(TryGetPawnOwner());
	if (GreystoneCharacter)
	{
		GreystoneCharacterMovement = GreystoneCharacter->GetCharacterMovement();
	}
}

void UG_AnimInstance::NativeUpdateAnimation(float Deltatime)
{
	Super::NativeUpdateAnimation(Deltatime);

	if (GreystoneCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(GreystoneCharacterMovement->Velocity);
		IsFalling = GreystoneCharacterMovement->IsFalling();
		CharacterState = GreystoneCharacter->GetCharacterState();
		ActionState = GreystoneCharacter->GetActionState();
		DeathPose = GreystoneCharacter->GetDeathPose();
	}
}
