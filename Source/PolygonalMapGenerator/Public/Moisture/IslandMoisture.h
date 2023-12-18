

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "DualMesh/Public/TriangleDualMesh.h"

#include "IslandMoisture.generated.h"

/**
 * A class which determines how much moisture different areas on the island receive.
 */
UCLASS(Blueprintable)
class POLYGONALMAPGENERATOR_API UIslandMoisture : public UDataAsset
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Procedural Generation|Island Generation|Moisture")
	virtual TSet<FPointIndex> FindRiverbanks(UTriangleDualMesh* Mesh, const TArray<int32>& s_flow) const;
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Procedural Generation|Island Generation|Moisture")
	virtual TSet<FPointIndex> FindLakeshores(UTriangleDualMesh* Mesh, const TArray<bool>& r_ocean, const TArray<bool>& r_water) const;

	virtual TSet<FPointIndex> FindMoistureSeeds_Implementation(UTriangleDualMesh* Mesh, const TArray<int32>& s_flow, const TArray<bool>& r_ocean, const TArray<bool>& r_water) const;
	virtual void AssignRegionMoisture_Implementation(TArray<float>& r_moisture, TArray<int32>& r_waterdistance, UTriangleDualMesh* Mesh, const TArray<bool>& r_water, const TSet<FPointIndex>& r_moisture_seeds) const;
	virtual void RedistributeRegionMoisture_Implementation(TArray<float>& r_moisture, UTriangleDualMesh* Mesh, const TArray<bool>& r_water, float MinMoisture, float MaxMoisture) const;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Procedural Generation|Island Generation|Moisture")
	TSet<FPointIndex> FindMoistureSeeds(UTriangleDualMesh* Mesh, const TArray<int32>& SideFlow, const TArray<bool>& OceanRegions, const TArray<bool>& WaterRegions) const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Procedural Generation|Island Generation|Moisture")
	void AssignRegionMoisture(UPARAM(ref) TArray<float>& RegionMoisture, UPARAM(ref) TArray<int32>& RegionWaterDistance, UTriangleDualMesh* Mesh, const TArray<bool>& WaterRegions, const TSet<FPointIndex>& MoistureSeedRegions) const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Procedural Generation|Island Generation|Moisture")
	void RedistributeRegionMoisture(UPARAM(ref) TArray<float>& RegionMoisture, UTriangleDualMesh* Mesh, const TArray<bool>& WaterRegions, float MinMoisture, float MaxMoisture) const;
	
	TSet<FPointIndex> find_moisture_seeds_r(UTriangleDualMesh* Mesh, const TArray<int32>& s_flow, const TArray<bool>& r_ocean, const TArray<bool>& r_water) const;
	void assign_r_moisture(TArray<float>& r_moisture, TArray<int32>& r_waterdistance, UTriangleDualMesh* Mesh, const TArray<bool>& r_water, const TSet<FPointIndex>& r_moisture_seeds) const;
	void redistribute_r_moisture(TArray<float>& r_moisture, UTriangleDualMesh* Mesh, const TArray<bool>& r_water, float MinMoisture, float MaxMoisture) const;
};
