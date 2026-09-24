#include "OpenSHC/UI/Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DA8A0
        void AppendCreditsClearImageCommand()
        {
            if (DAT_UnknownBinkCount::instance < 0x120) {
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].field0_0x0 = 0x28;
                DAT_UnknownBinkCount::instance = DAT_UnknownBinkCount::instance + 1;
            }
        }

    }
}
}
