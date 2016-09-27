#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;


UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming, 
	Locked,
	OutAmmo
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetBulletCount() const;

	EFiringState GetFiringState() const;

protected:
	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimTarget);

	UPROPERTY(BlueprintReadOnly, Category  = "State")
	EFiringState FiringState = EFiringState::Reloading;
	
	UPROPERTY(EditAnywhere)
	float LaunchSpeed = 4000.f;

	double ReloadTimeSeconds = 3;

	double LastFireTimeSeconds = 0;

	bool IsBarrelMoving() const;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	int BulletCount = 15;

private:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;

	FVector AimDirection;
};
