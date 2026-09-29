#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00530310
        void UnitsState::triggerDeathAnimationForAllWildlife()
        {
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                return;
            }
            for (int unitID = 1; unitID < (int)this->maxUnitCount; ++unitID) {
                if (this->units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[unitID].dying != 0) {
                    continue;
                }
                if (this->units[unitID].owner != 0) {
                    continue;
                }
                if (this->units[unitID].unitType == OpenSHC::Map::Units::UT_ANTELOPESHDEER
                    || this->units[unitID].unitType == OpenSHC::Map::Units::UT_LIONSHWOLF
                    || this->units[unitID].unitType == OpenSHC::Map::Units::UT_CAMELSHBEAR
                    || this->units[unitID].unitType == OpenSHC::Map::Units::UT_RABBIT) {
                    this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_STONE_DEATH_01;
                    this->units[unitID].animationCycleNumber = 0;
                    this->units[unitID].dying = 1;
                }
            }
        }

    }
}
}
