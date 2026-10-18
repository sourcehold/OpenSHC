#include "OpenSHC/Map/Units/UnitsState.func.hpp"
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
                (&this->selectionEuropeanArchers)[i] = 0;
            }
            for (int unitID = 1; unitID < (int)this->maxUnitCount; ++unitID) {
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
                    this->selectionEuropeanArchers = this->selectionEuropeanArchers + 1;
                    break;
                case OpenSHC::Map::Units::UT_E_XBOW:
                    this->selectionCrossbowmen = this->selectionCrossbowmen + 1;
                    break;
                case OpenSHC::Map::Units::UT_E_SPEAR:
                    this->selectionSpearmen = this->selectionSpearmen + 1;
                    break;
                case OpenSHC::Map::Units::UT_E_PIKE:
                    this->selectionPikemen = this->selectionPikemen + 1;
                    break;
                case OpenSHC::Map::Units::UT_E_MACE:
                    this->selectionMacemen = this->selectionMacemen + 1;
                    break;
                case OpenSHC::Map::Units::UT_E_SWORD:
                    this->selectionSwordsmen = this->selectionSwordsmen + 1;
                    break;
                case OpenSHC::Map::Units::UT_E_KNIGHT:
                    this->selectionKnights = this->selectionKnights + 1;
                    break;
                case OpenSHC::Map::Units::UT_E_LADDER:
                    this->selectionLaddermen = this->selectionLaddermen + 1;
                    break;
                case OpenSHC::Map::Units::UT_E_ENGINEER:
                    this->selectionEngineers = this->selectionEngineers + 1;
                    break;
                case OpenSHC::Map::Units::UT_E_MONK:
                    this->selectionMonks = this->selectionMonks + 1;
                    break;
                case OpenSHC::Map::Units::UT_TUNNELER:
                    this->selectionTunnelers = this->selectionTunnelers + 1;
                    break;
                case OpenSHC::Map::Units::UT_S_CATAPULT:
                    this->selectionCatapults = this->selectionCatapults + 1;
                    break;
                case OpenSHC::Map::Units::UT_S_TREBUCHET:
                    this->selectionTrebuchets = this->selectionTrebuchets + 1;
                    break;
                case OpenSHC::Map::Units::UT_S_MANGONEL:
                    this->selectionMangonel = this->selectionMangonel + 1;
                    break;
                case OpenSHC::Map::Units::UT_S_TOWER:
                    this->selectionSiegeTower = this->selectionSiegeTower + 1;
                    break;
                case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                    this->selectionBatteringRam = this->selectionBatteringRam + 1;
                    break;
                case OpenSHC::Map::Units::UT_S_SHIELD:
                    this->selectionShield = this->selectionShield + 1;
                    break;
                case OpenSHC::Map::Units::UT_S_BALLISTA:
                    this->selectionBallista = this->selectionBallista + 1;
                    break;
                case OpenSHC::Map::Units::UT_A_ARCHER:
                    this->selectionArabArcher = this->selectionArabArcher + 1;
                    break;
                case OpenSHC::Map::Units::UT_A_SLAVE:
                    this->selectionArabSlave = this->selectionArabSlave + 1;
                    break;
                case OpenSHC::Map::Units::UT_A_SLINGER:
                    this->selectionArabSlinger = this->selectionArabSlinger + 1;
                    break;
                case OpenSHC::Map::Units::UT_A_ASSASSIN:
                    this->selectionArabAssassin = this->selectionArabAssassin + 1;
                    break;
                case OpenSHC::Map::Units::UT_A_HARCHER:
                    this->selectionArabHorseArchers = this->selectionArabHorseArchers + 1;
                    break;
                case OpenSHC::Map::Units::UT_A_SWORDSMAN:
                    this->selectionArabSwordsman = this->selectionArabSwordsman + 1;
                    break;
                case OpenSHC::Map::Units::UT_A_FIRETHROWER:
                    this->selectionArabFireThrower = this->selectionArabFireThrower + 1;
                    break;
                case OpenSHC::Map::Units::UT_S_FBALLISTA:
                    this->selectionFireBallista = this->selectionFireBallista + 1;
                    break;
                default:
                    continue;
                }
                this->nHasOwnedUnitInSelection = 1;
            }
            this->selectionSlots[1] = -1;
            this->selectionSlots[2] = -1;
            this->selectionSlots[3] = -1;
            this->selectionSlots[4] = -1;
            this->selectionSlots[5] = -1;
            this->selectionSlots[6] = -1;
            this->selectionSlots[7] = -1;
            this->selectionSlots[0] = -1;
            int _slot = 0;
            for (int i = 0; i < 27; ++i) {
                if ((&this->selectionEuropeanArchers)[i] != 0) {
                    this->selectionSlots[_slot] = i;
                    _slot = _slot + 1;
                    if (_slot > 7) {
                        return;
                    }
                }
            }
        }

    }
}
}
