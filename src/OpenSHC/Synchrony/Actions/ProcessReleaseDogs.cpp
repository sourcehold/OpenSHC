#include "../../Synchrony.func.hpp"
#include "../Actions.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using DE::SHCDE::eSFX;
    using Map::Units::UnitType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00466430
    void Actions::ProcessReleaseDogs(int param_1, int buildingID, int buildingUID)
    {
        int iVar3;
        int iVar4;
        short* psVar6;
        int iVar7;
        int* piVar8;
        int iVar9;
        ushort uVar1 = DAT_BuildingsState::instance.buildings[buildingID].x;
        ushort uVar2 = DAT_BuildingsState::instance.buildings[buildingID].y;
        if (DAT_BuildingsState::instance.buildings[buildingID].uid == buildingUID) {
            DAT_BuildingsState::instance.buildings[buildingID].flagonsOfAleOrCheeseOrReleaseDogs = 1;
            piVar8 = &DAT_BuildingsState::instance.buildings[buildingID].insideUnitUID1;
            psVar6 = &DAT_BuildingsState::instance.buildings[buildingID].insideUnitID1;
            iVar9 = 4;
            do {
                *psVar6 = 0;
                *piVar8 = 0;
                psVar6 = psVar6 + 1;
                piVar8 = piVar8 + 1;
                iVar9 = iVar9 + -1;
            } while (iVar9);
            iVar9 = (short)uVar2 * 8;
            int iVar5 = (short)uVar1 * 8;
            iVar7 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, param_1, iVar5,
                iVar9, (int)(DAT_BuildingsState::instance.buildings[buildingID].terrainHeightUnk),
                Map::Units::UT_CAGEDOG);
            if (iVar7) {
                DAT_UnitsState::instance.units[iVar7].workplaceBuildingID_1 = (short)buildingID;
                iVar3 = DAT_BuildingsState::instance.buildings[buildingID].uid;
                DAT_BuildingsState::instance.buildings[buildingID].insideUnitID1 = (short)iVar7;
                iVar4 = DAT_UnitsState::instance.units[iVar7].uid;
                DAT_UnitsState::instance.units[iVar7].workplaceBuildingUID = iVar3;
                DAT_BuildingsState::instance.buildings[buildingID].insideUnitUID1 = iVar4;
            }
            iVar7 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, param_1,
                iVar5 + 8, iVar9, (int)(DAT_BuildingsState::instance.buildings[buildingID].terrainHeightUnk),
                Map::Units::UT_CAGEDOG);
            if (iVar7) {
                DAT_UnitsState::instance.units[iVar7].workplaceBuildingID_1 = (short)buildingID;
                iVar3 = DAT_BuildingsState::instance.buildings[buildingID].uid;
                DAT_BuildingsState::instance.buildings[buildingID].insideUnitID2 = (short)iVar7;
                iVar4 = DAT_UnitsState::instance.units[iVar7].uid;
                DAT_UnitsState::instance.units[iVar7].workplaceBuildingUID = iVar3;
                DAT_BuildingsState::instance.buildings[buildingID].insideUnitUID2 = iVar4;
            }
            iVar7 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, param_1, iVar5,
                iVar9 + 8, (int)(DAT_BuildingsState::instance.buildings[buildingID].terrainHeightUnk),
                Map::Units::UT_CAGEDOG);
            if (iVar7) {
                DAT_UnitsState::instance.units[iVar7].workplaceBuildingID_1 = (short)buildingID;
                iVar3 = DAT_BuildingsState::instance.buildings[buildingID].uid;
                DAT_BuildingsState::instance.buildings[buildingID].insideUnitID3 = (short)iVar7;
                iVar4 = DAT_UnitsState::instance.units[iVar7].uid;
                DAT_UnitsState::instance.units[iVar7].workplaceBuildingUID = iVar3;
                DAT_BuildingsState::instance.buildings[buildingID].insideUnitUID3 = iVar4;
            }
            iVar9 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, param_1,
                iVar5 + 8, iVar9 + 8, (int)(DAT_BuildingsState::instance.buildings[buildingID].terrainHeightUnk),
                Map::Units::UT_CAGEDOG);
            if (iVar9) {
                DAT_UnitsState::instance.units[iVar9].workplaceBuildingID_1 = (short)buildingID;
                iVar5 = DAT_BuildingsState::instance.buildings[buildingID].uid;
                DAT_BuildingsState::instance.buildings[buildingID].insideUnitID4 = (short)iVar9;
                iVar7 = DAT_UnitsState::instance.units[iVar9].uid;
                DAT_UnitsState::instance.units[iVar9].workplaceBuildingUID = iVar5;
                DAT_BuildingsState::instance.buildings[buildingID].insideUnitUID4 = iVar7;
            }
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x,
                (int)((short)DAT_BuildingsState::instance.buildings[buildingID].y), DE::SHCDE::FX_DOG_CAGE);
        }
    }

}
}
