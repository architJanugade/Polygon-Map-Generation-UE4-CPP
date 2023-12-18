

#include "Mesh/IslandMeshBuilder.h"
#include "DualMeshBuilder.h"

UIslandMeshBuilder::UIslandMeshBuilder()
{
	MapSize = FVector2D(107500.0, 107500.0);
	BoundarySpacing = 1000;
}

void UIslandMeshBuilder::AddPoints_Implementation(UDualMeshBuilder* Builder, FRandomStream& Rng) const
{
	// Do nothing
}

UTriangleDualMesh* UIslandMeshBuilder::GenerateDualMesh_Implementation(FRandomStream& Rng) const
{
	UDualMeshBuilder* builder = NewObject<UDualMeshBuilder>();
	builder->Initialize(MapSize, BoundarySpacing);
	AddPoints(builder, Rng);
	return builder->Create();
}
