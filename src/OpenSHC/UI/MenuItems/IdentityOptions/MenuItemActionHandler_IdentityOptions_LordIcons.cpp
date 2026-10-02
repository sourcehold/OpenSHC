#include "../IdentityOptions.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00491CE0
        void IdentityOptions::MenuItemActionHandler_IdentityOptions_LordIcons(int param_1, ...)
        {
            if (param_1 == 0x15) {
                DAT_GameCore::instance.selectedLordTypeUnk = 0;
                if (DAT_GameCore::instance.lordIconUnk < 0x14) {
                    DAT_GameCore::instance.lordIconUnk = 2;
                }
            } else if (param_1 == 0x16) {
                DAT_GameCore::instance.selectedLordTypeUnk = 1;
                if (DAT_GameCore::instance.lordIconUnk < 0x14) {
                    DAT_GameCore::instance.lordIconUnk = 3;
                }
            } else if (param_1 == 0x28) {
                DAT_GameCore::instance.lordIconUnk = DAT_GameCore::instance.lordIconUnk + -1;
                if (DAT_GameCore::instance.lordIconUnk < 2) {
                    DAT_GameCore::instance.lordIconUnk = 21;
                }
            } else if ((param_1 == 0x29)
                && (DAT_GameCore::instance.lordIconUnk = DAT_GameCore::instance.lordIconUnk + 1,
                    0x15 < DAT_GameCore::instance.lordIconUnk)) {
                DAT_GameCore::instance.lordIconUnk = 2;
            }
        }

    }
}
}
