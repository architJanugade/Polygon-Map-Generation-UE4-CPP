

#include "Water/IslandRadialWater.h"

UIslandRadialWater::UIslandRadialWater()
{
	Bumps = 3;
	StartAngle = 1.0f;
	AngleOffset = 1.0f;
	MinAngle = 0.5f;
	LandScale = 1.25f;
}

bool UIslandRadialWater::IsPointLand_Implementation(FPointIndex Point, UTriangleDualMesh* Mesh, const FVector2D& HalfMeshSize, const FVector2D& Offset, const FIslandShape& Shape) const
{
	FVector2D point = Mesh->r_pos(Point) - HalfMeshSize;
	point.X = LandScale * 2.0f * (point.X / (HalfMeshSize.X * 2.0f));
	point.Y = LandScale * 2.0f * (point.Y / (HalfMeshSize.Y * 2.0f));
	// Get the angle of the point from the center of the island
	float angle = FMath::Atan2(point.Y, point.X);
	// Get the normalized length of whichever axis is longer
	float length = 0.5f * (FMath::Max(FMath::Abs(point.X), FMath::Abs(point.Y)) + FVector2D::Distance(FVector2D::ZeroVector, point));
	// The inner radius has to be smaller than the length for this to be land
	float innerRadius;
	// The outer radius has to be larger than the length for this to be land
	float outerRadius;

	if ((FMath::Abs(angle - (AngleOffset * PI)) < MinAngle
		 || FMath::Abs(angle - (AngleOffset * PI) + 2.0f * PI) < MinAngle
		 || FMath::Abs(angle - (AngleOffset * PI) - 2.0f * PI) < MinAngle))
	{
		// Our angle is less than the minimum angle
		innerRadius = 0.2f;
		outerRadius = 0.2f;
	}
	else
	{
		innerRadius = 0.5f + 0.4f * FMath::Sin((StartAngle * PI) + Bumps * angle + FMath::Cos((Bumps + 3) * angle));
		outerRadius = 0.7f - 0.2f * FMath::Sin((StartAngle * PI) + Bumps * angle - FMath::Sin((Bumps + 2) * angle));
	}

	return !((length + WaterCutoff < innerRadius) || (length + WaterCutoff > innerRadius * Shape.IslandFragmentation && length + WaterCutoff < outerRadius));
}