#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"



#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Text {




// FUNCTION: STRONGHOLDCRUSADER 0x00471570
int UserTextHandler::getTextWidthUntilCurrentCursor()

{
int iVar1;

iVar1 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextWidthTillCursorUnk, DAT_TextManagerObject::ptr)(
this->textArray[this->textArrayIndex], (int)((int)(
this->textCursorIndexArray
[this->textArrayIndex])), (int)((int)(
this->textArrayFontSizes
[this->textArrayIndex])));
return iVar1;
}


}
}