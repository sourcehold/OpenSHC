#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/Tribes/AITribeType.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::Tribes::AITribeType;
    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Map::Units::SomeTribeBehaviorType;
    using OpenSHC::Map::Units::UnitInstructionType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CF180
    void AICState ::useAITribe_0xe_toPlaceTunnels(int playerID)

    {

        int _aiTribeID;

        uint _unitID;

        int _tribeID;

        int _countdown;

        short _size;

        if (((DAT_GameState::instance.playerDataArray[playerID].aiType != OpenSHC::AI::AIT_NULL)
                && (_aiTribeID = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0xe],
                    _aiTribeID != 0))
            && (DAT_TribesState::instance.tribes[_aiTribeID].uid
                == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0xe])) {

            _size = DAT_TribesState::instance.tribes[_aiTribeID].size;

            for (_countdown = (int)_size; (_size != 0 && (0 < _countdown)); _countdown = _countdown + -1) {

                _unitID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::popUnitFromTribe, DAT_TribesState::ptr)(_aiTribeID);

                _tribeID = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);

                DAT_TribesState::instance.tribes[_tribeID].attackWave
                    = (short)DAT_GameState::instance.playerDataArray[playerID].currentAttackWave;

                DAT_TribesState::instance.tribes[_tribeID].tribeType = OpenSHC::AI::Tribes::AITT_TUNNELERS;

                DAT_TribesState::instance.tribes[_tribeID].tribeBehaviorType = OpenSHC::Map::Units::STBT_0x415;

                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                    _unitID, _tribeID);

                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TroopValueState_Func::
                                      placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers,
                    DAT_TroopValueState::ptr)(_tribeID, OpenSHC::Commands::M_MAPPER_TUNNEL_CONSTRUCTION,
                    (uint)((int)(50)), (UnitInstructionType)((int)(21)));

                _size = DAT_TribesState::instance.tribes[_aiTribeID].size;
            }
        }

        return;
    }

}
}
