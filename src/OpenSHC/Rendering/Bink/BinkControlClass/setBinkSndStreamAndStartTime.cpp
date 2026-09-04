#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using OpenSHC::Audio::MSS::enums::SHC_SoundStream;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00408E70
        void BinkControlClass::setBinkSndStreamAndStartTime(int binkObjIndex, SHC_SoundStream soundStreamIndexUnk)
        {
            if ((DAT_SoundSystemState::instance.waveOutOpenUnk_0x8 != FALSE)
                && (DAT_SoundSystemState::instance.soundActiveUnk_0x0 != 0)) {
                this->soundStreamIndex[binkObjIndex] = soundStreamIndexUnk;
                this->startTime[binkObjIndex] = timeGetTime();
            }
        }

    }
}
}
