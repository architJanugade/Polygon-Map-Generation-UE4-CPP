

#include "Biomes/IslandBiome.h"

void UIslandBiome::AssignCoast_Implementation(TArray<bool>& r_coast, UTriangleDualMesh* Mesh, const TArray<bool>& r_ocean) const
{
	r_coast.Empty(Mesh->NumRegions);
	r_coast.SetNumZeroed(Mesh->NumRegions);
	for (FPointIndex r1 = 0; r1 < r_coast.Num(); r1++)
	{
		if (!r_ocean[r1])
		{
			TArray<FPointIndex> out_r = Mesh->r_circulate_r(r1);
			for (FPointIndex r2 : out_r)
			{
				if (r_ocean[r2])
				{
					r_coast[r1] = true;
					break;
				}
			}
		}
	}
}

void UIslandBiome::AssignTemperature_Implementation(TArray<float>& r_temperature, UTriangleDualMesh* Mesh, const TArray<bool>& r_ocean, const TArray<bool>& r_water, const TArray<float>& r_elevation, const TArray<float>& r_moisture, float NorthernTemperature, float SouthernTemperature) const
{
	r_temperature.Empty(Mesh->NumRegions);
	r_temperature.SetNumZeroed(Mesh->NumRegions);
	for (FPointIndex r = 0; r < r_temperature.Num(); r++)
	{
		float lat = Mesh->r_y(r) / Mesh->GetSize().Y; // 0.0 - 1.0
		float biased_temp = FMath::Lerp(NorthernTemperature, SouthernTemperature, lat);
		r_temperature[r] = 1.0f - r_elevation[r] + biased_temp;
	}
}

void UIslandBiome::AssignBiome_Implementation(TArray<FBiomeData>& r_biome, UTriangleDualMesh* Mesh, const TArray<bool>& r_ocean, const TArray<bool>& r_water, const TArray<bool>& r_coast, const TArray<float>& r_temperature, const TArray<float>& r_moisture) const
{
	r_biome.Empty(Mesh->NumRegions);
	r_biome.SetNumZeroed(Mesh->NumRegions);
	for (FPointIndex r = 0; r < r_biome.Num(); r++)
	{
		r_biome[r] = UIslandMapUtils::GetBiome(BiomeData, r_ocean[r], r_water[r], r_coast[r], r_temperature[r], r_moisture[r]);
	}
}

void UIslandBiome::assign_r_coast(TArray<bool>& r_coast, UTriangleDualMesh* Mesh, const TArray<bool>& r_ocean) const
{
	AssignCoast(r_coast, Mesh, r_ocean);
}

void UIslandBiome::assign_r_temperature(TArray<float>& r_temperature, UTriangleDualMesh* Mesh, const TArray<bool>& r_ocean, const TArray<bool>& r_water, const TArray<float>& r_elevation, const TArray<float>& r_moisture, float NorthernTemperature, float SouthernTemperature) const
{
	AssignTemperature(r_temperature, Mesh, r_ocean, r_water, r_elevation, r_moisture, NorthernTemperature, SouthernTemperature);
}

void UIslandBiome::assign_r_biome(TArray<FBiomeData>& r_biome, UTriangleDualMesh* Mesh, const TArray<bool>& r_ocean, const TArray<bool>& r_water, const TArray<bool>& r_coast, const TArray<float>& r_temperature, const TArray<float>& r_moisture) const
{
	AssignBiome(r_biome, Mesh, r_ocean, r_water, r_coast, r_temperature, r_moisture);
}
