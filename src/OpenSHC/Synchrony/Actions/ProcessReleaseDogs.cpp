#include "../Actions.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using namespace OpenSHC::Map::Units;

    // FUNCTION: STRONGHOLDCRUSADER 0x00466430
    void Actions::ProcessReleaseDogs(int param_1, int buildingID, int buildingUID)
    {
        int const x = DAT_BuildingsState::instance.buildings[buildingID].x;
        int const y = DAT_BuildingsState::instance.buildings[buildingID].y;
        if (DAT_BuildingsState::instance.buildings[buildingID].uid != buildingUID) {
            return;
        }
        DAT_BuildingsState::instance.buildings[buildingID].flagonsOfAleOrCheeseOrReleaseDogs = 1;
        for (int i = 0; i < 4; ++i) {
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitID[i] = 0;
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitUID[i] = 0;
        }
        int const dog0ID = MACRO_CALL_MEMBER(UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
            0, param_1, x * 8, y * 8, DAT_BuildingsState::instance.buildings[buildingID].terrainHeightUnk, UT_CAGEDOG);
        if (dog0ID != 0) {
            DAT_UnitsState::instance.units[dog0ID].workplaceBuildingID_1 = (short)buildingID;
            DAT_UnitsState::instance.units[dog0ID].workplaceBuildingUID
                = DAT_BuildingsState::instance.buildings[buildingID].uid;
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitID[0] = (short)dog0ID;
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitUID[0]
                = DAT_UnitsState::instance.units[dog0ID].uid;
        }
        int const dog1ID = MACRO_CALL_MEMBER(UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, param_1, x * 8 + 8,
            y * 8, DAT_BuildingsState::instance.buildings[buildingID].terrainHeightUnk, UT_CAGEDOG);
        if (dog1ID != 0) {
            DAT_UnitsState::instance.units[dog1ID].workplaceBuildingID_1 = (short)buildingID;
            DAT_UnitsState::instance.units[dog1ID].workplaceBuildingUID
                = DAT_BuildingsState::instance.buildings[buildingID].uid;
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitID[1] = (short)dog1ID;
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitUID[1]
                = DAT_UnitsState::instance.units[dog1ID].uid;
        }
        int const dog2ID = MACRO_CALL_MEMBER(UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, param_1, x * 8,
            y * 8 + 8, DAT_BuildingsState::instance.buildings[buildingID].terrainHeightUnk, UT_CAGEDOG);
        if (dog2ID != 0) {
            DAT_UnitsState::instance.units[dog2ID].workplaceBuildingID_1 = (short)buildingID;
            DAT_UnitsState::instance.units[dog2ID].workplaceBuildingUID
                = DAT_BuildingsState::instance.buildings[buildingID].uid;
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitID[2] = (short)dog2ID;
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitUID[2]
                = DAT_UnitsState::instance.units[dog2ID].uid;
        }
        int const dog3ID = MACRO_CALL_MEMBER(UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, param_1, x * 8 + 8,
            y * 8 + 8, DAT_BuildingsState::instance.buildings[buildingID].terrainHeightUnk, UT_CAGEDOG);
        if (dog3ID != 0) {
            DAT_UnitsState::instance.units[dog3ID].workplaceBuildingID_1 = (short)buildingID;
            DAT_UnitsState::instance.units[dog3ID].workplaceBuildingUID
                = DAT_BuildingsState::instance.buildings[buildingID].uid;
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitID[3] = (short)dog3ID;
            DAT_BuildingsState::instance.buildings[buildingID].insideUnitUID[3]
                = DAT_UnitsState::instance.units[dog3ID].uid;
        }
        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
            DAT_BuildingsState::instance.buildings[buildingID].x, DAT_BuildingsState::instance.buildings[buildingID].y,
            DE::SHCDE::FX_DOG_CAGE);
    }

}
}
