#include "OpenSHC/UI/MenuItems/DisableEuroTroops.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace DisableEuroTroops {

            using OpenSHC::UI::Enums::MenuModalType;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            // FUNCTION: STRONGHOLDCRUSADER 0x004BB540
            void MenuItemActionHandler_DisableEuroTroops_Main(int troopIndex, ...)
            {
                // indexes the seven barracks troop flags that directly precede SEC_MercRecruitable
                if ((uint)troopIndex <= 7) {
                    DAT_MapPropertiesState::instance.SEC_MercRecruitable[troopIndex - 7] ^= 1;
                    return;
                }
                if (troopIndex == -3) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                        DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_BUILDING_AVAILABILITY, FALSE);
                }
            }

        }
    }
}
}
