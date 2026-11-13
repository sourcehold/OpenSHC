#include "OpenSHC/UI/Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DA9A0
        void AppendCreditsImageEndCommand(int command, int gfxIndex)
        {
            if (DAT_UnknownBinkCount::instance < 288 && gfxIndex >= 0 && (command == 7 || command == 42)) {
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].commandType = command;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].soundStream = gfxIndex;
                DAT_UnknownBinkCount::instance += 1;
            }
        }

    }
}
}
