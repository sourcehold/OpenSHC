#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Game::GameMode;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042AC90
        void LobbyMenu::MenuItemRenderFunction_LobbyMenu_ChatBox(int param_1, ...)
        {
            BOOLEnum BVar1;
            int iVar2;
            int _widthTillCursor;
            char* textAddress;
            int yParam;
            int xParam;
            TextAlignment alignment;
            uint foregroundColor;
            uint backgroundColor;
            int fontSize;
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER) {
                if ((((DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE)
                         && (DAT_MenuModalComposition1::instance.activeModalDialogID
                             != OpenSHC::UI::Enums::MMT_SEND_MAP_TO))
                        && (DAT_MenuModalComposition1::instance.activeModalDialogID
                            != OpenSHC::UI::Enums::MMT_RECEIVE_MAP_FROM))
                    && (BVar1 = MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)(),
                        BVar1 != FALSE)) {}
                iVar2 = DAT_ButtonBackgroundBlendStrength::instance + -0x20;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if (param_1 != -3) {
                    if (param_1 == -2) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                            DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance + 2)),
                            (int)((int)(DAT_ButtonW::instance + DAT_ButtonX::instance)),
                            (int)((int)(DAT_ButtonH::instance + -2 + DAT_ButtonY::instance)),
                            ((int)(iVar2 * 0x10 + (iVar2 * 0x10 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                        _widthTillCursor
                            = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextWidthUntilCurrentCursor,
                                DAT_UserTextHandlerState::ptr)();
                        if (DAT_00b960dc::instance == 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                                DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 6 + _widthTillCursor,
                                (int)((int)(DAT_ButtonY::instance + 2)), DAT_ButtonX::instance + 7 + _widthTillCursor,
                                (int)((int)(DAT_ButtonH::instance + -2 + DAT_ButtonY::instance)),
                                (ushort)((int)(COL_DARK_LIME::instance.shortValue)));
                        }
                        iVar2 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                        iVar2 = ((int)(iVar2 + (iVar2 >> 0x1f & 0x1fU)) >> 5) + 0x20;
                        BVar1 = FALSE;
                        fontSize = 0x13;
                        backgroundColor = 0;
                        foregroundColor = 0xffffff;
                        alignment = OpenSHC::Text::TTA_LEFT;
                        yParam = DAT_ButtonY::instance + 5;
                        xParam = DAT_ButtonX::instance + 8;
                        textAddress = MACRO_CALL_MEMBER(
                            OpenSHC::Text::UserTextHandler_Func::getCurrentText, DAT_UserTextHandlerState::ptr)();
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                            DAT_TextManagerObject::ptr)(textAddress, xParam, yParam, alignment, foregroundColor,
                            backgroundColor, fontSize, BVar1, iVar2);
                    }
                    iVar2 = ((int)(iVar2 * 0x20 + (iVar2 * 0x20 >> 0x1f & 0x1fU)) >> 5) + 0x20;
                    if (param_1 == -1) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                            DAT_GameSynchronyState::instance
                                .DAT_PlayerNames[DAT_GameSynchronyState::instance.currentPlayerSlotID],
                            (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance + 6)),
                            OpenSHC::Text::TTA_LEFT, 0xa2ff, 0x3e66, 0x11, FALSE, iVar2);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, param_1, (int)((int)(DAT_ButtonX::instance)),
                        (int)((int)(DAT_ButtonY::instance + 6)), OpenSHC::Text::TTA_LEFT, 0xa2ff, 0x3e66, 0x11, FALSE,
                        iVar2);
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance + 3)),
                    (int)((int)(DAT_ButtonW::instance + DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonH::instance + DAT_ButtonY::instance)),
                    ((int)(iVar2 * 0x10 + (iVar2 * 0x10 >> 0x1f & 0x1fU)) >> 5) + 0x20);
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::renderChatMessageList,
                    DAT_GameSynchronyState::ptr)(DAT_ButtonX::instance + 8,
                    (int)((int)(DAT_ButtonH::instance + -0x1f + DAT_ButtonY::instance)),
                    (int)((int)(DAT_GameSynchronyState::instance.field237_0x1072f0)));
            }
        }

    }
}
}
