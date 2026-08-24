#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"





namespace OpenSHC {
namespace UI {
namespace Rendering {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00454990
void TextureRenderCore::setRenderingRect(int xPos,int yPos,int width,int heigth)

{
/* 
  Could also be, that this does not set the width and height, but the second x
   and y positions. From-To, basically. --TheRedDaemon
 */

this->renderingRect_16c854.left = xPos;
this->renderingRect_16c854.top = yPos;
this->renderingRect_16c854.right = width;
this->renderingRect_16c854.bottom = heigth;
return;
}


}
}
}