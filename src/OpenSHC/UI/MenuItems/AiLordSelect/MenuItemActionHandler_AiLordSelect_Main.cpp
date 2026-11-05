#include "../AiLordSelect.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LobbyAddAICurrentlyHoveredAI.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004AE7D0
        void AiLordSelect::MenuItemActionHandler_AiLordSelect_Main(int buttonID, ...)
        {
            if (buttonID == 100) {
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
                return;
            }
            if (buttonID > DAT_GameCore::instance.numOfAIsWithCastleUnk) {
                return;
            }
            DAT_LobbyAddAICurrentlyHoveredAI::instance = DAT_GameCore::instance.arrayOfLordIdsWithAIVsUnk[buttonID - 1];
            int slot = 0;
            // player slots 1 to 8 (0 is unused): the original compares with <= 8, which countof() would change
            for (int candidate = 1; candidate <= 8; ++candidate) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[candidate] == -1
                    && DAT_GameSynchronyState::instance.currentAIArray[candidate] == 0) {
                    slot = candidate;
                    break;
                }
            }
            if (slot == 0) {
                DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
                return;
            }
            DAT_GameSynchronyState::instance.currentAIArray[slot] = DAT_LobbyAddAICurrentlyHoveredAI::instance;
            MACRO_CALL(OpenSHC::Synchrony_Func::ResetAiVariationArrayValue)(slot);
            DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[slot] = 1;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = slot;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                OpenSHC::Commands::GCT_UNKNOWN_112);
            DAT_GameSynchronyState::instance.reparseMaps = TRUE;
            // message 22: the lord's line when he is added to the lobby
            MACRO_CALL(OpenSHC::UI::Helpers_Func::PlayAMessageFromAI)(
                DAT_GameSynchronyState::instance.currentAIArray[slot], 22);
            MACRO_CALL_MEMBER(
                OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions, DAT_GameSynchronyState::ptr)();
            int occupied = 0;
            // slots 1 to 8 again, compared with <= 8 as above
            for (int candidate = 1; candidate <= 8; ++candidate) {
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[candidate] != -1
                    || DAT_GameSynchronyState::instance.currentAIArray[candidate] != 0) {
                    ++occupied;
                }
            }
            if (occupied != 8) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
            DAT_MenuModalComposition1::instance.activeModalDialogID = OpenSHC::UI::Enums::MMT_NONE;
        }

    }
}
}
