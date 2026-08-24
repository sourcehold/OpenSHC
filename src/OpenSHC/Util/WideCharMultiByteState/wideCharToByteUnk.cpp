#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"



#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Util {




/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0046B170
char WideCharMultiByteState::wideCharToByteUnk(WCHAR wideChar)

{
uint _securityValue;
char _byteBuffer [12];

_securityValue = MSVC_SecurityCookie::instance ^ (uint)_byteBuffer;
MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize, this)(_byteBuffer, &wideChar, 1);
;
return _byteBuffer[0];
}


}
}