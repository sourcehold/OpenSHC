#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00534130
        void UnitsState::applyTunnelDamageAlongPathPlan(uint unitID)
        {
            uint _xPosition = this->units[unitID].ladderExitXPosition;
            uint _yPosition = this->units[unitID].ladderExitYPosition;
            int _tile = this->units[unitID].previousTilePosition;
            for (int _stepIndex = 0; _stepIndex < this->units[unitID].totalSizeOfPathPlan; ++_stepIndex) {
                if ((DAT_TileMapState::instance.LogicLayer[_tile] & 0x20000081U) == 0) {
                    if (DAT_TileMapState::instance.BuildingLayer[_tile] == 0
                        && (DAT_TileMapState::instance.HeightLayer[_tile] < 0x10
                            || DAT_TileMapState::instance.DefaultHeightLayer[_tile] < 0x10)) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::increaseHeightForTunnelWithBrush,
                            DAT_TileMapState::ptr)(_tile, _xPosition, _yPosition, -2);
                        DAT_TileMapState::instance.HeightLayer[_tile] = 0;
                    } else {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::processDamageToBuilding, DAT_TileMapState::ptr)(
                            _tile, _xPosition, _yPosition, 5, 0, this->units[unitID].owner, FALSE, 0);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                        DAT_PathFindingState::ptr)(1, _xPosition, _yPosition);
                }
                uint _packedDirections = (char)this->units[unitID].pathPlanStart[_stepIndex / 2];
                uint _direction;
                if ((_stepIndex & 1) == 0) {
                    _direction = _packedDirections & 0xf;
                } else {
                    _direction = (int)_packedDirections >> 4;
                }
                _xPosition = _xPosition
                    + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.xOffset;
                _tile = _tile + DAT_TileMapState::instance.directionTranslationMatrix[_yPosition][_direction];
                _yPosition = _yPosition
                    + DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].int_.yOffset;
            }
        }

    }
}
}
