// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Treasure.h"
#include "Characters/GreystoneCharacter.h"
#include "Kismet/GameplayStatics.h"

void ATreasure::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGreystoneCharacter* GreystoneCharacter = Cast<AGreystoneCharacter>(OtherActor);
	if (GreystoneCharacter)
	{
		if (PickupSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				PickupSound,
				GetActorLocation()
				);
		}
		Destroy();
	}
}
