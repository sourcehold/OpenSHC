#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_DisableMercPostPortraits.hpp"

namespace OpenSHC {
namespace UI {
    namespace Helpers {

        // FUNCTION: STRONGHOLDCRUSADER 0x00466E10
        void DisableMercPostPortraits() { DAT_DisableMercPostPortraits::instance = 1; }

    }
}
}
