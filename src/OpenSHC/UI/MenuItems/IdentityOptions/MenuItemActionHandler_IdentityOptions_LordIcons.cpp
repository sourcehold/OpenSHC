#include "../IdentityOptions.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00491CE0
        void IdentityOptions::MenuItemActionHandler_IdentityOptions_LordIcons(int param_1, ...)
        {
            if (param_1 == 21) {
                DAT_GameCore::instance.selectedLordTypeUnk = 0;
                if (DAT_GameCore::instance.lordIconUnk < 20) {
                    DAT_GameCore::instance.lordIconUnk = 2;
                }
            } else if (param_1 == 22) {
                DAT_GameCore::instance.selectedLordTypeUnk = 1;
                if (DAT_GameCore::instance.lordIconUnk < 20) {
                    DAT_GameCore::instance.lordIconUnk = 3;
                }
            } else if (param_1 == 40) {
                --DAT_GameCore::instance.lordIconUnk;
                if (DAT_GameCore::instance.lordIconUnk < 2) {
                    DAT_GameCore::instance.lordIconUnk = 21;
                }
            } else if ((param_1 == 41)
                && (DAT_GameCore::instance.lordIconUnk = DAT_GameCore::instance.lordIconUnk + 1,
                    21 < DAT_GameCore::instance.lordIconUnk)) {
                DAT_GameCore::instance.lordIconUnk = 2;
            }
        }

    }
}
}
