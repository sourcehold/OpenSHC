#include "../GreatestLord.func.hpp"

#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GreatestLordDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004B1990
        void GreatestLord::MenuItemActionHandler_GreatestLord_Main(int param_1, ...)
        {
            if ((param_1 == 1) || (param_1 == 100)) {
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            }
            if (param_1 == 10) {
                DAT_GreatestLordDefinedData::instance.tableSortBy = -1;
            }
            if (param_1 == 0xb) {
                DAT_GreatestLordDefinedData::instance.tableSortBy = 1;
            }
            if (param_1 == 0xc) {
                DAT_GreatestLordDefinedData::instance.tableSortBy = 0;
            }
        }

    }
}
}
