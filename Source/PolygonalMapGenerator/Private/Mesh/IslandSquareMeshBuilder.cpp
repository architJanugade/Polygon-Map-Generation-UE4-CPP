

#include "Mesh/IslandSquareMeshBuilder.h"
#include "DualMeshBuilder.h"

UIslandSquareMeshBuilder::UIslandSquareMeshBuilder()
{
	NumberOfPoints = 1000;
}

void UIslandSquareMeshBuilder::AddPoints_Implementation(UDualMeshBuilder* Builder, FRandomStream& Rng) const
{
	int32 gridSize = FMath::CeilToInt(FMath::Sqrt(NumberOfPoints));
	for (int32 x = 0; x < gridSize; x++)
	{
		for (int32 y = 0; y < gridSize; y++)
		{
			Builder->AddPoint(FVector2D((0.5f + x) / gridSize * MapSize.X, (0.5f + y) / gridSize * MapSize.Y));
		}
	}
}
