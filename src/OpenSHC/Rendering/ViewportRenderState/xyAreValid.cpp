#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"





namespace OpenSHC {
namespace Rendering {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:56:35.138000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00401000
BOOLEnum ViewportRenderState::xyAreValid(uint x,uint y)

{
if (((x < 400) && (y < 400)) &&
(this->DAT_BinaryTileMap400x400[y * 400 + x] != 0)) {
return TRUE;
}
return FALSE;
}


}
}