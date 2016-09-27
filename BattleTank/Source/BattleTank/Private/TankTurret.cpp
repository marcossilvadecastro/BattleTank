#include "BattleTank.h"
#include "TankTurret.h"



void UTankTurret::Rotate(float RotationSpeed)
{
	RotationSpeed = FMath::Clamp<float>(RotationSpeed, -1, +1);

	float RotationChange = RotationSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float Rotation = RotationChange + RelativeRotation.Yaw;
	SetRelativeRotation(FRotator(0.f , Rotation, 0.f));
}


