#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
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
            bool bVar1;
            int _playerID;
            int _macemen;
            _playerID = this->attackInfo.playerID_0x2c850;
            if (((0 < this->attackInfo.macemenTribeCount) && (3 < (int)this->attackInfo.field_0x2c854))
                && (!((byte)SEC_RNG::instance.currentNumber2 & 7))) {
                _macemen = this->attackInfo.macemenTribeArray[this->attackInfo.macemenTribeCount + -1];
                bVar1 = DAT_GameCore::instance.gameMode_2 != Game::GM_CAMPAIGN_MISSION;
                this->attackInfo.macemenTribeCount = this->attackInfo.macemenTribeCount + -1;
                DAT_TribesState::instance.tribes[_macemen].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
                if ((bVar1) || (0xe < DAT_GameCore::instance.missionNumber1to20)) {
                    _unitID = MACRO_CALL_MEMBER(
                        Map::Units::UnitsState_Func::getLivingSelectableUnit, DAT_UnitsState::ptr)(_playerID);
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction,
                        DAT_TribesState::ptr)(_macemen, (uint)((int)((int)DAT_UnitsState::instance.units[_unitID].x)),
                        (uint)((int)((int)DAT_UnitsState::instance.units[_unitID].y)), 0, 0,
                        Map::Units::Instructions::UMSE_0);
                }
            }
        }

    }
}
}
