#include "../BuildMenu.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        using OpenSHC::Map::Units::UnitTypeInt;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004393C0
        void BuildMenu::MenuItemActionHandler_BuildMenu_CurrentlySelectedTroops(int slotID, ...)
        {
            UnitTypeInt unitType;
            int _unitType;
            DAT_UnitsState::instance.unitControlsRelated = 1;
            if (slotID < 0x14) {
                _unitType = DAT_RenderingDefinedData::instance
                                .field1030_0x54a5c[DAT_UnitsState::instance.selectionSlots[slotID]];
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::queueClickNavigateMenuOrEscape,
                    DAT_UnitsState::ptr)(_unitType);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::filterUnitSelectionForUnitType,
                    DAT_UnitsState::ptr)(_unitType);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::recountUnitsInSelection, DAT_UnitsState::ptr)();
            }
            unitType = DAT_RenderingDefinedData::instance
                           .field1030_0x54a5c[DAT_UnitsState::instance.selectionSlots[slotID + -0x14]];
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::queueUnitTypeCommand, DAT_UnitsState::ptr)(
                unitType);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::filterUnitSelectionExcludeUnitType,
                DAT_UnitsState::ptr)(unitType);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::recountUnitsInSelection, DAT_UnitsState::ptr)();
        }

    }
}
}
