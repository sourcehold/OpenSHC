#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00418C80
    void Buildings::UpdateTower1()
    {
        int iVar5;
        int local_20[8];
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int iVar1 = DAT_CurrentBuildingID::instance;
        int iVar4 = DAT_CurrentBuildingID::instance * 0x32c;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
        DAT_BuildingsState::instance.buildings[iVar1].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[iVar1].animationFrame = 0;
        DAT_BuildingsState::instance.buildings[iVar1].someX = DAT_BuildingsState::instance.buildings[iVar1].x + 1;
        DAT_BuildingsState::instance.buildings[iVar1].someY = DAT_BuildingsState::instance.buildings[iVar1].y + 1;
        DAT_BuildingsState::instance.buildings[iVar1].extraAnimationSprite1 = 0x7d;
        DAT_BuildingsState::instance.buildings[iVar1].extraOverlayImage2 = 0x7c;
        DAT_BuildingsState::instance.buildings[iVar1].extraAnimationSprite2 = 0;
        DAT_BuildingsState::instance.buildings[iVar1].extraAnimationSprite3 = 0;
        DAT_BuildingsState::instance.buildings[iVar1].extraAnimationSprite4 = 0;
        DAT_BuildingsState::instance.buildings[iVar1].extraOverlayImage1 = 0;
        DAT_BuildingsState::instance.buildings[iVar1].damageDecoration[0] = 0;
        DAT_BuildingsState::instance.buildings[iVar1].damageDecoration[1] = 0;
        DAT_BuildingsState::instance.buildings[iVar1].damageDecoration[2] = 0;
        DAT_BuildingsState::instance.buildings[iVar1].damageDecoration[3] = 0;
        DAT_BuildingsState::instance.buildings[iVar1].damageDecoration[4] = 0;
        DAT_BuildingsState::instance.buildings[iVar1].damageDecoration[5] = 0;
        DAT_BuildingsState::instance.buildings[iVar1].damageDecoration[6] = 0;
        local_20[1] = 0;
        local_20[2] = 0;
        local_20[3] = 0;
        local_20[4] = 0;
        local_20[5] = 0;
        local_20[6] = 0;
        local_20[7] = 0;
        DAT_BuildingsState::instance.buildings[iVar1].damageDecoration[7] = 0;
        local_20[0] = 0;
        iVar5 = 9
            - (DAT_BuildingsState::instance.buildings[iVar1].currentHealth * 9)
                / (int)DAT_BuildingsState::instance.buildings[iVar1].maxHealth;
        if (iVar5 < 9) {
            if (!iVar5)
                goto LAB_00418e05;
        } else {
            iVar5 = 8;
        }
        if (0 < iVar5) {
            uint uVar8 = DAT_BuildingsState::instance.buildings[iVar1].fireRelatedRNG1;
            uint uVar3 = (int)uVar8 >> 8;
            do {
                uint uVar6 = uVar8 & 0xf;
                uint uVar7 = uVar3 & 7;
                uVar8 = uVar8 + 1;
                uVar3 = uVar3 + 1;
                iVar5 = iVar5 + -1;
                local_20[uVar7] = uVar6 + 1;
            } while (iVar5);
        }
        DAT_BuildingsState::instance.buildings[iVar1].damageDecoration[0] = local_20[0];
        DAT_BuildingsState::instance.buildings[iVar1].damageDecoration[1] = local_20[1];
        DAT_BuildingsState::instance.buildings[iVar1].damageDecoration[2] = local_20[2];
        DAT_BuildingsState::instance.buildings[iVar1].damageDecoration[3] = local_20[3];
        DAT_BuildingsState::instance.buildings[iVar1].damageDecoration[4] = local_20[4];
        DAT_BuildingsState::instance.buildings[iVar1].damageDecoration[5] = local_20[5];
        DAT_BuildingsState::instance.buildings[iVar1].damageDecoration[6] = local_20[6];
        DAT_BuildingsState::instance.buildings[iVar1].damageDecoration[7] = local_20[7];
    LAB_00418e05:
        short sVar2 = DAT_BuildingsState::instance.buildings[iVar1].tileScanCountdown;
        if ((0 < sVar2)
            && (sVar2 = sVar2 + -1, DAT_BuildingsState::instance.buildings[iVar1].tileScanCountdown = sVar2, !sVar2)) {
            iVar5 = 0;
            sVar2 = 0;
            do {
                MACRO_CALL_MEMBER(Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(
                    iVar5, 3);
                iVar1 = DAT_CurrentBuildingID::instance;
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
                    sVar2 = 1;
                    break;
                }
                iVar5 = iVar5 + 1;
            } while (iVar5 < DAT_TileMapState::instance.constructionTileCount);
            iVar4 = DAT_CurrentBuildingID::instance * 0x32c;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].hasUnitsOntop = sVar2;
            DAT_BuildingsState::instance.buildings[iVar1].tileScanCountdown = 100;
        }
        if (*(short*)((int)DAT_BuildingsState::instance.buildings[0].quarryLinkedOxTethers + iVar4 + 0x2e) != 0) {
            *(undefined4*)((int)&DAT_BuildingsState::instance.buildings[0].extraOverlayImage2 + iVar4) = 0x7e;
        }
    }

}
}
