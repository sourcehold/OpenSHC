#include "../AICState.func.hpp"

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

    // FUNCTION: STRONGHOLDCRUSADER 0x004CF180
    void AICState::useAITribe_0xe_toPlaceTunnels(int playerID)
    {
        if (DAT_GameState::instance.playerDataArray[playerID].aiType == OpenSHC::AI::AIT_NULL)
            return;
        int _aiTribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0xe];
        if (_aiTribeID == 0)
            return;
        if (DAT_TribesState::instance.tribes[_aiTribeID].uid
            != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0xe])
            return;
        int _countdown = DAT_TribesState::instance.tribes[_aiTribeID].size;

        while (DAT_TribesState::instance.tribes[_aiTribeID].size != 0) {
            if (_countdown <= 0)
                break;

            int _unitID = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TribesState_Func::popUnitFromTribe, DAT_TribesState::ptr)(_aiTribeID);
            // Yes this line has to be right here for the code to match.
            _countdown--;

            int _tribeID = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TribesState_Func::createTribeForPlayer, DAT_TribesState::ptr)(playerID);

            DAT_TribesState::instance.tribes[_tribeID].attackWave
                = DAT_GameState::instance.playerDataArray[playerID].currentAttackWave;

            DAT_TribesState::instance.tribes[_tribeID].tribeType = OpenSHC::AI::Tribes::AITT_TUNNELERS;

            DAT_TribesState::instance.tribes[_tribeID].tribeBehaviorType = OpenSHC::Map::Units::STBT_0x415;

            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::addUnitToTribe, DAT_TribesState::ptr)(
                _unitID, _tribeID);

            MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TroopValueState_Func::placeSiegeTentOrTunnelAtSuitableLocationAndAssignEngineers,
                DAT_TroopValueState::ptr)(
                _tribeID, OpenSHC::Commands::M_MAPPER_TUNNEL_CONSTRUCTION, 50, (UnitInstructionType)21);
        }
    }

}
}
