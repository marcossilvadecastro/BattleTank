#include "BattleTank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth/ (float)MaxHealt;
}

ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay() 
{
	Super::BeginPlay();
	CurrentHealth = MaxHealt;
}

float ATank::TakeDamage
(
	float DamageAmount,
	struct FDamageEvent const & DamageEvent,
	class AController * EventInstigator,
	AActor * DamageCauser
)
{
	int32 iDamageAmount = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(iDamageAmount, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0) 
	{
		OnDeath.Broadcast();
	}
	return DamageToApply;
}