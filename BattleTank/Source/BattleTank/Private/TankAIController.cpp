#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn) 
	{
		ATank* PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath() 
{
	if (GetPawn()) 
	{
		GetPawn()->DetachFromControllerPendingDestroy();
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (auto TankPlayerController = GetWorld()->GetFirstPlayerController()->GetPawn())
	{

		MoveToActor(TankPlayerController, AcceptableRadius);

		AimingComponent->AimAt(TankPlayerController->GetActorLocation());

		if (AimingComponent->GetFiringState() != EFiringState::Reloading) 
		{
			AimingComponent->Fire();
		}
		
	}
}


