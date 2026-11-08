#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00536A60
        int UnitsState::selectionContainsCombatUnit(uint unitID)
        {
            // the first selected unit of the current player per unit type
            uint selectedUnitsMap[80];
            for (int i = 0; i < 80; ++i) {
                selectedUnitsMap[i] = 0;
            }
            BOOLEnum hasMatch = FALSE;
            int const currentPlayerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            for (DAT_CurrentUnitSlotID::instance = unitID; DAT_CurrentUnitSlotID::instance < this->maxUnitCount;
                DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                if (this->units[DAT_CurrentUnitSlotID::instance].logicalState == ULS_NORMAL
                    && this->units[DAT_CurrentUnitSlotID::instance].dying == 0
                    && this->units[DAT_CurrentUnitSlotID::instance].owner == currentPlayerSlotID
                    && this->units[DAT_CurrentUnitSlotID::instance].isSelected != 0
                    && selectedUnitsMap[this->units[DAT_CurrentUnitSlotID::instance].unitType] == 0) {
                    selectedUnitsMap[this->units[DAT_CurrentUnitSlotID::instance].unitType]
                        = DAT_CurrentUnitSlotID::instance;
                    hasMatch = TRUE;
                }
            }
            if (!hasMatch) {
                return -1;
            }
            // ranged units first, then siege engines, infantry and the rest
            if (selectedUnitsMap[UT_E_ARCHER] != 0) {
                return selectedUnitsMap[UT_E_ARCHER];
            }
            if (selectedUnitsMap[UT_E_ARCHER_DEBUG] != 0) {
                return selectedUnitsMap[UT_E_ARCHER_DEBUG];
            }
            if (selectedUnitsMap[UT_E_XBOW] != 0) {
                return selectedUnitsMap[UT_E_XBOW];
            }
            if (selectedUnitsMap[UT_A_ARCHER] != 0) {
                return selectedUnitsMap[UT_A_ARCHER];
            }
            if (selectedUnitsMap[UT_A_HARCHER] != 0) {
                return selectedUnitsMap[UT_A_HARCHER];
            }
            if (selectedUnitsMap[UT_A_SLINGER] != 0) {
                return selectedUnitsMap[UT_A_SLINGER];
            }
            if (selectedUnitsMap[UT_A_FIRETHROWER] != 0) {
                return selectedUnitsMap[UT_A_FIRETHROWER];
            }
            if (selectedUnitsMap[UT_S_FBALLISTA] != 0) {
                return selectedUnitsMap[UT_S_FBALLISTA];
            }
            if (selectedUnitsMap[UT_S_CATAPULT] != 0) {
                return selectedUnitsMap[UT_S_CATAPULT];
            }
            if (selectedUnitsMap[UT_S_TREBUCHET] != 0) {
                return selectedUnitsMap[UT_S_TREBUCHET];
            }
            if (selectedUnitsMap[UT_S_MANGONEL] != 0) {
                return selectedUnitsMap[UT_S_MANGONEL];
            }
            if (selectedUnitsMap[UT_S_BALLISTA] != 0) {
                return selectedUnitsMap[UT_S_BALLISTA];
            }
            if (selectedUnitsMap[UT_E_SPEAR] != 0) {
                return selectedUnitsMap[UT_E_SPEAR];
            }
            if (selectedUnitsMap[UT_E_PIKE] != 0) {
                return selectedUnitsMap[UT_E_PIKE];
            }
            if (selectedUnitsMap[UT_E_MACE] != 0) {
                return selectedUnitsMap[UT_E_MACE];
            }
            if (selectedUnitsMap[UT_E_SWORD] != 0) {
                return selectedUnitsMap[UT_E_SWORD];
            }
            if (selectedUnitsMap[UT_E_KNIGHT] != 0) {
                return selectedUnitsMap[UT_E_KNIGHT];
            }
            if (selectedUnitsMap[UT_TUNNELER] != 0) {
                return selectedUnitsMap[UT_TUNNELER];
            }
            if (selectedUnitsMap[UT_E_LADDER] != 0) {
                return selectedUnitsMap[UT_E_LADDER];
            }
            if (selectedUnitsMap[UT_E_ENGINEER] != 0) {
                return selectedUnitsMap[UT_E_ENGINEER];
            }
            if (selectedUnitsMap[UT_E_MONK] != 0) {
                return selectedUnitsMap[UT_E_MONK];
            }
            if (selectedUnitsMap[UT_A_SLAVE] != 0) {
                return selectedUnitsMap[UT_A_SLAVE];
            }
            if (selectedUnitsMap[UT_A_ASSASSIN] != 0) {
                return selectedUnitsMap[UT_A_ASSASSIN];
            }
            if (selectedUnitsMap[UT_A_SWORDSMAN] != 0) {
                return selectedUnitsMap[UT_A_SWORDSMAN];
            }
            if (selectedUnitsMap[UT_LORD] != 0) {
                return selectedUnitsMap[UT_LORD];
            }
            if (selectedUnitsMap[UT_S_TOWER] != 0) {
                return selectedUnitsMap[UT_S_TOWER];
            }
            if (selectedUnitsMap[UT_S_BATTERINGRAM] != 0) {
                return selectedUnitsMap[UT_S_BATTERINGRAM];
            }
            if (selectedUnitsMap[UT_S_SHIELD] != 0) {
                return selectedUnitsMap[UT_S_SHIELD];
            }
            return -1;
        }

    }
}
}
