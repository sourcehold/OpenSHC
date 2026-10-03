#include "../MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_MiniMapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      Renders a horizontal strip of minimap pixels for a given map row range. For each tile, determines   the base
      colour from LogicLayer flags (water, trees, terrain type) and MiniMapDefinedData colour   tables, then applies a
      luminescence multiplier per channel (RGB555 or RGB565). Writes results   into the minimap pixel buffer at
      DAT_MinimapViewState, with support for 1x and 2x scale modes.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B5330
    void MinimapViewState::renderMinimapTileStripWithLuminescence(
        uint param_1, int param_2, int param_3, uint param_4, int param_5)
    {
        int iVar1;
        int iVar2;
        uint uVar3;
        uint uVar4;
        int iVar5;
        uint uVar6;
        int _yOffset;
        int iVar7;
        int iVar8;
        uint uVar9;
        uint uVar10;
        int iVar11;
        int iVar12;
        uint uVar13;
        uint _isRGB565;
        int local_58;
        int* local_50;
        int local_4c;
        uint local_48;
        int local_44;
        int local_40;
        int local_3c;
        int local_38;
        int local_2c;
        int local_24;
        int _tile;
        uint _tile1003;
        int _paramSum;
        int _vpHeight;
        _vpHeight = DAT_ViewportRenderState::instance.viewportState.viewportHeight;
        _yOffset = param_4 * 400;
        _paramSum = param_4 + param_5;
        uVar10 = 0;
        iVar8 = 1;
        local_58 = 1;
        local_3c = 2;
        if ((param_1 & 4) != 0) {
            local_58 = 2;
            iVar8 = 2;
        }
        iVar1 = (int)(400 / (longlong)param_2) * iVar8;
        _isRGB565 = (uint)(DAT_WindowAndDirectDraw::instance.colorBitMode == 1381);
        if (DAT_TileMapState::instance.mapSize < 200) {
            uVar10 = 100;
            local_3c = 1;
        }
        iVar2 = DAT_ViewportRenderState::instance.viewportState.viewportHeight + 1;
        iVar12 = 8;
        if (DAT_TileMapState::instance.mapOrientation != 0) {
            if (DAT_TileMapState::instance.mapOrientation == 6) {
                iVar12 = 80408;
            } else if (DAT_TileMapState::instance.mapOrientation == 4) {
                iVar12 = 160808;
            } else {
                iVar12 = 8;
                if (DAT_TileMapState::instance.mapOrientation == 2) {
                    iVar12 = 241208;
                }
            }
        }
        uVar3 = uVar10 / 2;
        local_44 = iVar12 + 1 + uVar3 * 0x191;
        iVar8 = iVar8 * 200 - uVar10;
        if ((int)uVar10 < iVar8) {
            local_48 = 0;
            param_5 = 0;
            local_40 = iVar2;
            do {
                if (local_40 == iVar2) {
                    local_40 = _vpHeight;
                    iVar12 = param_2 / 2;
                    local_24 = 200;
                } else {
                    iVar12 = 0;
                    local_24 = 201;
                    local_40 = iVar2;
                }
                if (_yOffset / 100 <= (int)uVar10) {
                    if ((_paramSum * 400) / 100 <= (int)uVar10) {}
                    if ((local_58 != 2) || ((local_48 & 1) == 0)) {
                        iVar11 = uVar3 - 2;
                        local_2c = iVar1 / local_3c - uVar3;
                        if (iVar11 < local_2c) {
                            uVar6 = (iVar11 - uVar3) * param_2 + iVar12;
                            local_50
                                = DAT_ViewportRenderState::instance.screenPointToTileNumber + uVar3 + local_44 + -10;
                            local_2c = local_2c - iVar11;
                            do {
                                _tile = *local_50;
                                _tile1003 = DAT_TileMapState::instance.LogicLayer[_tile];
                                iVar12 = 0;
                                if ((_tile1003 & 0x40000000) == 0) {
                                    if ((_tile1003 & 0x3000) == 0) {
                                        uVar9 = DAT_MiniMapDefinedData::instance.field90_0x27c[0].integer;
                                        if ((_tile1003 & 8) == 0) {
                                            while ((uVar9 & _tile1003) == 0) {
                                                if (uVar9 == 0)
                                                    goto LAB_004b55d3;
                                                iVar11 = iVar12 + 1;
                                                iVar12 = iVar12 + 1;
                                                uVar9 = DAT_MiniMapDefinedData::instance.field90_0x27c[iVar11].integer;
                                            }
                                            param_4 = (uint)DAT_MiniMapDefinedData::instance.field90_0x27c[iVar12]
                                                          .colorModeSpecificValue[_isRGB565];
                                        } else if ((DAT_TileMapState::instance.MiscDisplayLayer[_tile] & 0x2000) == 0) {
                                        LAB_004b55d3:
                                            param_4 = 0;
                                        } else {
                                            param_4 = (uint)DAT_MiniMapDefinedData::instance.field1_0x20[_isRGB565];
                                        }
                                    } else {
                                        param_4 = (uint)DAT_MiniMapDefinedData::instance.field16_0x144[_isRGB565
                                            + ((int)(short)DAT_TileMapState::instance.RandomLayer[_tile] & 3U) * 2];
                                    }
                                } else {
                                    param_4 = (uint)DAT_MiniMapDefinedData::instance.field6_0x74[_isRGB565
                                        + ((int)(short)DAT_TileMapState::instance.RandomLayer[_tile] & 3U) * 2];
                                }
                                if (((DAT_TileMapState::instance.LuminesenceLayer[_tile] != 2) && ((short)param_4 != 0))
                                    && ((_tile1003 & 2) == 0)) {
                                    iVar12 = DAT_MiniMapDefinedData::instance
                                                 .field0_0x0[DAT_TileMapState::instance.LuminesenceLayer[_tile]];
                                    if (_isRGB565 == 0) {
                                        uVar9 = (int)((param_4 & 0x7c00) * iVar12) / 100;
                                        if (0x7c00 < (int)uVar9) {
                                            uVar9 = 0x7c00;
                                        }
                                        uVar13 = (int)((param_4 & 0x3e0) * iVar12) / 100;
                                        uVar9 = uVar9 & 0x7c00;
                                        if (0x3e0 < (int)uVar13) {
                                            uVar13 = 0x3e0;
                                        }
                                        uVar13 = uVar13 & 0x3e0;
                                    } else {
                                        uVar9 = (int)((param_4 & 0xf800) * iVar12) / 100;
                                        if (0xf800 < (int)uVar9) {
                                            uVar9 = 0xf800;
                                        }
                                        uVar13 = (int)((param_4 & 0x7e0) * iVar12) / 100;
                                        uVar9 = uVar9 & 0xf800;
                                        if (0x7e0 < (int)uVar13) {
                                            uVar13 = 0x7e0;
                                        }
                                        uVar13 = uVar13 & 0x7e0;
                                    }
                                    uVar4 = (int)((param_4 & 0x1f) * iVar12) / 100;
                                    if (0x1f < (int)uVar4) {
                                        uVar4 = 0x1f;
                                    }
                                    param_4 = uVar4 & 0x1f | uVar13 | uVar9;
                                }
                                if (local_58 == 1) {
                                    local_38 = 0;
                                    uVar9 = param_4;
                                    if (0 < param_2) {
                                        do {
                                            if (((-1 < (int)(uVar6 + local_38))
                                                    && ((int)(uVar6 + local_38) < iVar1 * param_2))
                                                && (local_4c = 0, 0 < param_3)) {
                                                do {
                                                    if ((short)uVar9 == 0) {
                                                        uVar9 = (uint)this
                                                                    ->field18_0x27144[((param_5 + local_4c) * 400) / 2
                                                                        + uVar6 + local_38];
                                                        param_4 = uVar9;
                                                    }
                                                    *(undefined2*)((uVar6 + local_38) * 2
                                                        + (int)DAT_MinimapViewState::instance.field17_0x44
                                                        + (param_5 + local_4c) * 400) = (undefined2)param_4;
                                                    local_4c = local_4c + 1;
                                                } while (local_4c < param_3);
                                            }
                                            local_38 = local_38 + 1;
                                        } while (local_38 < param_2);
                                    }
                                } else {
                                    uVar9 = uVar6 & 1;
                                    if ((int)uVar9 < param_2) {
                                        iVar11 = ((param_2 - uVar9) - 1 >> 1) + 1;
                                        iVar12 = uVar6 + uVar9;
                                        uVar9 = param_4;
                                        do {
                                            if ((-1 < iVar12) && (iVar12 < iVar1 * param_2)) {
                                                iVar7 = 0;
                                                if (0 < param_3) {
                                                    do {
                                                        iVar5 = (param_5 + iVar7) / local_58;
                                                        if ((short)uVar9 == 0) {
                                                            uVar9 = (uint)this->field18_0x27144[(iVar5 * 400) / 2
                                                                + iVar12 / local_58];
                                                            param_4 = uVar9;
                                                        }
                                                        *(undefined2*)((iVar12 / local_58) * 2
                                                            + (int)DAT_MinimapViewState::instance.field17_0x44
                                                            + iVar5 * 400) = (undefined2)param_4;
                                                        iVar7 = iVar7 + 1;
                                                    } while (iVar7 < param_3);
                                                }
                                            }
                                            iVar12 = iVar12 + 2;
                                            iVar11 = iVar11 + -1;
                                        } while (iVar11 != 0);
                                    }
                                }
                                uVar6 = uVar6 + param_2;
                                local_50 = local_50 + 1;
                                local_2c = local_2c + -1;
                            } while (local_2c != 0);
                        }
                    }
                }
                local_48 = local_48 + param_3;
                param_5 = param_5 + param_3;
                local_44 = local_44 + local_24;
                uVar10 = uVar10 + 1;
            } while ((int)uVar10 < iVar8);
        }
    }

}
}
