

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "PolygonalMapGenerator.h"
#include "DualMesh/Public/TriangleDualMesh.h"

#include "IslandMapUtils.h"

#include "IslandRivers.generated.h"

/**
 * A class which determines where "springs" are on the island, and then
 * generates rivers which flow downstream from these springs.
 */
UCLASS(Blueprintable)
class POLYGONALMAPGENERATOR_API UIslandRivers : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float MinSpringElevation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float MaxSpringElevation;

public:
	UIslandRivers();

protected:
	/**
	* Is this triangle water?
	*/
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Procedural Generation|Island Generation|Rivers")
	virtual bool IsTriangleWater(FTriangleIndex t, UTriangleDualMesh* Mesh, const TArray<bool>& WaterRegions) const;
	UFUNCTION(BlueprintCallable, Category = "Procedural Generation|Island Generation|Rivers")
	virtual TArray<URiver*> CreateRiver(FTriangleIndex RiverTriangle, TArray<int32> &s_flow, TMap<FTriangleIndex, URiver*> RiverMap, UTriangleDualMesh* Mesh, const TArray<FSideIndex>& t_downslope_s, FRandomStream& RiverRng) const;

	virtual TArray<FTriangleIndex> FindSpringTriangles_Implementation(UTriangleDualMesh* Mesh, const TArray<bool>& r_water, const TArray<float>& t_elevation, const TArray<FSideIndex>& t_downslope_s) const;
	virtual void AssignSideFlow_Implementation(TArray<int32>& s_flow, TArray<URiver*>& Rivers, UTriangleDualMesh* Mesh, const TArray<FSideIndex>& t_downslope_s, const TArray<FTriangleIndex>& river_t, FRandomStream& RiverRNG) const;

public:
	/**
	* Find candidates for river sources
	*
	* Unlike the assign_* functions this does not write into an existing array
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Procedural Generation|Island Generation|Rivers")
	TArray<FTriangleIndex> FindSpringTriangles(UTriangleDualMesh* Mesh, const TArray<bool>& WaterRegions, const TArray<float>& TriangleElevations, const TArray<FSideIndex>& TriangleSideDownslopes) const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Procedural Generation|Island Generation|Rivers")
	void AssignSideFlow(UPARAM(ref) TArray<int32>& SideFlow, UPARAM(ref) TArray<URiver*>& Rivers, UTriangleDualMesh* Mesh, const TArray<FSideIndex>& TriangleSideDownslopes, const TArray<FTriangleIndex>& RiverTriangles, UPARAM(ref) FRandomStream& RiverRNG) const;

	TArray<FTriangleIndex> find_spring_t(UTriangleDualMesh* Mesh, const TArray<bool>& r_water, const TArray<float>& t_elevation, const TArray<FSideIndex>& t_downslope_s) const;
	void assign_s_flow(TArray<int32>& s_flow, TArray<URiver*>& Rivers, UTriangleDualMesh* Mesh, const TArray<FSideIndex>& t_downslope_s, const TArray<FTriangleIndex>& river_t, FRandomStream& RiverRNG) const;
};
