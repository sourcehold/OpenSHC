#include "../BuildMenu.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        using OpenSHC::Map::Units::UnitTypeInt;

        // FUNCTION: STRONGHOLDCRUSADER 0x004393C0
        void BuildMenu::MenuItemActionHandler_BuildMenu_CurrentlySelectedTroops(int slotID, ...)
        {
            DAT_UnitsState::instance.unitControlsRelated = 1;
            // 20 selection slots: buttons 0-19 keep only a slot's unit type selected, 20-39 drop it
            if (slotID < 20) {
                UnitTypeInt const unitType
                    = DAT_RenderingDefinedData::instance
                          .SelectionSlotUnitTypes[DAT_UnitsState::instance.selectionSlots[slotID]];
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::queueClickNavigateMenuOrEscape,
                    DAT_UnitsState::ptr)(unitType);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::filterUnitSelectionForUnitType,
                    DAT_UnitsState::ptr)(unitType);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::recountUnitsInSelection, DAT_UnitsState::ptr)();
                return;
            }
            UnitTypeInt const unitType
                = DAT_RenderingDefinedData::instance
                      .SelectionSlotUnitTypes[DAT_UnitsState::instance.selectionSlots[slotID - 20]];
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::queueUnitTypeCommand, DAT_UnitsState::ptr)(
                unitType);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::filterUnitSelectionExcludeUnitType,
                DAT_UnitsState::ptr)(unitType);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::recountUnitsInSelection, DAT_UnitsState::ptr)();
        }

    }
}
}
