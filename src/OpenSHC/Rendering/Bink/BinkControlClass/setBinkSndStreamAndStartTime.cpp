#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"



#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Rendering {
namespace Bink {

using OpenSHC::Audio::MSS::enums::SHC_SoundStream;
using OpenSHC::WindowsHelper::Enums::BOOLEnum;


/* 
  WARNING: Enum "UnsortedBinkFlagInt": Some values do not have unique names
 */

/* 
  decompilerscript: committed: 2025-01-30 21:57:43.216000
 */


// FUNCTION: STRONGHOLDCRUSADER 0x00408E70
void BinkControlClass::setBinkSndStreamAndStartTime(int binkObjIndex,SHC_SoundStream soundStreamIndexUnk)

{
DWORD _currentSysTime;

if ((DAT_SoundSystemState::instance.waveOutOpenUnk_0x8 != FALSE) &&
(DAT_SoundSystemState::instance.soundActiveUnk_0x0 != 0)) {
this->soundStreamIndex[binkObjIndex] = soundStreamIndexUnk;
_currentSysTime = timeGetTime();
this->startTime[binkObjIndex] = _currentSysTime;
}
return;
}


}
}
}