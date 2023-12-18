

#include "Mesh/IslandPoissonMeshBuilder.h"
#include "DualMeshBuilder.h"

UIslandPoissonMeshBuilder::UIslandPoissonMeshBuilder()
{
	PoissonSize = FVector2D(100000.0, 100000.0);
	PoissonSpacing = 1075.0f;
	PoissonSamples = 30;
}

void UIslandPoissonMeshBuilder::AddPoints_Implementation(UDualMeshBuilder* Builder, FRandomStream& Rng) const
{
	Builder->AddPoisson(Rng, MapSize - PoissonSize, PoissonSpacing, PoissonSamples);
}
