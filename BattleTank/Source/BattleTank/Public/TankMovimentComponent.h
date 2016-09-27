#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovimentComponent.generated.h"


class UTankTrack;
/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovimentComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
private:
	UTankTrack* LeftTrack;
	UTankTrack* RightTrack;

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void MoveForward(float Speed);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntentMoveRight(float Speed);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed);
};
