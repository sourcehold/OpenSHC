#include "OpenSHC/Util/Timing/Stopwatch.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"





namespace OpenSHC {
namespace Util {
namespace Timing {

using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x0046CEF0
void Stopwatch::stop()

{
DWORD _currentTime;

if (this->running_0x4 != FALSE) {
_currentTime = timeGetTime();
this->stopTime_0xc = _currentTime;
this->running_0x4 = FALSE;
this->duration_0x0 = _currentTime - this->startTime_0x8;
}
return;
}


}
}
}