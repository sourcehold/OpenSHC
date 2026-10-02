#include "../General.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/COL_DARK_LIME.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::Text::TextArrayIndexType;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0047CCA0
        void General::MenuItemRenderFunction_General_TextInputDisplay(int param_1, ...)
        {
            int _textWidth;
            char* pcVar1;
            int xParam;
            int iVar2;
            int _textArrayIndex;
            if ((param_1 == 3) && (DAT_GameCore::instance.unknownFlag_0x118 == TRUE)) {}
            _textWidth = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::getTextWidthUntilCurrentCursor, DAT_UserTextHandlerState::ptr)();
            DAT_ButtonCurrentlyInteracting::instance = FALSE;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(-1, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            switch (param_1) {
            case 0:
                /*
                  tcp ip
                 */
                if (DAT_UserTextHandlerState::instance.textArrayIndex == OpenSHC::Text::TAIT_FIVE__NUMERIC_DOT) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 6 + _textWidth,
                        (int)((int)(DAT_ButtonY::instance + 3)), DAT_ButtonX::instance + 7 + _textWidth,
                        (int)((int)(DAT_ButtonH::instance + -4 + DAT_ButtonY::instance)),
                        (ushort)((int)(COL_DARK_LIME::instance.shortValue)));
                }
                _textArrayIndex = 5;
                break;
            case 1:
                if (DAT_UserTextHandlerState::instance.textArrayIndex == OpenSHC::Text::TAIT_SIX__NUMERIC_ONLY) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 6 + _textWidth,
                        (int)((int)(DAT_ButtonY::instance + 3)), DAT_ButtonX::instance + 7 + _textWidth,
                        (int)((int)(DAT_ButtonH::instance + -4 + DAT_ButtonY::instance)),
                        (ushort)((int)(COL_DARK_LIME::instance.shortValue)));
                }
                _textArrayIndex = 6;
                break;
            case 2:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 6 + _textWidth,
                    (int)((int)(DAT_ButtonY::instance + 3)), DAT_ButtonX::instance + 7 + _textWidth,
                    (int)((int)(DAT_ButtonH::instance + -4 + DAT_ButtonY::instance)),
                    (ushort)((int)(COL_DARK_LIME::instance.shortValue)));
                _textArrayIndex = 7;
                break;
            case 3:
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 6 + _textWidth,
                    (int)((int)(DAT_ButtonY::instance + 3)), DAT_ButtonX::instance + 7 + _textWidth,
                    (int)((int)(DAT_ButtonH::instance + -4 + DAT_ButtonY::instance)),
                    (ushort)((int)(COL_DARK_LIME::instance.shortValue)));
                _textArrayIndex = 0;
                break;
            case 4:
                if (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_MAIN_MENU) {
                    DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 6 + _textWidth,
                    (int)((int)(DAT_ButtonY::instance + 3)), DAT_ButtonX::instance + 7 + _textWidth,
                    (int)((int)(DAT_ButtonH::instance + -4 + DAT_ButtonY::instance)),
                    (ushort)((int)(COL_DARK_LIME::instance.shortValue)));
                _textArrayIndex = DAT_ButtonY::instance + 6;
                iVar2 = DAT_ButtonX::instance + 6;
                pcVar1 = MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    pcVar1, iVar2, _textArrayIndex, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x11, FALSE, 0);
                DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            default:
                break;
            }
            iVar2 = DAT_ButtonY::instance + 6;
            xParam = DAT_ButtonX::instance + 6;
            pcVar1 = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                DAT_UserTextHandlerState::ptr)(_textArrayIndex);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                pcVar1, xParam, iVar2, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x11, FALSE, 0);
        }

    }
}
}
