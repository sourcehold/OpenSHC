#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "../TroopValueState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051F5C0
        void TroopValueState::scanForSiegeTentPoints()
        {
            int _flatTileCount;
            int _neighbourTile;
            uint _x;
            uint _y;
            int _candidateTile;
            int _innerDirection;
            int _outerDirection;
            int _index;
            DAT_TroopValueState::instance.attackInfo.tentPoints = 0;
            for (_candidateTile = 0; _candidateTile < 80400; _candidateTile = _candidateTile + 1) {
                if ((DAT_TileMapState::instance.AIInfoLayer[_candidateTile] == '\b')
                    && (_flatTileCount = 0, DAT_TileMapState::instance.UnitLayer[_candidateTile] == 0)) {
                    _y = (uint)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_candidateTile];
                    uint const _baseHeight = (uint)DAT_TileMapState::instance.HeightLayer[_candidateTile];
                    for (_outerDirection = 0; _outerDirection < 8; _outerDirection++) {
                        uint _neighbourHeight = (uint)DAT_TileMapState::instance
                                                    .HeightLayer[DAT_TileMapState::instance
                                                                     .directionTranslationMatrix[_y][_outerDirection]
                                                        + _candidateTile];
                        _neighbourTile = DAT_TileMapState::instance.directionTranslationMatrix[_y][_outerDirection]
                            + _candidateTile;
                        if ((int)_neighbourHeight > (int)(_baseHeight + 6)
                            || (int)_neighbourHeight < (int)(_baseHeight - 6)
                            || DAT_TileMapState::instance.UnitLayer[_neighbourTile] != 0
                            || this->attackInfo.startCon
                                != (short)DAT_TileMapState::instance.PathConnectionLayer[_neighbourTile]
                            || (DAT_TileMapState::instance.LogicLayer[_neighbourTile] & 0xa0002400U)) {
                            break;
                        }
                        _neighbourHeight = _baseHeight + 8;
                        _innerDirection = 0;
                        do {
                            uint _neighbourValue = (uint)DAT_TileMapState::instance
                                                       .HeightLayer[DAT_TileMapState::instance
                                                                        .directionTranslationMatrix[_y][_innerDirection]
                                                           + _neighbourTile];
                            int _innerNeighbourTile
                                = DAT_TileMapState::instance.directionTranslationMatrix[_y][_innerDirection]
                                + _neighbourTile;
                            if ((int)_neighbourValue > (int)_neighbourHeight
                                || (int)_neighbourValue < (int)(_baseHeight - 8)
                                || DAT_TileMapState::instance.UnitLayer[_innerNeighbourTile] != 0
                                || this->attackInfo.startCon
                                    != (short)DAT_TileMapState::instance.PathConnectionLayer[_innerNeighbourTile]
                                || (DAT_TileMapState::instance.LogicLayer[_innerNeighbourTile] & 0xa0002400U)) {
                                break;
                            }
                            _neighbourValue = (uint)DAT_TileMapState::instance
                                                  .HeightLayer[DAT_TileMapState::instance
                                                                   .directionTranslationMatrix[_y][_innerDirection + 1]
                                                      + _neighbourTile];
                            _innerNeighbourTile
                                = DAT_TileMapState::instance.directionTranslationMatrix[_y][_innerDirection + 1]
                                + _neighbourTile;
                            if ((int)_neighbourValue > (int)_neighbourHeight
                                || (int)_neighbourValue < (int)(_baseHeight - 8)
                                || DAT_TileMapState::instance.UnitLayer[_innerNeighbourTile] != 0
                                || this->attackInfo.startCon
                                    != (short)DAT_TileMapState::instance.PathConnectionLayer[_innerNeighbourTile]
                                || (_neighbourValue = DAT_TileMapState::instance.LogicLayer[_innerNeighbourTile],
                                    (_neighbourValue & 0x2000) != 0 || ((_neighbourValue & 0x20000000)))
                                || (int)_neighbourValue < 0 || (_neighbourValue & 0x400)) {
                                _flatTileCount = _flatTileCount + 1;
                                break;
                            }
                            _neighbourValue = (uint)DAT_TileMapState::instance
                                                  .HeightLayer[DAT_TileMapState::instance
                                                                   .directionTranslationMatrix[_y][_innerDirection + 2]
                                                      + _neighbourTile];
                            _innerNeighbourTile
                                = DAT_TileMapState::instance.directionTranslationMatrix[_y][_innerDirection + 2]
                                + _neighbourTile;
                            if ((int)_neighbourValue > (int)_neighbourHeight
                                || (int)_neighbourValue < (int)(_baseHeight - 8)
                                || DAT_TileMapState::instance.UnitLayer[_innerNeighbourTile] != 0
                                || this->attackInfo.startCon
                                    != (short)DAT_TileMapState::instance.PathConnectionLayer[_innerNeighbourTile]
                                || (_neighbourValue = DAT_TileMapState::instance.LogicLayer[_innerNeighbourTile],
                                    (_neighbourValue & 0x2000) != 0)
                                || (_neighbourValue & 0x20000000) || (int)_neighbourValue < 0
                                || (_neighbourValue & 0x400)) {
                                _flatTileCount = _flatTileCount + 2;
                                break;
                            }
                            _neighbourValue = (uint)DAT_TileMapState::instance
                                                  .HeightLayer[DAT_TileMapState::instance
                                                                   .directionTranslationMatrix[_y][_innerDirection + 3]
                                                      + _neighbourTile];
                            _innerNeighbourTile
                                = DAT_TileMapState::instance.directionTranslationMatrix[_y][_innerDirection + 3]
                                + _neighbourTile;
                            if ((int)_neighbourValue > (int)_neighbourHeight
                                || (int)_neighbourValue < (int)(_baseHeight - 8)
                                || DAT_TileMapState::instance.UnitLayer[_innerNeighbourTile] != 0
                                || this->attackInfo.startCon
                                    != (short)DAT_TileMapState::instance.PathConnectionLayer[_innerNeighbourTile]
                                || (_neighbourValue = DAT_TileMapState::instance.LogicLayer[_innerNeighbourTile],
                                    (_neighbourValue & 0x2000) != 0)
                                || (_neighbourValue & 0x20000000) || (int)_neighbourValue < 0
                                || (_neighbourValue & 0x400)) {
                                _flatTileCount = _flatTileCount + 3;
                                break;
                            }
                            _innerDirection = _innerDirection + 4;
                            _flatTileCount = _flatTileCount + 4;
                        } while (_innerDirection < 8);
                    }
                    if (63 < _flatTileCount) {
                        _x = _candidateTile - DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile;
                        BOOLEnum hasTentZoneFlag
                            = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::findAIZoneWithFlags,
                                DAT_PathFindingState::ptr)(6, _x, _y, 0x80);
                        if (!hasTentZoneFlag) {
                            DAT_TileMapState::instance.AIInfoLayer[_candidateTile]
                                = DAT_TileMapState::instance.AIInfoLayer[_candidateTile] | 0x80;
                            int _sIndex = MACRO_CALL_MEMBER(
                                Map::Units::TroopValueState_Func::getSiegeIndexForTile, this)(_candidateTile);
                            _index = DAT_TroopValueState::instance.attackInfo.tentPointsNext;
                            if (_sIndex) {
                                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_sIndex].someCounter
                                    = DAT_TroopValueState::instance.attackInfo.someCounter1;
                            } else {
                                DAT_TroopValueState::instance.attackInfo
                                    .tentPointsValues[DAT_TroopValueState::instance.attackInfo.tentPointsNext]
                                    .x = _x;
                                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_index].y = _y;
                                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_index].tile = _candidateTile;
                                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_index].someCounter
                                    = DAT_TroopValueState::instance.attackInfo.someCounter1;
                                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_index].zero = 0;
                                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_index].three = 0;
                                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_index].tribeUID = 0;
                                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_index].tribeID = 0;
                            }
                            DAT_TroopValueState::instance.attackInfo.tentPoints
                                = DAT_TroopValueState::instance.attackInfo.tentPoints + 1;
                            if (2000 <= DAT_TroopValueState::instance.attackInfo.tentPoints) {
                                return;
                            }
                        }
                    }
                }
            }
        }

    }
}
}
