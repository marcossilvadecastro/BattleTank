#include "BattleTank.h"
#include "TankBarrel.h"


void UTankBarrel::Elevate(float DeltaSpeed) 
{

	DeltaSpeed = FMath::Clamp<float>(DeltaSpeed, -1, +1);

	float ElevationChange =  DeltaSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = ElevationChange + RelativeRotation.Pitch;
	float Elevation = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(Elevation, 0.f, 0.f));
}




