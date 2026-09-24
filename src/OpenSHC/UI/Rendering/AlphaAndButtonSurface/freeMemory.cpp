#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        // FUNCTION: STRONGHOLDCRUSADER 0x0045D0B0
        void AlphaAndButtonSurface::freeMemory()
        {
            if (this->surfacePtr != (ushort*)0x0) {
                MACRO_CALL(OpenSHC::OS_Func::_free_base)(this->surfacePtr);
            }
        }

    }
}
}
