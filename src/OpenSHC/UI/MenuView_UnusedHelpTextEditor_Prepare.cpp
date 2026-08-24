#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Menu.hpp"
#include "OpenSHC/Text/TextEditorState.func.hpp"



#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"

namespace OpenSHC {

using OpenSHC::UI::Menu;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004403D0
void UI::MenuView_UnusedHelpTextEditor_Prepare()

{
Menu *pMVar1;

DAT_MenuHandlerState::instance.y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
DAT_MenuHandlerState::instance.x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
(DAT_MenuHandlerState::instance.currentMenu)->xPosition = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
pMVar1->yPosition = DAT_MenuHandlerState::instance.y;
MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::bltTextToScreenIfNeedBe, DAT_TextEditorState::ptr)();
return;
}


}