#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankAimingComponent::AimAt(FVector Target)
{

	if (Barrel) 
	{
		FVector SuggestedVelocity;
		if (UGameplayStatics::SuggestProjectileVelocity(
			this,
			SuggestedVelocity,
			Barrel->GetSocketLocation("Projectile"),
			Target,
			LaunchSpeed,
			false,
			0.f,
			0.f,
			ESuggestProjVelocityTraceOption::DoNotTrace
		)) 
		{
			AimDirection = SuggestedVelocity.GetSafeNormal();
			MoveBarrelTowards(AimDirection);
		}
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimTarget) 
{
	if (Barrel && Turret) 
	{
		FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
		FRotator TargetRotation = AimTarget.Rotation();

		FRotator DeltaRotation = TargetRotation - BarrelRotator;

		Barrel->Elevate(DeltaRotation.Pitch);
		float MinYawValue = FMath::Abs(DeltaRotation.Yaw) > 180 ? -DeltaRotation.Yaw : DeltaRotation.Yaw;
		Turret->Rotate(MinYawValue);
	}

}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::Fire()
{
	if(
			Barrel && ProjectileBlueprint && 
			(FiringState == EFiringState::Aiming ||
			FiringState == EFiringState::Locked)
		)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTimeSeconds = FPlatformTime::Seconds();
		BulletCount--;
	}
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (BulletCount <= 0 ) 
	{
		FiringState = EFiringState::OutAmmo;
	}
	else if (FPlatformTime::Seconds() - LastFireTimeSeconds < ReloadTimeSeconds) 
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving()) 
	{
		FiringState = EFiringState::Aiming;
	}
	else 
	{
		FiringState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(Barrel)) { return false; }

	return Barrel->GetForwardVector().Equals(AimDirection, 0.01);
}

void UTankAimingComponent::BeginPlay()
{
	LastFireTimeSeconds = FPlatformTime::Seconds();
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int UTankAimingComponent::GetBulletCount() const 
{
	return BulletCount;
}