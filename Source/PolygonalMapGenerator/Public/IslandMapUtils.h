

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "GameplayTagsManager.h"

#include "PolygonalMapGenerator.h"
#include "Delaunator/Public/DelaunayHelper.h"
#include "DualMesh/Public/TriangleDualMesh.h"
#include "ProceduralMeshComponent.h"

#include "IslandMapUtils.generated.h"

USTRUCT(BlueprintType)
struct POLYGONALMAPGENERATOR_API FIslandShape
{
	GENERATED_BODY()
	// How many iterations we should have when smoothing the island.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Points", meta = (ClampMin = "0"))
	int32 Octaves;
	// Modifies the scale of the noise used to generate water versus land.
	// Larger values will generate many small islands. Smaller values will make one big island.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map", meta = (ClampMin = "0.01"))
	float IslandFragmentation;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Map")
	TArray<float> Amplitudes;

	FIslandShape()
	{
		Octaves = 5;
		IslandFragmentation = 1.0f;
	}
};

UCLASS(BlueprintType)
class POLYGONALMAPGENERATOR_API URiver : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FTriangleIndex> RiverTriangles;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FSideIndex> Downslopes;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	URiver* FeedsInto;

public:
	void Add(FTriangleIndex Triangle, FSideIndex Downslope)
	{
		RiverTriangles.Add(Triangle);
		Downslopes.Add(Downslope);
	}

	int32 Length() const
	{
		return RiverTriangles.Num();
	}
};

USTRUCT(BlueprintType)
struct POLYGONALMAPGENERATOR_API FBiomeBias
{
	GENERATED_BODY()
	// How much rainfall the island receives. Higher values are wetter.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Map", meta = (ClampMin = "-1.0", ClampMax = "1.0"))
	float Rainfall;
	// How hot the northern part of the island is. Higher values are hotter.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Map", meta = (ClampMin = "-1.5", ClampMax = "1.5"))
	float NorthernTemperature;
	// How hot the southern part of the island is. Higher values are hotter.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Map", meta = (ClampMin = "-1.5", ClampMax = "1.5"))
	float SouthernTemperature;

	FBiomeBias()
	{
		Rainfall = 0.0f;
		NorthernTemperature = 0.0f;
		SouthernTemperature = 0.0f;
	}
};

USTRUCT(BlueprintType)
struct FBiomeData : public FGameplayTagTableRow
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsOcean;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsWater;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCoast;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float MinMoisture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float MaxMoisture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float MinTemperature;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float MaxTemperature;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor DebugColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* BiomeMaterial;

public:
	FBiomeData()
	{
		bIsOcean = false;
		bIsWater = false;
		bIsCoast = false;

		MinMoisture = 0.0f;
		MaxMoisture = 1.0f;

		MinTemperature = 0.0f;
		MaxTemperature = 1.0f;

		DebugColor = FColor::Magenta;
		BiomeMaterial = NULL;
	}
};

USTRUCT(BlueprintType)
struct POLYGONALMAPGENERATOR_API FIslandPolygon
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FBiomeData Biome;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FVector> VertexPoints;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<FTriangleIndex> Vertices;
};

USTRUCT(BlueprintType)
struct POLYGONALMAPGENERATOR_API FMapMeshData
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FVector> Vertices;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FLinearColor> VertexColors;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<int32> Triangles;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FVector> Normals;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FVector2D> UV0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FProcMeshTangent> Tangents;
};

/**
 * A collection of utilities used in island generation.
 */
UCLASS()
class POLYGONALMAPGENERATOR_API UIslandMapUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Procedural Generation|Island Generation|Utils")
	static void RandomShuffle(TArray<FTriangleIndex>& OutShuffledArray, UPARAM(ref) FRandomStream& Rng);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Procedural Generation|Island Generation|Utils")
	static float FBMNoise(const TArray<float>& Amplitudes, const FVector2D& Position);

	// Given a BiomeData table and a collection of data about a point, returns a biome.
	// Note that the given FName is TECHNICALLY a GameplayTag.
	// If you have GameplayTags enabled, you should be able to use the GameplayTag Find function to convert
	// the FName into a GameplayTag.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Procedural Generation|Island Generation|Biomes")
	static FBiomeData GetBiome(const UDataTable* BiomeData, bool bIsOcean, bool bIsWater, bool bIsCoast, float Temperature, float Moisture);
	UFUNCTION(BlueprintCallable, Category = "Procedural Generation|Island Generation|Debug")
	static void DrawDelaunayFromMap(class AIslandMap* Map);
	//UFUNCTION(BlueprintCallable, Category = "Procedural Generation|Island Generation|Debug")
	UFUNCTION()
	static void DrawVoronoiFromMap(class AIslandMap* Map);
	UFUNCTION(BlueprintCallable, Category = "Procedural Generation|Island Generation|Debug")
	static void DrawDelaunayMesh(AActor* Context, UTriangleDualMesh* Mesh, const TArray<float>& RegionElevations, const TArray<int32>& SideFlow, const TArray<URiver*>& Rivers, const TArray<float> &TriangleElevations, const TArray<FBiomeData>& RegionBiomes);
	//UFUNCTION(BlueprintCallable, Category = "Procedural Generation|Island Generation|Debug")
	UFUNCTION()
	static void DrawVoronoiMesh(AActor* Context, UTriangleDualMesh* Mesh, const TArray<FIslandPolygon>& Polygons, const TArray<int32>& SideFlow, const TArray<URiver*>& Rivers, const TArray<float>& TriangleElevations);
	UFUNCTION(BlueprintCallable, Category = "Procedural Generation|Island Generation|Debug")
	static void DrawRivers(AActor* Context, UTriangleDualMesh* Mesh, const TArray<URiver*>& Rivers, const TArray<int32>& SideFlow, const TArray<float> &TriangleElevations);

	UFUNCTION(BlueprintCallable, Category = "Procedural Generation|Island Generation")
	static void GenerateMesh(class AIslandMap* Map, UProceduralMeshComponent* MapMesh, float ZScale);
	UFUNCTION(BlueprintCallable, Category = "Procedural Generation|Island Generation")
	static void GenerateMapMeshSingleMaterial(UTriangleDualMesh* Mesh, UProceduralMeshComponent* MapMesh, float ZScale, const TArray<float>& RegionElevation);
	UFUNCTION(BlueprintCallable, Category = "Procedural Generation|Island Generation")
	static void GenerateMapMeshMultiMaterial(UTriangleDualMesh* Mesh, UProceduralMeshComponent* MapMesh, float ZScale, const TArray<float>& RegionElevation, const TArray<bool>& CostalRegions, const TArray<FBiomeData> RegionBiomes);
};