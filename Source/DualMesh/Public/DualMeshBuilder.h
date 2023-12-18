

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TriangleDualMesh.h"
#include "DualMeshBuilder.generated.h"

/**
* Generates a random triangle mesh for the given area.
 */
UCLASS()
class DUALMESH_API UDualMeshBuilder : public UObject
{
	GENERATED_BODY()
protected:
	TArray<FVector2D> Points;
	int32 NumBoundaryRegions;
	FVector2D MaxMeshSize;

protected:
	TArray<FVector2D> AddBoundaryPoints(int32 Spacing, const FVector2D& Size);

public:
	UDualMeshBuilder();

public:
	void Initialize(const FVector2D& MaxSize, int32 BoundarySpacing = 0);
	void AddPoint(const FVector2D& Point);
	void AddPoints(const TArray<FVector2D>& NewPoints);
	TArray<FVector2D> GetBoundaryPoints() const;
	void ClearNonBoundaryPoints();
	void AddPoisson(FRandomStream& Rng, FVector2D MapOffset = FVector2D(0.0f, 0.0f), float Spacing = 1.0f, int32 MaxStepSamples = 30);

	UTriangleDualMesh* Create();
};
