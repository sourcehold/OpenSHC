#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"





namespace OpenSHC {
namespace Text {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;
using OpenSHC::Text::TextAlignment;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00424620
void TextManager::renderNumber(int number,int xPosition,int yPosition,uint color1,uint color2,int fontSize,BOOLEnum keepOffsetX)

{
MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, this)(number, xPosition, yPosition, OpenSHC::Text::TTA_LEFT, color1, color2, fontSize, 
keepOffsetX, 0);
return;
}


}
}