#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"



#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UnknownStopwatch.hpp"

namespace OpenSHC {
namespace UI {

using OpenSHC::Text::TextAlignment;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x004AFA50
void Rendering::RenderUnknownDisplayElement7(int posX,int posY,DWORD elementState)

{
MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(DAT_UnknownStopwatch::instance.duration_0x0, posX, posY + 5, OpenSHC::Text::TTA_RIGHT, 0x80ff
, 0, 0xf, FALSE, 0);
return;
}


}
}