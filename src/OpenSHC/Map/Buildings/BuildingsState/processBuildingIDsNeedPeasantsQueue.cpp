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
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(buildingID, 0)
                        == FALSE) {
                        int unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding,
                            DAT_UnitsState::ptr)(OpenSHC::Map::Units::UT_QUARRYMASON, buildingID, playerID, 0);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding, this)(
                            buildingID, unitID, 0);
                    }

                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(buildingID, 1)
                        == FALSE) {
                        int unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding,
                            DAT_UnitsState::ptr)(OpenSHC::Map::Units::UT_QUARRYMASON, buildingID, playerID, 1);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding, this)(
                            buildingID, unitID, 1);
                    }

                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(buildingID, 2)
                        == FALSE) {
                        int unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding,
                            DAT_UnitsState::ptr)(OpenSHC::Map::Units::UT_QUARRYMASON, buildingID, playerID, 2);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding, this)(
                            buildingID, unitID, 2);
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
                } else {
                    // The mill, water pot and cathedral share the code for their three workers
                    UnitType workerType;
                    if (this->buildings[buildingID].buildingType == BT_MILL) {
                        workerType = (UnitType)DAT_BuildingDefinedData::instance.WorkerTypeForBuildingType[BT_MILL];
                    } else if (this->buildings[buildingID].buildingType == BT_WATERPOT) {
                        workerType = (UnitType)DAT_BuildingDefinedData::instance.WorkerTypeForBuildingType[BT_WATERPOT];
                    } else if (this->buildings[buildingID].buildingType == BT_CHURCH) {
                        workerType = (UnitType)DAT_BuildingDefinedData::instance.WorkerTypeForBuildingType[BT_CHURCH];
                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(
                                buildingID, 0)
                            == FALSE) {
                            int unitID
                                = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding,
                                    DAT_UnitsState::ptr)(workerType, buildingID, playerID, 0);
                            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding,
                                this)(buildingID, unitID, 0);
                        }

                        if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(
                                buildingID, 1)
                            == FALSE) {
                            int unitID
                                = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding,
                                    DAT_UnitsState::ptr)(workerType, buildingID, playerID, 1);
                            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding,
                                this)(buildingID, unitID, 1);
                        }

                        continue;
                    } else if (this->buildings[buildingID].buildingType == BT_CATHEDRAL) {
                        workerType
                            = (UnitType)DAT_BuildingDefinedData::instance.WorkerTypeForBuildingType[BT_CATHEDRAL];
                    } else {
                        continue;
                    }
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(buildingID, 0)
                        == FALSE) {
                        int unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding,
                            DAT_UnitsState::ptr)(workerType, buildingID, playerID, 0);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding, this)(
                            buildingID, unitID, 0);
                    }

                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(buildingID, 1)
                        == FALSE) {
                        int unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding,
                            DAT_UnitsState::ptr)(workerType, buildingID, playerID, 1);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding, this)(
                            buildingID, unitID, 1);
                    }

                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasWorker, this)(buildingID, 2)
                        == FALSE) {
                        int unitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::assignPeasantToBuilding,
                            DAT_UnitsState::ptr)(workerType, buildingID, playerID, 2);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::assignWorkerToBuilding, this)(
                            buildingID, unitID, 2);
                    }
                }
            }
        }

    }
}
}
