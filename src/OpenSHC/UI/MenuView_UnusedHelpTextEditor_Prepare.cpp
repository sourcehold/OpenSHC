#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Menu.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {

using OpenSHC::UI::Menu;

// FUNCTION: STRONGHOLDCRUSADER 0x004403D0
void UI::MenuView_UnusedHelpTextEditor_Prepare()
{
    int y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
    int x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
    Menu* pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
    pMVar1->xPosition = x;
    pMVar1->yPosition = y;
    DAT_MenuHandlerState::instance.y = y;
    DAT_MenuHandlerState::instance.x = x;
    MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::bltTextToScreenIfNeedBe, DAT_TextEditorState::ptr)();
}

}
