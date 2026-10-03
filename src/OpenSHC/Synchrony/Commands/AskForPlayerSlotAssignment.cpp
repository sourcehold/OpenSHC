#include "../../Synchrony.func.hpp"
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
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::Commands::GameCommandType;
    using OpenSHC::Game::GameMode;
    using OpenSHC::UI::Enums::MenuViewType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      also called on Option menu   decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0048F870
    void Commands::AskForPlayerSlotAssignment()
    {
        char _commandSenderIsHost;
        int _commandOriginPlayer;
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
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[0] = -1;
                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] = -1;
                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] = -1;
                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] = -1;
                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] = -1;
                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] = -1;
                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] = -1;
                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] = -1;
                DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] = 1;
                MACRO_CALL(OpenSHC::OS_Func::_memcpy)(
                    (void*)((int)DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94 + 0x29400),
                    (void*)((DAT_GameCore::instance.lordIconUnk + -2) * 0x2100
                        + (int)DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94),
                    0x2100);
                DAT_TextureRenderCoreObject::instance
                    .field69_0x98[DAT_GameSynchronyState::instance.currentPlayerSlotID + 0x13] = 0x2100;
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&_commandSenderIsHost, 1,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            if (_commandSenderIsHost != '\0') {
                DAT_GameSynchronyState::instance.DAT_TwoIfNotHost = 2;
            }
            if (DAT_GameSynchronyState::instance.isHost != FALSE) {
                _commandOriginPlayer = DAT_GameSynchronyState::instance.DPLAYX_ReceivedPlayerID;
                /*
                  we are host
                 */
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                    _commandOriginPlayer = 1;
                    /*
                      single player code
                     */
                }
                DAT_GameSynchronyState::instance.protocolInvokerPlayerID
                    = MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::addPlayerToCurrentPlayerArray,
                        DAT_GameSynchronyState::ptr)(_commandOriginPlayer);
                MACRO_CALL(OpenSHC::Synchrony_Func::PutPlayerIntoRandomSlot)(
                    DAT_GameSynchronyState::instance.protocolInvokerPlayerID);
                _commandOriginPlayer = DAT_GameSynchronyState::instance.protocolInvokerPlayerID;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::clearGameCommandEntry,
                    DAT_GameSynchronyState::ptr)(DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID);
                DAT_GameSynchronyState::instance.protocolInvokerPlayerID = _commandOriginPlayer;
                if (DAT_GameSynchronyState::instance.currentPlayerSlotID == 0) {
                    DAT_GameSynchronyState::instance.currentPlayerSlotID = _commandOriginPlayer;
                    if (DAT_GameCore::instance.lordIconUnk >= 2) {
                        MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                            DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_SHARE_AIV_HASH);
                    }
                    MACRO_CALL(OpenSHC::OS_Func::_memcpy)(
                        (void*)((DAT_GameSynchronyState::instance.currentPlayerSlotID + 0x13) * 0x2100
                            + (int)DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94),
                        (void*)((DAT_GameCore::instance.lordIconUnk + -2) * 0x2100
                            + (int)DAT_TextureRenderCoreObject::instance.bitmapsFaces_0x94),
                        0x2100);
                    DAT_TextureRenderCoreObject::instance
                        .field69_0x98[DAT_GameSynchronyState::instance.currentPlayerSlotID + 0x13] = 0x2100;
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_ASSIGN_PLAYERID_TO_PLAYER_SLOT);
                }
                DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[_commandOriginPlayer] = 0;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_HOST_SHARE_LOBBY_STATE);
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = 1;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_TRIGGER_LOBBY_PLAYER_INFORMATION_REFRESH);
                if ((DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_CRUSADE_MISSION_INTRO)
                    || (-1 < DAT_GameCore::instance.menuSwitchDelay)) {
                    MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                        DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_CHANGE_MAP_SELECTION);
                }
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                    DAT_GameSynchronyState::ptr)();
                DAT_GameSynchronyState::instance.reparseMaps = TRUE;
            }
        }
    }

}
}
