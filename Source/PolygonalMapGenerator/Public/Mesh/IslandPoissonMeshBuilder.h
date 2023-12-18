

#pragma once

#include "CoreMinimal.h"
#include "Mesh/IslandMeshBuilder.h"
#include "IslandPoissonMeshBuilder.generated.h"

/**
 * 
 */
UCLASS()
class POLYGONALMAPGENERATOR_API UIslandPoissonMeshBuilder : public UIslandMeshBuilder
{
	GENERATED_BODY()
public:
	// The size of our map, starting at (0, 0).
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Map")
	FVector2D PoissonSize;
	// How much spacing between Poisson points.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Points", meta = (ClampMin = "0.0"))
	float PoissonSpacing;
	// Maximum samples to generate each step.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Points", meta = (ClampMin = "0"))
	int32 PoissonSamples;

public:
	UIslandPoissonMeshBuilder();

protected:
	virtual void AddPoints_Implementation(UDualMeshBuilder* Builder, FRandomStream& Rng) const override;
};
