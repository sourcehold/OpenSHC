#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00530650
        void UnitsState::makeUnitsDisappearThatCannotReachTheKeep(int playerID)
        {
            dword _areaOfKeep
                = (short)DAT_TileMapState::instance
                      .PathConnectionLayer[DAT_GameState::instance.playerDataArray[playerID].campground.tileEntry];
            for (int unitID = 1; unitID < (int)this->maxUnitCount; ++unitID) {
                if (this->units[unitID].owner != playerID) {
                    continue;
                }
                if (this->units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[unitID].isSelectable_OR_matchTime != 0) {
                    continue;
                }
                if (this->units[unitID].dying != 0) {
                    continue;
                }
                if (this->units[unitID].isStalked != 0) {
                    continue;
                }
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::calculateCanPlayerUnitsNavigateToAreaFromArea,
                        DAT_PathFindingState::ptr)(playerID, (short)_areaOfKeep,
                        (short)DAT_TileMapState::instance.PathConnectionLayer[this->units[unitID].tile], 0)
                    != 0) {
                    continue;
                }
                this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
                this->units[unitID].animationCycleNumber = 0;
                this->units[unitID].disappearFadeAlphaCountdown = 0;
                this->units[unitID].dying = 1;
            }
        }

    }
}
}
