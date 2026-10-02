#include "../MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace UI {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B5F70
    void MinimapViewState::locatePlayerKeepPositionsOnMinimap(uint param_1, int param_2, int param_3)
    {
        int iVar1;
        int iVar2;
        int iVar3;
        uint uVar4;
        uint uVar5;
        int* piVar6;
        int iVar7;
        int iVar8;
        int iVar9;
        int iVar10;
        int iVar11;
        int local_34;
        int local_30;
        uint local_2c;
        uint local_28;
        int local_24;
        int local_20;
        int local_18;
        iVar1 = DAT_ViewportRenderState::instance.viewportState.viewportHeight;
        iVar8 = 1;
        local_2c = 0;
        iVar7 = 8;
        local_34 = 1;
        local_24 = 2;
        this->DAT_MapU4B64.keepPositions[0].x = -1;
        this->DAT_MapU4B64.keepPositions[0].y = -1;
        this->DAT_MapU4B64.keepPositions[1].x = -1;
        this->DAT_MapU4B64.keepPositions[1].y = -1;
        this->DAT_MapU4B64.keepPositions[2].x = -1;
        this->DAT_MapU4B64.keepPositions[2].y = -1;
        this->DAT_MapU4B64.keepPositions[3].x = -1;
        this->DAT_MapU4B64.keepPositions[3].y = -1;
        this->DAT_MapU4B64.keepPositions[4].x = -1;
        this->DAT_MapU4B64.keepPositions[4].y = -1;
        this->DAT_MapU4B64.keepPositions[5].x = -1;
        this->DAT_MapU4B64.keepPositions[5].y = -1;
        this->DAT_MapU4B64.keepPositions[6].x = -1;
        this->DAT_MapU4B64.keepPositions[6].y = -1;
        this->DAT_MapU4B64.keepPositions[7].x = -1;
        this->DAT_MapU4B64.keepPositions[7].y = -1;
        if ((param_1 & 4) != 0) {
            local_34 = 2;
            iVar8 = 2;
        }
        if (DAT_TileMapState::instance.mapSize < 0xc9) {
            local_2c = 100;
            local_24 = 1;
        }
        iVar2 = DAT_ViewportRenderState::instance.viewportState.viewportHeight + 1;
        if (DAT_TileMapState::instance.mapOrientation != 0) {
            if (DAT_TileMapState::instance.mapOrientation == 6) {
                iVar7 = 0x13a18;
            } else if (DAT_TileMapState::instance.mapOrientation == 4) {
                iVar7 = 0x27428;
            } else if (DAT_TileMapState::instance.mapOrientation == 2) {
                iVar7 = 0x3ae38;
            }
        }
        uVar5 = local_2c / 2;
        iVar9 = iVar8 * 200 - local_2c;
        iVar7 = uVar5 * 0x191 + 1 + iVar7;
        if ((int)local_2c < iVar9) {
            local_28 = 0;
            param_1 = 0;
            local_30 = iVar2;
            do {
                if (local_30 == iVar2) {
                    local_30 = iVar1;
                    iVar10 = param_2 / 2;
                    local_18 = 200;
                } else {
                    iVar10 = 0;
                    local_18 = 0xc9;
                    local_30 = iVar2;
                }
                if (-1 < (int)local_2c) {
                    if (399 < (int)local_2c) {}
                    if (((local_34 != 2) || ((local_28 & 1) == 0))
                        && (local_20 = ((int)(400 / (longlong)param_2) * iVar8) / local_24 - uVar5,
                            (int)uVar5 < local_20)) {
                        local_20 = local_20 - uVar5;
                        piVar6 = DAT_ViewportRenderState::instance.screenPointToTileNumber + uVar5 + iVar7 + -8;
                        do {
                            iVar3 = (int)DAT_TileMapState::instance.BuildingLayer[*piVar6];
                            if (((iVar3 != 0)
                                    && ((int)(short)DAT_BuildingsState::instance.buildings[iVar3].buildingType - 0x28U
                                        < 5))
                                && (iVar3 = (int)DAT_BuildingsState::instance.buildings[iVar3].owner,
                                    this->DAT_MapU4B64.keepPositions[iVar3 + -1].x == -1)) {
                                uVar4 = param_1;
                                iVar11 = iVar10;
                                if (local_34 != 1) {
                                    uVar4 = (int)param_1 / local_34;
                                    iVar11 = iVar10 / local_34;
                                }
                                this->DAT_MapU4B64.keepPositions[iVar3 + -1].x = iVar11;
                                this->DAT_MapU4B64.keepPositions[iVar3 + -1].y = uVar4;
                            }
                            iVar10 = iVar10 + param_2;
                            piVar6 = piVar6 + 1;
                            local_20 = local_20 + -1;
                        } while (local_20 != 0);
                    }
                }
                iVar7 = iVar7 + local_18;
                local_28 = local_28 + param_3;
                param_1 = param_1 + param_3;
                local_2c = local_2c + 1;
            } while ((int)local_2c < iVar9);
        }
    }

}
}
