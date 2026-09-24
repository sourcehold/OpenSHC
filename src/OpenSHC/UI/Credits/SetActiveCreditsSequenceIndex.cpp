#include "OpenSHC/UI/Credits.func.hpp"

#include "OpenSHC/Globals/DAT_00ed3120.hpp"
#include "OpenSHC/Globals/DAT_00ed3124.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D9270
        void __cdecl SetActiveCreditsSequenceIndex(undefined4 param_1)
        {
            DAT_00ed3124::instance = param_1;
            DAT_00ed3120::instance = 0;
        }

    }
}
}
