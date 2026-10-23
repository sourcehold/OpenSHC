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

        // FUNCTION: STRONGHOLDCRUSADER 0x005347E0
        void UnitsState::applyDragBoxSelectionByPriority()
        {
            this->field14_0x55c = 0;
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
            int _otherOwnUnits = 0;
            int _catapults = 0;
            int _trebuchets = 0;
            int _siegeTowers = 0;
            int _batteringRams = 0;
            int _shields = 0;
            int _mangonels = 0;
            int _ballistas = 0;
            int _priority = 0;
            uint _lordUnitID = 0;
            int _siegeEngineUnits = 0;
            for (DAT_CurrentUnitSlotID::instance = 1; (int)DAT_CurrentUnitSlotID::instance < (int)this->maxUnitCount;
                DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                if (this->units[DAT_CurrentUnitSlotID::instance].logicalState != OpenSHC::Map::Units::ULS_NORMAL
                    || this->units[DAT_CurrentUnitSlotID::instance].dying != 0
                    || this->units[DAT_CurrentUnitSlotID::instance].isSelectable_OR_matchTime == 0
                    || this->units[DAT_CurrentUnitSlotID::instance].unknownTestAgainst0_2 != 0
                    || this->units[DAT_CurrentUnitSlotID::instance].state.generic
                        == OpenSHC::Map::Units::States::US_JESTER_ROAM_TO
                    || (this->units[DAT_CurrentUnitSlotID::instance].drawX == 0
                        && this->units[DAT_CurrentUnitSlotID::instance].drawY == 0)
                    || this->units[DAT_CurrentUnitSlotID::instance].drawX
                            + this->units[DAT_CurrentUnitSlotID::instance].drawXOffset
                        >= _boxRight
                    || this->units[DAT_CurrentUnitSlotID::instance].drawY
                            + this->units[DAT_CurrentUnitSlotID::instance].someDrawYOffset
                        >= _boxBottom
                    || this->units[DAT_CurrentUnitSlotID::instance].spriteWidthUnk
                            + this->units[DAT_CurrentUnitSlotID::instance].drawX
                            + this->units[DAT_CurrentUnitSlotID::instance].drawXOffset
                        < _boxLeft
                    || this->units[DAT_CurrentUnitSlotID::instance].spriteHeightUnk
                            + this->units[DAT_CurrentUnitSlotID::instance].drawY
                            + this->units[DAT_CurrentUnitSlotID::instance].someDrawYOffset
                        < _boxTop
                    || (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_TUNNELER
                        && (this->units[DAT_CurrentUnitSlotID::instance].state.generic
                                == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk
                            || this->units[DAT_CurrentUnitSlotID::instance].state.generic
                                == OpenSHC::Map::Units::States::US_STAND_UPUnk))) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].owner
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    if (this->units[DAT_CurrentUnitSlotID::instance].owner != 0) {
                        this->field14_0x55c = this->units[DAT_CurrentUnitSlotID::instance].owner;
                    }
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_LORD) {
                    _lordUnitID = DAT_CurrentUnitSlotID::instance;
                    _otherOwnUnits = _otherOwnUnits + 1;
                    continue;
                }
                _siegeEngineUnits = _siegeEngineUnits + 1;
                if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_S_CATAPULT) {
                    _catapults = _catapults + 1;
                } else if (this->units[DAT_CurrentUnitSlotID::instance].unitType
                    == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                    _trebuchets = _trebuchets + 1;
                } else if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_S_TOWER) {
                    _siegeTowers = _siegeTowers + 1;
                } else if (this->units[DAT_CurrentUnitSlotID::instance].unitType
                    == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {
                    _batteringRams = _batteringRams + 1;
                } else if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_S_SHIELD) {
                    _shields = _shields + 1;
                } else if (this->units[DAT_CurrentUnitSlotID::instance].unitType
                    == OpenSHC::Map::Units::UT_S_MANGONEL) {
                    _mangonels = _mangonels + 1;
                } else if (this->units[DAT_CurrentUnitSlotID::instance].unitType
                    == OpenSHC::Map::Units::UT_S_BALLISTA) {
                    _ballistas = _ballistas + 1;
                } else if (this->units[DAT_CurrentUnitSlotID::instance].unitType
                    == OpenSHC::Map::Units::UT_S_FBALLISTA) {
                    _priority = _priority + 1;
                } else {
                    _otherOwnUnits = _otherOwnUnits + 1;
                }
            }
            if (_lordUnitID != 0 && _siegeEngineUnits != 0) {
                _otherOwnUnits = _otherOwnUnits - 1;
                _lordUnitID = 0;
            }
            if (_otherOwnUnits != 0 || _catapults != 0 || _trebuchets != 0 || _siegeTowers != 0 || _batteringRams != 0
                || _shields != 0 || _mangonels != 0 || _ballistas != 0 || _priority != 0) {
                _priority = 0;
            } else {
                _priority = 9;
            }
            this->totalUnitsInSelection = 0;
            for (DAT_CurrentUnitSlotID::instance = 1; (int)DAT_CurrentUnitSlotID::instance < (int)this->maxUnitCount;
                DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                this->units[DAT_CurrentUnitSlotID::instance].isSelected = 0;
                if (this->units[DAT_CurrentUnitSlotID::instance].logicalState != OpenSHC::Map::Units::ULS_NORMAL
                    || this->units[DAT_CurrentUnitSlotID::instance].dying != 0
                    || this->units[DAT_CurrentUnitSlotID::instance].isSelectable_OR_matchTime == 0
                    || this->units[DAT_CurrentUnitSlotID::instance].unknownTestAgainst0_2 != 0
                    || this->units[DAT_CurrentUnitSlotID::instance].state.generic
                        == OpenSHC::Map::Units::States::US_JESTER_ROAM_TO
                    || (this->units[DAT_CurrentUnitSlotID::instance].drawX == 0
                        && this->units[DAT_CurrentUnitSlotID::instance].drawY == 0)
                    || this->units[DAT_CurrentUnitSlotID::instance].drawX
                            + this->units[DAT_CurrentUnitSlotID::instance].drawXOffset
                        >= _boxRight
                    || this->units[DAT_CurrentUnitSlotID::instance].drawY
                            + this->units[DAT_CurrentUnitSlotID::instance].someDrawYOffset
                        >= _boxBottom
                    || this->units[DAT_CurrentUnitSlotID::instance].spriteWidthUnk
                            + this->units[DAT_CurrentUnitSlotID::instance].drawX
                            + this->units[DAT_CurrentUnitSlotID::instance].drawXOffset
                        < _boxLeft
                    || this->units[DAT_CurrentUnitSlotID::instance].spriteHeightUnk
                            + this->units[DAT_CurrentUnitSlotID::instance].drawY
                            + this->units[DAT_CurrentUnitSlotID::instance].someDrawYOffset
                        < _boxTop
                    || (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_TUNNELER
                        && (this->units[DAT_CurrentUnitSlotID::instance].state.generic
                                == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk
                            || this->units[DAT_CurrentUnitSlotID::instance].state.generic
                                == OpenSHC::Map::Units::States::US_STAND_UPUnk))) {
                    continue;
                }
                switch (_priority) {
                case 0:
                    if (this->units[DAT_CurrentUnitSlotID::instance].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        if (this->units[DAT_CurrentUnitSlotID::instance].unitType != OpenSHC::Map::Units::UT_LORD
                            || _lordUnitID != 0) {
                            this->units[DAT_CurrentUnitSlotID::instance].isSelected = 1;
                            this->totalUnitsInSelection = this->totalUnitsInSelection + 1;
                        }
                    }
                    break;
                case 1:
                    if (this->units[DAT_CurrentUnitSlotID::instance].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        if (this->units[DAT_CurrentUnitSlotID::instance].unitType
                            == OpenSHC::Map::Units::UT_S_CATAPULT) {
                            this->units[DAT_CurrentUnitSlotID::instance].isSelected = 1;
                            this->totalUnitsInSelection = this->totalUnitsInSelection + 1;
                        }
                    }
                    break;
                case 2:
                    if (this->units[DAT_CurrentUnitSlotID::instance].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        if (this->units[DAT_CurrentUnitSlotID::instance].unitType
                            == OpenSHC::Map::Units::UT_S_TREBUCHET) {
                            this->units[DAT_CurrentUnitSlotID::instance].isSelected = 1;
                            this->totalUnitsInSelection = this->totalUnitsInSelection + 1;
                        }
                    }
                    break;
                case 3:
                    if (this->units[DAT_CurrentUnitSlotID::instance].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_S_TOWER) {
                            this->units[DAT_CurrentUnitSlotID::instance].isSelected = 1;
                            this->totalUnitsInSelection = this->totalUnitsInSelection + 1;
                        }
                    }
                    break;
                case 4:
                    if (this->units[DAT_CurrentUnitSlotID::instance].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        if (this->units[DAT_CurrentUnitSlotID::instance].unitType
                            == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {
                            this->units[DAT_CurrentUnitSlotID::instance].isSelected = 1;
                            this->totalUnitsInSelection = this->totalUnitsInSelection + 1;
                        }
                    }
                    break;
                case 5:
                    if (this->units[DAT_CurrentUnitSlotID::instance].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_S_SHIELD) {
                            this->units[DAT_CurrentUnitSlotID::instance].isSelected = 1;
                            this->totalUnitsInSelection = this->totalUnitsInSelection + 1;
                        }
                    }
                    break;
                case 6:
                    if (this->units[DAT_CurrentUnitSlotID::instance].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        if (this->units[DAT_CurrentUnitSlotID::instance].unitType
                            == OpenSHC::Map::Units::UT_S_MANGONEL) {
                            this->units[DAT_CurrentUnitSlotID::instance].isSelected = 1;
                            this->totalUnitsInSelection = this->totalUnitsInSelection + 1;
                        }
                    }
                    break;
                case 7:
                    if (this->units[DAT_CurrentUnitSlotID::instance].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        if (this->units[DAT_CurrentUnitSlotID::instance].unitType
                            == OpenSHC::Map::Units::UT_S_BALLISTA) {
                            this->units[DAT_CurrentUnitSlotID::instance].isSelected = 1;
                            this->totalUnitsInSelection = this->totalUnitsInSelection + 1;
                        }
                    }
                    break;
                case 8:
                    if (this->units[DAT_CurrentUnitSlotID::instance].owner
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        if (this->units[DAT_CurrentUnitSlotID::instance].unitType
                            == OpenSHC::Map::Units::UT_S_FBALLISTA) {
                            this->units[DAT_CurrentUnitSlotID::instance].isSelected = 1;
                            this->totalUnitsInSelection = this->totalUnitsInSelection + 1;
                        }
                    }
                    break;
                case 9:
                    if (this->units[DAT_CurrentUnitSlotID::instance].owner
                        != DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        this->units[DAT_CurrentUnitSlotID::instance].isSelected = 1;
                        this->totalUnitsInSelection = this->totalUnitsInSelection + 1;
                    }
                }
            }
        }

    }
}
}
