#include "OpenSHC/UI/Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DA810
        void AppendCreditsListTerminator()
        {
            if (DAT_UnknownBinkCount::instance < 288) {
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field0_0x0 = 0x20;
                DAT_UnknownBinkCount::instance = DAT_UnknownBinkCount::instance + 1;
            }
        }

    }
}
}
