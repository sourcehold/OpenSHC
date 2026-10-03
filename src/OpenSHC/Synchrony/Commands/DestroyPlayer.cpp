#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      called in multiplayer error: 0x4D   Stronghold 1: KickMPPlayer   decompilerscript: committed: 2025-01-30
      21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0048A8A0
    void Commands::DestroyPlayer()
    {
        char cVar1;
        int iVar2;
        char* pcVar3;
        char* pcVar4;
        short local_4[2];
        int _playerID;
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
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(local_4, 2, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = (int)local_4[0];
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(local_4, 2, OpenSHC::Commands::GCPL_DYNAMIC_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = (int)local_4[0];
            DAT_GameSynchronyState::instance.unknownIncrementBy40_01
                = DAT_GameSynchronyState::instance.unknownIncrementBy40_01 + -0x28;
            if (DAT_GameSynchronyState::instance
                    .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                == 0xffffffff) {
                if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID) {}
            } else if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                if (DAT_GameSynchronyState::instance.DPLAYX_4A != (IDirectPlay4A**)0x0) {
                    ((IDirectPlay4A*)DAT_GameSynchronyState::instance.DPLAYX_4A)
                        ->DestroyPlayer(DAT_GameSynchronyState::instance
                                .currentPlayerFullIDArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]);
                }
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::destroyPlayerCompletely, DAT_GameState::ptr)(
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
                _playerID = DAT_GameSynchronyState::instance.DAT_GameCommandParam0;
                iVar2 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                            .lordID;
                if (DAT_UnitsState::instance.units[iVar2].uid
                    == DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                        .lordUID) {
                    DAT_UnitsState::instance.units[iVar2].lastEncounteredEnemyPlayerID = 0;
                }
                /*
                  player left
                 */
                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[_playerID] = -1;
                DAT_GameSynchronyState::instance
                    .DAT_PlayerSlotArraySomeValue[DAT_GameSynchronyState::instance.DAT_GameCommandParam0] = 0;
                DAT_GameSynchronyState::instance.isIncludedPlayer[_playerID] = FALSE;
                DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[_playerID] = 0;
                DAT_GameSynchronyState::instance.DAT_MultiplayerGameVersions[_playerID] = 0;
                /*
                  "has left the game"   added by script: "has left the game"
                 */
                pcVar3 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 0x59);
                pcVar4 = DAT_GameSynchronyState::instance.receivedChatMessage;
                do {
                    cVar1 = *pcVar3;
                    *pcVar4 = cVar1;
                    pcVar3 = pcVar3 + 1;
                    pcVar4 = pcVar4 + 1;
                } while (cVar1 != '\0');
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 0);
                DAT_GameSynchronyState::instance
                    .DAT_PlayerNames[DAT_GameSynchronyState::instance.DAT_GameCommandParam0][0] = '\0';
            }
            if (DAT_GameSynchronyState::instance.field261_0x109298 == 0) {
                DAT_GameSynchronyState::instance.field261_0x109298 = 1;
                pcVar3 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION,
                    (int)((int)(DAT_GameSynchronyState::instance.DAT_GameCommandParam1)));
                pcVar4 = DAT_GameSynchronyState::instance.receivedChatMessage;
                do {
                    cVar1 = *pcVar3;
                    *pcVar4 = cVar1;
                    pcVar3 = pcVar3 + 1;
                    pcVar4 = pcVar4 + 1;
                } while (cVar1 != '\0');
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addChatMessageToDisplayList,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID, 0);
            }
        }
    }

}
}
