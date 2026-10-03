#include "../../Synchrony.func.hpp"
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

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::DE::SHCDE::eTextSections;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0048B4E0
    void Commands::VoteKick_SEND_L_E_C_A_F_H_ZAP()
    {
        char cVar1;
        int iVar2;
        int iVar3;
        char* pcVar4;
        char* pcVar5;
        short local_4[2];
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
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(local_4, 2, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = (int)local_4[0];
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(local_4, 2, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = (int)local_4[0];
            if ((DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                    == DAT_GameSynchronyState::instance.currentPlayerSlotID)
                && (DAT_GameSynchronyState::instance.field261_0x109298 == 0)) {
                DAT_GameSynchronyState::instance.field261_0x109298 = 0;
                pcVar4 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION,
                    (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam1)));
                pcVar5 = DAT_GameSynchronyState::instance.receivedChatMessage;
                do {
                    cVar1 = *pcVar4;
                    *pcVar5 = cVar1;
                    pcVar4 = pcVar4 + 1;
                    pcVar5 = pcVar5 + 1;
                } while (cVar1 != '\0');
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, 0);
            }
            if (DAT_GameSynchronyState::instance
                    .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                != 0xffffffff) {
                if (DAT_GameSynchronyState::instance.DPLAYX_4A != (IDirectPlay4A**)0x0) {
                    ((IDirectPlay4A*)DAT_GameSynchronyState::instance.DPLAYX_4A)
                        ->DestroyPlayer(DAT_GameSynchronyState::instance
                                .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]);
                }
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::destroyPlayerCompletely, DAT_GameState::ptr)(
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
                iVar3 = DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
                iVar2 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                            .lordID;
                if (DAT_UnitsState::instance.units[iVar2].uid
                    == DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                        .lordUID) {
                    DAT_UnitsState::instance.units[iVar2].lastEncounteredEnemyPlayerID = 0;
                }
                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar3] = -1;
                DAT_GameSynchronyState::instance
                    .DAT_PlayerSlotArraySomeValue[DAT_GameSynchronyState::instance.DAT_GameCommandParam0] = 0;
                /*
                  added by script: "has left the game"
                 */
                pcVar4 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x59);
                pcVar5 = DAT_GameSynchronyState::instance.receivedChatMessage;
                do {
                    cVar1 = *pcVar4;
                    *pcVar5 = cVar1;
                    pcVar4 = pcVar4 + 1;
                    pcVar5 = pcVar5 + 1;
                } while (cVar1 != '\0');
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 0);
                DAT_GameSynchronyState::instance
                    .DAT_PlayerNames[DAT_GameSynchronyState::instance.DAT_GameCommandParam0][0] = '\0';
                DAT_GameSynchronyState::instance
                    .receivedSyncStatusByPlayerUnk[DAT_GameSynchronyState::instance.DAT_GameCommandParam0] = 2;
                DAT_GameSynchronyState::instance
                    .syncRelatedStatusArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam0] = 1;
            }
        }
    }

}
}
