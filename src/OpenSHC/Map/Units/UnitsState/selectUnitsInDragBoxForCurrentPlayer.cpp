#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00534D10
        void UnitsState::selectUnitsInDragBoxForCurrentPlayer()
        {
            LONG _boxLeft;
            LONG _boxRight;
            if (DAT_MouseState::instance.selectionBox.right < DAT_MouseState::instance.selectionBox.left) {
                _boxLeft = DAT_MouseState::instance.selectionBox.right;
                _boxRight = DAT_MouseState::instance.selectionBox.left;
            } else {
                _boxLeft = DAT_MouseState::instance.selectionBox.left;
                _boxRight = DAT_MouseState::instance.selectionBox.right;
            }
            LONG _boxTop;
            LONG _boxBottom;
            if (DAT_MouseState::instance.selectionBox.bottom < DAT_MouseState::instance.selectionBox.top) {
                _boxTop = DAT_MouseState::instance.selectionBox.bottom;
                _boxBottom = DAT_MouseState::instance.selectionBox.top;
            } else {
                _boxTop = DAT_MouseState::instance.selectionBox.top;
                _boxBottom = DAT_MouseState::instance.selectionBox.bottom;
            }
            this->totalUnitsInSelection = 0;
            for (DAT_CurrentUnitSlotID::instance = 1; (int)DAT_CurrentUnitSlotID::instance < (int)this->maxUnitCount;
                DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                this->units[DAT_CurrentUnitSlotID::instance].isSelected = 0;
                if (this->units[DAT_CurrentUnitSlotID::instance].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].dying != 0) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].isSelectable_OR_matchTime == 0) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].unknownTestAgainst0_2 != 0) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].state.generic
                    == OpenSHC::Map::Units::States::US_JESTER_ROAM_TO) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].ifSelectedThenPlayerID
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    if (this->units[DAT_CurrentUnitSlotID::instance].drawX == 0
                        && this->units[DAT_CurrentUnitSlotID::instance].drawY == 0) {
                        continue;
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].drawX
                            + this->units[DAT_CurrentUnitSlotID::instance].drawXOffset
                        >= _boxRight) {
                        continue;
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].drawY
                            + this->units[DAT_CurrentUnitSlotID::instance].someDrawYOffset
                        >= _boxBottom) {
                        continue;
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].spriteWidthUnk
                            + this->units[DAT_CurrentUnitSlotID::instance].drawX
                            + this->units[DAT_CurrentUnitSlotID::instance].drawXOffset
                        < _boxLeft) {
                        continue;
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].spriteHeightUnk
                            + this->units[DAT_CurrentUnitSlotID::instance].drawY
                            + this->units[DAT_CurrentUnitSlotID::instance].someDrawYOffset
                        < _boxTop) {
                        continue;
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_S_TOWER
                        && this->units[DAT_CurrentUnitSlotID::instance].state.generic
                            == (OpenSHC::Map::Units::States::US_STAND_UPUnk
                                | OpenSHC::Map::Units::States::US_IDLEUnk)) {
                        continue;
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_TUNNELER
                        && (this->units[DAT_CurrentUnitSlotID::instance].state.generic
                                == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk
                            || this->units[DAT_CurrentUnitSlotID::instance].state.generic
                                == OpenSHC::Map::Units::States::US_STAND_UPUnk)) {
                        continue;
                    }
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID
                    && this->units[DAT_CurrentUnitSlotID::instance].unitType != OpenSHC::Map::Units::UT_LORD) {
                    this->units[DAT_CurrentUnitSlotID::instance].isSelected = 1;
                    this->totalUnitsInSelection = this->totalUnitsInSelection + 1;
                }
            }
        }

    }
}
}
