#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Location/Point8IntXY.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {
        using OpenSHC::Map::Location::Point8IntXY;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004974D0
        BOOL PathFindingState::findNeighbourTileThatCanServeAsClimbPointClosestToXY(uint x, uint y, uint x2, uint y2)
        {
            int iVar2;
            int (*paiVar3)[8];
            int _candidate2;
            int _tile2;
            uint _c2Height;
            int* piVar4;
            int _minDistance;
            BOOL _status;
            ushort _area1;
            uint uVar1 = y2;
            if (399 < x || 399 < y || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return 0;
            }
            if (x2 < 400 && y2 < 400 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y2 * 400 + x2] != '\0') {
                _tile2 = DAT_ViewportRenderState::instance.translationMatrix[y2].addXgetTile + x2;
                /*
                  height 2
                 */
                y2 = (uint)DAT_TileMapState::instance.HeightLayer[_tile2];
                _area1
                    = DAT_TileMapState::instance
                          .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
                _status = 0;
                _minDistance = 1000;
                if (DAT_TileMapState::instance.BuildingLayer[_tile2] != 0) {
                    /*
                      add building height to height2
                     */
                    iVar2 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                        DAT_BuildingsState::ptr)((int)DAT_TileMapState::instance.BuildingLayer[_tile2]);
                    y2 = y2 + iVar2;
                }
                paiVar3 = DAT_TileMapState::instance.directionTranslationMatrix + uVar1;
                piVar4 = &DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[0].int_.yOffset;
                do {
                    /*
                      for each direction relative to tile 2, do
                     */
                    _candidate2 = (*paiVar3)[0] + _tile2;
                    if ((DAT_TileMapState::instance.PathConnectionLayer[_candidate2] == _area1)
                        && (DAT_TileMapState::instance.UnitLayer[_candidate2] == 0)) {
                        /*
                          area is same as area1, no units on this tile   compute the total height at this candidate tile
                         */
                        _c2Height = (uint)DAT_TileMapState::instance.HeightLayer[_candidate2];
                        if (DAT_TileMapState::instance.BuildingLayer[_candidate2] != 0) {
                            iVar2 = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                DAT_BuildingsState::ptr)((int)DAT_TileMapState::instance.BuildingLayer[_candidate2]);
                            _c2Height = _c2Height + iVar2;
                        }
                        if ((int)y2 <= (int)(_c2Height + 16) && (int)(_c2Height - 4294967280) <= (int)y2) {
                            /*
                              if the height of this candidate tile is within 16 of the tile2 height   then, compute the
                              distance between x,y and the candidate2 tile
                             */
                            MACRO_CALL_MEMBER(
                                OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                                DAT_DirectionAlgorithmState::ptr)(x, (int)(y),
                                (int)(((Point8IntXY*)(piVar4 + -1))->xOffset + x2), (int)(*piVar4 + uVar1));
                            if (DAT_DirectionAlgorithmState::instance.distanceHigh < _minDistance) {
                                this->climbX = ((Point8IntXY*)(piVar4 + -1))->xOffset + x2;
                                _minDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                                this->climbY = *piVar4 + uVar1;
                                _status = 1;
                            }
                        }
                    }
                    paiVar3 = (int (*)[8])(*paiVar3 + 1);
                    piVar4 = piVar4 + 2;
                } while ((int)piVar4 < 0xb4908c);
                return _status;
            }
            return 0;
        }

    }
}
}
