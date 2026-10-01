#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI/MenuViews/UnusedHelpTextEditor.func.hpp"
#include "OpenSHC/UI/Menu.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace UnusedHelpTextEditor {

            using OpenSHC::UI::Menu;

            // FUNCTION: STRONGHOLDCRUSADER 0x004403D0
            void MenuView_UnusedHelpTextEditor_Prepare()
            {
                int const y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
                int const x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                Menu* const menu = DAT_MenuHandlerState::instance.currentMenu;
                menu->xPosition = x;
                menu->yPosition = y;
                DAT_MenuHandlerState::instance.y = y;
                DAT_MenuHandlerState::instance.x = x;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::bltTextToScreenIfNeedBe, DAT_TextEditorState::ptr)();
            }

        }
    }
}
}
