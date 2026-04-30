/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Navigation/PathFindingState.hpp'
*/

#pragma once

#include "OpenSHC/Map/ClimbData.hpp"
#include "OpenSHC/Map/Navigation/PathFindingStatePartB.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::ClimbData;
        using OpenSHC::Map::Navigation::PathFindingStatePartB;
        using OpenSHC::Map::Units::UnitTypeInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x000CC670
        class PathFindingState {
        public:
            undefined4 maxClimbDataCount; // 0x00000000 length: 4
            undefined4 searchGeneration; // 0x00000004 length: 4
            undefined4 unitX; // 0x00000008 length: 4
            undefined4 unitY; // 0x0000000C length: 4
            undefined4 destinationX; // 0x00000010 length: 4
            undefined4 destinationY; // 0x00000014 length: 4
            undefined4 climbX; // 0x00000018 length: 4
            undefined4 climbY; // 0x0000001C length: 4
            undefined4 mappingYRelated; // 0x00000020 length: 4
            undefined4 yLimit; // 0x00000024 length: 4
            undefined4 field10_0x28; // 0x00000028 length: 4
            undefined4 ALG_TargetX; // 0x0000002C length: 4
            undefined4 ALG_TargetY; // 0x00000030 length: 4
            undefined4 ALG_TargetTile; // 0x00000034 length: 4
            undefined4 resultX; // 0x00000038 length: 4
            undefined4 resultY; // 0x0000003C length: 4
            undefined4 resultTile; // 0x00000040 length: 4
            undefined4 ALG_ResultX; // 0x00000044 length: 4
            undefined4 ALG_ResultY; // 0x00000048 length: 4
            undefined4 ALG_ResultTile; // 0x0000004C length: 4
            undefined1 padding_0x50[12]; // 0x00000050 length: 12
            undefined4 ALGO_TotalTroopValue; // 0x0000005C length: 4
            undefined4 ALGO_TotalTroopCount; // 0x00000060 length: 4
            undefined4 field34_0x64; // 0x00000064 length: 4
            undefined1 padding_0x68[4]; // 0x00000068 length: 4
            undefined4 toggleUpdateSeparateAreaTileMap; // 0x0000006C length: 4
            undefined4 field40_0x70; // 0x00000070 length: 4
            undefined4 field41_0x74; // 0x00000074 length: 4
            undefined4 DAT_lWys; // 0x00000078 length: 4
            undefined4 field43_0x7c; // 0x0000007C length: 4
            undefined4 notAllAssassinsUnk; // 0x00000080 length: 4
            undefined4 climbIsIllegal; // 0x00000084 length: 4
            undefined4 allAssassinsUnk; // 0x00000088 length: 4
            undefined4 distance; // 0x0000008C length: 4
            undefined4 field48_0x90; // 0x00000090 length: 4
            undefined4 field49_0x94; // 0x00000094 length: 4
            undefined4 field50_0x98; // 0x00000098 length: 4
            undefined4 field51_0x9c; // 0x0000009C length: 4
            undefined4 calculations; // 0x000000A0 length: 4
            undefined4 DAT_Mini_spreads; // 0x000000A4 length: 4
            undefined4 DAT_Easy; // 0x000000A8 length: 4
            undefined4 DAT_Hard; // 0x000000AC length: 4
            undefined4 searchNonmatchCount; // 0x000000B0 length: 4
            undefined4 searchMatchCounter; // 0x000000B4 length: 4
            undefined1 padding_0xb8[4]; // 0x000000B8 length: 4
            undefined4 DAT_Ass; // 0x000000BC length: 4
            undefined4 field63_0xc0; // 0x000000C0 length: 4
            undefined4 DAT_Test_likely; // 0x000000C4 length: 4
            undefined4 DAT_Test_gatehouse; // 0x000000C8 length: 4
            undefined4 totalZones; // 0x000000CC length: 4
            undefined1 padding_0xd0[8]; // 0x000000D0 length: 8
            undefined4 DAT_NumberOfLadderTeleports; // 0x000000D8 length: 4
            undefined4 DAT_GreatestLadderLoading; // 0x000000DC length: 4
            int zoneSizesArray[1000]; // 0x000000E0 length: 4000
            undefined4 sum; // 0x00001080 length: 4
            ClimbData climbData[200]; // 0x00001084 length: 103200
            PathFindingStatePartB searchQueue; // 0x0001A3A4 length: 729804

        private:
            PathFindingState(PathFindingState const&);
            void operator=(PathFindingState const&);

            PathFindingState();
            ~PathFindingState();

        public:
            // Constructor
            PathFindingState* Constructor_PathFindingState();

            undefined4 getComputationalTileIndex();

            int getTileInSearchQueue(int index);

            void bindPathPlanToAlgorithmStateAndReset(byte* pPathPlan);

            void findClosestTileToStartingTile(int param_1);

            void findNextTileInExistingSearchThatIsModuloDistanceAway(int modulo, int x, int y);

            dword pathFindingResultBased(int param_1, int x, int y, int extraDistance);

            dword findNextTileByModuloAmongPreviousSearchNotOnDefensiveStructure(int modulo, int x, int y);

            BOOLEnum doMoveFromTileToTile(
                int unitID, int tile, int y, int direction, int param_5, int ignoreAssassinClimbing);

            BOOL findNeighbourTileThatCanServeAsClimbPointClosestToXY(uint x, uint y, uint x2, uint y2);

            void findPositionForGivenClimbArea(int area, uint x, uint y);

            BOOLEnum findLinkageBasedPathOrWalkRadius(
                uint x, uint y, int x2, int y2, int maxIterations, BOOLEnum continuePreviousSearch);

            undefined4 findSuitableSpawnLocationUnk(int x, int y, int x2, int y2, int param_5, int param_6);

            BOOLEnum findPathUsingClimbingWithHeightMargin16(
                uint x, uint y, uint x2, uint y2, int budget, BOOLEnum continueSearch);

            BOOLEnum pathFindingWithBuildingsIncluded(
                uint x, uint y, uint x2, uint y2, int maxOptionsToTry, int zeroMeansResetAlgorithm);

            undefined4 calculatePathKeepAndWallsGatesNotAllowed(int x1, int y1, int x2, int y2, int maxTries);

            uint commitUnitPathPlanUsingWalkLayer(uint param_1, int param_2, int param_3);

            BOOLEnum updateSeparateAreaTileMap(int forceUpdate);

            BOOLEnum updatePathLinkageLayerBasedOnBuildingsUnk(int yUnk, int tile);

            void updatePathLinkageLayerAtTileForSomeLogicalReason(int tile, int y);

            void updatePathLinkageTileMapRelatedToGates(int buildingID);

            undefined8 updatePathLinkageTileMapRelatedToKeeps(int buildingID);

            void updatePathLinkageTileMapRelatedToSiegeTower(int param_1);

            BOOLEnum tracePathPlanToDestinationViaUnoccupiedTiles(uint x, uint y, uint destX, uint destY);

            void reverseCurrentPathPlan();

            void raiseLand2(uint x, uint y, int maxDistance);

            void updateWalkAndPathLayer(int param_1, uint xPosition, uint yPosition);

            void setChangedLayerZeroBasedOn40x40Layer(uint flag_and_offset);

            BOOLEnum getYSmallerThanYLimit();

            void pathFindingDeerAndLionsUnk(int originArea, uint destinationX, uint destinationY);

            void algTunnelerFindTarget(int playerID, int targetPlayerID, int distance, int originX, int originY);

            void findMapBorderEdgeTileAndStoreInSignpostData(int signpostID, int maxDistance, uint x, uint y);

            void findFurthestSeaTile(int budget, uint x, uint y);

            void getTileInSquareBrush(int brushTileIndex, uint x, uint y);

            undefined4 setupBabyTreeLocationInfo(int param_1, int treeType, uint x, uint y);

            BOOLEnum findNoTreeInRange(int budget, uint x, uint y);

            BOOLEnum findDestinationCostLowerThan6(int tile, int maxDistance);

            void computeTotalUnitsWithinDistance(
                int playerID, int sameTeamUnits, int someLogicalTileProperty, int tile, int distance);

            void computeNextRallyPointDestination(int unitID, int xPos, int yPos);

            BOOLEnum findDirectNeighbourWalkableTile(uint x, uint y);

            void findPathableTileWithoutUnitWithBuildingAtXY(int unitID, int x, int y);

            void findFreeTileOnDefensiveStructure(int unitID, int x, int y);

            void findWalkableTileThatDoesNotContainUnit(int unitID, uint x, uint y, int considerUnits);

            undefined4 someBinaryAlgFunctionPathFinding(int param_1);

            undefined4 findClosestFreeTileNearUnitOnBuilding(
                int buildingID, int unitID, int x, int y, int* pX, int* pY);

            BOOLEnum checkEnemyBuildingOrDefensiveStructureWithin12Tiles(int playerID, uint x, uint y);

            void budgetFloodFillOnCertainPathLayer(uint x, uint y, int marker, int budget);

            void updateUnitDeathHeatmapIn3SpacesAroundTile(uint x, uint y);

            void recomputeALGPathFindingTileMapUnk(int someMax, uint x, uint y, undefined4 param_4);

            void updateAIZoneWithFloodFill0x20(int max, uint x, uint y);

            BOOLEnum findAIZoneWithFlags(int maxDistance, uint x, uint y, undefined4 aiInfoFlags);

            int findArcherRelatedAttackInfoIndex(int max, uint x, uint y, int tribeID);

            int findSupportPointIndex(int max, uint x, uint y, int tribeID);

            int algFindAttackAngle(int maxDistance200, uint x, uint y, int tribeID);

            dword findAppropriateLocationForSiegeTent(
                int distanceUnk, uint x, uint y, undefined4 selectionID, uint requiredDistanceFromAIZone, int playerID);

            dword pathFindingRelated(int param_1, uint param_2, uint param_3, int param_4);

            dword pathfindingRelated49ff20(uint x, uint y, int playerID, uint distanceUnk, int param_5);

            dword meth_0x4a01d0(uint param_1, uint param_2, int param_3, uint param_4);

            int meth_0x4a0460(int param_1, int param_2, int param_3, int param_4);

            int meth_0x4a06b0(int param_1, int param_2, int param_3, int param_4);

            int getGatehouseNearSomethingUnk(int param_1, int param_2, int param_3, int maxDistance);

            int findDistanceOrThreatLevelToUnitUnk(int param_1, int param_2, int param_3, int param_4);

            void setWalkabilityBorderLogicLayerForSmallerMapSizes();

            void aggressiveStanceTargetBuildingAtRange(int unitID, int maxDistance);

            BOOLEnum isEnemyTooCloseUnk(int playerID, uint x, uint y, int requiredDistance);

            int tracePathToFriendlyDefensesAndReturnTileUnk(int playerID, uint x, uint y);

            dword findOwnedGatehouse(int playerID, uint x, uint y);

            undefined4 isTileInRangeOfKeepRange(int playerID, uint x, uint y, int range);

            undefined4 findSomeSuitableLocationUnk(int param_1, uint x, uint y, int param_4);

            void placeCommemoratingStatueAtGoodLocation(int playerID);

            BOOLEnum isSignPostWithinDistance(uint x, uint y, int limit);

            undefined4 spreadAlgorithmForFlagsAndBraziersUnk(int playerID, uint x, uint y, int param_4, int param_5);

            undefined4 igniteFireAtTilesDistanceAway(int tile, int maxDistance, int playerID);

            BOOLEnum findAccessibleWallAndNearbyFreeTile(uint unitID, int tile, int* pFreeTile, int* pDefensesTile);

            undefined4 meth_0x4a36b0(int param_1, int param_2, int param_3, int param_4);

            undefined4 certainDamageToUnitsUnk(int param_1, int param_2, int param_3, int param_4, undefined4 param_5);

            bool pathFindingToAttackCastleIncludingMoat(undefined4 playerID, int wallOwnerPlayerID, uint x, uint y,
                byte* out_successUnk, int* out_x, int* out_y);

            void computeAIZoneLayer(int attackedPlayerID, int canReachKeep);

            int setClimbBasedOnClosestClimbData(int unitID, int ladderWallGroup, int ladderArea);

            BOOLEnum isUsableClimbWallWithinArea(int area, int wallDataID);

            void clearLaddermanWalledData(int param_1);

            void reprocessLadddermanWallData(int laddermanWalledDataID);

            undefined4 meth_0x4a4c70(int param_1, int param_2);

            void meth_0x4a52d0();

            int calculateCanPlayerUnitsNavigateToAreaFromArea(
                int playerID, dword fromArea, dword toArea, int permitClimb);

            dword meth_0x4a58a0(int param_1, dword param_2, dword param_3);

            BOOLEnum calculateCanReachUsingCachedAreaLogic(int tile1, int tile2);

            undefined4 meth_0x4a5da0(int param_1, uint param_2, uint param_3, uint param_4, uint param_5);

            void updatePathLinkageLayerForEachBuildingAtEachTile();

            void updatePathLinkagesInAllEightDirections(int y, int tile);

            void meth_0x4a6010(int param_1, uint param_2, uint param_3, int param_4, int param_5, int param_6,
                int param_7, int param_8, int param_9);

            void storeDestinationOptionsUnk(int signpostID);

            void setDestinationPairsBasedOnPreviousSearch(int playerIDMin1, int attackedPlayerID);

            void setMoveDestinationPairs(int playerIDmin1, int playerID, int maxCost);

            void spawnUnitAndAddToTribe(
                int playerID, int displayColor, int count, UnitTypeInt unitType, undefined4 tribeID);

            void computeAttackVectorsBasedOnXAndY(int playerID);

            undefined4 meth_0x4a6ab0(int param_1, uint param_2, uint param_3);

            int canNavigateFunctionReturnsArea(int playerID, dword targetArea, uint unitX, uint unitY);

            void updateWalkLayerAndAIPathCostLayer(int limit, uint borderDistance, dword fromArea, int playerID);

            void pathfindingForAttacksUnk(int tribeID, int buildingID, int param_3, dword param_4, int param_5);

            void pathPlanningForTribe(
                uint tribeID, undefined4 targetUnitID, uint x, uint y, int unitCount, dword area, int playerID);

            void findFreeSpaceNextToEnemyDefensiveStructureInSameAreaWithinDistance(
                int tile, int maxDestinations, int* area, int playerID, int shortenedDistance, int direction);

            void populateDestinationsArrayWithWallTileAndFreeTilePairInSameArea(
                int tile, int maxDestinations, dword area, int playerID);

            int findUnitPreferredOrientationBasedConnectedTile(int unitID, int tile);

            int findBuildingAccessPoint(int unitID, int buildingID, int* pResultTile);

            void pathfindingUpdate_0x4a8ab0(int param_1);

            undefined4 isOpponentBuildingInRange(
                int playerID, uint x, uint y, int range, undefined4 param_5, undefined4 param_6, int keepRange);

            void clearAllLadderManWalledData();

            int createClimbData(int size, int buildingID, int unitID, int direction);

            void updateClimbData();

            void traceAndCommitPathPlan(uint x, uint y, uint x2, uint y2, int param_5);

            dword doPathfinding(int param_1, int param_2);

            undefined4 retraceAndCommitPathPlan();
        };

        static_assert_cpp98_obj(sizeof(PathFindingState) == 837232, PathFindingState);

#pragma pack(pop)

        MACRO_STRUCT_RESOLVER(PathFindingState, false, Address::SHC_3BB0A8C1_0x012BB8C8) pDAT_PathFindingState;

    } // namespace Navigation
} // namespace Map
} // namespace OpenSHC
