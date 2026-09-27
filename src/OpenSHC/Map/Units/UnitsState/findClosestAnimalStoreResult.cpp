#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00537AA0
        int UnitsState::findClosestAnimalStoreResult(int maxDistance, BOOLEnum excludeCows, uint x, uint y)
        {
            if (x > 399 || y > 399) {
                return 0;
            }
            if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
                return 0;
            }
            ushort _areaOfOrigin
                = DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
            this->unusedUnitIDArrayIndex = 0;
            int _bestScore = 10000;
            int _bestUnitID = 0;
            for (int unitID = 1; unitID < (int)this->maxUnitCount; ++unitID) {
                if (this->units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[unitID].dying != 0) {
                    continue;
                }
                if (this->units[unitID].unknownTestAgainst0_2 != 0) {
                    continue;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
                    continue;
                }
                if (excludeCows == FALSE) {
                    if (this->units[unitID].unitType != OpenSHC::Map::Units::UT_ANTELOPESHDEER
                        && this->units[unitID].unitType != OpenSHC::Map::Units::UT_RABBIT
                        && this->units[unitID].unitType != OpenSHC::Map::Units::UT_COW) {
                        continue;
                    }
                } else if (this->units[unitID].isStalked != 0) {
                    continue;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(x, y, this->units[unitID].x, this->units[unitID].y);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh > maxDistance) {
                    continue;
                }
                if (DAT_TileMapState::instance.PathConnectionLayer[this->units[unitID].tile] != _areaOfOrigin) {
                    continue;
                }
                this->unusedUnitIDArray[this->unusedUnitIDArrayIndex] = (short)unitID;
                this->unusedUnitIDArrayIndex = this->unusedUnitIDArrayIndex + 1;
                int _score = DAT_DirectionAlgorithmState::instance.distanceHigh + this->units[unitID].huntedBy * 3;
                if (_score < _bestScore) {
                    _bestScore = _score;
                    _bestUnitID = unitID;
                }
            }
            return _bestUnitID;
        }

    }
}
}
