#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"



#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
namespace Rendering {

using OpenSHC::Rendering::Enums::RenderTarget;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00468C50
void PencilRenderCore::setupPencilSurface()

{
this->surfacePtr = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
if (this->surfaceTarget == OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
this->surfacePtr = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
}
if (this->surfaceTarget != OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
this->horizontalByteSize = 8112;
return;
}
this->horizontalByteSize = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
return;
}


}
}
}