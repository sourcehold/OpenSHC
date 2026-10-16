#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
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
            int tribeID;
            int iVar1;
            int iVar2;
            iVar2 = this->attackInfo.playerID_0x2c850;
            if ((((0 < this->attackInfo.knightTribeCount) && (9 < (int)this->attackInfo.field_0x2c854))
                    && ((99 < (int)this->attackInfo.field_0x2c854
                        || (0 < DAT_GameState::instance.playerDataArray[this->attackInfo.playerID_0x2c850]
                                .previousSiegeWeaponsCount))))
                && (!((byte)SEC_RNG::instance.currentNumber2 & 7))) {
                tribeID = this->attackInfo.macemenTribeArray[this->attackInfo.knightTribeCount + 99];
                iVar1 = DAT_GameState::instance.playerDataArray[this->attackInfo.playerID_0x2c850]
                            .previousSiegeWeaponsCount;
                this->attackInfo.knightTribeCount = this->attackInfo.knightTribeCount + -1;
                DAT_TribesState::instance.tribes[tribeID].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
                if (!iVar1) {
                    iVar2 = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getLivingSelectableUnit, DAT_UnitsState::ptr)(iVar2);
                } else {
                    iVar2 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::findActiveSiegeEngineForTribe,
                        DAT_UnitsState::ptr)(iVar2);
                }
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction,
                    DAT_TribesState::ptr)(tribeID, (uint)((int)((int)DAT_UnitsState::instance.units[iVar2].x)),
                    (uint)((int)((int)DAT_UnitsState::instance.units[iVar2].y)), 0, 0,
                    Map::Units::Instructions::UMSE_0);
            }
        }

    }
}
}
