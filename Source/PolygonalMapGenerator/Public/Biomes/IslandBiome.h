

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"

#include "DualMesh/Public/TriangleDualMesh.h"

#include "IslandMapUtils.h"

#include "IslandBiome.generated.h"

/**
 * A class which assigns biomes to parts of the island based on their attributes.
 */
UCLASS(Blueprintable)
class POLYGONALMAPGENERATOR_API UIslandBiome : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* BiomeData;

protected:
	virtual void AssignCoast_Implementation(TArray<bool>& r_coast, UTriangleDualMesh* Mesh, const TArray<bool>& r_ocean) const;
	virtual void AssignTemperature_Implementation(TArray<float>& r_temperature, UTriangleDualMesh* Mesh, const TArray<bool>& r_ocean, const TArray<bool>& r_water, const TArray<float>& r_elevation, const TArray<float>& r_moisture, float NorthernTemperature, float SouthernTemperature) const;
	virtual void AssignBiome_Implementation(TArray<FBiomeData>& r_biome, UTriangleDualMesh* Mesh, const TArray<bool>& r_ocean, const TArray<bool>& r_water, const TArray<bool>& r_coast, const TArray<float>& r_temperature, const TArray<float>& r_moisture) const;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Procedural Generation|Island Generation|Biome")
	void AssignCoast(UPARAM(ref) TArray<bool>& CoastalRegions, UTriangleDualMesh* Mesh, const TArray<bool>& OceanRegions) const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Procedural Generation|Island Generation|Biome")
	void AssignTemperature(UPARAM(ref) TArray<float>& RegionTemperatures, UTriangleDualMesh* Mesh, const TArray<bool>& OceanRegions, const TArray<bool>& WaterRegions, const TArray<float>& RegionElevations, const TArray<float>& RegionMoisture, float NorthernTemperature, float SouthernTemperature) const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Procedural Generation|Island Generation|Biome")
	void AssignBiome(UPARAM(ref) TArray<FBiomeData>& RegionBiomes, UTriangleDualMesh* Mesh, const TArray<bool>& OceanRegions, const TArray<bool>& WaterRegions, const TArray<bool>& CoastalRegions, const TArray<float>& RegionTemperature, const TArray<float>& RegionMoisture) const;
	
	void assign_r_coast(TArray<bool>& r_coast, UTriangleDualMesh* Mesh, const TArray<bool>& r_ocean) const;
	void assign_r_temperature(TArray<float>& r_temperature, UTriangleDualMesh* Mesh, const TArray<bool>& r_ocean, const TArray<bool>& r_water, const TArray<float>& r_elevation, const TArray<float>& r_moisture, float NorthernTemperature, float SouthernTemperature) const;
	void assign_r_biome(TArray<FBiomeData>& r_biome, UTriangleDualMesh* Mesh, const TArray<bool>& r_ocean, const TArray<bool>& r_water, const TArray<bool>& r_coast, const TArray<float>& r_temperature, const TArray<float>& r_moisture) const;
};
