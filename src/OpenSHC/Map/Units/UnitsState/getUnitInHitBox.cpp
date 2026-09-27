#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053D9C0
        uint UnitsState::getUnitInHitBox(undefined4 param_1)
        {
            int _hitboxXStart;
            int _hitboxXEnd;
            if (DAT_MouseState::instance.hitboxXEnd < DAT_MouseState::instance.hitboxXStart) {
                _hitboxXStart = DAT_MouseState::instance.hitboxXEnd;
                _hitboxXEnd = DAT_MouseState::instance.hitboxXStart;
            } else {
                _hitboxXStart = DAT_MouseState::instance.hitboxXStart;
                _hitboxXEnd = DAT_MouseState::instance.hitboxXEnd;
            }
            int _hitboxYStart;
            int _hitboxYEnd;
            if (DAT_MouseState::instance.hitboxYEnd < DAT_MouseState::instance.hitboxYStart) {
                _hitboxYStart = DAT_MouseState::instance.hitboxYEnd;
                _hitboxYEnd = DAT_MouseState::instance.hitboxYStart;
            } else {
                _hitboxYStart = DAT_MouseState::instance.hitboxYStart;
                _hitboxYEnd = DAT_MouseState::instance.hitboxYEnd;
            }
            int _currentPlayerSlotID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            for (DAT_CurrentUnitSlotID::instance = 1; (int)DAT_CurrentUnitSlotID::instance < (int)this->maxUnitCount;
                DAT_CurrentUnitSlotID::instance = DAT_CurrentUnitSlotID::instance + 1) {
                if (this->units[DAT_CurrentUnitSlotID::instance].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].dying != 0) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].unknownTestAgainst0_2 != 0) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].state.generic
                    == OpenSHC::Map::Units::States::US_JESTER_ROAM_TO) {
                    continue;
                }
                if (DAT_MinimapViewState::instance.field15_0x3c == 0) {
                    if (this->units[DAT_CurrentUnitSlotID::instance].drawX == 0
                        && this->units[DAT_CurrentUnitSlotID::instance].drawY == 0) {
                        continue;
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].drawX
                            + this->units[DAT_CurrentUnitSlotID::instance].drawXOffset
                        >= _hitboxXEnd) {
                        continue;
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].drawY
                            + this->units[DAT_CurrentUnitSlotID::instance].someDrawYOffset
                        >= _hitboxYEnd) {
                        continue;
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].spriteWidthUnk
                            + this->units[DAT_CurrentUnitSlotID::instance].drawX
                            + this->units[DAT_CurrentUnitSlotID::instance].drawXOffset
                        < _hitboxXStart) {
                        continue;
                    }
                    if (this->units[DAT_CurrentUnitSlotID::instance].spriteHeightUnk
                            + this->units[DAT_CurrentUnitSlotID::instance].drawY
                            + this->units[DAT_CurrentUnitSlotID::instance].someDrawYOffset
                        < _hitboxYStart) {
                        continue;
                    }
                } else {
                    int _tileDistanceX = DAT_ViewportRenderState::instance.viewportState.mouseTileX
                        - this->units[DAT_CurrentUnitSlotID::instance].x;
                    if (_tileDistanceX < 0) {
                        _tileDistanceX = -_tileDistanceX;
                    }
                    if (_tileDistanceX > 1) {
                        continue;
                    }
                    int _tileDistanceY = DAT_ViewportRenderState::instance.viewportState.mouseTileY
                        - this->units[DAT_CurrentUnitSlotID::instance].y;
                    if (_tileDistanceY < 0) {
                        _tileDistanceY = -_tileDistanceY;
                    }
                    if (_tileDistanceY > 1) {
                        continue;
                    }
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_S_TOWER
                    && this->units[DAT_CurrentUnitSlotID::instance].state.generic
                        == (OpenSHC::Map::Units::States::US_STAND_UPUnk | OpenSHC::Map::Units::States::US_IDLEUnk)) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_TUNNELER
                    && (this->units[DAT_CurrentUnitSlotID::instance].state.generic
                            == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk
                        || this->units[DAT_CurrentUnitSlotID::instance].state.generic
                            == OpenSHC::Map::Units::States::US_STAND_UPUnk)) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_CAMELSHBEAR) {
                    continue;
                }
                if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_ANTELOPESHDEER
                    && MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::selectionHasNoRangedUnits, this)()
                        != 0) {
                    continue;
                }
                switch (param_1) {
                case 0:
                    return DAT_CurrentUnitSlotID::instance;
                case 1:
                    if (DAT_GameState::instance.mapAndTime
                            .playerTeams[this->units[DAT_CurrentUnitSlotID::instance].owner]
                        != DAT_GameState::instance.mapAndTime.playerTeams[_currentPlayerSlotID]) {
                        return DAT_CurrentUnitSlotID::instance;
                    }
                    break;
                case 2:
                    if (this->units[DAT_CurrentUnitSlotID::instance].owner == _currentPlayerSlotID) {
                        if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_S_CATAPULT
                            || this->units[DAT_CurrentUnitSlotID::instance].unitType
                                == OpenSHC::Map::Units::UT_S_TREBUCHET
                            || this->units[DAT_CurrentUnitSlotID::instance].unitType
                                == OpenSHC::Map::Units::UT_S_BATTERINGRAM
                            || this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_S_TOWER
                            || this->units[DAT_CurrentUnitSlotID::instance].unitType
                                == OpenSHC::Map::Units::UT_S_MANGONEL
                            || this->units[DAT_CurrentUnitSlotID::instance].unitType
                                == OpenSHC::Map::Units::UT_S_BALLISTA
                            || this->units[DAT_CurrentUnitSlotID::instance].unitType
                                == OpenSHC::Map::Units::UT_S_FBALLISTA
                            || this->units[DAT_CurrentUnitSlotID::instance].unitType
                                == OpenSHC::Map::Units::UT_S_SHIELD) {
                            return DAT_CurrentUnitSlotID::instance;
                        }
                    }
                    break;
                case 3:
                    if (this->units[DAT_CurrentUnitSlotID::instance].owner == _currentPlayerSlotID) {
                        return DAT_CurrentUnitSlotID::instance;
                    }
                    break;
                case 4:
                    if (this->units[DAT_CurrentUnitSlotID::instance].owner != 0
                        && this->units[DAT_CurrentUnitSlotID::instance].isSelectable_OR_matchTime != 0) {
                        return DAT_CurrentUnitSlotID::instance;
                    }
                    break;
                case 5:
                    if (this->units[DAT_CurrentUnitSlotID::instance].owner == _currentPlayerSlotID
                        && this->units[DAT_CurrentUnitSlotID::instance].isSelectable_OR_matchTime != 0) {
                        return DAT_CurrentUnitSlotID::instance;
                    }
                    break;
                case 6:
                    if (this->units[DAT_CurrentUnitSlotID::instance].unitType == OpenSHC::Map::Units::UT_E_LADDER
                        && this->units[DAT_CurrentUnitSlotID::instance].owner == _currentPlayerSlotID) {
                        return DAT_CurrentUnitSlotID::instance;
                    }
                }
            }
            return 0;
        }

    }
}
}
