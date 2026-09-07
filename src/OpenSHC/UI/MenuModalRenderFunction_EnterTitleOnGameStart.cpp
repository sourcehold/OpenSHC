#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {

// FUNCTION: STRONGHOLDCRUSADER 0x00491BF0
void UI::MenuModalRenderFunction_EnterTitleOnGameStart(int x,int y,int width,int height)
{

MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner, DAT_PencilRenderCore::ptr)(5, 6, x, y, width);
}

}
