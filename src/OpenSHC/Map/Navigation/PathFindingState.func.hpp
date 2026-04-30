/**
  path: 'OpenSHC/Map/Navigation/PathFindingState.func.hpp'
*/

#include "OpenSHC/Map/Navigation/PathFindingState.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"
namespace OpenSHC {
namespace Map {
    namespace Navigation {
        namespace PathFindingState_Func {

            using OpenSHC::Map::Units::UnitTypeInt;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(undefined4 (PathFindingState::*)(), false, Address::SHC_3BB0A8C1_0x00496E20,
                &PathFindingState::getComputationalTileIndex)
            getComputationalTileIndex;

            MACRO_FUNCTION_RESOLVER(int (PathFindingState::*)(int), false, Address::SHC_3BB0A8C1_0x00496E30,
                &PathFindingState::getTileInSearchQueue)
            getTileInSearchQueue;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(byte*), false, Address::SHC_3BB0A8C1_0x00496EA0,
                &PathFindingState::bindPathPlanToAlgorithmStateAndReset)
            bindPathPlanToAlgorithmStateAndReset;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int), false, Address::SHC_3BB0A8C1_0x00496EC0,
                &PathFindingState::findClosestTileToStartingTile)
            findClosestTileToStartingTile;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00496F90,
                &PathFindingState::findNextTileInExistingSearchThatIsModuloDistanceAway)
            findNextTileInExistingSearchThatIsModuloDistanceAway;

            MACRO_FUNCTION_RESOLVER(dword (PathFindingState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00497080, &PathFindingState::pathFindingResultBased)
            pathFindingResultBased;

            MACRO_FUNCTION_RESOLVER(dword (PathFindingState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00497180,
                &PathFindingState::findNextTileByModuloAmongPreviousSearchNotOnDefensiveStructure)
            findNextTileByModuloAmongPreviousSearchNotOnDefensiveStructure;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (PathFindingState::*)(int, int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00497280, &PathFindingState::doMoveFromTileToTile)
            doMoveFromTileToTile;

            MACRO_FUNCTION_RESOLVER(BOOL (PathFindingState::*)(uint, uint, uint, uint), false,
                Address::SHC_3BB0A8C1_0x004974D0,
                &PathFindingState::findNeighbourTileThatCanServeAsClimbPointClosestToXY)
            findNeighbourTileThatCanServeAsClimbPointClosestToXY;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, uint, uint), false,
                Address::SHC_3BB0A8C1_0x00497690, &PathFindingState::findPositionForGivenClimbArea)
            findPositionForGivenClimbArea;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (PathFindingState::*)(uint, uint, int, int, int, BOOLEnum), false,
                Address::SHC_3BB0A8C1_0x00497740, &PathFindingState::findLinkageBasedPathOrWalkRadius)
            findLinkageBasedPathOrWalkRadius;

            MACRO_FUNCTION_RESOLVER(undefined4 (PathFindingState::*)(int, int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00497B80, &PathFindingState::findSuitableSpawnLocationUnk)
            findSuitableSpawnLocationUnk;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (PathFindingState::*)(uint, uint, uint, uint, int, BOOLEnum), false,
                Address::SHC_3BB0A8C1_0x00498020, &PathFindingState::findPathUsingClimbingWithHeightMargin16)
            findPathUsingClimbingWithHeightMargin16;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (PathFindingState::*)(uint, uint, uint, uint, int, int), false,
                Address::SHC_3BB0A8C1_0x00498400, &PathFindingState::pathFindingWithBuildingsIncluded)
            pathFindingWithBuildingsIncluded;

            MACRO_FUNCTION_RESOLVER(undefined4 (PathFindingState::*)(int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x00498A40, &PathFindingState::calculatePathKeepAndWallsGatesNotAllowed)
            calculatePathKeepAndWallsGatesNotAllowed;

            MACRO_FUNCTION_RESOLVER(uint (PathFindingState::*)(uint, int, int), false, Address::SHC_3BB0A8C1_0x00498FD0,
                &PathFindingState::commitUnitPathPlanUsingWalkLayer)
            commitUnitPathPlanUsingWalkLayer;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (PathFindingState::*)(int), false, Address::SHC_3BB0A8C1_0x004995E0,
                &PathFindingState::updateSeparateAreaTileMap)
            updateSeparateAreaTileMap;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (PathFindingState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004999C0,
                &PathFindingState::updatePathLinkageLayerBasedOnBuildingsUnk)
            updatePathLinkageLayerBasedOnBuildingsUnk;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00499DC0,
                &PathFindingState::updatePathLinkageLayerAtTileForSomeLogicalReason)
            updatePathLinkageLayerAtTileForSomeLogicalReason;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int), false, Address::SHC_3BB0A8C1_0x00499FA0,
                &PathFindingState::updatePathLinkageTileMapRelatedToGates)
            updatePathLinkageTileMapRelatedToGates;

            MACRO_FUNCTION_RESOLVER(undefined8 (PathFindingState::*)(int), false, Address::SHC_3BB0A8C1_0x0049A1C0,
                &PathFindingState::updatePathLinkageTileMapRelatedToKeeps)
            updatePathLinkageTileMapRelatedToKeeps;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int), false, Address::SHC_3BB0A8C1_0x0049A2E0,
                &PathFindingState::updatePathLinkageTileMapRelatedToSiegeTower)
            updatePathLinkageTileMapRelatedToSiegeTower;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (PathFindingState::*)(uint, uint, uint, uint), false,
                Address::SHC_3BB0A8C1_0x0049A370, &PathFindingState::tracePathPlanToDestinationViaUnoccupiedTiles)
            tracePathPlanToDestinationViaUnoccupiedTiles;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(), false, Address::SHC_3BB0A8C1_0x0049A5E0,
                &PathFindingState::reverseCurrentPathPlan)
            reverseCurrentPathPlan;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(uint, uint, int), false,
                Address::SHC_3BB0A8C1_0x0049A6D0, &PathFindingState::raiseLand2)
            raiseLand2;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, uint, uint), false,
                Address::SHC_3BB0A8C1_0x0049AAD0, &PathFindingState::updateWalkAndPathLayer)
            updateWalkAndPathLayer;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(uint), false, Address::SHC_3BB0A8C1_0x0049AF50,
                &PathFindingState::setChangedLayerZeroBasedOn40x40Layer)
            setChangedLayerZeroBasedOn40x40Layer;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (PathFindingState::*)(), false, Address::SHC_3BB0A8C1_0x0049B1C0,
                &PathFindingState::getYSmallerThanYLimit)
            getYSmallerThanYLimit;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, uint, uint), false,
                Address::SHC_3BB0A8C1_0x0049B1D0, &PathFindingState::pathFindingDeerAndLionsUnk)
            pathFindingDeerAndLionsUnk;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x0049B5B0, &PathFindingState::algTunnelerFindTarget)
            algTunnelerFindTarget;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, int, uint, uint), false,
                Address::SHC_3BB0A8C1_0x0049B940, &PathFindingState::findMapBorderEdgeTileAndStoreInSignpostData)
            findMapBorderEdgeTileAndStoreInSignpostData;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, uint, uint), false,
                Address::SHC_3BB0A8C1_0x0049BBF0, &PathFindingState::findFurthestSeaTile)
            findFurthestSeaTile;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, uint, uint), false,
                Address::SHC_3BB0A8C1_0x0049BE60, &PathFindingState::getTileInSquareBrush)
            getTileInSquareBrush;

            MACRO_FUNCTION_RESOLVER(undefined4 (PathFindingState::*)(int, int, uint, uint), false,
                Address::SHC_3BB0A8C1_0x0049C020, &PathFindingState::setupBabyTreeLocationInfo)
            setupBabyTreeLocationInfo;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (PathFindingState::*)(int, uint, uint), false,
                Address::SHC_3BB0A8C1_0x0049C370, &PathFindingState::findNoTreeInRange)
            findNoTreeInRange;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (PathFindingState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0049C5C0,
                &PathFindingState::findDestinationCostLowerThan6)
            findDestinationCostLowerThan6;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x0049C690, &PathFindingState::computeTotalUnitsWithinDistance)
            computeTotalUnitsWithinDistance;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0049CB00,
                &PathFindingState::computeNextRallyPointDestination)
            computeNextRallyPointDestination;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (PathFindingState::*)(uint, uint), false, Address::SHC_3BB0A8C1_0x0049CD60,
                &PathFindingState::findDirectNeighbourWalkableTile)
            findDirectNeighbourWalkableTile;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0049CE40,
                &PathFindingState::findPathableTileWithoutUnitWithBuildingAtXY)
            findPathableTileWithoutUnitWithBuildingAtXY;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0049D0E0,
                &PathFindingState::findFreeTileOnDefensiveStructure)
            findFreeTileOnDefensiveStructure;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, uint, uint, int), false,
                Address::SHC_3BB0A8C1_0x0049D340, &PathFindingState::findWalkableTileThatDoesNotContainUnit)
            findWalkableTileThatDoesNotContainUnit;

            MACRO_FUNCTION_RESOLVER(undefined4 (PathFindingState::*)(int), false, Address::SHC_3BB0A8C1_0x0049D640,
                &PathFindingState::someBinaryAlgFunctionPathFinding)
            someBinaryAlgFunctionPathFinding;

            MACRO_FUNCTION_RESOLVER(undefined4 (PathFindingState::*)(int, int, int, int, int*, int*), false,
                Address::SHC_3BB0A8C1_0x0049D880, &PathFindingState::findClosestFreeTileNearUnitOnBuilding)
            findClosestFreeTileNearUnitOnBuilding;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (PathFindingState::*)(int, uint, uint), false,
                Address::SHC_3BB0A8C1_0x0049DB30,
                &PathFindingState::checkEnemyBuildingOrDefensiveStructureWithin12Tiles)
            checkEnemyBuildingOrDefensiveStructureWithin12Tiles;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(uint, uint, int, int), false,
                Address::SHC_3BB0A8C1_0x0049DDC0, &PathFindingState::budgetFloodFillOnCertainPathLayer)
            budgetFloodFillOnCertainPathLayer;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(uint, uint), false, Address::SHC_3BB0A8C1_0x0049E0D0,
                &PathFindingState::updateUnitDeathHeatmapIn3SpacesAroundTile)
            updateUnitDeathHeatmapIn3SpacesAroundTile;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, uint, uint, undefined4), false,
                Address::SHC_3BB0A8C1_0x0049E510, &PathFindingState::recomputeALGPathFindingTileMapUnk)
            recomputeALGPathFindingTileMapUnk;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, uint, uint), false,
                Address::SHC_3BB0A8C1_0x0049E9E0, &PathFindingState::updateAIZoneWithFloodFill0x20)
            updateAIZoneWithFloodFill0x20;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (PathFindingState::*)(int, uint, uint, undefined4), false,
                Address::SHC_3BB0A8C1_0x0049EDF0, &PathFindingState::findAIZoneWithFlags)
            findAIZoneWithFlags;

            MACRO_FUNCTION_RESOLVER(int (PathFindingState::*)(int, uint, uint, int), false,
                Address::SHC_3BB0A8C1_0x0049F040, &PathFindingState::findArcherRelatedAttackInfoIndex)
            findArcherRelatedAttackInfoIndex;

            MACRO_FUNCTION_RESOLVER(int (PathFindingState::*)(int, uint, uint, int), false,
                Address::SHC_3BB0A8C1_0x0049F2D0, &PathFindingState::findSupportPointIndex)
            findSupportPointIndex;

            MACRO_FUNCTION_RESOLVER(int (PathFindingState::*)(int, uint, uint, int), false,
                Address::SHC_3BB0A8C1_0x0049F540, &PathFindingState::algFindAttackAngle)
            algFindAttackAngle;

            MACRO_FUNCTION_RESOLVER(dword (PathFindingState::*)(int, uint, uint, undefined4, uint, int), false,
                Address::SHC_3BB0A8C1_0x0049F7D0, &PathFindingState::findAppropriateLocationForSiegeTent)
            findAppropriateLocationForSiegeTent;

            MACRO_FUNCTION_RESOLVER(dword (PathFindingState::*)(int, uint, uint, int), false,
                Address::SHC_3BB0A8C1_0x0049FC00, &PathFindingState::pathFindingRelated)
            pathFindingRelated;

            MACRO_FUNCTION_RESOLVER(dword (PathFindingState::*)(uint, uint, int, uint, int), false,
                Address::SHC_3BB0A8C1_0x0049FF20, &PathFindingState::pathfindingRelated49ff20)
            pathfindingRelated49ff20;

            MACRO_FUNCTION_RESOLVER(dword (PathFindingState::*)(uint, uint, int, uint), false,
                Address::SHC_3BB0A8C1_0x004A01D0, &PathFindingState::meth_0x4a01d0)
            meth_0x4a01d0;

            MACRO_FUNCTION_RESOLVER(int (PathFindingState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x004A0460, &PathFindingState::meth_0x4a0460)
            meth_0x4a0460;

            MACRO_FUNCTION_RESOLVER(int (PathFindingState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x004A06B0, &PathFindingState::meth_0x4a06b0)
            meth_0x4a06b0;

            MACRO_FUNCTION_RESOLVER(int (PathFindingState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x004A08E0, &PathFindingState::getGatehouseNearSomethingUnk)
            getGatehouseNearSomethingUnk;

            MACRO_FUNCTION_RESOLVER(int (PathFindingState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x004A0B20, &PathFindingState::findDistanceOrThreatLevelToUnitUnk)
            findDistanceOrThreatLevelToUnitUnk;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(), false, Address::SHC_3BB0A8C1_0x004A0E50,
                &PathFindingState::setWalkabilityBorderLogicLayerForSmallerMapSizes)
            setWalkabilityBorderLogicLayerForSmallerMapSizes;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004A1230,
                &PathFindingState::aggressiveStanceTargetBuildingAtRange)
            aggressiveStanceTargetBuildingAtRange;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (PathFindingState::*)(int, uint, uint, int), false,
                Address::SHC_3BB0A8C1_0x004A15B0, &PathFindingState::isEnemyTooCloseUnk)
            isEnemyTooCloseUnk;

            MACRO_FUNCTION_RESOLVER(int (PathFindingState::*)(int, uint, uint), false, Address::SHC_3BB0A8C1_0x004A16C0,
                &PathFindingState::tracePathToFriendlyDefensesAndReturnTileUnk)
            tracePathToFriendlyDefensesAndReturnTileUnk;

            MACRO_FUNCTION_RESOLVER(dword (PathFindingState::*)(int, uint, uint), false,
                Address::SHC_3BB0A8C1_0x004A19B0, &PathFindingState::findOwnedGatehouse)
            findOwnedGatehouse;

            MACRO_FUNCTION_RESOLVER(undefined4 (PathFindingState::*)(int, uint, uint, int), false,
                Address::SHC_3BB0A8C1_0x004A1C40, &PathFindingState::isTileInRangeOfKeepRange)
            isTileInRangeOfKeepRange;

            MACRO_FUNCTION_RESOLVER(undefined4 (PathFindingState::*)(int, uint, uint, int), false,
                Address::SHC_3BB0A8C1_0x004A1D30, &PathFindingState::findSomeSuitableLocationUnk)
            findSomeSuitableLocationUnk;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int), false, Address::SHC_3BB0A8C1_0x004A21B0,
                &PathFindingState::placeCommemoratingStatueAtGoodLocation)
            placeCommemoratingStatueAtGoodLocation;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (PathFindingState::*)(uint, uint, int), false,
                Address::SHC_3BB0A8C1_0x004A2650, &PathFindingState::isSignPostWithinDistance)
            isSignPostWithinDistance;

            MACRO_FUNCTION_RESOLVER(undefined4 (PathFindingState::*)(int, uint, uint, int, int), false,
                Address::SHC_3BB0A8C1_0x004A2A90, &PathFindingState::spreadAlgorithmForFlagsAndBraziersUnk)
            spreadAlgorithmForFlagsAndBraziersUnk;

            MACRO_FUNCTION_RESOLVER(undefined4 (PathFindingState::*)(int, int, int), false,
                Address::SHC_3BB0A8C1_0x004A2DD0, &PathFindingState::igniteFireAtTilesDistanceAway)
            igniteFireAtTilesDistanceAway;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (PathFindingState::*)(uint, int, int*, int*), false,
                Address::SHC_3BB0A8C1_0x004A3220, &PathFindingState::findAccessibleWallAndNearbyFreeTile)
            findAccessibleWallAndNearbyFreeTile;

            MACRO_FUNCTION_RESOLVER(undefined4 (PathFindingState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x004A36B0, &PathFindingState::meth_0x4a36b0)
            meth_0x4a36b0;

            MACRO_FUNCTION_RESOLVER(undefined4 (PathFindingState::*)(int, int, int, int, undefined4), false,
                Address::SHC_3BB0A8C1_0x004A3B20, &PathFindingState::certainDamageToUnitsUnk)
            certainDamageToUnitsUnk;

            MACRO_FUNCTION_RESOLVER(bool (PathFindingState::*)(undefined4, int, uint, uint, byte*, int*, int*), false,
                Address::SHC_3BB0A8C1_0x004A4140, &PathFindingState::pathFindingToAttackCastleIncludingMoat)
            pathFindingToAttackCastleIncludingMoat;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004A4470,
                &PathFindingState::computeAIZoneLayer)
            computeAIZoneLayer;

            MACRO_FUNCTION_RESOLVER(int (PathFindingState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004A4930,
                &PathFindingState::setClimbBasedOnClosestClimbData)
            setClimbBasedOnClosestClimbData;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (PathFindingState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004A4B30,
                &PathFindingState::isUsableClimbWallWithinArea)
            isUsableClimbWallWithinArea;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int), false, Address::SHC_3BB0A8C1_0x004A4B80,
                &PathFindingState::clearLaddermanWalledData)
            clearLaddermanWalledData;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int), false, Address::SHC_3BB0A8C1_0x004A4BB0,
                &PathFindingState::reprocessLadddermanWallData)
            reprocessLadddermanWallData;

            MACRO_FUNCTION_RESOLVER(undefined4 (PathFindingState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004A4C70,
                &PathFindingState::meth_0x4a4c70)
            meth_0x4a4c70;

            MACRO_FUNCTION_RESOLVER(
                void (PathFindingState::*)(), false, Address::SHC_3BB0A8C1_0x004A52D0, &PathFindingState::meth_0x4a52d0)
            meth_0x4a52d0;

            MACRO_FUNCTION_RESOLVER(int (PathFindingState::*)(int, dword, dword, int), false,
                Address::SHC_3BB0A8C1_0x004A5320, &PathFindingState::calculateCanPlayerUnitsNavigateToAreaFromArea)
            calculateCanPlayerUnitsNavigateToAreaFromArea;

            MACRO_FUNCTION_RESOLVER(dword (PathFindingState::*)(int, dword, dword), false,
                Address::SHC_3BB0A8C1_0x004A58A0, &PathFindingState::meth_0x4a58a0)
            meth_0x4a58a0;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (PathFindingState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004A5B00,
                &PathFindingState::calculateCanReachUsingCachedAreaLogic)
            calculateCanReachUsingCachedAreaLogic;

            MACRO_FUNCTION_RESOLVER(undefined4 (PathFindingState::*)(int, uint, uint, uint, uint), false,
                Address::SHC_3BB0A8C1_0x004A5DA0, &PathFindingState::meth_0x4a5da0)
            meth_0x4a5da0;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(), false, Address::SHC_3BB0A8C1_0x004A5F60,
                &PathFindingState::updatePathLinkageLayerForEachBuildingAtEachTile)
            updatePathLinkageLayerForEachBuildingAtEachTile;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004A5F90,
                &PathFindingState::updatePathLinkagesInAllEightDirections)
            updatePathLinkagesInAllEightDirections;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, uint, uint, int, int, int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x004A6010, &PathFindingState::meth_0x4a6010)
            meth_0x4a6010;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int), false, Address::SHC_3BB0A8C1_0x004A6520,
                &PathFindingState::storeDestinationOptionsUnk)
            storeDestinationOptionsUnk;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004A65E0,
                &PathFindingState::setDestinationPairsBasedOnPreviousSearch)
            setDestinationPairsBasedOnPreviousSearch;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004A66D0,
                &PathFindingState::setMoveDestinationPairs)
            setMoveDestinationPairs;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, int, int, UnitTypeInt, undefined4), false,
                Address::SHC_3BB0A8C1_0x004A67D0, &PathFindingState::spawnUnitAndAddToTribe)
            spawnUnitAndAddToTribe;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int), false, Address::SHC_3BB0A8C1_0x004A69F0,
                &PathFindingState::computeAttackVectorsBasedOnXAndY)
            computeAttackVectorsBasedOnXAndY;

            MACRO_FUNCTION_RESOLVER(undefined4 (PathFindingState::*)(int, uint, uint), false,
                Address::SHC_3BB0A8C1_0x004A6AB0, &PathFindingState::meth_0x4a6ab0)
            meth_0x4a6ab0;

            MACRO_FUNCTION_RESOLVER(int (PathFindingState::*)(int, dword, uint, uint), false,
                Address::SHC_3BB0A8C1_0x004A6DF0, &PathFindingState::canNavigateFunctionReturnsArea)
            canNavigateFunctionReturnsArea;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, uint, dword, int), false,
                Address::SHC_3BB0A8C1_0x004A7090, &PathFindingState::updateWalkLayerAndAIPathCostLayer)
            updateWalkLayerAndAIPathCostLayer;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, int, int, dword, int), false,
                Address::SHC_3BB0A8C1_0x004A75B0, &PathFindingState::pathfindingForAttacksUnk)
            pathfindingForAttacksUnk;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(uint, undefined4, uint, uint, int, dword, int), false,
                Address::SHC_3BB0A8C1_0x004A79A0, &PathFindingState::pathPlanningForTribe)
            pathPlanningForTribe;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, int, int*, int, int, int), false,
                Address::SHC_3BB0A8C1_0x004A7F50,
                &PathFindingState::findFreeSpaceNextToEnemyDefensiveStructureInSameAreaWithinDistance)
            findFreeSpaceNextToEnemyDefensiveStructureInSameAreaWithinDistance;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int, int, dword, int), false,
                Address::SHC_3BB0A8C1_0x004A83B0,
                &PathFindingState::populateDestinationsArrayWithWallTileAndFreeTilePairInSameArea)
            populateDestinationsArrayWithWallTileAndFreeTilePairInSameArea;

            MACRO_FUNCTION_RESOLVER(int (PathFindingState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004A8780,
                &PathFindingState::findUnitPreferredOrientationBasedConnectedTile)
            findUnitPreferredOrientationBasedConnectedTile;

            MACRO_FUNCTION_RESOLVER(int (PathFindingState::*)(int, int, int*), false, Address::SHC_3BB0A8C1_0x004A8860,
                &PathFindingState::findBuildingAccessPoint)
            findBuildingAccessPoint;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(int), false, Address::SHC_3BB0A8C1_0x004A8AB0,
                &PathFindingState::pathfindingUpdate_0x4a8ab0)
            pathfindingUpdate_0x4a8ab0;

            MACRO_FUNCTION_RESOLVER(undefined4 (PathFindingState::*)(int, uint, uint, int, undefined4, undefined4, int),
                false, Address::SHC_3BB0A8C1_0x004A9200, &PathFindingState::isOpponentBuildingInRange)
            isOpponentBuildingInRange;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(), false, Address::SHC_3BB0A8C1_0x004A94E0,
                &PathFindingState::clearAllLadderManWalledData)
            clearAllLadderManWalledData;

            MACRO_FUNCTION_RESOLVER(int (PathFindingState::*)(int, int, int, int), false,
                Address::SHC_3BB0A8C1_0x004A9510, &PathFindingState::createClimbData)
            createClimbData;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(), false, Address::SHC_3BB0A8C1_0x004A9680,
                &PathFindingState::updateClimbData)
            updateClimbData;

            MACRO_FUNCTION_RESOLVER(void (PathFindingState::*)(uint, uint, uint, uint, int), false,
                Address::SHC_3BB0A8C1_0x004A97D0, &PathFindingState::traceAndCommitPathPlan)
            traceAndCommitPathPlan;

            MACRO_FUNCTION_RESOLVER(dword (PathFindingState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004A9B20,
                &PathFindingState::doPathfinding)
            doPathfinding;

            MACRO_FUNCTION_RESOLVER(undefined4 (PathFindingState::*)(), false, Address::SHC_3BB0A8C1_0x004A9DD0,
                &PathFindingState::retraceAndCommitPathPlan)
            retraceAndCommitPathPlan;

        } // namespace PathFindingState_Func
    } // namespace Navigation
} // namespace Map
} // namespace OpenSHC
