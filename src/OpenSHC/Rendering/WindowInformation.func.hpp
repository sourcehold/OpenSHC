/**
  path: 'OpenSHC/Rendering/WindowInformation.func.hpp'
*/

#include "OpenSHC/Rendering/WindowInformation.hpp"
#include "winnt.h"
namespace OpenSHC {
namespace Rendering {
    namespace WindowInformation_Func {

        MACRO_FUNCTION_RESOLVER(void (WindowInformation::*)(LONG, LONG, LONG, LONG), false,
            Address::SHC_3BB0A8C1_0x00467F60, &WindowInformation::storeWindowRectangleInfoUnk)
        storeWindowRectangleInfoUnk;

    } // namespace WindowInformation_Func
} // namespace Rendering
} // namespace OpenSHC
