#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00537C10
        int UnitsState::findClosestEnemyByAreaAndRange(int range, uint x, uint y, int playerID)
        {
            if (x >= 400 || y >= 400) {
                return 0;
            }
            if (*(char*)(y * 400 + 0x21aec98 + x) == '\0') {
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
                if (this->units[unitID].isStalked != 0) {
                    continue;
                }
                if (DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                    == DAT_GameState::instance.mapAndTime.playerTeams[this->units[unitID].owner]) {
                    continue;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(x, y, this->units[unitID].x, this->units[unitID].y);
                if (DAT_DirectionAlgorithmState::instance.distanceHigh > range) {
                    continue;
                }
                if (DAT_TileMapState::instance.PathConnectionLayer[this->units[unitID].tile] != _areaOfOrigin) {
                    continue;
                }
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
