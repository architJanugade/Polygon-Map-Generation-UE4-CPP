

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "DualMesh/Public/TriangleDualMesh.h"

#include "IslandMeshBuilder.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class POLYGONALMAPGENERATOR_API UIslandMeshBuilder : public UDataAsset
{
	GENERATED_BODY()

public:
	// The size of our map, starting at (0, 0).
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Map")
	FVector2D MapSize;
	// The amount of spacing on the edge of the map.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Edges", meta = (ClampMin = "0"))
	int32 BoundarySpacing;

public:
	UIslandMeshBuilder();

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Procedural Generation|Island Generation|Points")
	void AddPoints(UDualMeshBuilder* Builder, UPARAM(ref) FRandomStream& Rng) const;
	virtual void AddPoints_Implementation(UDualMeshBuilder* Builder, FRandomStream& Rng) const;
	virtual UTriangleDualMesh* GenerateDualMesh_Implementation(FRandomStream& Rng) const;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Procedural Generation|Island Generation|Points")
	UTriangleDualMesh* GenerateDualMesh(UPARAM(ref) FRandomStream& Rng) const;
};
