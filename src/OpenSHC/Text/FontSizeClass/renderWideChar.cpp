#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"



#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Text {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00473830
int FontSizeClass::renderWideChar(undefined4 param_1,int param_2,int param_3,int param_4,int param_5)

{
char charId;
int iVar1;

charId = MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::wideCharToByteUnk, DAT_WideCharMultiByteState::ptr)((WCHAR)param_1);
iVar1 = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderCharUnk, this)(charId, param_2, param_3, param_4, param_5);
return iVar1;
}


}
}