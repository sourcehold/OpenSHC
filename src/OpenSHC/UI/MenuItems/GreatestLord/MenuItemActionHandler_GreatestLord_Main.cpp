#include "../GreatestLord.func.hpp"

#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GreatestLordDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using UI::Enums::MenuModalType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004B1990
        void GreatestLord::MenuItemActionHandler_GreatestLord_Main(int param_1, ...)
        {
            if ((param_1 == 1) || (param_1 == 100)) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(UI::Enums::MMT_NONE, FALSE);
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
