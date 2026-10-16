#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Game::GameMode2;
        using Map::Units::Behavior::UnitStanceEnum;
        using Map::Units::Instructions::UnitMatchSpeedEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051CF90
        void TroopValueState::trySendMacemenTribeToAttack()
        {
            int _unitID;
            int _playerID = DAT_TroopValueState::instance.attackInfo.playerID_0x2c850;
            if (0 < DAT_TroopValueState::instance.attackInfo.macemenTribeCount
                && 3 < (int)DAT_TroopValueState::instance.attackInfo.attackInfoTickWrapCount
                && !((byte)SEC_RNG::instance.currentNumber2 & 7)) {
                int _macemen = DAT_TroopValueState::instance.attackInfo
                                   .macemenTribeArray[DAT_TroopValueState::instance.attackInfo.macemenTribeCount + -1];
                bool bVar1 = DAT_GameCore::instance.gameMode_2 != Game::GM_CAMPAIGN_MISSION;
                DAT_TroopValueState::instance.attackInfo.macemenTribeCount
                    = DAT_TroopValueState::instance.attackInfo.macemenTribeCount + -1;
                DAT_TribesState::instance.tribes[_macemen].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
                if ((bVar1) || (0xe < DAT_GameCore::instance.missionNumber1to20)) {
                    _unitID = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getLivingSelectableUnit, DAT_UnitsState::ptr)(_playerID);
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                        _macemen, (uint)(DAT_UnitsState::instance.units[_unitID].x),
                        (uint)(DAT_UnitsState::instance.units[_unitID].y), 0, 0, Map::Units::Instructions::UMSE_0);
                }
            }
        }

    }
}
}
