

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PoissonDiscUtilities.generated.h"

/**
 * 
 */
UCLASS()
class DUALMESH_API UPoissonDiscUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* Generate samples using a PoissonDisc distribution in 2D space.
	* @param Samples - Returned TArray of FVector2D containing the sample positions.
	* @param Seed - Seed used for generation of samples.
	* @param Size - Size of area to generate samples in.
	* @param MininumDistance - Minimum distance between samples.
	* @param MaxStepSamples - Maximum samples to generate each step.
	* @param WrapX - Wrap output in X direction.
	* @param WrapY - Wrap output in Y direction.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Distribute in 2D (Poisson Disc)"), Category = "Procedural Generation|Random Sampling|Distribution")
	static void Distribute2D(TArray<FVector2D>& Samples, int32 Seed = 0, FVector2D Size = FVector2D(1.0, 1.0), FVector2D StartLocation = FVector2D(0.0f, 0.0f), float MinimumDistance = 1.0f, int32 MaxStepSamples = 30, bool WrapX = false, bool WrapY = false);

	/**
	* Generate samples using a PoissonDisc distribution in 3D space.
	* @param Samples - Returned TArray of FVector containing the sample positions.
	* @param Seed - Seed used for generation of samples.
	* @param Size - Size of area to generate samples in.
	* @param MininumDistance - Minimum distance between samples.
	* @param MaxStepSamples - Maximum samples to generate each step.
	* @param WrapX - Wrap output in X direction.
	* @param WrapY - Wrap output in Y direction.
	* @param WrapZ - Wrap output in Z direction.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, meta = (DisplayName = "Distribute in 3D (Poisson Disc)"), Category = "Procedural Generation|Random Sampling|Distribution")
	static void Distribute3D(TArray<FVector>& Samples, int32 Seed = 0, FVector Size = FVector(1.0, 1.0, 1.0), float MinimumDistance = 1.0f, int32 MaxStepSamples = 30, bool WrapX = false, bool WrapY = false, bool WrapZ = false);
};
