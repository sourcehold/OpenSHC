#include "../Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DABF0
        void AppendCreditsSoundStreamCommand(int command, int value)
        {
            int const maxCommands = sizeof(DAT_ARRAY_00eb9b68::instance) / sizeof(DAT_ARRAY_00eb9b68::instance[0]);
            if (DAT_UnknownBinkCount::instance < maxCommands) {
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].commandType = command;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].soundStream = value;
                ++DAT_UnknownBinkCount::instance;
            }
        }

    }
}
}
