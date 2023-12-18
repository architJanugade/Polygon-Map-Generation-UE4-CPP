

#pragma once

#include "CoreMinimal.h"
#include "Mesh/IslandMeshBuilder.h"
#include "IslandSquareMeshBuilder.generated.h"

/**
 * 
 */
UCLASS()
class POLYGONALMAPGENERATOR_API UIslandSquareMeshBuilder : public UIslandMeshBuilder
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "1"))
	int32 NumberOfPoints;

public:
	UIslandSquareMeshBuilder();

protected:
	virtual void AddPoints_Implementation(UDualMeshBuilder* Builder, FRandomStream& Rng) const override;
};
