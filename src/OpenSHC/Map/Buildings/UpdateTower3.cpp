#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0041EB00
    void Buildings::UpdateTower3()
    {
        int iVar1;
        int* piVar3;
        uint uVar4;
        uint uVar5;
        int iVar6;
        int iVar7;
        uint uVar8;
        int local_20[8];
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar6 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
        DAT_BuildingsState::instance.buildings[iVar6].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[iVar6].extraAnimationSprite1 = 4;
        DAT_BuildingsState::instance.buildings[iVar6].extraAnimationSprite2 = 0;
        DAT_BuildingsState::instance.buildings[iVar6].extraAnimationSprite3 = 0;
        DAT_BuildingsState::instance.buildings[iVar6].extraAnimationSprite4 = 0;
        DAT_BuildingsState::instance.buildings[iVar6].extraOverlayImage1 = 0;
        DAT_BuildingsState::instance.buildings[iVar6].animationFrame = 0;
        DAT_BuildingsState::instance.buildings[iVar6].damageDecoration[0] = 0;
        DAT_BuildingsState::instance.buildings[iVar6].damageDecoration[1] = 0;
        DAT_BuildingsState::instance.buildings[iVar6].damageDecoration[2] = 0;
        DAT_BuildingsState::instance.buildings[iVar6].damageDecoration[3] = 0;
        DAT_BuildingsState::instance.buildings[iVar6].damageDecoration[4] = 0;
        DAT_BuildingsState::instance.buildings[iVar6].damageDecoration[5] = 0;
        DAT_BuildingsState::instance.buildings[iVar6].damageDecoration[6] = 0;
        DAT_BuildingsState::instance.buildings[iVar6].damageDecoration[7] = 0;
        DAT_BuildingsState::instance.buildings[iVar6].someX = DAT_BuildingsState::instance.buildings[iVar6].x + 2;
        DAT_BuildingsState::instance.buildings[iVar6].someY = DAT_BuildingsState::instance.buildings[iVar6].y + 2;
        piVar3 = &DAT_BuildingsState::instance.buildings[iVar6].buildingProgress;
        *piVar3 = *piVar3 + 1;
        if (0x27 < DAT_BuildingsState::instance.buildings[iVar6].buildingProgress) {
            DAT_BuildingsState::instance.buildings[iVar6].buildingProgress = 0;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::computeBuildingEntranceFlagsForOrientations,
                DAT_BuildingsState::ptr)(iVar6);
        }
        iVar1 = MACRO_CALL_MEMBER(
            Map::Buildings::BuildingsState_Func::hasBuildingExitFlagForOrientation, DAT_BuildingsState::ptr)(iVar6);
        if (iVar1) {
            DAT_BuildingsState::instance.buildings[iVar6].extraAnimationSprite2 = 0x51;
            DAT_BuildingsState::instance.buildings[iVar6].animationFrame = 1;
        }
        iVar1 = MACRO_CALL_MEMBER(
            Map::Buildings::BuildingsState_Func::hasBuildingEntranceFlagForOrientation, DAT_BuildingsState::ptr)(iVar6);
        if (iVar1) {
            DAT_BuildingsState::instance.buildings[iVar6].extraAnimationSprite4 = 0x5a;
            DAT_BuildingsState::instance.buildings[iVar6].animationFrame = 1;
        }
        local_20[1] = 0;
        local_20[2] = 0;
        local_20[3] = 0;
        local_20[4] = 0;
        local_20[5] = 0;
        local_20[6] = 0;
        local_20[7] = 0;
        local_20[0] = 0;
        iVar1 = 9
            - (DAT_BuildingsState::instance.buildings[iVar6].currentHealth * 9)
                / (int)DAT_BuildingsState::instance.buildings[iVar6].maxHealth;
        if (iVar1 < 9) {
            if (!iVar1)
                goto LAB_0041ecf0;
        } else {
            iVar1 = 8;
        }
        if (0 < iVar1) {
            uVar4 = DAT_BuildingsState::instance.buildings[iVar6].fireRelatedRNG1;
            uint uVar2 = (int)uVar4 >> 8;
            do {
                uVar8 = uVar4 & 0xf;
                uVar5 = uVar2 & 7;
                uVar4 = uVar4 + 1;
                uVar2 = uVar2 + 1;
                iVar1 = iVar1 + -1;
                local_20[uVar5] = uVar8 + 1;
            } while (iVar1);
        }
        DAT_BuildingsState::instance.buildings[iVar6].damageDecoration[0] = local_20[0];
        DAT_BuildingsState::instance.buildings[iVar6].damageDecoration[1] = local_20[1];
        DAT_BuildingsState::instance.buildings[iVar6].damageDecoration[2] = local_20[2];
        DAT_BuildingsState::instance.buildings[iVar6].damageDecoration[3] = local_20[3];
        DAT_BuildingsState::instance.buildings[iVar6].damageDecoration[4] = local_20[4];
        DAT_BuildingsState::instance.buildings[iVar6].damageDecoration[5] = local_20[5];
        DAT_BuildingsState::instance.buildings[iVar6].damageDecoration[6] = local_20[6];
        DAT_BuildingsState::instance.buildings[iVar6].damageDecoration[7] = local_20[7];
    LAB_0041ecf0:
        if (DAT_BuildingsState::instance.field34_0x18e074) {
            iVar6 = 0;
            do {
                MACRO_CALL_MEMBER(Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(
                    iVar6, 5);
                iVar1 = DAT_ViewportRenderState::instance
                            .translationMatrix
                                [(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y
                                    + DAT_TileMapState::instance.buildingY]
                            .addXgetTile
                    + (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x
                    + DAT_TileMapState::instance.buildingX;
                iVar7 = 0;
                DAT_TileMapState::instance.MiscDisplayLayer[iVar1]
                    = DAT_TileMapState::instance.MiscDisplayLayer[iVar1] & 0xffef;
                piVar3 = DAT_BuildingDefinedData::instance.field420_0xa77c
                    + (DAT_TileMapState::instance.mapOrientation / 2) * 6;
                do {
                    if (*piVar3 == iVar6) {
                        DAT_TileMapState::instance.MiscDisplayLayer[iVar1]
                            = DAT_TileMapState::instance.MiscDisplayLayer[iVar1] | 0x10;
                        break;
                    }
                    iVar7 = iVar7 + 1;
                    piVar3 = piVar3 + 1;
                } while (iVar7 < 6);
                iVar6 = iVar6 + 1;
            } while (iVar6 < DAT_TileMapState::instance.constructionTileCount);
        }
    }

}
}
