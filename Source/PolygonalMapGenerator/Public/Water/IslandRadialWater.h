

#pragma once

#include "CoreMinimal.h"
#include "Water/IslandWater.h"
#include "IslandRadialWater.generated.h"

/**
 * 
 */
UCLASS()
class POLYGONALMAPGENERATOR_API UIslandRadialWater : public UIslandWater
{
	GENERATED_BODY()

public:
	// The number of sine waves which form bumps along the island.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bumps")
	int32 Bumps;
	// The start angle for the sin function, in radians.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Angle")
	float StartAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Angle")
	float AngleOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Angle")
	float MinAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Angle")
	float LandScale;

public:
	UIslandRadialWater();

protected:
	virtual bool IsPointLand_Implementation(FPointIndex Point, UTriangleDualMesh* Mesh, const FVector2D& HalfMeshSize, const FVector2D& Offset, const FIslandShape& Shape) const override;
};
