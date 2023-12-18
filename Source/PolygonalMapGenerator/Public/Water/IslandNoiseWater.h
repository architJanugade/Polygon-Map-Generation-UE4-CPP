

#pragma once

#include "CoreMinimal.h"
#include "Water/IslandWater.h"
#include "IslandNoiseWater.generated.h"

/**
 * 
 */
UCLASS()
class POLYGONALMAPGENERATOR_API UIslandNoiseWater : public UIslandWater
{
	GENERATED_BODY()

protected:
	virtual bool IsPointLand_Implementation(FPointIndex Point, UTriangleDualMesh* Mesh, const FVector2D& HalfMeshSize, const FVector2D& Offset, const FIslandShape& Shape) const override;
};
