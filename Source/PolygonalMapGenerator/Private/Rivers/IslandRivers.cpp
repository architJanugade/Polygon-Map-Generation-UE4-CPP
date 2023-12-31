

#include "Rivers/IslandRivers.h"

UIslandRivers::UIslandRivers()
{
	MinSpringElevation = 0.3f;
	MaxSpringElevation = 0.9f;
}

bool UIslandRivers::IsTriangleWater(FTriangleIndex t, UTriangleDualMesh* Mesh, const TArray<bool>& r_water) const
{
	TArray<FPointIndex> regions = Mesh->t_circulate_r(t);
	for (FPointIndex r : regions)
	{
		if (r_water[r])
		{
			return true;
		}
	}
	return false;
}

TArray<FTriangleIndex> UIslandRivers::FindSpringTriangles_Implementation(UTriangleDualMesh* Mesh, const TArray<bool>& r_water, const TArray<float>& t_elevation, const TArray<FSideIndex>& t_downslope_s) const
{
	TSet<FTriangleIndex> spring_t;
	if (Mesh != NULL)
	{
		// Add everything above some elevation, but not lakes
		// We skip every other triangle to ensure that we don't select neighboring triangles later
		for (FTriangleIndex t = 0; t < Mesh->NumSolidTriangles; t += 2)
		{
			if (t_elevation[t] >= MinSpringElevation &&
				t_elevation[t] <= MaxSpringElevation &&
				!IsTriangleWater(t, Mesh, r_water))
			{
				spring_t.Add(t);
			}
		}
	}
	else
	{
		UE_LOG(LogMapGen, Error, TEXT("Mesh was invalid!"));
	}
	return spring_t.Array();
}

TArray<URiver*> UIslandRivers::CreateRiver(FTriangleIndex RiverTriangle, TArray<int32> &s_flow, TMap<FTriangleIndex, URiver*> RiverMap, UTriangleDualMesh* Mesh, const TArray<FSideIndex>& t_downslope_s, FRandomStream& RiverRng) const
{
	TSet<FTriangleIndex> processedSlopes;
	TArray<URiver*> createdRivers;
	URiver* currentRiver = NULL;
	FSideIndex lastS = FSideIndex();
	while(true)
	{
		if (processedSlopes.Contains(RiverTriangle))
		{
			UE_LOG(LogMapGen, Warning, TEXT("Tried to process a slope we've already processed once this loop! We have an infinite loop."));
			break;
		}

		FSideIndex s = t_downslope_s[RiverTriangle];
		if (!s.IsValid())
		{
			// Hit the coastline; add the last triangles
			s = Mesh->s_opposite_s(lastS);
			if (s.IsValid())
			{
				s_flow[s]++;

				if (!RiverMap.Contains(RiverTriangle))
				{
					if (currentRiver == NULL)
					{
						// Make a new river, just for 1 triangle
						currentRiver = NewObject<URiver>();
						createdRivers.Add(currentRiver);
					}
					currentRiver->Add(RiverTriangle, s);
					RiverMap.Add(RiverTriangle, currentRiver);
				}
				else if (currentRiver != NULL && RiverMap[RiverTriangle] != NULL)
				{
					currentRiver->FeedsInto = RiverMap[RiverTriangle];
					currentRiver = NULL;
				}
			}
			break;
		}

		if (!RiverMap.Contains(RiverTriangle))
		{
			// This triangle doesn't have a river in it yet
			if (currentRiver == NULL)
			{
				// Make a new river
				currentRiver = NewObject<URiver>();
				if (currentRiver == NULL)
				{
					UE_LOG(LogMapGen, Error, TEXT("Could not create a new river!"));
					break;
				}
				createdRivers.Add(currentRiver);
			}

			// Now that we know we have a river, mark it as being traversed
			currentRiver->Add(RiverTriangle, s);
			RiverMap.Add(RiverTriangle, currentRiver);
		}
		else if (currentRiver != NULL && RiverMap[RiverTriangle] != NULL)
		{
			// The current river joins as a tributary of the river at this location
			currentRiver->FeedsInto = RiverMap[RiverTriangle];
			currentRiver = NULL;
		}

		// Each river contributes 1 more flow down to the coastline
		s_flow[s]++;
		processedSlopes.Add(RiverTriangle);

		FTriangleIndex next_t = Mesh->s_outer_t(s);
		if (next_t == RiverTriangle)
		{
			// Loop onto ourselves
			break;
		}

		RiverTriangle = next_t;
		lastS = s;
	}

	// One final pass; make sure none of the rivers are null
	TArray<URiver*> riverArray;
	for (int i = 0; i < createdRivers.Num(); i++)
	{
		if (createdRivers[i] == NULL)
		{
			UE_LOG(LogMapGen, Error, TEXT("River at index %d was null!"), i);
		}
		else
		{
			riverArray.Add(createdRivers[i]);
		}
	}
	return riverArray;
}

void UIslandRivers::AssignSideFlow_Implementation(TArray<int32>& s_flow, TArray<URiver*>& Rivers, UTriangleDualMesh* Mesh, const TArray<FSideIndex>& t_downslope_s, const TArray<FTriangleIndex>& river_t, FRandomStream& RiverRng) const
{
	if (Mesh)
	{
		Rivers.Empty(river_t.Num());
		s_flow.Empty(Mesh->NumSides);
		s_flow.SetNumZeroed(Mesh->NumSides);
		TMap<FTriangleIndex, URiver*> riverTriangles;
		for (int i = 0; i < river_t.Num(); i++)
		{
			Rivers.Append(CreateRiver(river_t[i], s_flow, riverTriangles, Mesh, t_downslope_s, RiverRng));
		}
	}
	else
	{
		UE_LOG(LogMapGen, Error, TEXT("Mesh was invalid!"));
	}
}

TArray<FTriangleIndex> UIslandRivers::find_spring_t(UTriangleDualMesh* Mesh, const TArray<bool>& r_water, const TArray<float>& t_elevation, const TArray<FSideIndex>& t_downslope_s) const
{
	return FindSpringTriangles(Mesh, r_water, t_elevation, t_downslope_s);
}

void UIslandRivers::assign_s_flow(TArray<int32>& s_flow, TArray<URiver*>& Rivers, UTriangleDualMesh* Mesh, const TArray<FSideIndex>& t_downslope_s, const TArray<FTriangleIndex>& river_t, FRandomStream& RiverRng) const
{
	AssignSideFlow(s_flow, Rivers, Mesh, t_downslope_s, river_t, RiverRng);
}