// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/GreystoneCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Items/Item.h"
#include "Components/AttributeComponent.h"
#include "Items/Weapons/Weapon.h"
#include  "Items/Soul.h"
#include "Widget/SlashHUD.h"
#include "Widget/SlashOverlay.h"
#include "Animation/AnimMontage.h"

// Sets default values
AGreystoneCharacter::AGreystoneCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);

}

void AGreystoneCharacter::Tick(float DeltaTime)
{
	if (Attributes && SlashOverlay)
	{
	
	}
}

void AGreystoneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AGreystoneCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AGreystoneCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &AGreystoneCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &AGreystoneCharacter::LookUp);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &AGreystoneCharacter::Jump);
	PlayerInputComponent->BindAction(FName("Equip"), IE_Pressed, this, &AGreystoneCharacter::EKeyPressed);
	PlayerInputComponent->BindAction(FName("Attack"), IE_Pressed, this, &AGreystoneCharacter::Attack);
	PlayerInputComponent->BindAction(FName("Dodge"), IE_Pressed, this, &AGreystoneCharacter::Dodge);
}

void AGreystoneCharacter::Jump()
{
	if (IsUnoccupied())
	{
		Super::Jump();
	}

}

float AGreystoneCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	HandleDamage(DamageAmount);
	SetHUDHealth();
	return DamageAmount;
}

void AGreystoneCharacter::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	Super::GetHit_Implementation(ImpactPoint, Hitter);

	SetWeaponCollisionEnabled(ECollisionEnabled::NoCollision);
	if (Attributes && Attributes->GetHealthPercent() > 0.f)
	{
		ActionState = EActionState::EAS_HitReaction;
	}
}

void AGreystoneCharacter::SetOverlappingItem(AItem* Item)
{
	OverlappingItem = Item;
}


void AGreystoneCharacter::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("EngageableTarget"));
	InitializeSlashOverlay();
}

void AGreystoneCharacter::MoveForward(float Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;
	if (Controller && (Value != 0.f))
	{
		// find out which way is forward
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AGreystoneCharacter::MoveRight(float Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;
	if (Controller && (Value != 0.f))
	{
		// find out which way is right
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AGreystoneCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AGreystoneCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void AGreystoneCharacter::EKeyPressed()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon)
	{
		if (EquippedWeapon)
		{
			EquippedWeapon->Destroy();
		}
		EquipWeapon(OverlappingWeapon);
	}
	else
	{
		if (CanDisarm())
		{
			Disarm();
		}
		else if (CanArm())
		{
			Arm();
		}
	}
}

void AGreystoneCharacter::Attack()
{
	Super::Attack();
	if (CanAttack())
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
}

void AGreystoneCharacter::Dodge()
{
	PlayDodgeMontage();
	ActionState = EActionState::EAS_Dodge;
	if (Attributes && SlashOverlay)
	{
		
	}
}

void AGreystoneCharacter::EquipWeapon(AWeapon* Weapon)
{
	Weapon->Equip(GetMesh(), FName("RightHandSocket"), this, this);
	CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	OverlappingItem = nullptr;
	EquippedWeapon = Weapon;
}

void AGreystoneCharacter::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void AGreystoneCharacter::DodgeEnd()
{
	Super::DodgeEnd();

	ActionState = EActionState::EAS_Unoccupied;
}

bool AGreystoneCharacter::CanAttack()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_Unequipped;
}

bool AGreystoneCharacter::CanDisarm()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_Unequipped;
}

bool AGreystoneCharacter::CanArm()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState == ECharacterState::ECS_Unequipped &&
		EquippedWeapon;
}

void AGreystoneCharacter::Disarm()
{
	PlayEquipMontage(FName("Unequip"));
	CharacterState = ECharacterState::ECS_Unequipped;
	ActionState = EActionState::EAS_EquippingWeapon;
}

void AGreystoneCharacter::Arm()
{
	PlayEquipMontage(FName("Equip"));
	CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	ActionState = EActionState::EAS_EquippingWeapon;
}

void AGreystoneCharacter::AttachWeaponToBack()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("SpineSocket"));
	}
}

void AGreystoneCharacter::AttachWeaponToHand()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("RightHandSocket"));
	}
}

void AGreystoneCharacter::PlayEquipMontage(const FName& SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage)
	{
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
	}
}

void AGreystoneCharacter::Die_Implementation()
{
	Super::Die_Implementation();

	ActionState = EActionState::EAS_Dead;
	DisableMeshCollision();
}



bool AGreystoneCharacter::IsOccupied()
{
	return ActionState != EActionState::EAS_Unoccupied;
}

void AGreystoneCharacter::FinishEquipping()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void AGreystoneCharacter::HitReactEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

bool AGreystoneCharacter::IsUnoccupied()
{
	return ActionState == EActionState::EAS_Unoccupied;
}

void AGreystoneCharacter::InitializeSlashOverlay()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		ASlashHUD* SlashHUD = Cast<ASlashHUD>(PlayerController->GetHUD());
		if (SlashHUD)
		{
			SlashOverlay = SlashHUD->GetSlashOverlay();
			if (SlashOverlay && Attributes)
			{
				SlashOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
				SlashOverlay->SetStaminaBarPercent(1.f);
				SlashOverlay->SetGold(0);
				SlashOverlay->SetSouls(0);
			}
		}
	}
}

void AGreystoneCharacter::SetHUDHealth()
{
	if (SlashOverlay && Attributes)
	{
		SlashOverlay->SetHealthBarPercent(Attributes->GetHealthPercent());
	}
}

void AGreystoneCharacter::AddSouls(ASoul* Soul)
{
	if (Attributes && SlashOverlay)
	{
		Attributes->AddSouls(Soul->GetSouls());
		SlashOverlay->SetSouls(Attributes->GetSouls());
	}
}