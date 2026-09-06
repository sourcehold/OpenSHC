#include "../SoundSystem.func.hpp"

#include "OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        // FUNCTION: STRONGHOLDCRUSADER 0x0047A570
        void SoundSystem::setSection1079_28_4_(int param_1)
        {
            DAT_SoundEffectsHelperData1::ptr->SEC_Section1079.field7_0x1c = param_1;
        }

    }
}
}
