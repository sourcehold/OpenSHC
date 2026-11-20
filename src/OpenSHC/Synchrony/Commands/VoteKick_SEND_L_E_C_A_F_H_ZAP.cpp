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

    // FUNCTION: STRONGHOLDCRUSADER 0x0048B4E0
    void Commands::VoteKick_SEND_L_E_C_A_F_H_ZAP()
    {
        DAT_GameSynchronyState::instance.DAT_CommandSize = 4;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 2,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam1, 2,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        short readBuffer;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&readBuffer, 2, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = readBuffer;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&readBuffer, 2, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
            OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = readBuffer;
        if ((DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                == DAT_GameSynchronyState::instance.currentPlayerSlotID)
            && (DAT_GameSynchronyState::instance.connectionNoticeShown == 0)) {
            DAT_GameSynchronyState::instance.connectionNoticeShown = 0;
            strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION,
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam1));
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, 0);
        }
        if (DAT_GameSynchronyState::instance
                .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
            != -1) {
            if (DAT_GameSynchronyState::instance.DPLAYX_4A != NULL) {
                DAT_GameSynchronyState::instance.DPLAYX_4A->DestroyPlayer(DAT_GameSynchronyState::instance
                        .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]);
            }
            MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::destroyPlayerCompletely, DAT_GameState::ptr)(
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
            int const playerID = DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
            int const lordID
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                      .lordID;
            if (DAT_UnitsState::instance.units[lordID].uid
                == DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                    .lordUID) {
                DAT_UnitsState::instance.units[lordID].lastEncounteredEnemyPlayerID = 0;
            }
            DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] = -1;
            DAT_GameSynchronyState::instance
                .DAT_PlayerSlotArraySomeValue[DAT_GameSynchronyState::instance.DAT_GameCommandParam0] = 0;
            // "has left the game"
            strcpy(DAT_GameSynchronyState::instance.receivedChatMessage,
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 89));
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 0);
            DAT_GameSynchronyState::instance.DAT_PlayerNames[DAT_GameSynchronyState::instance.DAT_GameCommandParam0][0]
                = '\0';
            DAT_GameSynchronyState::instance
                .receivedSyncStatusByPlayerUnk[DAT_GameSynchronyState::instance.DAT_GameCommandParam0] = 2;
            DAT_GameSynchronyState::instance
                .syncRelatedStatusArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam0] = 1;
        }
    }

}
}
