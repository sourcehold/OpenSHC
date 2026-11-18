#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/DAT_00b960dc.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042AC90
        void LobbyMenu::MenuItemRenderFunction_LobbyMenu_ChatBox(int buttonID, ...)
        {
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                return;
            }
            if (DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE
                && DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_SEND_MAP_TO
                && DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_RECEIVE_MAP_FROM
                && MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)()) {
                return;
            }
            int const blend = DAT_ButtonBackgroundBlendStrength::instance - 32;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            // Nested, not early returns (early returns: quick_diff 0.9671 -> 0.6184)
            if (buttonID != -3) {
                if (buttonID != -2) {
                    // the waiting room's texts, and for -1 the player's own name
                    if (buttonID != -1) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, buttonID,
                            DAT_ButtonX::instance, DAT_ButtonY::instance + 6, OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_00A2FF, OpenSHC::Rendering::Colors::COL_003E66, 17, FALSE,
                            blend * 32 / 32 + 32);
                        return;
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance
                            .DAT_PlayerNames[DAT_GameSynchronyState::instance.currentPlayerSlotID],
                        DAT_ButtonX::instance, DAT_ButtonY::instance + 6, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_00A2FF, OpenSHC::Rendering::Colors::COL_003E66, 17, FALSE,
                        blend * 32 / 32 + 32);
                    return;
                }
                // -2: the line being typed, with the cursor behind it
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance + 2,
                    DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance - 2,
                    blend * 16 / 32 + 32);
                int const cursorX
                    = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextWidthUntilCurrentCursor,
                        DAT_UserTextHandlerState::ptr)();
                if (DAT_00b960dc::instance == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 6 + cursorX, DAT_ButtonY::instance + 2,
                        DAT_ButtonX::instance + 7 + cursorX, DAT_ButtonH::instance + DAT_ButtonY::instance - 2,
                        COL_DARK_LIME::instance.shortValue);
                }
                // the blend strength read again after the calls (the blend local: quick_diff 0.9671 -> 0.8803)
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getCurrentText,
                                                    DAT_UserTextHandlerState::ptr)(),
                    DAT_ButtonX::instance + 8, DAT_ButtonY::instance + 5, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_FFFFFF, OpenSHC::Rendering::Colors::COL_000000, 19, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                return;
            }
            // -3: the chat messages
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, DAT_ButtonY::instance + 3,
                DAT_ButtonW::instance + DAT_ButtonX::instance, DAT_ButtonH::instance + DAT_ButtonY::instance,
                blend * 16 / 32 + 32);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::renderChatMessageList,
                DAT_GameSynchronyState::ptr)(DAT_ButtonX::instance + 8,
                DAT_ButtonH::instance + DAT_ButtonY::instance - 31, DAT_GameSynchronyState::instance.chatScrollOffset);
        }

    }
}
}
