#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D020
        void TroopValueState::trySendKnightTribeToAttack()
        {
            int const playerID = DAT_TroopValueState::instance.attackInfo.playerID_0x2c850;
            if (DAT_TroopValueState::instance.attackInfo.knightTribeCount <= 0
                || (int)DAT_TroopValueState::instance.attackInfo.attackInfoTickWrapCount < 10
                || ((int)DAT_TroopValueState::instance.attackInfo.attackInfoTickWrapCount < 100
                    && DAT_GameState::instance.playerDataArray[playerID].previousSiegeWeaponsCount <= 0)
                || ((byte)SEC_RNG::instance.currentNumber2 & 7)) {
                return;
            }
            int const siegeWeaponsCount = DAT_GameState::instance.playerDataArray[playerID].previousSiegeWeaponsCount;
            --DAT_TroopValueState::instance.attackInfo.knightTribeCount;
            int const tribeID = DAT_TroopValueState::instance.attackInfo
                                    .knightTribeArray[DAT_TroopValueState::instance.attackInfo.knightTribeCount];
            DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
            int unitID;
            if (siegeWeaponsCount) {
                unitID = MACRO_CALL_MEMBER(
                    Map::Units::UnitsState_Func::findActiveSiegeEngineForTribe, DAT_UnitsState::ptr)(playerID);
            } else {
                unitID = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::getLivingSelectableUnit, DAT_UnitsState::ptr)(
                    playerID);
            }
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, 0, 0,
                Map::Units::Instructions::UMSE_0);
        }

    }
}
}
