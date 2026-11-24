#include "../Commands.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    // one face: 66 rows of 64 pixels of two bytes
    int const FACE_HEIGHT = 66;
    int const FACE_WIDTH = 64;
    int const FACE_SIZE = FACE_HEIGHT * FACE_WIDTH * 2;

    // FUNCTION: STRONGHOLDCRUSADER 0x0048F870
    void Commands::AskForPlayerSlotAssignment()
    {
        DAT_GameSynchronyState::instance.DAT_CommandSize = 1;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.isHost, 1,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan != OpenSHC::Commands::GCS_EXECUTE) {
            return;
        }
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            // alone, the player takes slot 1 and every other slot is empty
            for (int slot = 0; slot < countof(DAT_GameSynchronyState::instance.currentPlayerFullIDArray); ++slot) {
                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[slot] = -1;
            }
            DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
            DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] = 1;
            // the chosen lord's face becomes the slot's face (the players' faces follow the 20 lords' faces; the slots
            // start at 1)
            MACRO_CALL(OpenSHC::OS_Func::_memcpy)(DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94
                    + (DAT_GameSynchronyState::instance.currentPlayerSlotID + 19) * FACE_HEIGHT * FACE_WIDTH,
                DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94
                    + (DAT_GameCore::instance.lordIconUnk - 2) * FACE_HEIGHT * FACE_WIDTH,
                FACE_SIZE);
            DAT_TextureRenderCoreObject::instance
                .bitmapFaceSizes[DAT_GameSynchronyState::instance.currentPlayerSlotID + 19] = FACE_SIZE;
            return;
        }
        char senderIsHost;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
            DAT_GameSynchronyState::ptr)(&senderIsHost, sizeof(senderIsHost),
            OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
        if (senderIsHost) {
            DAT_GameSynchronyState::instance.DAT_TwoIfNotHost = 2;
        }
        if (!DAT_GameSynchronyState::instance.isHost) {
            return;
        }
        // the host gives the sender a slot; in a single player skirmish the sender is player 1
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
            DAT_GameSynchronyState::instance.protocolInvokerPlayerID
                = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addPlayerToCurrentPlayerArray,
                    DAT_GameSynchronyState::ptr)(1);
        } else {
            DAT_GameSynchronyState::instance.protocolInvokerPlayerID
                = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addPlayerToCurrentPlayerArray,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.DPLAYX_ReceivedPlayerID);
        }
        MACRO_CALL(OpenSHC::Synchrony_Func::PutPlayerIntoRandomSlot)(
            DAT_GameSynchronyState::instance.protocolInvokerPlayerID);
        // clearing the command entry must not lose the new slot
        int const senderSlot = DAT_GameSynchronyState::instance.protocolInvokerPlayerID;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::clearGameCommandEntry,
            DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID);
        DAT_GameSynchronyState::instance.protocolInvokerPlayerID = senderSlot;
        if (DAT_GameSynchronyState::instance.currentPlayerSlotID == 0) {
            // the host itself had no slot yet
            DAT_GameSynchronyState::instance.currentPlayerSlotID = senderSlot;
            if (DAT_GameCore::instance.lordIconUnk >= 2) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SHARE_AIV_HASH);
            }
            MACRO_CALL(OpenSHC::OS_Func::_memcpy)(DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94
                    + (DAT_GameSynchronyState::instance.currentPlayerSlotID + 19) * FACE_HEIGHT * FACE_WIDTH,
                DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94
                    + (DAT_GameCore::instance.lordIconUnk - 2) * FACE_HEIGHT * FACE_WIDTH,
                FACE_SIZE);
            DAT_TextureRenderCoreObject::instance
                .bitmapFaceSizes[DAT_GameSynchronyState::instance.currentPlayerSlotID + 19] = FACE_SIZE;
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_ASSIGN_PLAYERID_TO_PLAYER_SLOT);
        }
        DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[senderSlot] = 0;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            OpenSHC::Commands::GCT_HOST_SHARE_LOBBY_STATE);
        DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 1;
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            OpenSHC::Commands::GCT_TRIGGER_LOBBY_PLAYER_INFORMATION_REFRESH);
        if (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_CRUSADE_MISSION_INTRO
            || DAT_GameCore::instance.menuSwitchDelay > -1) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_CHANGE_MAP_SELECTION);
        }
        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            OpenSHC::Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
        MACRO_CALL_MEMBER(
            OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions, DAT_GameSynchronyState::ptr)();
        DAT_GameSynchronyState::instance.reparseMaps = TRUE;
    }

}
}
