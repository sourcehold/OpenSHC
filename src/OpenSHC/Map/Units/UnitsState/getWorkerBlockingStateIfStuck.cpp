#include "../UnitsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/States/UnitState_Baker.hpp"
#include "OpenSHC/Map/Units/States/UnitState_DairyFarmer.hpp"
#include "OpenSHC/Map/Units/States/UnitState_Fletcher.hpp"
#include "OpenSHC/Map/Units/States/UnitState_HopsFarmer.hpp"
#include "OpenSHC/Map/Units/States/UnitState_Hunter.hpp"
#include "OpenSHC/Map/Units/States/UnitState_Miller.hpp"
#include "OpenSHC/Map/Units/States/UnitState_QuarryWorker.hpp"
#include "OpenSHC/Map/Units/States/UnitState_WheatFarmer.hpp"
#include "OpenSHC/Map/Units/States/UnitState_Woodcutter.hpp"
#include "OpenSHC/Map/Units/WorkerBlockingState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0053A150
        int UnitsState::getWorkerBlockingStateIfStuck(int unitID)
        {
            int _state = this->units[unitID].state.generic;
            if (this->units[unitID].dying) {
                return OpenSHC::Map::Units::WBS_NONE;
            }
            switch (this->units[unitID].unitType) {
            case OpenSHC::Map::Units::UT_WOODCUTTER:
                if (_state == OpenSHC::Map::Units::States::USWC_AWAITING_STORE_SPACE) {
                    return OpenSHC::Map::Units::WBS_STOCKPILE_FULL;
                }
                if (_state == OpenSHC::Map::Units::States::USWC_RESTING) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::findTree, DAT_LandscapeState::ptr)(
                            this->units[unitID].owner, this->units[unitID].x, this->units[unitID].y)
                        != 0) {
                        return OpenSHC::Map::Units::WBS_NONE;
                    }
                    return OpenSHC::Map::Units::WBS_NO_TREES;
                }
                break;
            case OpenSHC::Map::Units::UT_FLETCHER:
                switch (_state) {
                case OpenSHC::Map::Units::States::USF_AWAITING_STORE_SPACE:
                    return OpenSHC::Map::Units::WBS_ARMOURY_FULL;
                case OpenSHC::Map::Units::States::USF_WAITING_OR_RESTING:
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                            DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_WOOD, 1, this->units[unitID].owner)
                        != 0) {
                        return OpenSHC::Map::Units::WBS_NONE;
                    }
                    return OpenSHC::Map::Units::WBS_NO_WOOD;
                }
                break;
            case OpenSHC::Map::Units::UT_HUNTER:
                if (_state == OpenSHC::Map::Units::States::USH_AWAITING_STORE_SPACE) {
                    return OpenSHC::Map::Units::WBS_GRANARY_FULL;
                }
                if (_state == OpenSHC::Map::Units::States::USH_RESTING_7) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::findNearestShootableDeer, this)(unitID)
                        != 0) {
                        return OpenSHC::Map::Units::WBS_NONE;
                    }
                    return OpenSHC::Map::Units::WBS_NO_DEER;
                }
                break;
            case OpenSHC::Map::Units::UT_QUARRYWORKER:
            case OpenSHC::Map::Units::UT_PITCHMAN:
                switch (_state) {
                case OpenSHC::Map::Units::States::USQW_AWAITING_STORE_SPACE:
                    return OpenSHC::Map::Units::WBS_STOCKPILE_FULL;
                }
                break;
            case OpenSHC::Map::Units::UT_WHEATFARMER:
                if (_state == OpenSHC::Map::Units::States::USWF_AWAITING_STORE_SPACE) {
                    return OpenSHC::Map::Units::WBS_STOCKPILE_FULL;
                }
                break;
            case OpenSHC::Map::Units::UT_HOPSFARMER:
                if (_state == OpenSHC::Map::Units::States::USHF_AWAIT_STORE_SPACE) {
                    return OpenSHC::Map::Units::WBS_STOCKPILE_FULL;
                }
                break;
            case OpenSHC::Map::Units::UT_APPLEFARMER:
                if (_state == OpenSHC::Map::Units::States::US_FIRE_WEAPONUnk) {
                    return OpenSHC::Map::Units::WBS_GRANARY_FULL;
                }
                break;
            case OpenSHC::Map::Units::UT_DAIRYFARMER:
                if (_state == OpenSHC::Map::Units::States::USDF_AWAIT_STORE_SPACE) {
                    return OpenSHC::Map::Units::WBS_GRANARY_FULL;
                }
                break;
            case OpenSHC::Map::Units::UT_MILLER:
                switch (_state) {
                case OpenSHC::Map::Units::States::USM_WAITING_1:
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                            DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_WHEAT, 1, this->units[unitID].owner)
                        != 0) {
                        return OpenSHC::Map::Units::WBS_NONE;
                    }
                    return OpenSHC::Map::Units::WBS_NO_WHEAT;
                case OpenSHC::Map::Units::States::USM_AWAITING_STORE_SPACE:
                    return OpenSHC::Map::Units::WBS_STOCKPILE_FULL;
                }
                break;
            case OpenSHC::Map::Units::UT_BAKER:
                switch (_state) {
                case OpenSHC::Map::Units::States::USB_WAITING_0:
                case OpenSHC::Map::Units::States::USB_WAITING_1:
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingResourceAmountByUid,
                            DAT_BuildingsState::ptr)(
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].workplaceBuildingID_1,
                            DAT_BuildingsState::instance
                                .buildings[DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance]
                                        .workplaceBuildingID_1]
                                .uid,
                            OpenSHC::Game::Resources::RT_FLOUR)
                        != 0) {
                        return OpenSHC::Map::Units::WBS_NONE;
                    }
                    return OpenSHC::Map::Units::WBS_NO_FLOUR;
                case OpenSHC::Map::Units::States::USB_AWAITING_STORE_SPACE:
                    return OpenSHC::Map::Units::WBS_GRANARY_FULL;
                }
                break;
            case OpenSHC::Map::Units::UT_BREWER:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_IDLEUnk:
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                            DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_HOPS, 1,
                            DAT_UnitsState::instance.units[DAT_CurrentUnitSlotID::instance].owner)
                        != 0) {
                        return OpenSHC::Map::Units::WBS_NONE;
                    }
                    return OpenSHC::Map::Units::WBS_NO_HOPS;
                case OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk:
                    return OpenSHC::Map::Units::WBS_STOCKPILE_FULL;
                }
                break;
            case OpenSHC::Map::Units::UT_POLETURNER:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_IDLEUnk:
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                            DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_WOOD, 1, this->units[unitID].owner)
                        != 0) {
                        return OpenSHC::Map::Units::WBS_NONE;
                    }
                    return OpenSHC::Map::Units::WBS_NO_WOOD;
                case OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk:
                    return OpenSHC::Map::Units::WBS_ARMOURY_FULL;
                }
                break;
            case OpenSHC::Map::Units::UT_SMITH:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_IDLEUnk:
                case OpenSHC::Map::Units::States::US_STATE_9Unk:
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                            DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_IRON, 1, this->units[unitID].owner)
                        != 0) {
                        return OpenSHC::Map::Units::WBS_NONE;
                    }
                    return OpenSHC::Map::Units::WBS_NO_IRON;
                case OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk:
                    return OpenSHC::Map::Units::WBS_ARMOURY_FULL;
                }
                break;
            case OpenSHC::Map::Units::UT_ARMORER:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_IDLEUnk:
                case OpenSHC::Map::Units::States::US_STATE_9Unk:
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                            DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_IRON, 1, this->units[unitID].owner)
                        != 0) {
                        return OpenSHC::Map::Units::WBS_NONE;
                    }
                    return OpenSHC::Map::Units::WBS_NO_IRON;
                case OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk:
                    return OpenSHC::Map::Units::WBS_ARMOURY_FULL;
                }
                break;
            case OpenSHC::Map::Units::UT_TANNER:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_IDLEUnk:
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::findNearestIdleCowForPlayer, this)(
                            this->units[unitID].owner, this->units[unitID].x, this->units[unitID].y)
                        != 0) {
                        return OpenSHC::Map::Units::WBS_NONE;
                    }
                    return OpenSHC::Map::Units::WBS_NO_COWS;
                case OpenSHC::Map::Units::States::US_LOOK_AROUNDUnk:
                    return OpenSHC::Map::Units::WBS_ARMOURY_FULL;
                }
                break;
            case OpenSHC::Map::Units::UT_TRANSPORTMINER:
                if (_state == OpenSHC::Map::Units::States::US_STATE_3Unk) {
                    return OpenSHC::Map::Units::WBS_STOCKPILE_FULL;
                }
                break;
            case OpenSHC::Map::Units::UT_INNKEEPER:
                switch (_state) {
                case OpenSHC::Map::Units::States::US_IDLEUnk:
                    if (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getStorageBuildingForResourceTypeAndAmount,
                            DAT_BuildingsState::ptr)(OpenSHC::Game::Resources::RT_ALE, 1, this->units[unitID].owner)
                        != 0) {
                        return OpenSHC::Map::Units::WBS_NONE;
                    }
                    return OpenSHC::Map::Units::WBS_NO_ALE;
                }
                break;
            }
            return OpenSHC::Map::Units::WBS_NONE;
        }

    }
}
}
