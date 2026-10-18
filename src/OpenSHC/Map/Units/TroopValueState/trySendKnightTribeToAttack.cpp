#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

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

        using Map::Units::Behavior::UnitStanceEnum;
        using Map::Units::Instructions::UnitMatchSpeedEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051D020
        void TroopValueState::trySendKnightTribeToAttack()
        {
            int _unitID = DAT_TroopValueState::instance.attackInfo.playerID_0x2c850;
            if (0 < DAT_TroopValueState::instance.attackInfo.knightTribeCount
                && 10 <= (int)DAT_TroopValueState::instance.attackInfo.attackInfoTickWrapCount
                && (100 <= (int)DAT_TroopValueState::instance.attackInfo.attackInfoTickWrapCount
                    || (0 < DAT_GameState::instance.playerDataArray[_unitID].previousSiegeWeaponsCount))
                && !((byte)SEC_RNG::instance.currentNumber2 & 7)) {
                int const _siegeWeaponsCount
                    = DAT_GameState::instance.playerDataArray[_unitID].previousSiegeWeaponsCount;
                DAT_TroopValueState::instance.attackInfo.knightTribeCount
                    = DAT_TroopValueState::instance.attackInfo.knightTribeCount + -1;
                int tribeID = DAT_TroopValueState::instance.attackInfo
                                  .knightTribeArray[DAT_TroopValueState::instance.attackInfo.knightTribeCount];
                DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
                if (_siegeWeaponsCount) {
                    _unitID = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::findActiveSiegeEngineForTribe, DAT_UnitsState::ptr)(_unitID);
                } else {
                    _unitID = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getLivingSelectableUnit, DAT_UnitsState::ptr)(_unitID);
                }
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(tribeID,
                    (uint)(DAT_UnitsState::instance.units[_unitID].x),
                    (uint)(DAT_UnitsState::instance.units[_unitID].y), 0, 0, Map::Units::Instructions::UMSE_0);
            }
        }

    }
}
}
