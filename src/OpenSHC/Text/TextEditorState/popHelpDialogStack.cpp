#include "OpenSHC/Text/TextEditorState.func.hpp"





namespace OpenSHC {
namespace Text {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00462150
void TextEditorState::popHelpDialogStack()

{
int iVar1;
undefined4 *puVar2;
undefined4 *puVar3;
bool bVar4;

this->currentHelpSectionID = this->helpSectionHistoryStack[0];
bVar4 = this->helpSectionHistoryStack[0] == -1;
puVar2 = this->helpSectionHistoryStack;
puVar3 = this->helpSectionHistoryStack;
for (iVar1 = 29; puVar2 = puVar2 + 1, iVar1 != 0; iVar1 = iVar1 + -1) {
*puVar3 = *puVar2;
puVar3 = puVar3 + 1;
}
this->helpSectionHistoryStack[0x1d] = 0xffffffff;
if (bVar4) {
MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::closeHelpDialogAndReturnToMenu, this)();
return;
}
MACRO_CALL_MEMBER(OpenSHC::Text::TextEditorState_Func::loadAndLayoutHelpContent, this)();
return;
}


}
}