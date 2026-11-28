#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00402E20
        uint EntityState::computeLineOfSightDistance(
            int x, int y, int height, int targetX, int targetY, int targetHeight, int param_7)
        {
            int iVar1;
            int iVar2;
            short sVar3;
            bool bVar4;
            bool bVar5;
            int iVar6;
            int iVar7;
            uint uVar8;
            int iVar9;
            int iVar10;
            int iVar11;
            uint uVar12;
            int iVar13;
            int iVar14;
            int* piVar15;
            uint local_44;
            uint local_40;
            int local_3c;
            int local_38;
            uint local_30;
            int local_1c;
            iVar9 = y;
            local_1c = -1;
            uVar12 = 0;
            local_44 = 100000;
            local_30 = 0;
            local_40 = 0;
            bVar4 = true;
            bVar5 = false;
            if (targetHeight + 0x36 < height) {
                uVar12 = 100;
                local_40 = 100;
            }
            iVar6 = (int)(y + (y >> 0x1f & 7U)) >> 3;
            iVar10 = (int)((x >> 0x1f & 7U) + x) >> 3;
            iVar7 = DAT_ViewportRenderState::instance.translationMatrix[iVar6].addXgetTile + iVar10;
            local_3c = x;
            local_38 = y;
            if ((DAT_TileMapState::instance.LogicLayer[iVar7] & 0x10000000U)) {
                height = height + 10;
            }
            sVar3 = -1;
            if (DAT_TileMapState::instance.BuildingLayer[iVar7] != 0) {
                sVar3 = DAT_TileMapState::instance.BuildingLayer[iVar7];
            }
            if (targetY < y) {
                iVar7 = y - targetY;
            } else {
                iVar7 = targetY - y;
            }
            if (targetX < x) {
                iVar11 = x - targetX;
            } else {
                iVar11 = targetX - x;
            }
            iVar1 = (uint)(x <= targetX) * 2 + -1;
            iVar2 = (uint)(y <= targetY) * 2 + -1;
            if (!iVar11) {
                if (iVar7) {
                    if (0x1b < uVar12) {
                        uVar12 = 0x1c;
                    }
                    uVar8 = 0;
                    local_40 = uVar12 / 2;
                    local_44 = 0;
                    iVar9 = -1;
                    this->lineOfSightClearanceSteps = uVar12;
                    do {
                        local_38 = local_38 + iVar2;
                        iVar6 = iVar9;
                        if (((local_44 & 1)) && (!param_7)) {
                            iVar6 = DAT_ViewportRenderState::instance
                                        .translationMatrix[(int)(local_38 + (local_38 >> 0x1f & 7U)) >> 3]
                                        .addXgetTile
                                + iVar10;
                            if (!(DAT_TileMapState::instance.LogicLayer[iVar6] & 0x400300U)) {
                                bVar4 = false;
                                this->lineOfSightClearanceSteps = local_44;
                            }
                            if (!local_40) {
                                if (iVar9 == iVar6) {
                                    if (bVar5) {
                                        uVar12 = local_38 - y >> 0x1f;
                                        iVar9 = ((local_38 - y ^ uVar12) - uVar12) * (targetHeight - height);
                                        goto LAB_004033cf;
                                    }
                                } else {
                                    bVar5 = false;
                                    if (((char)DAT_TileMapState::instance.LogicLayer[iVar6] < '\0')
                                        || ((sVar3 != DAT_TileMapState::instance.BuildingLayer[iVar6]
                                            && ((!bVar4
                                                || (!(DAT_TileMapState::instance.LogicLayer[iVar6] & 0x400200U))))))) {
                                        bVar5 = true;
                                        uVar8 = MACRO_CALL_MEMBER(Map::TileMapState_Func::returnSomeHeight,
                                            DAT_TileMapState::ptr)(iVar6, 1);
                                        uVar12 = local_38 - y >> 0x1f;
                                        iVar9 = ((local_38 - y ^ uVar12) - uVar12) * (targetHeight - height);
                                    LAB_004033cf:
                                        if (iVar9 / iVar7 + height < (int)uVar8) {
                                            return 0;
                                        }
                                    }
                                }
                            } else {
                                local_40 = local_40 - 1;
                            }
                        }
                        if ((x == targetX) && (local_38 == targetY)) {
                            return local_44;
                        }
                        local_44 = local_44 + 1;
                        iVar9 = iVar6;
                        if (999 < (int)local_44) {
                            return local_44;
                        }
                    } while (true);
                }
            } else {
                if (!iVar7) {
                    if (0x1b < uVar12) {
                        uVar12 = 0x1c;
                    }
                    uVar8 = uVar12 / 2;
                    local_44 = 0;
                    this->lineOfSightClearanceSteps = uVar12;
                    while (true) {
                        local_3c = local_3c + iVar1;
                        if (((local_44 & 1)) && (!param_7)) {
                            iVar9 = ((int)(local_3c + (local_3c >> 0x1f & 7U)) >> 3)
                                + DAT_ViewportRenderState::instance.translationMatrix[iVar6].addXgetTile;
                            if (!(DAT_TileMapState::instance.LogicLayer[iVar9] & 0x400300U)) {
                                bVar4 = false;
                                this->lineOfSightClearanceSteps = local_44;
                            }
                            if (!uVar8) {
                                if (local_1c == iVar9) {
                                    local_1c = iVar9;
                                    if ((bVar5)
                                        && (uVar12 = local_3c - x >> 0x1f,
                                            (int)(((local_3c - x ^ uVar12) - uVar12) * (targetHeight - height)) / iVar11
                                                    + height
                                                < (int)local_30)) {
                                        return 0;
                                    }
                                } else {
                                    bVar5 = false;
                                    if (((char)DAT_TileMapState::instance.LogicLayer[iVar9] < '\0')
                                        || ((local_1c = iVar9,
                                            sVar3 != DAT_TileMapState::instance.BuildingLayer[iVar9]
                                                && ((!bVar4
                                                    || (!(DAT_TileMapState::instance.LogicLayer[iVar9]
                                                        & 0x400200U))))))) {
                                        bVar5 = true;
                                        local_30 = MACRO_CALL_MEMBER(Map::TileMapState_Func::returnSomeHeight,
                                            DAT_TileMapState::ptr)(iVar9, 1);
                                        uVar12 = local_3c - x >> 0x1f;
                                        local_1c = iVar9;
                                        if ((int)(((local_3c - x ^ uVar12) - uVar12) * (targetHeight - height)) / iVar11
                                                + height
                                            < (int)local_30) {
                                            return 0;
                                        }
                                    }
                                }
                            } else {
                                uVar8 = uVar8 - 1;
                                local_1c = iVar9;
                            }
                        }
                        if ((local_3c == targetX) && (y == targetY))
                            break;
                        local_44 = local_44 + 1;
                        if (999 < (int)local_44) {
                            return local_44;
                        }
                    }
                    return local_44;
                }
                if (iVar7 <= iVar11) {
                    iVar7 = iVar7 * 2;
                    iVar6 = iVar7 - iVar11;
                    if ((targetHeight < height) && (uVar12)) {
                        uVar8 = targetX - x >> 0x1f;
                        iVar10 = (targetX - x ^ uVar8) - uVar8;
                        iVar10 = ((int)(iVar10 + (iVar10 >> 0x1f & 7U)) >> 3) + -1;
                        if (4 < iVar10) {
                            iVar10 = 4;
                        }
                        if (1 < iVar10) {
                            y = iVar10 + -1;
                            iVar10 = iVar1;
                            do {
                                local_30 = MACRO_CALL_MEMBER(Map::TileMapState_Func::returnSomeHeight,
                                    DAT_TileMapState::ptr)((((int)(targetX + (targetX >> 0x1f & 7U)) >> 3) - iVar10)
                                        + DAT_ViewportRenderState::instance
                                            .translationMatrix[(int)(targetY + (targetY >> 0x1f & 7U)) >> 3]
                                            .addXgetTile,
                                    1);
                                if (targetHeight < (int)local_30) {
                                    uVar12 = 0x1c;
                                }
                                iVar10 = iVar10 + iVar1;
                                y = y + -1;
                            } while (y);
                        }
                    }
                    local_40 = uVar12 / 2;
                    local_44 = 0;
                    iVar10 = x;
                    iVar14 = -1;
                    this->lineOfSightClearanceSteps = uVar12;
                    while (true) {
                        iVar10 = iVar10 + iVar1;
                        iVar13 = iVar7;
                        if (0 < iVar6) {
                            iVar9 = iVar9 + iVar2;
                            iVar13 = iVar7 + iVar11 * -2;
                            local_38 = iVar9;
                        }
                        iVar6 = iVar6 + iVar13;
                        iVar13 = iVar14;
                        if (((local_44 & 1)) && (!param_7)) {
                            iVar13 = ((int)(iVar10 + (iVar10 >> 0x1f & 7U)) >> 3)
                                + DAT_ViewportRenderState::instance
                                      .translationMatrix[(int)(iVar9 + (iVar9 >> 0x1f & 7U)) >> 3]
                                      .addXgetTile;
                            if (!(DAT_TileMapState::instance.LogicLayer[iVar13] & 0x400300U)) {
                                bVar4 = false;
                                this->lineOfSightClearanceSteps = local_44;
                            }
                            if (!local_40) {
                                if (iVar14 == iVar13) {
                                    if ((bVar5)
                                        && (uVar12 = iVar10 - x >> 0x1f,
                                            (int)(((iVar10 - x ^ uVar12) - uVar12) * (targetHeight - height)) / iVar11
                                                    + height
                                                < (int)local_30)) {
                                        return 0;
                                    }
                                } else {
                                    bVar5 = false;
                                    if (((char)DAT_TileMapState::instance.LogicLayer[iVar13] < '\0')
                                        || ((sVar3 != DAT_TileMapState::instance.BuildingLayer[iVar13]
                                            && ((!bVar4
                                                || (!(DAT_TileMapState::instance.LogicLayer[iVar13] & 0x400200U))))))) {
                                        bVar5 = true;
                                        local_30 = MACRO_CALL_MEMBER(Map::TileMapState_Func::returnSomeHeight,
                                            DAT_TileMapState::ptr)(iVar13, 1);
                                        uVar12 = iVar10 - x >> 0x1f;
                                        iVar9 = local_38;
                                        if ((int)(((iVar10 - x ^ uVar12) - uVar12) * (targetHeight - height)) / iVar11
                                                + height
                                            < (int)local_30) {
                                            return 0;
                                        }
                                    }
                                }
                            } else {
                                local_40 = local_40 - 1;
                            }
                        }
                        if ((iVar10 == targetX) && (iVar9 == targetY))
                            break;
                        local_44 = local_44 + 1;
                        iVar14 = iVar13;
                        if (999 < (int)local_44) {
                            return local_44;
                        }
                    }
                    return local_44;
                }
                iVar11 = iVar11 * 2;
                iVar9 = iVar11 - iVar7;
                if ((targetHeight < height) && (local_40)) {
                    uVar12 = targetY - y >> 0x1f;
                    iVar6 = (targetY - y ^ uVar12) - uVar12;
                    iVar6 = ((int)(iVar6 + (iVar6 >> 0x1f & 7U)) >> 3) + -1;
                    if (4 < iVar6) {
                        iVar6 = 4;
                    }
                    if (1 < iVar6) {
                        piVar15 = (int*)((int)DAT_ViewportRenderState::ptr
                            + (((int)(targetY + (targetY >> 0x1f & 7U)) >> 3) - iVar2) * 0xc + 0x188728);
                        iVar6 = iVar6 + -1;
                        do {
                            local_30 = MACRO_CALL_MEMBER(Map::TileMapState_Func::returnSomeHeight,
                                DAT_TileMapState::ptr)(*piVar15 + ((int)(targetX + (targetX >> 0x1f & 7U)) >> 3), 1);
                            if (targetHeight < (int)local_30) {
                                local_40 = 0x1c;
                            }
                            piVar15 = piVar15 + iVar2 * -3;
                            iVar6 = iVar6 + -1;
                        } while (iVar6);
                    }
                }
                this->lineOfSightClearanceSteps = local_40;
                local_40 = local_40 / 2;
                local_44 = 0;
                iVar6 = y;
                iVar10 = -1;
                do {
                    iVar6 = iVar6 + iVar2;
                    iVar14 = iVar11;
                    if (0 < iVar9) {
                        x = x + iVar1;
                        iVar14 = iVar11 + iVar7 * -2;
                        local_3c = x;
                    }
                    iVar9 = iVar9 + iVar14;
                    iVar14 = iVar10;
                    if (((local_44 & 1)) && (!param_7)) {
                        iVar14 = ((int)(x + (x >> 0x1f & 7U)) >> 3)
                            + DAT_ViewportRenderState::instance
                                  .translationMatrix[(int)(iVar6 + (iVar6 >> 0x1f & 7U)) >> 3]
                                  .addXgetTile;
                        if (!(DAT_TileMapState::instance.LogicLayer[iVar14] & 0x400300U)) {
                            bVar4 = false;
                            this->lineOfSightClearanceSteps = local_44;
                        }
                        if (!local_40) {
                            if (iVar10 == iVar14) {
                                if ((bVar5)
                                    && (uVar12 = iVar6 - y >> 0x1f,
                                        (int)(((iVar6 - y ^ uVar12) - uVar12) * (targetHeight - height)) / iVar7
                                                + height
                                            < (int)local_30)) {
                                    return 0;
                                }
                            } else {
                                bVar5 = false;
                                if (((char)DAT_TileMapState::instance.LogicLayer[iVar14] < '\0')
                                    || ((sVar3 != DAT_TileMapState::instance.BuildingLayer[iVar14]
                                        && ((!bVar4
                                            || (!(DAT_TileMapState::instance.LogicLayer[iVar14] & 0x400200U))))))) {
                                    bVar5 = true;
                                    local_30 = MACRO_CALL_MEMBER(Map::TileMapState_Func::returnSomeHeight,
                                        DAT_TileMapState::ptr)(iVar14, 1);
                                    uVar12 = iVar6 - y >> 0x1f;
                                    x = local_3c;
                                    if ((int)(((iVar6 - y ^ uVar12) - uVar12) * (targetHeight - height)) / iVar7
                                            + height
                                        < (int)local_30) {
                                        return 0;
                                    }
                                }
                            }
                        } else {
                            local_40 = local_40 - 1;
                        }
                    }
                } while (((x != targetX) || (iVar6 != targetY))
                    && (local_44 = local_44 + 1, iVar10 = iVar14, (int)local_44 < 1000));
            }
            return local_44;
        }

    }
}
}
