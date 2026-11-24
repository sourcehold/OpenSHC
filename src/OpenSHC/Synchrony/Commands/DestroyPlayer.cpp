// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../Commands.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x0048A8A0
    void Commands::DestroyPlayer()
    {
        // the player's slot and the number of the connection text
        DAT_GameSynchronyState::instance.DAT_CommandSize = 4;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 2,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 2,
                OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        short readBuffer;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&readBuffer, 2, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = readBuffer;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&readBuffer, 2, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = readBuffer;
        DAT_GameSynchronyState::instance.unknownIncrementBy40_01 -= 40;
        if (DAT_GameSynchronyState::instance
                    .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                != -1
            && DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
            // another player leaves: out of the session, out of the game and out of the lobby's lists
            if (DAT_GameSynchronyState::instance.DPLAYX_4A != NULL) {
                DAT_GameSynchronyState::instance.DPLAYX_4A->DestroyPlayer(DAT_GameSynchronyState::instance
                        .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]);
            }
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::destroyPlayerCompletely, DAT_GameState::ptr)(
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
            int const playerID = DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
            int const lordID = DAT_GameState::instance.playerDataArray[playerID].lordID;
            if (DAT_UnitsState::instance.units[lordID].uid
                == DAT_GameState::instance.playerDataArray[playerID].lordUID) {
                DAT_UnitsState::instance.units[lordID].lastEncounteredEnemyPlayerID = 0;
            }
            // these two read the slot from the parameter, the three after them from the local (the local or the
            // parameter in all five loses the match)
            DAT_GameSynchronyState::instance
                .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam0] = -1;
            DAT_GameSynchronyState::instance
                .DAT_PlayerSlotArraySomeValue[DAT_GameSynchronyState::instance.DAT_GameCommandParam0] = 0;
            DAT_GameSynchronyState::instance.isIncludedPlayer[playerID] = FALSE;
            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[playerID] = 0;
            DAT_GameSynchronyState::instance.DAT_MultiplayerGameVersions[playerID] = 0;
            // "has left the game"
            strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 89));
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 0);
            DAT_GameSynchronyState::instance.DAT_PlayerNames[DAT_GameSynchronyState::instance.DAT_GameCommandParam0][0]
                = '\0';
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                == DAT_GameSynchronyState::instance.currentPlayerSlotID
            && !DAT_GameSynchronyState::instance.connectionNoticeShown) {
            // this machine is the one removed: it shows the connection text once
            DAT_GameSynchronyState::instance.connectionNoticeShown = 1;
            strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION,
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1));
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, 0);
        }
    }

}
}
