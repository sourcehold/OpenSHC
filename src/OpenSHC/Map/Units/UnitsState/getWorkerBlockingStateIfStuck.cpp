#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::Resources::ResourceType;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053A150
        int UnitsState::getWorkerBlockingStateIfStuck(int unitID)
        {
            int _state = this->units[unitID].state.generic;
            if (this->units[unitID].dying != 0) {
                return 0;
            }
            switch (this->units[unitID].unitType) {
            case OpenSHC::Map::Units::UT_WOODCUTTER:
                if (_state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
                    return 0x2f;
                }
                if (_state == (UnitState)10) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::findTree, DAT_LandscapeState::ptr)(
                            this->units[unitID].owner, this->units[unitID].x, this->units[unitID].y)
                        != 0) {
                        return 0;
                    }
                    return 0x32;
                }
                break;
            case OpenSHC::Map::Units::UT_FLETCHER:
                if (_state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
                    return 0x31;
                }
                if (_state != OpenSHC::Map::Units::States::US_STAND_UPUnk) {
                    return 0;
                }
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                        DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_WOOD, 1, this->units[unitID].owner)
                    != 0) {
                    return 0;
                }
                return 0x33;
            case OpenSHC::Map::Units::UT_HUNTER:
                if (_state == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
                    return 0x30;
                }
                if (_state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::findNearestShootableDeer, this)(unitID)
                        != 0) {
                        return 0;
                    }
                    return 0x34;
                }
                break;
            case OpenSHC::Map::Units::UT_QUARRYWORKER:
            case OpenSHC::Map::Units::UT_PITCHMAN:
                if (_state == (UnitState)2) {
                    return 0x2f;
                }
                break;
            case OpenSHC::Map::Units::UT_WHEATFARMER:
                if (_state == (OpenSHC::Map::Units::States::US_STAND_UPUnk | OpenSHC::Map::Units::States::US_IDLEUnk)) {
                    return 0x2f;
                }
                break;
            case OpenSHC::Map::Units::UT_HOPSFARMER:
                if (_state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
                    return 0x2f;
                }
                break;
            case OpenSHC::Map::Units::UT_APPLEFARMER:
                if (_state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
                    return 0x30;
                }
                break;
            case OpenSHC::Map::Units::UT_DAIRYFARMER:
                if (_state == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
                    return 0x30;
                }
                break;
            case OpenSHC::Map::Units::UT_MILLER:
                if (_state == OpenSHC::Map::Units::States::US_IDLEUnk) {
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                            DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_WHEAT, 1, this->units[unitID].owner)
                        != 0) {
                        return 0;
                    }
                    return 0x35;
                }
                if (_state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
                    return 0x2f;
                }
                break;
            case OpenSHC::Map::Units::UT_BAKER:
                if (_state < 0) {
                    break;
                }
                if (_state < 2) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingResourceAmountByUid,
                            DAT_BuildingsState::ptr)(
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1,
                            DAT_BuildingsState::instance
                                .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                        .workplaceBuildingID_1]
                                .uid,
                            OpenSHC::Game::Resources::RT_FLOUR)
                        != 0) {
                        return 0;
                    }
                    return 0x36;
                }
                if (_state == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
                    return 0x30;
                }
                break;
            case OpenSHC::Map::Units::UT_BREWER:
                if (_state == OpenSHC::Map::Units::States::US_IDLEUnk) {
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                            DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_HOPS, 1,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner)
                        != 0) {
                        return 0;
                    }
                    return 0x37;
                }
                if (_state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
                    return 0x2f;
                }
                break;
            case OpenSHC::Map::Units::UT_POLETURNER:
                if (_state == OpenSHC::Map::Units::States::US_IDLEUnk) {
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                            DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_WOOD, 1, this->units[unitID].owner)
                        != 0) {
                        return 0;
                    }
                    return 0x33;
                }
                if (_state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
                    return 0x31;
                }
                break;
            case OpenSHC::Map::Units::UT_SMITH:
            case OpenSHC::Map::Units::UT_ARMORER:
                if (_state != OpenSHC::Map::Units::States::US_IDLEUnk) {
                    if (_state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
                        return 0x31;
                    }
                    if (_state
                        != (OpenSHC::Map::Units::States::US_STAND_UPUnk | OpenSHC::Map::Units::States::US_IDLEUnk)) {
                        return 0;
                    }
                }
                if (MACRO_CALL_MEMBER(
                        OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                        DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_IRON, 1, this->units[unitID].owner)
                    != 0) {
                    return 0;
                }
                return 0x38;
            case OpenSHC::Map::Units::UT_TANNER:
                if (_state == OpenSHC::Map::Units::States::US_IDLEUnk) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::findNearestIdleCowForPlayer, this)(
                            this->units[unitID].owner, this->units[unitID].x, this->units[unitID].y)
                        != 0) {
                        return 0;
                    }
                    return 0x39;
                }
                if (_state == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
                    return 0x31;
                }
                break;
            case OpenSHC::Map::Units::UT_TRANSPORTMINER:
                if (_state == (UnitState)3) {
                    return 0x2f;
                }
                break;
            case OpenSHC::Map::Units::UT_INNKEEPER:
                if (_state == OpenSHC::Map::Units::States::US_IDLEUnk) {
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                            DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_ALE, 1, this->units[unitID].owner)
                        != 0) {
                        return 0;
                    }
                    return 0x3a;
                }
            }
            return 0;
        }

    }
}
}
