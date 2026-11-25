#include "../TraderSettings.func.hpp"

#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace TraderSettings {

            // FUNCTION: STRONGHOLDCRUSADER 0x004BA780
            void MenuItemActionHandler_TraderSettings(int button, ...)
            {
                // Buttons -1, -2, ... switch the trader's goods on or off in the order field_0x345c lists them.
                if (button < 0) {
                    // The row in a local: -1 - button written into the index loses the match
                    int const row = -1 - button;
                    DAT_MapPropertiesState::instance.SEC_Section1065
                        .tradeabilityArray[DAT_MissionAestheticsDefinedData::instance.field_0x345c[row]] ^= TRUE;
                    return;
                }
                switch (button) {
                case 37:
                    // OK: close the dialog.
                    MACRO_CALL_MEMBER(MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                        Enums::MMT_NONE, FALSE);
                    break;
                case 1111:
                    // The goods selected in the list.
                    DAT_MapPropertiesState::instance.SEC_Section1065
                        .tradeabilityArray[DAT_MissionAestheticsDefinedData::instance
                                .field_0x345c[DAT_MapPropertiesState::instance.indexStored]] ^= TRUE;
                    break;
                }
            }

        }
    }
}
}
