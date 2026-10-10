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

    // FUNCTION: STRONGHOLDCRUSADER 0x0041EDA0
    void Buildings::UpdateTower4()
    {
        int iVar1;
        int* piVar3;
        short sVar4;
        int iVar5;
        uint uVar6;
        uint uVar7;
        int iVar8;
        uint uVar9;
        int local_20[8];
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar5 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
        DAT_BuildingsState::instance.buildings[iVar5].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[iVar5].extraAnimationSprite1 = 2;
        DAT_BuildingsState::instance.buildings[iVar5].extraAnimationSprite2 = 0;
        DAT_BuildingsState::instance.buildings[iVar5].extraAnimationSprite3 = 0;
        DAT_BuildingsState::instance.buildings[iVar5].extraAnimationSprite4 = 0;
        DAT_BuildingsState::instance.buildings[iVar5].extraOverlayImage1 = 0;
        DAT_BuildingsState::instance.buildings[iVar5].extraOverlayImage2 = 0x7a;
        DAT_BuildingsState::instance.buildings[iVar5].extraOverlayImage3 = 0;
        DAT_BuildingsState::instance.buildings[iVar5].animationFrame = 0;
        DAT_BuildingsState::instance.buildings[iVar5].damageDecoration[0] = 0;
        DAT_BuildingsState::instance.buildings[iVar5].damageDecoration[1] = 0;
        DAT_BuildingsState::instance.buildings[iVar5].damageDecoration[2] = 0;
        DAT_BuildingsState::instance.buildings[iVar5].damageDecoration[3] = 0;
        DAT_BuildingsState::instance.buildings[iVar5].damageDecoration[4] = 0;
        DAT_BuildingsState::instance.buildings[iVar5].damageDecoration[5] = 0;
        DAT_BuildingsState::instance.buildings[iVar5].damageDecoration[6] = 0;
        DAT_BuildingsState::instance.buildings[iVar5].damageDecoration[7] = 0;
        DAT_BuildingsState::instance.buildings[iVar5].someX = DAT_BuildingsState::instance.buildings[iVar5].x + 2;
        DAT_BuildingsState::instance.buildings[iVar5].someY = DAT_BuildingsState::instance.buildings[iVar5].y + 2;
        piVar3 = &DAT_BuildingsState::instance.buildings[iVar5].buildingProgress;
        *piVar3 = *piVar3 + 1;
        if (0x27 < DAT_BuildingsState::instance.buildings[iVar5].buildingProgress) {
            DAT_BuildingsState::instance.buildings[iVar5].buildingProgress = 0;
            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::computeBuildingEntranceFlagsForOrientations,
                DAT_BuildingsState::ptr)(iVar5);
        }
        iVar1 = MACRO_CALL_MEMBER(
            Map::Buildings::BuildingsState_Func::hasBuildingExitFlagForOrientation, DAT_BuildingsState::ptr)(iVar5);
        if (iVar1) {
            DAT_BuildingsState::instance.buildings[iVar5].extraAnimationSprite2 = 0x51;
            DAT_BuildingsState::instance.buildings[iVar5].animationFrame = 1;
        }
        iVar1 = MACRO_CALL_MEMBER(
            Map::Buildings::BuildingsState_Func::hasBuildingEntranceFlagForOrientation, DAT_BuildingsState::ptr)(iVar5);
        if (iVar1) {
            DAT_BuildingsState::instance.buildings[iVar5].extraAnimationSprite4 = 0x5a;
            DAT_BuildingsState::instance.buildings[iVar5].animationFrame = 1;
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
            - (DAT_BuildingsState::instance.buildings[iVar5].currentHealth * 9)
                / (int)DAT_BuildingsState::instance.buildings[iVar5].maxHealth;
        if (iVar1 < 9) {
            if (!iVar1)
                goto LAB_0041efa6;
        } else {
            iVar1 = 8;
        }
        iVar8 = iVar5;
        if (0 < iVar1) {
            uVar6 = DAT_BuildingsState::instance.buildings[iVar5].fireRelatedRNG1;
            uint uVar2 = (int)uVar6 >> 8;
            do {
                uVar7 = uVar6 & 0xf;
                uVar9 = uVar2 & 7;
                uVar6 = uVar6 + 1;
                uVar2 = uVar2 + 1;
                iVar1 = iVar1 + -1;
                local_20[uVar9] = uVar7 + 1;
                iVar8 = DAT_CurrentBuildingID::instance;
            } while (iVar1);
        }
        DAT_BuildingsState::instance.buildings[iVar5].damageDecoration[0] = local_20[0];
        DAT_BuildingsState::instance.buildings[iVar5].damageDecoration[1] = local_20[1];
        DAT_BuildingsState::instance.buildings[iVar5].damageDecoration[2] = local_20[2];
        DAT_BuildingsState::instance.buildings[iVar5].damageDecoration[3] = local_20[3];
        DAT_BuildingsState::instance.buildings[iVar5].damageDecoration[4] = local_20[4];
        DAT_BuildingsState::instance.buildings[iVar5].damageDecoration[5] = local_20[5];
        DAT_BuildingsState::instance.buildings[iVar5].damageDecoration[6] = local_20[6];
        DAT_BuildingsState::instance.buildings[iVar5].damageDecoration[7] = local_20[7];
        iVar5 = iVar8;
    LAB_0041efa6:
        iVar1 = 0;
        if (DAT_BuildingsState::instance.field34_0x18e074) {
            do {
                MACRO_CALL_MEMBER(Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(
                    iVar1, 6);
                iVar5 = DAT_ViewportRenderState::instance
                            .translationMatrix
                                [(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y
                                    + DAT_TileMapState::instance.buildingY]
                            .addXgetTile
                    + (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x
                    + DAT_TileMapState::instance.buildingX;
                iVar8 = 0;
                DAT_TileMapState::instance.MiscDisplayLayer[iVar5]
                    = DAT_TileMapState::instance.MiscDisplayLayer[iVar5] & 0xffef;
                piVar3 = DAT_BuildingDefinedData::instance.field421_0xa7dc
                    + (DAT_TileMapState::instance.mapOrientation / 2) * 8;
                do {
                    if (*piVar3 == iVar1) {
                        DAT_TileMapState::instance.MiscDisplayLayer[iVar5]
                            = DAT_TileMapState::instance.MiscDisplayLayer[iVar5] | 0x10;
                        break;
                    }
                    iVar8 = iVar8 + 1;
                    piVar3 = piVar3 + 1;
                } while (iVar8 < 8);
                iVar1 = iVar1 + 1;
                iVar5 = DAT_CurrentBuildingID::instance;
            } while (iVar1 < DAT_TileMapState::instance.constructionTileCount);
        }
        iVar1 = iVar5 * 0x32c;
        sVar4 = DAT_BuildingsState::instance.buildings[iVar5].tileScanCountdown;
        if ((0 < sVar4)
            && (sVar4 = sVar4 + -1, DAT_BuildingsState::instance.buildings[iVar5].tileScanCountdown = sVar4, !sVar4)) {
            iVar5 = 0;
            sVar4 = 0;
            do {
                MACRO_CALL_MEMBER(Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(
                    iVar5, 6);
                iVar8 = DAT_CurrentBuildingID::instance;
                if (DAT_TileMapState::instance
                        .UnitLayer[DAT_ViewportRenderState::instance
                                       .translationMatrix[(short)DAT_BuildingsState::instance
                                                              .buildings[DAT_CurrentBuildingID::instance]
                                                              .y
                                           + DAT_TileMapState::instance.buildingY]
                                       .addXgetTile
                            + (int)(short)DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x
                            + DAT_TileMapState::instance.buildingX]
                    != 0) {
                    sVar4 = 1;
                    break;
                }
                iVar5 = iVar5 + 1;
            } while (iVar5 < DAT_TileMapState::instance.constructionTileCount);
            iVar1 = DAT_CurrentBuildingID::instance * 0x32c;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].hasUnitsOntop = sVar4;
            DAT_BuildingsState::instance.buildings[iVar8].tileScanCountdown = 100;
        }
        if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar1 + 0x2e) != 0) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraOverlayImage3 + iVar1) = 0x7b;
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraOverlayImage2 + iVar1) = 0;
        }
    }

}
}
