#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"



#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace Text {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0045D690
void TextEditorState::bltTextToScreenIfNeedBe()

{
if (this->intArray1[0x14] != 0) {
if (((this->savedMenuViewType == 0xc) ||
(this->savedMenuViewType == 0xe)) ||
(this->savedMenuViewType == 0x10)) {
MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::WindowAndDirectDraw_Func::bltMapGameSurfaceToScreenMenuSurfaceComplete, DAT_WindowAndDirectDraw::ptr)();
}
this->intArray1[0x14] = 0;
}
return;
}


}
}