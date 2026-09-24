#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Map::Buildings::BuildingType;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040F9D0
        void BuildingsState::processBuildingIDsNeedPeasantsQueue(undefined4 playerID)
        {
            // Assigns peasants to the free worker slots of the queued buildings
            for (int i = 0; i < (int)this->DAT_CountOfBuildingsNeedPeasants; ++i) {
                int buildingID = (short)this->DAT_BuildingIDsNeedPeasantsQueue[i];
                if (this->buildings[buildingID].buildingTypeBasedEmployeeCount == 1) {
                    int unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding,
                        DAT_UnitsState::ptr)((UnitType)DAT_BuildingDefinedData::instance
                                                 .WorkerTypeForBuildingType[this->buildings[buildingID].buildingType],
                        buildingID, playerID, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding, this)(
                        buildingID, unitID, 0);
                    continue;
                }

                if (this->buildings[buildingID].buildingType == BT_QUARRY) {
                    for (int worker = 0; worker < 3; ++worker) {
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(
                                buildingID, worker)
                            == FALSE) {
                            int unitID = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding, DAT_UnitsState::ptr)(
                                OpenSHC::Map::Units::UT_QUARRYMASON, buildingID, playerID, worker);
                            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding,
                                this)(buildingID, unitID, worker);
                        }
                    }
                } else if (this->buildings[buildingID].buildingType == BT_IRONMINE) {
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(buildingID, 0)
                        == FALSE) {
                        int unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding,
                            DAT_UnitsState::ptr)(OpenSHC::Map::Units::UT_MINER, buildingID, playerID, 0);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding, this)(
                            buildingID, unitID, 0);
                    }
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(buildingID, 1)
                        == FALSE) {
                        int unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding,
                            DAT_UnitsState::ptr)(OpenSHC::Map::Units::UT_TRANSPORTMINER, buildingID, playerID, 1);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding, this)(
                            buildingID, unitID, 1);
                    }
                } else if (this->buildings[buildingID].buildingType == BT_MILL
                    || this->buildings[buildingID].buildingType == BT_WATERPOT
                    || this->buildings[buildingID].buildingType == BT_CATHEDRAL) {
                    for (int worker = 0; worker < 3; ++worker) {
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(
                                buildingID, worker)
                            == FALSE) {
                            int unitID = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding, DAT_UnitsState::ptr)(
                                (UnitType)DAT_BuildingDefinedData::instance
                                    .WorkerTypeForBuildingType[this->buildings[buildingID].buildingType],
                                buildingID, playerID, worker);
                            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding,
                                this)(buildingID, unitID, worker);
                        }
                    }
                } else if (this->buildings[buildingID].buildingType == BT_CHURCH) {
                    for (int worker = 0; worker < 2; ++worker) {
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(
                                buildingID, worker)
                            == FALSE) {
                            int unitID = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding, DAT_UnitsState::ptr)(
                                (UnitType)DAT_BuildingDefinedData::instance.WorkerTypeForBuildingType[BT_CHURCH],
                                buildingID, playerID, worker);
                            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding,
                                this)(buildingID, unitID, worker);
                        }
                    }
                }
            }
        }

    }
}
}
