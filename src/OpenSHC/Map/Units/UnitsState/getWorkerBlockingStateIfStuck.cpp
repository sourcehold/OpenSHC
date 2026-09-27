#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::Resources::ResourceType;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053A150
        int UnitsState::getWorkerBlockingStateIfStuck(int unitID)
        {
            if (this->units[unitID].dying != 0) {
                return 0;
            }
            switch (this->units[unitID].unitType) {
            case OpenSHC::Map::Units::UT_WOODCUTTER:
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
                    return 0x2f;
                }
                if (this->units[unitID].state.generic == (UnitState)10) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::findTree, DAT_LandscapeState::ptr)(
                            this->units[unitID].owner, this->units[unitID].x, this->units[unitID].y)
                        != 0) {
                        return 0;
                    }
                    return 0x32;
                }
                break;
            case OpenSHC::Map::Units::UT_FLETCHER:
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
                    return 0x31;
                }
                if (this->units[unitID].state.generic != OpenSHC::Map::Units::States::US_STAND_UPUnk) {
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
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
                    return 0x30;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::findNearestShootableDeer, this)(unitID)
                        != 0) {
                        return 0;
                    }
                    return 0x34;
                }
                break;
            case OpenSHC::Map::Units::UT_QUARRYWORKER:
            case OpenSHC::Map::Units::UT_PITCHMAN:
                if (this->units[unitID].state.generic == (UnitState)2) {
                    return 0x2f;
                }
                break;
            case OpenSHC::Map::Units::UT_WHEATFARMER:
                if (this->units[unitID].state.generic
                    == (OpenSHC::Map::Units::States::US_STAND_UPUnk | OpenSHC::Map::Units::States::US_IDLEUnk)) {
                    return 0x2f;
                }
                break;
            case OpenSHC::Map::Units::UT_HOPSFARMER:
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
                    return 0x2f;
                }
                break;
            case OpenSHC::Map::Units::UT_APPLEFARMER:
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
                    return 0x30;
                }
                break;
            case OpenSHC::Map::Units::UT_DAIRYFARMER:
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_RELOAD_WEAPONUnk) {
                    return 0x30;
                }
                break;
            case OpenSHC::Map::Units::UT_MILLER:
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_IDLEUnk) {
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                            DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_WHEAT, 1, this->units[unitID].owner)
                        != 0) {
                        return 0;
                    }
                    return 0x35;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
                    return 0x2f;
                }
                break;
            case OpenSHC::Map::Units::UT_BAKER:
                if ((short)this->units[unitID].state.generic < 0) {
                    break;
                }
                if ((short)this->units[unitID].state.generic < 2) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingResourceAmountByUid,
                            DAT_BuildingsState::ptr)(this->units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1,
                            DAT_BuildingsState::instance
                                .buildings[this->units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1]
                                .uid,
                            OpenSHC::Game::Resources::RT_FLOUR)
                        != 0) {
                        return 0;
                    }
                    return 0x36;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
                    return 0x30;
                }
                break;
            case OpenSHC::Map::Units::UT_BREWER:
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_IDLEUnk) {
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                            DAT_BuildingsState::ptr)(
                            OpenSHC::Game::Resources::RT_HOPS, 1, this->units[DAT_CurrentUnitSlotID::instance].owner)
                        != 0) {
                        return 0;
                    }
                    return 0x37;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
                    return 0x2f;
                }
                break;
            case OpenSHC::Map::Units::UT_POLETURNER:
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_IDLEUnk) {
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                            DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_WOOD, 1, this->units[unitID].owner)
                        != 0) {
                        return 0;
                    }
                    return 0x33;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
                    return 0x31;
                }
                break;
            case OpenSHC::Map::Units::UT_SMITH:
            case OpenSHC::Map::Units::UT_ARMORER:
                if (this->units[unitID].state.generic != OpenSHC::Map::Units::States::US_IDLEUnk) {
                    if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
                        return 0x31;
                    }
                    if (this->units[unitID].state.generic
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
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_IDLEUnk) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::findNearestIdleCowForPlayer, this)(
                            this->units[unitID].owner, this->units[unitID].x, this->units[unitID].y)
                        != 0) {
                        return 0;
                    }
                    return 0x39;
                }
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk) {
                    return 0x31;
                }
                break;
            case OpenSHC::Map::Units::UT_TRANSPORTMINER:
                if (this->units[unitID].state.generic == (UnitState)3) {
                    return 0x2f;
                }
                break;
            case OpenSHC::Map::Units::UT_INNKEEPER:
                if (this->units[unitID].state.generic == OpenSHC::Map::Units::States::US_IDLEUnk) {
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
