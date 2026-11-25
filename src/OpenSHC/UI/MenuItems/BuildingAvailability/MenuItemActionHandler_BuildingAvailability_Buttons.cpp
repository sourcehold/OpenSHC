#include "../BuildingAvailability.func.hpp"

#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace BuildingAvailability {

            // FUNCTION: STRONGHOLDCRUSADER 0x004BB2C0
            void MenuItemActionHandler_BuildingAvailability_Buttons(int action, ...)
            {
                // Buttons from 1000 toggle a row, from 2000 open the row's own menu.
                if (action >= 1000 && action < 2000) {
                    DAT_MapPropertiesState::instance.buildingAvailability[DAT_MissionAestheticsDefinedData::instance
                            .BuildingAvailabilityStructIndexForNameArray[DAT_MapPropertiesState::instance
                                                                             .DAT_BuildingAvailabilityScrollbarOffset
                                + action - 1000]] ^= 1;
                    return;
                }
                if (action >= 2000 && action < 3000) {
                    // The row's mapper picks the menu; this case order gives the order of the code blocks.
                    switch (DAT_MissionAestheticsDefinedData::instance
                            .BuildingNameRelatedStructArray[DAT_MissionAestheticsDefinedData::instance
                                    .BuildingAvailabilityStructIndexForNameArray
                                        [DAT_MapPropertiesState::instance.DAT_BuildingAvailabilityScrollbarOffset
                                            + action - 2000]]
                            .field_0x4[0]
                            .identifier1) {
                    case Commands::M_MAPPER_BARRACKS_EURO:
                        MACRO_CALL_MEMBER(MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(Enums::MMT_DISABLE_ARAB_TROOPS, FALSE);
                        break;
                    case Commands::M_MAPPER_BARRACKS_ARAB:
                        MACRO_CALL_MEMBER(MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(Enums::MMT_DISABLE_EURO_TROOPS, FALSE);
                        break;
                    case Commands::M_MAPPER_FLETCHER:
                    case Commands::M_MAPPER_POLETURNER:
                    case Commands::M_MAPPER_BLACKSMITH:
                        MACRO_CALL_MEMBER(MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition1::ptr)(Enums::MMT_DISABLE_WEAPON, FALSE);
                        break;
                    }
                    return;
                }
                // -2 and -1 scroll the 19 rows down and up, 37 closes the menu. A switch, as an if/else chain moves the
                // blocks.
                switch (action) {
                case -2:
                    // The row count is compared as a signed number.
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
