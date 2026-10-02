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

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Map::Units::UnitType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00466430
    void Actions::ProcessReleaseDogs(int param_1, int buildingID, int buildingUID)
    {
        int uVar1;
        int uVar2;
        int iVar3;
        int iVar4;
        int iVar5;
        short* psVar6;
        int iVar7;
        int* piVar8;
        int iVar9;
        uVar1 = (short)DAT_BuildingsState::instance.buildings[buildingID].x;
        uVar2 = (short)DAT_BuildingsState::instance.buildings[buildingID].y;
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
            } while (iVar9 != 0);
            iVar9 = uVar2 * 8;
            iVar5 = uVar1 * 8;
            iVar7 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, param_1,
                iVar5, iVar9, (int)((int)(DAT_BuildingsState::instance.buildings[buildingID].terrainHeightUnk)),
                OpenSHC::Map::Units::UT_CAGEDOG);
            if (iVar7 != 0) {
                DAT_UnitsState::instance.units[iVar7].workplaceBuildingID_1 = (short)buildingID;
                iVar3 = DAT_BuildingsState::instance.buildings[buildingID].uid;
                DAT_BuildingsState::instance.buildings[buildingID].insideUnitID1 = (short)iVar7;
                iVar4 = DAT_UnitsState::instance.units[iVar7].uid;
                DAT_UnitsState::instance.units[iVar7].workplaceBuildingUID = iVar3;
                DAT_BuildingsState::instance.buildings[buildingID].insideUnitUID1 = iVar4;
            }
            iVar7 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, param_1,
                iVar5 + 8, iVar9, (int)((int)(DAT_BuildingsState::instance.buildings[buildingID].terrainHeightUnk)),
                OpenSHC::Map::Units::UT_CAGEDOG);
            if (iVar7 != 0) {
                DAT_UnitsState::instance.units[iVar7].workplaceBuildingID_1 = (short)buildingID;
                iVar3 = DAT_BuildingsState::instance.buildings[buildingID].uid;
                DAT_BuildingsState::instance.buildings[buildingID].insideUnitID2 = (short)iVar7;
                iVar4 = DAT_UnitsState::instance.units[iVar7].uid;
                DAT_UnitsState::instance.units[iVar7].workplaceBuildingUID = iVar3;
                DAT_BuildingsState::instance.buildings[buildingID].insideUnitUID2 = iVar4;
            }
            iVar7 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, param_1,
                iVar5, iVar9 + 8, (int)((int)(DAT_BuildingsState::instance.buildings[buildingID].terrainHeightUnk)),
                OpenSHC::Map::Units::UT_CAGEDOG);
            if (iVar7 != 0) {
                DAT_UnitsState::instance.units[iVar7].workplaceBuildingID_1 = (short)buildingID;
                iVar3 = DAT_BuildingsState::instance.buildings[buildingID].uid;
                DAT_BuildingsState::instance.buildings[buildingID].insideUnitID3 = (short)iVar7;
                iVar4 = DAT_UnitsState::instance.units[iVar7].uid;
                DAT_UnitsState::instance.units[iVar7].workplaceBuildingUID = iVar3;
                DAT_BuildingsState::instance.buildings[buildingID].insideUnitUID3 = iVar4;
            }
            iVar9 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(0, param_1,
                iVar5 + 8, iVar9 + 8, (int)((int)(DAT_BuildingsState::instance.buildings[buildingID].terrainHeightUnk)),
                OpenSHC::Map::Units::UT_CAGEDOG);
            if (iVar9 != 0) {
                DAT_UnitsState::instance.units[iVar9].workplaceBuildingID_1 = (short)buildingID;
                iVar5 = DAT_BuildingsState::instance.buildings[buildingID].uid;
                DAT_BuildingsState::instance.buildings[buildingID].insideUnitID4 = (short)iVar9;
                iVar7 = DAT_UnitsState::instance.units[iVar9].uid;
                DAT_UnitsState::instance.units[iVar9].workplaceBuildingUID = iVar5;
                DAT_BuildingsState::instance.buildings[buildingID].insideUnitUID4 = iVar7;
            }
            MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x,
                (int)((int)((short)DAT_BuildingsState::instance.buildings[buildingID].y)),
                OpenSHC::DE::SHCDE::FX_DOG_CAGE);
        }
    }

}
}
