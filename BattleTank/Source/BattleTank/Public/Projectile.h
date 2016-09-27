#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	void LaunchProjectile(float Speed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float TimeToDestoy = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ProjectileDamage = 20.f;

	void OnDestroyTimerExpired();

	UProjectileMovementComponent* ProjectileComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Components")
	UParticleSystemComponent*  LaunchBlast = nullptr;

	UPROPERTY(EditAnywhere, Category = "Components")
	UParticleSystemComponent*  ImpactBlast = nullptr;

	UPROPERTY(EditAnywhere, Category = "Components")
	URadialForceComponent* Explosion = nullptr;
	
	
};
