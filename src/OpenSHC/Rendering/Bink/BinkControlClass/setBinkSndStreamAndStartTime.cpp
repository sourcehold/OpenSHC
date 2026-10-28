#include "../../../Rendering.func.hpp"
#include "../BinkControlClass.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00408E70
        void BinkControlClass::setBinkSndStreamAndStartTime(int binkObjIndex, SHC_SoundStream soundStreamIndexUnk)
        {
            if ((DAT_SoundSystemState::instance.waveOutOpenUnk_0x8)
                && (DAT_SoundSystemState::instance.soundActiveUnk_0x0 != 0)) {
                this->soundStreamIndex[binkObjIndex] = soundStreamIndexUnk;
                this->startTime[binkObjIndex] = timeGetTime();
            }
        }

    }
}
}
