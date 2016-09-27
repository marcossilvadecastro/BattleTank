#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovimentComponent.h"



void UTankMovimentComponent::MoveForward(float Speed)
{
	if (LeftTrack && RightTrack)
	{
		LeftTrack->SetThrottle(Speed);
		RightTrack->SetThrottle(Speed);
	}
}

void UTankMovimentComponent::IntentMoveRight(float Speed)
{
	if (LeftTrack && RightTrack)
	{
		LeftTrack->SetThrottle(Speed);
		RightTrack->SetThrottle(-Speed);
	}
}

void UTankMovimentComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovimentComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	MoveForward(ForwardThrow);

	FVector TurnRightVector = FVector::CrossProduct(TankForward, AIForwardIntention);
	IntentMoveRight(TurnRightVector.Z);
}

