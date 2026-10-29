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
        BOOL PathFindingState::findNeighbourTileThatCanServeAsClimbPointClosestToXY(uint ySpace, uint y, uint x2, uint y2)
        {
            if (399 < ySpace || 399 < y) {
                return 0;
            }
            if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + ySpace] == '\0') {
                return 0;
            }
            if (399 < x2 || 399 < y2) {
                return 0;
            }
            if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y2 * 400 + x2] == '\0') {
                return 0;
            }
            int _tile2 = DAT_ViewportRenderState::instance.translationMatrix[y2].addXgetTile + x2;
            int _area1 = (short)DAT_TileMapState::instance
                             .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + ySpace];
            /*
              high 2
             */
            int _height2 = DAT_TileMapState::instance.HeightLayer[_tile2];
            BOOL _status = 0;
            int _minDistance = 1000;
            if (DAT_TileMapState::instance.BuildingLayer[_tile2] != 0) {
                /*
                  add building high to height2
                 */
                _height2 += MACRO_CALL_MEMBER(
                    OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                    DAT_BuildingsState::ptr)((int)DAT_TileMapState::instance.BuildingLayer[_tile2]);
            }
            for (int _direction = 0; _direction < 8; _direction = _direction + 1) {
                /*
                  for each direction relative to tileUnk 2, do
                 */
                int _candidate2 = DAT_TileMapState::instance.directionTranslationMatrix[y2][_direction] + _tile2;
                if ((short)DAT_TileMapState::instance.PathConnectionLayer[_candidate2] == _area1
                    && (short)DAT_TileMapState::instance.UnitLayer[_candidate2] == 0) {
                    /*
                      area is same as area1, no units on this tileUnk   compute the total high at this candidate tileUnk
                     */
                    int _c2Height = DAT_TileMapState::instance.HeightLayer[_candidate2];
                    if (DAT_TileMapState::instance.BuildingLayer[_candidate2] != 0) {
                        _c2Height += MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                            DAT_BuildingsState::ptr)((int)DAT_TileMapState::instance.BuildingLayer[_candidate2]);
                    }
                    if (_height2 <= _c2Height + 16 && _height2 >= _c2Height - 16) {
                        /*
                          if the high of this candidate tileUnk is within 16 of the tile2 high   then, compute the
                          distance between ySpace,y and the candidate2 tileUnk
                         */
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)(ySpace, (int)(y),
                            (int)(DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.xOffset
                                + x2),
                            (int)(DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.yOffset
                                + y2));
                        int _distance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                        if (_distance < _minDistance) {
                            this->climbX
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.xOffset
                                + x2;
                            _minDistance = _distance;
                            this->climbY
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.yOffset
                                + y2;
                            _status = 1;
                        }
                    }
                }
            }
            return _status;
        }

    }
}
}
