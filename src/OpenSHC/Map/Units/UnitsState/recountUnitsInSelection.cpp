#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Units/Selection/UnitSelectionEnumInt.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00535240
        void UnitsState::recountUnitsInSelection()
        {
            for (int i = 0; i <= 26; ++i) {
                this->selectionUnitType[i] = 0;
            }
            for (int unitID = 1; unitID < this->maxUnitCount; ++unitID) {
                if (this->units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[unitID].dying != 0) {
                    continue;
                }
                if (this->units[unitID].owner != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    continue;
                }
                if (this->units[unitID].isSelected == 0) {
                    continue;
                }
                switch (this->units[unitID].unitType) {
                case OpenSHC::Map::Units::UT_E_ARCHER:
                    this->selectionUnitType[Selection::USE_E_ARCHERS]
                        = this->selectionUnitType[Selection::USE_E_ARCHERS] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_E_XBOW:
                    this->selectionUnitType[Selection::USE_E_CROSSBOWMEN]
                        = this->selectionUnitType[Selection::USE_E_CROSSBOWMEN] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_E_SPEAR:
                    this->selectionUnitType[Selection::USE_E_SPEARMEN]
                        = this->selectionUnitType[Selection::USE_E_SPEARMEN] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_E_PIKE:
                    this->selectionUnitType[Selection::USE_E_PIKEMEN]
                        = this->selectionUnitType[Selection::USE_E_PIKEMEN] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_E_MACE:
                    this->selectionUnitType[Selection::USE_E_MACEMEN]
                        = this->selectionUnitType[Selection::USE_E_MACEMEN] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_E_SWORD:
                    this->selectionUnitType[Selection::USE_E_SWORDSMEN]
                        = this->selectionUnitType[Selection::USE_E_SWORDSMEN] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_E_KNIGHT:
                    this->selectionUnitType[Selection::USE_E_KNIGHTS]
                        = this->selectionUnitType[Selection::USE_E_KNIGHTS] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_E_LADDER:
                    this->selectionUnitType[Selection::USE_E_LADDERMEN]
                        = this->selectionUnitType[Selection::USE_E_LADDERMEN] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_E_ENGINEER:
                    this->selectionUnitType[Selection::USE_E_ENGINEERS]
                        = this->selectionUnitType[Selection::USE_E_ENGINEERS] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_E_MONK:
                    this->selectionUnitType[Selection::USE_E_MONKS]
                        = this->selectionUnitType[Selection::USE_E_MONKS] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_TUNNELER:
                    this->selectionUnitType[Selection::USE_E_TUNNELERS]
                        = this->selectionUnitType[Selection::USE_E_TUNNELERS] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_S_CATAPULT:
                    this->selectionUnitType[Selection::USE_E_CATAPULTS]
                        = this->selectionUnitType[Selection::USE_E_CATAPULTS] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_S_TREBUCHET:
                    this->selectionUnitType[Selection::USE_E_TREBUCHETS]
                        = this->selectionUnitType[Selection::USE_E_TREBUCHETS] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_S_MANGONEL:
                    this->selectionUnitType[Selection::USE_E_MANGONELS]
                        = this->selectionUnitType[Selection::USE_E_MANGONELS] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_S_TOWER:
                    this->selectionUnitType[Selection::USE_E_SIEGETOWERS]
                        = this->selectionUnitType[Selection::USE_E_SIEGETOWERS] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                    this->selectionUnitType[Selection::USE_E_BATTERING_RAMS]
                        = this->selectionUnitType[Selection::USE_E_BATTERING_RAMS] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_S_SHIELD:
                    this->selectionUnitType[Selection::USE_E_SHIELDS]
                        = this->selectionUnitType[Selection::USE_E_SHIELDS] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_S_BALLISTA:
                    this->selectionUnitType[Selection::USE_E_BALLISTAS]
                        = this->selectionUnitType[Selection::USE_E_BALLISTAS] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_A_ARCHER:
                    this->selectionUnitType[Selection::USE_A_ARAB_ARCHERS]
                        = this->selectionUnitType[Selection::USE_A_ARAB_ARCHERS] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_A_SLAVE:
                    this->selectionUnitType[Selection::USE_A_SLAVES]
                        = this->selectionUnitType[Selection::USE_A_SLAVES] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_A_SLINGER:
                    this->selectionUnitType[Selection::USE_A_SLINGERS]
                        = this->selectionUnitType[Selection::USE_A_SLINGERS] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_A_ASSASSIN:
                    this->selectionUnitType[Selection::USE_A_ASSASSINS]
                        = this->selectionUnitType[Selection::USE_A_ASSASSINS] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_A_HARCHER:
                    this->selectionUnitType[Selection::USE_A_HORSE_ARCHERS]
                        = this->selectionUnitType[Selection::USE_A_HORSE_ARCHERS] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_A_SWORDSMAN:
                    this->selectionUnitType[Selection::USE_A_SWORDSMEN]
                        = this->selectionUnitType[Selection::USE_A_SWORDSMEN] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_A_FIRETHROWER:
                    this->selectionUnitType[Selection::USE_A_FIRETHROWERS]
                        = this->selectionUnitType[Selection::USE_A_FIRETHROWERS] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                case OpenSHC::Map::Units::UT_S_FBALLISTA:
                    this->selectionUnitType[Selection::USE_A_FIRE_BALLISTAS]
                        = this->selectionUnitType[Selection::USE_A_FIRE_BALLISTAS] + 1;
                    this->nHasOwnedUnitInSelection = 1;
                    break;
                default:
                    break;
                }
            }
            int _slot = 0;
            for (int k = 0; k < 8; ++k) {
                this->selectionSlots[k] = -1;
            }
            for (int i = 0; i <= 26; ++i) {
                if (this->selectionUnitType[i] != 0) {
                    this->selectionSlots[_slot] = i;
                    _slot = _slot + 1;
                    if (_slot >= 8) {
                        break;
                    }
                }
            }
        }

    }
}
}
