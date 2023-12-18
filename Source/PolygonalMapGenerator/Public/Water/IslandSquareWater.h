

#pragma once

#include "CoreMinimal.h"
#include "Water/IslandWater.h"
#include "IslandSquareWater.generated.h"

/**
 * 
 */
UCLASS()
class POLYGONALMAPGENERATOR_API UIslandSquareWater : public UIslandWater
{
	GENERATED_BODY()
	
protected:
	virtual bool IsPointLand_Implementation(FPointIndex Point, UTriangleDualMesh* Mesh, const FVector2D& HalfMeshSize, const FVector2D& Offset, const FIslandShape& Shape) const override;
};
