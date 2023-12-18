

#include "Water/IslandNoiseWater.h"

bool UIslandNoiseWater::IsPointLand_Implementation(FPointIndex Point, UTriangleDualMesh* Mesh, const FVector2D& HalfMeshSize, const FVector2D& Offset, const FIslandShape& Shape) const
{
	FVector2D nVector = Mesh->r_pos(Point);
	nVector.X /= HalfMeshSize.X;
	nVector.Y /= HalfMeshSize.Y;
	nVector = (nVector + Offset) * Shape.IslandFragmentation;
	float n = UIslandMapUtils::FBMNoise(Shape.Amplitudes, nVector);
	float distance = FMath::Max(FMath::Abs(nVector.X), FMath::Abs(nVector.Y));
	return n * distance * distance > WaterCutoff;
}
