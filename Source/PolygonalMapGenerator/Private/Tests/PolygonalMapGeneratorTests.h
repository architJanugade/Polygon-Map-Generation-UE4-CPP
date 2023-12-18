

#pragma once

#include "CoreMinimal.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWaterTest, "Procedural Generation.PolygonalMapGenerator.Check Water Generation", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter | EAutomationTestFlags::LowPriority)

bool FWaterTest::RunTest(const FString& Parameters)
{
	return true;
}