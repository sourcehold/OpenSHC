#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00536A60
        int UnitsState::selectionContainsCombatUnit(uint unitID)
        {
            /* create a unittype array of length 80 and initialize it with 0's */
            uint selectedUnitsMap[80];
            for (int i = 0; i < 80; ++i) {
                selectedUnitsMap[i] = 0;
            }
            /* for every unit in the game, we check whether it is owned by the current
               player, whether the unit has 3 properties, and whether it has not been
               mentioned in the size 80 array. Then, we put that ID at that location.

               map<unit_type, unit_id> */
            bool _hasMatch = false;
            for (DAT_CurrentUnitSlotID::instance = unitID;
                (int)DAT_CurrentUnitSlotID::instance < (int)this->maxUnitCount;
                DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                if (this->units[DAT_CurrentUnitSlotID::instance].logicalState == OpenSHC::Map::Units::ULS_NORMAL
                    && this->units[DAT_CurrentUnitSlotID::instance].dying == 0
                    && this->units[DAT_CurrentUnitSlotID::instance].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID
                    && this->units[DAT_CurrentUnitSlotID::instance].isSelected != 0
                    && selectedUnitsMap[(short)this->units[DAT_CurrentUnitSlotID::instance].unitType] == 0) {
                    selectedUnitsMap[(short)this->units[DAT_CurrentUnitSlotID::instance].unitType]
                        = DAT_CurrentUnitSlotID::instance;
                    _hasMatch = true;
                }
            }
            /* if we have at least 1 match, return it. the order of returning seems really
               arbitrary, but maybe it means something */
            if (!_hasMatch) {
                return -1;
            }
            /* E_ARCHER */
            if (selectedUnitsMap[0x16] != 0) {
                return selectedUnitsMap[0x16];
            }
            if (selectedUnitsMap[0x26] != 0) {
                return selectedUnitsMap[0x26];
            }
            /* E_XBOW */
            if (selectedUnitsMap[0x17] != 0) {
                return selectedUnitsMap[0x17];
            }
            /* A_ARCHER */
            if (selectedUnitsMap[0x46] != 0) {
                return selectedUnitsMap[0x46];
            }
            /* A_HARCHER */
            if (selectedUnitsMap[0x4a] != 0) {
                return selectedUnitsMap[0x4a];
            }
            /* A_SLINGER */
            if (selectedUnitsMap[0x48] != 0) {
                return selectedUnitsMap[0x48];
            }
            /* A_FIRETHROWER */
            if (selectedUnitsMap[0x4c] != 0) {
                return selectedUnitsMap[0x4c];
            }
            /* S_FBALLISTA */
            if (selectedUnitsMap[0x4d] != 0) {
                return selectedUnitsMap[0x4d];
            }
            /* S_CATAPULT */
            if (selectedUnitsMap[0x27] != 0) {
                return selectedUnitsMap[0x27];
            }
            /* S_TREBUCHET */
            if (selectedUnitsMap[0x28] != 0) {
                return selectedUnitsMap[0x28];
            }
            /* S_MANGONEL */
            if (selectedUnitsMap[0x29] != 0) {
                return selectedUnitsMap[0x29];
            }
            /* S_BALLISTA */
            if (selectedUnitsMap[0x3d] != 0) {
                return selectedUnitsMap[0x3d];
            }
            /* E_SPEARMAN */
            if (selectedUnitsMap[0x18] != 0) {
                return selectedUnitsMap[0x18];
            }
            /* E_PIKEMAN */
            if (selectedUnitsMap[0x19] != 0) {
                return selectedUnitsMap[0x19];
            }
            /* E_MACEMAN */
            if (selectedUnitsMap[0x1a] != 0) {
                return selectedUnitsMap[0x1a];
            }
            /* E_SWORDSMAN */
            if (selectedUnitsMap[0x1b] != 0) {
                return selectedUnitsMap[0x1b];
            }
            /* E_KNIGHT */
            if (selectedUnitsMap[0x1c] != 0) {
                return selectedUnitsMap[0x1c];
            }
            /* TUNNELER */
            if (selectedUnitsMap[5] != 0) {
                return selectedUnitsMap[5];
            }
            /* E_LADDERMAN */
            if (selectedUnitsMap[0x1d] != 0) {
                return selectedUnitsMap[0x1d];
            }
            /* E_ENGINEER */
            if (selectedUnitsMap[0x1e] != 0) {
                return selectedUnitsMap[0x1e];
            }
            /* E_MONK */
            if (selectedUnitsMap[0x25] != 0) {
                return selectedUnitsMap[0x25];
            }
            /* A_SLAVE */
            if (selectedUnitsMap[0x47] != 0) {
                return selectedUnitsMap[0x47];
            }
            /* A_ASSASSIN */
            if (selectedUnitsMap[0x49] != 0) {
                return selectedUnitsMap[0x49];
            }
            /* A_SWORDSMAN */
            if (selectedUnitsMap[0x4b] != 0) {
                return selectedUnitsMap[0x4b];
            }
            /* LORD */
            if (selectedUnitsMap[0x37] != 0) {
                return selectedUnitsMap[0x37];
            }
            /* S_TOWER */
            if (selectedUnitsMap[0x3a] != 0) {
                return selectedUnitsMap[0x3a];
            }
            /* S_BATTERINGRAM */
            if (selectedUnitsMap[0x3b] != 0) {
                return selectedUnitsMap[0x3b];
            }
            /* S_SHIELD */
            if (selectedUnitsMap[0x3c] != 0) {
                return selectedUnitsMap[0x3c];
            }
            return -1;
        }

    }
}
}
