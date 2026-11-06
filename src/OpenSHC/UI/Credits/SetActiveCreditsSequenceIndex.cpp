#include "../Credits.func.hpp"

#include "OpenSHC/Globals/DAT_00ed3124.hpp"
#include "OpenSHC/Globals/INT_00ed3120.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D9270
        void __cdecl SetActiveCreditsSequenceIndex(undefined4 sequenceIndex)
        {
            DAT_00ed3124::instance = sequenceIndex;
            INT_00ed3120::instance = 0;
        }

    }
}
}
