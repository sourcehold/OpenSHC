#include "../GreatestLord.func.hpp"

#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_GreatestLordDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B1990
        void GreatestLord::MenuItemActionHandler_GreatestLord_Main(int button, ...)
        {
            if (button == 1 || button == 100) {
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_NONE, FALSE);
            }
            if (button == 10) {
                DAT_GreatestLordDefinedData::instance.tableSortBy = -1;
            }
            if (button == 11) {
                DAT_GreatestLordDefinedData::instance.tableSortBy = 1;
            }
            if (button == 12) {
                DAT_GreatestLordDefinedData::instance.tableSortBy = 0;
            }
        }

    }
}
}
