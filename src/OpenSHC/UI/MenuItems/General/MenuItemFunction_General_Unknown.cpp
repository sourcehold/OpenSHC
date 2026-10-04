#include "OpenSHC/UI/MenuItems/General.func.hpp"

#include "OpenSHC/Globals/DAT_StopHandlingMenuItems.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace General {

            // FUNCTION: STRONGHOLDCRUSADER 0x00440410
            void MenuItemFunction_General_Unknown(int param_1, ...) { DAT_StopHandlingMenuItems::instance = 0; }

        }
    }
}
}
