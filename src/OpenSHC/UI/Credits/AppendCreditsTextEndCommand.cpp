#include "OpenSHC/UI/Credits.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_NumberOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"

namespace OpenSHC {
namespace UI {
    namespace Credits {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DACF0
        void AppendCreditsTextEndCommand(int command, int textIndex)
        {
            if (DAT_UnknownBinkCount::instance < 288 && textIndex >= 0
                && textIndex < (int)DAT_NumberOfStoredMenuStrings::instance && command == 16) {
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].commandType = 16;
                DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkCount::instance].soundStream = textIndex;
                DAT_UnknownBinkCount::instance += 1;
            }
        }

    }
}
}
