#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"



#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Text {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00471670
dword FontSizeClass::getWideCharWidth(WCHAR wChar)

{
char _resChar;
dword dVar1;

_resChar = MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::wideCharToByteUnk, DAT_WideCharMultiByteState::ptr)(wChar);
dVar1 = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::getCharWidthUnk, this)(_resChar);
return(dword)( dVar1);
}


}
}