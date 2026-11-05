#include "../BuildingAvailability.func.hpp"

#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAvailability {

            // FUNCTION: STRONGHOLDCRUSADER 0x004BB2C0
            void MenuItemActionHandler_BuildingAvailability_Buttons(int param_1, ...)
            {
                // Buttons from 1000 toggle a row, from 2000 open the row's own menu.
                if (param_1 >= 1000 && param_1 < 2000) {
                    DAT_MapPropertiesState::instance.buildingAvailability[DAT_MissionAestheticsDefinedData::instance
                            .BuildingAvailabilityStructIndexForNameArray[DAT_MapPropertiesState::instance
                                                                             .DAT_BuildingAvailabilityScrollbarOffset
                                + param_1 - 1000]] ^= 1;
                    return;
                }
                if (param_1 >= 2000 && param_1 < 3000) {
                    // 50, 82 and 83 are the weapons, 86 the Arabian troops and 87 the European ones. The cases stay in
                    // the original's block order.
                    switch (DAT_MissionAestheticsDefinedData::instance
                            .BuildingNameRelatedStructArray[DAT_MissionAestheticsDefinedData::instance
                                    .BuildingAvailabilityStructIndexForNameArray
                                        [DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset
                                            + param_1 - 2000]]
                            .field_0x4[0]
                            .identifier1) {
                    case 86:
                        MACRO_CALL_MEMBER(MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(Enums::MMT_DISABLE_ARAB_TROOPS, FALSE);
                        return;
                    case 87:
                        MACRO_CALL_MEMBER(MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(Enums::MMT_DISABLE_EURO_TROOPS, FALSE);
                        return;
                    case 50:
                    case 82:
                    case 83:
                        MACRO_CALL_MEMBER(MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(Enums::MMT_DISABLE_WEAPON, FALSE);
                        return;
                    }
                    return;
                }
                // -2 and -1 scroll the 19 rows down and up, 37 closes the menu. A switch, as an if/else chain moves the
                // blocks.
                switch (param_1) {
                case -2:
                    if (DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset
                        < (int)DAT_MapPropertiesState::instance.buildingAvailabilityRowCount - 19) {
                        ++DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset;
                    }
                    break;
                case -1:
                    if (DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset > 0) {
                        --DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset;
                    }
                    break;
                case 37:
                    MACRO_CALL_MEMBER(MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                        Enums::MMT_NONE, FALSE);
                    break;
                }
            }

        }
    }
}
}
