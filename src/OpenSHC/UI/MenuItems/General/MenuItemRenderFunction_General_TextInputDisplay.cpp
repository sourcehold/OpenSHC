#include "../General.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/Text/TextArrayIndexType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

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

        // FUNCTION: STRONGHOLDCRUSADER 0x0047CCA0
        void General::MenuItemRenderFunction_General_TextInputDisplay(int field, ...)
        {
            // == TRUE: the original compares with 1 (a truthiness test: quick_diff 0.9664 -> 0.9365); field 3, the
            // title box, is hidden while a title is set
            if (field == 3 && DAT_GameCore::instance.isNameEntryActive == TRUE) {
                return;
            }
            int const cursorX = MACRO_CALL_MEMBER(
                OpenSHC::Text::UserTextHandler_Func::getTextWidthUntilCurrentCursor, DAT_UserTextHandlerState::ptr)();
            DAT_ButtonCurrentlyInteracting::instance = FALSE;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                AlphaAndButtonSurfaceObj::ptr)(-1, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
            // the cursor at the typing position, then the text 6 pixels in from the corner
            // the text in each case, merged but for the index (one call after the switch: quick_diff 0.9664 -> 0.9365)
            switch (field) {
            case 0: {
                // fields 0 and 1 show the cursor only while their text is the one being typed
                if (DAT_UserTextHandlerState::instance.textArrayIndex == OpenSHC::Text::TAIT_FIVE__NUMERIC_DOT) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 6 + cursorX, DAT_ButtonY::instance + 3,
                        DAT_ButtonX::instance + 7 + cursorX, DAT_ButtonY::instance + DAT_ButtonH::instance - 4,
                        COL_DARK_LIME::instance.shortValue);
                }
                int const textY = DAT_ButtonY::instance + 6;
                int const textX = DAT_ButtonX::instance + 6;
                char* const text = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                    DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_FIVE__NUMERIC_DOT);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    text, textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 17, FALSE, 0);
                break;
            }
            case 1: {
                if (DAT_UserTextHandlerState::instance.textArrayIndex == OpenSHC::Text::TAIT_SIX__NUMERIC_ONLY) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 6 + cursorX, DAT_ButtonY::instance + 3,
                        DAT_ButtonX::instance + 7 + cursorX, DAT_ButtonY::instance + DAT_ButtonH::instance - 4,
                        COL_DARK_LIME::instance.shortValue);
                }
                int const textY = DAT_ButtonY::instance + 6;
                int const textX = DAT_ButtonX::instance + 6;
                char* const text = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                    DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_SIX__NUMERIC_ONLY);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    text, textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 17, FALSE, 0);
                break;
            }
            case 2: {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 6 + cursorX, DAT_ButtonY::instance + 3,
                    DAT_ButtonX::instance + 7 + cursorX, DAT_ButtonY::instance + DAT_ButtonH::instance - 4,
                    COL_DARK_LIME::instance.shortValue);
                int const textY = DAT_ButtonY::instance + 6;
                int const textX = DAT_ButtonX::instance + 6;
                char* const text = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                    DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_SEVEN__NUMERIC_ONLY);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    text, textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 17, FALSE, 0);
                break;
            }
            case 3: {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 6 + cursorX, DAT_ButtonY::instance + 3,
                    DAT_ButtonX::instance + 7 + cursorX, DAT_ButtonY::instance + DAT_ButtonH::instance - 4,
                    COL_DARK_LIME::instance.shortValue);
                int const textY = DAT_ButtonY::instance + 6;
                int const textX = DAT_ButtonX::instance + 6;
                char* const text = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                    DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_ZERO);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    text, textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 17, FALSE, 0);
                break;
            }
            case 4: {
                // outside the main menu this field is drawn on the map's surface
                if (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_MAIN_MENU) {
                    DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + 6 + cursorX, DAT_ButtonY::instance + 3,
                    DAT_ButtonX::instance + 7 + cursorX, DAT_ButtonY::instance + DAT_ButtonH::instance - 4,
                    COL_DARK_LIME::instance.shortValue);
                int const textY = DAT_ButtonY::instance + 6;
                int const textX = DAT_ButtonX::instance + 6;
                char* const text = MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer,
                    DAT_UserTextHandlerState::ptr)(OpenSHC::Text::TAIT_ZERO);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    text, textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 17, FALSE, 0);
                DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                break;
            }
            }
        }

    }
}
}
