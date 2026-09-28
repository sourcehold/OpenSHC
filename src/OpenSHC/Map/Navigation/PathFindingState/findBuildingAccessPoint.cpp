#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Map/Navigation/Algorithms/XYPair.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
            using OpenSHC::Map::Navigation::Algorithms::XYPair;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          Function Summary: Find Building Access Point   This function solves the problem: "Where should a unit walk to
          interact with this building?"   What It Does:   Phase 1: Find All Valid Access Points      Iterates through
          predefined perimeter positions around the building   Validates each position with three checks:      Height
          Check #1: Access tile within 32 units of building foundation   Navigation Check: Unit can path to this area
          Height Check #2: Access tile within 16 units of building's terrain height            Phase 2: Choose Closest
          Valid Point   3. Calculates distance from unit to each valid access point   4. Returns the closest one       *
          Finds the best accessible tile for a unit to approach a building.    * This function determines where a unit
          should walk to interact with a building    *     * Algorithm:    * 1. Get all potential access points around
          the building perimeter    * 2. Filter by height compatibility (< 32 units from building base, < 16 from
          terrain)    * 3. Filter by navigation area connectivity    * 4. Choose the closest valid access point to the
          unit    *     * @param this - PathFindingState object pointer    * @param unitID - ID of the unit trying to
          access the building    * @param buildingID - ID of the target building    * @param param_3 - Output parameter:
          returns the building tile adjacent to access point    * @return Tile index of best access point, or 0 if none
          found      decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A8860
        int PathFindingState::findBuildingAccessPoint(int unitID, int buildingID, int* pResultTile)
        {
            int _buildingX;
            uint _heightDiff;
            int _canNav;
            uint _heightDiff2;
            int _candidate2;
            int _buildingY;
            XYPair* pXVar1;
            uint uVar2;
            int _closestDistance;
            int _closestTile;
            int _entranceCandidate;
            int _counter;
            int _accessibleIndex;
            int _validAccessPointsCount;
            int _limit;
            int _pairsOfAccessAndAdjacent[200][2];
            int _accessibleTilesCount;
            int _yOffset;
            byte _buidingDefHeight;
            uint _buildingSize;
            byte _cHeight;
            ushort _unitArea;
            short _unitOwner;
            /*
              === GET BUILDING INFORMATION ===
             */
            _buildingY = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y;
            _buildingX = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x;
            /*
              Get the default/base height of the building's foundation
             */
            _buidingDefHeight
                = DAT_TileMapState::instance.DefaultHeightLayer[DAT_BuildingsState::instance.buildings[buildingID]
                        .currentTilePositionAdjusted];
            /*
              === GET UNIT INFORMATION ===
             */
            _unitArea = DAT_TileMapState::instance.PathConnectionLayer[DAT_UnitsState::instance.units[unitID].tile];
            _unitOwner = DAT_UnitsState::instance.units[unitID].owner;
            /*
              === GET BUILDING SIZE AND ACCESS POINT COUNT ===
             */
            _buildingSize = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
            /*
              Lookup table: building size -> number of accessible perimeter tiles   Example: 2x2 building has 8 access
              points, etc.
             */
            _accessibleTilesCount = DAT_BuildingDefinedData::instance.BuildingAccessibleTilesCount[_buildingSize];
            /*
              Count of valid access points found
             */
            _validAccessPointsCount = 0;
            /*
              Current access point being checked
             */
            _accessibleIndex = 0;
            /*
              Countdown for loop
             */
            _limit = _accessibleTilesCount;
            if (0 < _accessibleTilesCount) {
                do {
                    /*
                      === PHASE 1: FIND ALL VALID ACCESS POINTS ===      Get the offset for this access point relative
                      to building origin   This iterates through predefined perimeter positions
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBuildingEntrancesOffset,
                        DAT_BuildingsState::ptr)(_buildingSize, 1, _accessibleIndex, 0);
                    _yOffset = DAT_BuildingsState::instance.DAT_TempYOffset;
                    /*
                      Calculate absolute tile position of this access point
                     */
                    _entranceCandidate
                        = DAT_ViewportRenderState::instance
                              .translationMatrix[_buildingY + DAT_BuildingsState::instance.DAT_TempYOffset]
                              .addXgetTile
                        + DAT_BuildingsState::instance.DAT_TempXOffset + _buildingX;
                    /*
                      Get height of the access tile
                     */
                    _cHeight = DAT_TileMapState::instance.HeightLayer[_entranceCandidate];
                    _heightDiff = (uint)_buidingDefHeight - (uint)_cHeight;
                    /*
                      Compute absolute value: abs(_heightDiff) < 32
                     */
                    /*
                      === HEIGHT VALIDATION #1: Building Foundation Height ===   Check if access point is within 32
                      height units of building base
                     */
                    /*
                      === NAVIGATION AREA VALIDATION ===   Check if unit can reach this access point
                     */
                    /*
                      === HEIGHT VALIDATION #2: Building Terrain Height ===   Check if access point is within 16 height
                      units of building's actual terrain   height
                     */
                    if (((int)((_heightDiff ^ (int)_heightDiff >> 0x1f) - ((int)_heightDiff >> 0x1f)) < 32)
                        && ((((int)(short)DAT_TileMapState::instance.PathConnectionLayer[_entranceCandidate]
                                     == (int)(short)_unitArea
                                 || (_canNav = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                                     calculateCanPlayerUnitsNavigateToAreaFromArea,
                                         this)((int)_unitOwner, (dword)((int)((int)(short)_unitArea)),
                                         (dword)((int)((int)(short)
                                                 DAT_TileMapState::instance.PathConnectionLayer[_entranceCandidate])),
                                         0),
                                     _canNav != 0))
                            && (_heightDiff2 = (int)DAT_BuildingsState::instance.buildings[buildingID].terrainHeightUnk
                                    - (uint)_cHeight,
                                uVar2 = (int)_heightDiff2 >> 0x1f, (int)((_heightDiff2 ^ uVar2) - uVar2) < 16)))) {
                        /*
                          === ACCESS POINT IS VALID - ADD TO LIST ===      Store the access tile
                         */
                        _pairsOfAccessAndAdjacent[_validAccessPointsCount][0] = _entranceCandidate;
                        /*
                          Initialize adjacent building tile (will find next)
                         */
                        _pairsOfAccessAndAdjacent[_validAccessPointsCount][1] = 0;
                        /*
                          === FIND ADJACENT BUILDING TILE ===   Search cardinal directions (horizontal first) to find
                          which building tile   is adjacent to this access point
                         */
                        pXVar1 = DAT_ClimbLogicDefinedData::instance.CardinalHorizontalFirstSearchOrder;
                        do {
                            _candidate2
                                = DAT_ViewportRenderState::instance.translationMatrix[pXVar1->y + _yOffset + _buildingY]
                                      .addXgetTile
                                + pXVar1->x + DAT_BuildingsState::instance.DAT_TempXOffset + _buildingX;
                            /*
                              Check if this tile belongs to our building
                             */
                            if (DAT_TileMapState::instance.BuildingLayer[_candidate2] == buildingID) {
                                /*
                                  Found it! Store the building tile adjacent to the access point
                                 */
                                _pairsOfAccessAndAdjacent[_validAccessPointsCount][1] = _candidate2;
                                break;
                            }
                            pXVar1 = pXVar1 + 1;
                            /*
                              Check all cardinal directions
                             */
                        } while ((int)pXVar1 < 0xb39238);
                        /*
                          Increment valid access point count
                         */
                        _validAccessPointsCount = _validAccessPointsCount + 1;
                    }
                    /*
                      Move to next access point
                     */
                    _accessibleIndex = _accessibleIndex + 1;
                    if (_accessibleTilesCount <= _accessibleIndex) {
                        _accessibleIndex = 0;
                    }
                    _limit = _limit + -1;
                } while (_limit != 0);
            }
            /*
              === PHASE 2: CHOOSE CLOSEST ACCESS POINT ===   Loop counter
             */
            _counter = 0;
            /*
              Index of best access point (-1 = none found)
             */
            _closestTile = -1;
            /*
              Initialize output parameter
             */
            *pResultTile = 0;
            /*
              Best distance so far (initialized to very large)
             */
            _closestDistance = 10000;
            /*
              If we found any valid access points
             */
            if (0 < _validAccessPointsCount) {
                do {
                    /*
                      === CALCULATE DISTANCE FROM UNIT TO ACCESS POINT ===      Convert tile index back to X,Y
                      coordinates
                     */
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[unitID].x,
                        (int)((int)(DAT_UnitsState::instance.units[unitID].y)),
                        _pairsOfAccessAndAdjacent[_counter][0]
                            - DAT_ViewportRenderState::instance
                                .translationMatrix[DAT_ViewportRenderState::instance
                                        .tileTranslationMatrix_YComponent[_pairsOfAccessAndAdjacent[_counter][0]]]
                                .addXgetTile,
                        (int)((int)(DAT_ViewportRenderState::instance
                                .tileTranslationMatrix_YComponent[_pairsOfAccessAndAdjacent[_counter][0]])));
                    /*
                      If this access point is closer than previous best
                     */
                    if (DAT_DirectionAlgorithmState::instance.distanceHigh < _closestDistance) {
                        /*
                          Update best distance
                         */
                        /*
                          Remember this index
                         */
                        _closestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                        _closestTile = _counter;
                    }
                    _counter = _counter + 1;
                } while (_counter < _validAccessPointsCount);
                /*
                  === RETURN BEST ACCESS POINT ===
                 */
                if (_closestTile != -1) {
                    /*
                      Set output parameter: adjacent building tile
                     */
                    *pResultTile = _pairsOfAccessAndAdjacent[_closestTile][1];
                    /*
                      Return: access point tile
                     */
                    return _pairsOfAccessAndAdjacent[_closestTile][0];
                }
            }
            /*
              No valid access points found
             */
            return 0;
        }

    }
}
}
