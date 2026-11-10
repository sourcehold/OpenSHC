#include "../Helpers.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x00429650
    void Helpers::CallbackSetMultiplayerSpeedLevel()
    {
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            Commands::GCT_CHANGE_GAME_INTENSITY_OR_BALANCE);
        DAT_GameSynchronyState::instance.field_0x1072e8 = -1;
        DAT_GameSynchronyState::instance.field_0x1072ec = -1;
        // "Game Speed"
        MACRO_CALL(OS_Func::_sprintf)(DAT_GameSynchronyState::instance.receivedChatMessage, s__s__d_005a2284,
            MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 82),
            DAT_GameSynchronyState::instance.skirmishGameSpeedLevel);
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(
            DAT_GameSynchronyState::instance.receivedChatMessage);
        // Tell everyone but the player who changed it.
        for (int receiver = 0; receiver < 9; ++receiver) {
            DAT_GameSynchronyState::instance.DAT_ChatMessageReceiverArray[receiver] = 1;
        }
        DAT_GameSynchronyState::instance
            .DAT_ChatMessageReceiverArray[DAT_GameSynchronyState::instance.currentPlayerSlotID] = 0;
        DAT_GameSynchronyState::instance.DAT_ChatTauntOrMessage = 10000;
        MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
            Commands::GCT_TAUNT_OR_CHAT);
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::clearEntry, DAT_UserTextHandlerState::ptr)(
            DAT_UserTextHandlerState::instance.textArrayIndex);
    }

}
}
