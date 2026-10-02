#include "../MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_MiniMapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B58D0
    void MinimapViewState::renderMinimapTileColors(uint param_1, int param_2, int param_3, int param_4, uint param_5)
    {
        int iVar1;
        int iVar2;
        int iVar3;
        uint uVar4;
        uint _tileRandom;
        uint _tileColor;
        int iVar5;
        int iVar6;
        int iVar7;
        int iVar8;
        int iVar9;
        uint _colorMode;
        int local_54;
        int local_50;
        int local_4c;
        int local_48;
        int* local_40;
        uint local_3c;
        int local_38;
        int local_30;
        int local_2c;
        int local_24;
        int local_20;
        int _tile;
        uint _tile1003;
        byte _tileTerrain;
        int _viewportWidth;
        _viewportWidth = DAT_ViewportRenderState::instance.viewportState.viewportHeight;
        iVar6 = param_4 * 400;
        iVar2 = param_4 + param_5;
        _tileColor = 0;
        iVar7 = 1;
        local_54 = 1;
        local_38 = 2;
        if ((param_1 & 4) != 0) {
            iVar7 = 2;
            local_54 = 2;
        }
        iVar3 = (int)(400 / (longlong)param_2) * iVar7;
        _colorMode = (uint)(DAT_WindowAndDirectDraw::instance.colorBitMode == 1381);
        if (DAT_TileMapState::instance.mapSize < 200) {
            _tileColor = 100;
            local_38 = 1;
        }
        iVar1 = DAT_ViewportRenderState::instance.viewportState.viewportHeight + 1;
        if (DAT_TileMapState::instance.mapOrientation == 0) {
            iVar5 = 8;
        } else if (DAT_TileMapState::instance.mapOrientation == 6) {
            iVar5 = 80408;
        } else if (DAT_TileMapState::instance.mapOrientation == 4) {
            iVar5 = 160808;
        } else {
            iVar5 = 241208;
            if (DAT_TileMapState::instance.mapOrientation != 2) {
                iVar5 = 8;
            }
        }
        uVar4 = _tileColor / 2;
        iVar7 = iVar7 * 200 - _tileColor;
        local_50 = iVar5 + 1 + uVar4 * 401;
        if ((int)_tileColor < iVar7) {
            local_3c = 0;
            local_4c = 0;
            param_1 = _tileColor;
            local_48 = iVar1;
            do {
                if (local_48 == iVar1) {
                    local_48 = _viewportWidth;
                    param_5 = param_2 / 2;
                    local_20 = 200;
                } else {
                    param_5 = 0;
                    local_20 = 0xc9;
                    local_48 = iVar1;
                }
                if (iVar6 / 100 <= (int)param_1) {
                    if ((iVar2 * 400) / 100 <= (int)param_1) {}
                    if (((local_54 != 2) || ((local_3c & 1) == 0))
                        && (local_24 = iVar3 / local_38 - uVar4, (int)uVar4 < local_24)) {
                        local_40 = DAT_ViewportRenderState::instance.screenPointToTileNumber + uVar4 + local_50 + -8;
                        local_24 = local_24 - uVar4;
                        do {
                            _tile = *local_40;
                            _tile1003 = DAT_TileMapState::instance.LogicLayer[_tile];
                            _tileTerrain = DAT_TileMapState::instance.Logic2Layer[_tile];
                            _tileRandom = (uint)(short)DAT_TileMapState::instance.RandomLayer[_tile];
                            if ((_tile1003 & 0x30) == 0) {
                                if ((_tile1003 & 1) == 0) {
                                    if ((_tile1003 & 0x200000) == 0) {
                                        if ((_tile1003 & 0x100000) == 0) {
                                            if ((_tile1003 & 0x20000) == 0) {
                                                if ((char)_tile1003 < '\0') {
                                                    _tileColor
                                                        = (uint)DAT_MiniMapDefinedData::instance
                                                              .MinimapColorArray[_colorMode + (_tileRandom & 3) * 2];
                                                } else if ((_tile1003 & 0x40000) == 0) {
                                                    if ((_tileTerrain & 0x40) == 0) {
                                                        if ((_tileTerrain & 0x20) == 0) {
                                                            if (((_tileTerrain & 0x10) == 0)
                                                                || ((_tile1003 & 0x8000) == 0)) {
                                                                if (((char)_tileTerrain < '\0')
                                                                    && ((_tile1003 & 0x8000) != 0)) {
                                                                    _tileColor = (uint)DAT_MiniMapDefinedData::instance
                                                                                     .field19_0x174[_colorMode
                                                                                         + (_tileRandom & 3) * 2];
                                                                } else if (((_tileTerrain & 1) == 0)
                                                                    || ((_tile1003 & 0x8000) == 0)) {
                                                                    if ((_tile1003 & 0x80000) == 0) {
                                                                        if ((_tile1003 & 0xa0000000) == 0) {
                                                                            if (0x10 < DAT_TileMapState::instance
                                                                                    .HeightLayer[_tile])
                                                                                goto LAB_004b5bbe;
                                                                            if (((_tileTerrain & 2) == 0)
                                                                                && ((_tile1003 & 8) == 0)) {
                                                                                _tileColor
                                                                                    = (uint)DAT_MiniMapDefinedData::
                                                                                          instance
                                                                                              .field14_0x104[_colorMode
                                                                                                  + (_tileRandom & 7)
                                                                                                      * 2];
                                                                            } else {
                                                                                _tileColor
                                                                                    = (uint)DAT_MiniMapDefinedData::
                                                                                          instance
                                                                                              .field15_0x124[_colorMode
                                                                                                  + (_tileRandom & 7)
                                                                                                      * 2];
                                                                            }
                                                                        } else {
                                                                            _tileColor
                                                                                = (uint)DAT_MiniMapDefinedData::instance
                                                                                      .field13_0xf4[_colorMode
                                                                                          + (_tileRandom & 3) * 2];
                                                                        }
                                                                    } else {
                                                                        _tileColor
                                                                            = (uint)DAT_MiniMapDefinedData::instance
                                                                                  .field12_0xe4[_colorMode
                                                                                      + (_tileRandom & 3) * 2];
                                                                    }
                                                                } else {
                                                                    _tileColor = (uint)DAT_MiniMapDefinedData::instance
                                                                                     .field18_0x164[_colorMode
                                                                                         + (_tileRandom & 3) * 2];
                                                                }
                                                            } else {
                                                                _tileColor = (uint)DAT_MiniMapDefinedData::instance
                                                                                 .field20_0x184[_colorMode
                                                                                     + (_tileRandom & 3) * 2];
                                                            }
                                                        } else {
                                                            _tileColor
                                                                = (uint)DAT_MiniMapDefinedData::instance
                                                                      .field11_0xd4[_colorMode + (_tileRandom & 3) * 2];
                                                        }
                                                    } else {
                                                    LAB_004b5bbe:
                                                        _tileColor
                                                            = (uint)DAT_MiniMapDefinedData::instance
                                                                  .field17_0x154[_colorMode + (_tileRandom & 3) * 2];
                                                    }
                                                } else {
                                                    _tileColor = (uint)DAT_MiniMapDefinedData::instance
                                                                     .field9_0xb4[_colorMode + (_tileRandom & 3) * 2];
                                                }
                                            } else {
                                                _tileColor = (uint)DAT_MiniMapDefinedData::instance
                                                                 .field7_0x84[_colorMode + (_tileRandom & 7) * 2];
                                            }
                                        } else {
                                            _tileColor = (uint)DAT_MiniMapDefinedData::instance
                                                             .field3_0x44[_colorMode + (_tileRandom & 3) * 2];
                                        }
                                    } else {
                                        _tileColor = (uint)DAT_MiniMapDefinedData::instance
                                                         .field4_0x54[_colorMode + (_tileRandom & 7) * 2];
                                    }
                                } else {
                                    _tileColor = (uint)DAT_MiniMapDefinedData::instance
                                                     .field2_0x24[_colorMode + (_tileRandom & 7) * 2];
                                }
                            } else {
                                _tileColor = 0;
                            }
                            (*(short*)&param_4) = (ushort)_tileColor;
                            if (DAT_TileMapState::instance.LuminesenceLayer[_tile] != 2) {
                                iVar5 = DAT_MiniMapDefinedData::instance
                                            .field0_0x0[DAT_TileMapState::instance.LuminesenceLayer[_tile]];
                                if (_colorMode == 0) {
                                    iVar8 = (int)((_tileColor & 0x7c00) * iVar5) / 100;
                                    if (0x7c00 < iVar8) {
                                        iVar8 = 31744;
                                    }
                                    iVar9 = (int)((_tileColor & 0x3e0) * iVar5) / 100;
                                    if (0x3e0 < iVar9) {
                                        iVar9 = 992;
                                    }
                                    iVar5 = (int)((_tileColor & 0x1f) * iVar5) / 100;
                                    if (0x1f < iVar5) {
                                        iVar5 = 31;
                                    }
                                    (*(short*)&param_4)
                                        = (ushort)iVar5 & 0x1f | (ushort)iVar9 & 0x3e0 | (ushort)iVar8 & 0x7c00;
                                } else {
                                    iVar8 = (int)((_tileColor & 0xf800) * iVar5) / 100;
                                    if (0xf800 < iVar8) {
                                        iVar8 = 0xf800;
                                    }
                                    iVar9 = (int)((_tileColor & 0x7e0) * iVar5) / 100;
                                    if (0x7e0 < iVar9) {
                                        iVar9 = 0x7e0;
                                    }
                                    iVar5 = (int)((_tileColor & 0x1f) * iVar5) / 100;
                                    if (0x1f < iVar5) {
                                        iVar5 = 0x1f;
                                    }
                                    (*(short*)&param_4)
                                        = (ushort)iVar5 & 0x1f | (ushort)iVar9 & 0x7e0 | (ushort)iVar8 & 0xf800;
                                }
                            }
                            if (local_54 == 1) {
                                local_2c = 0;
                                if (0 < param_2) {
                                    do {
                                        if (((-1 < (int)(param_5 + local_2c))
                                                && ((int)(param_5 + local_2c) < iVar3 * param_2))
                                            && (local_30 = 0, 0 < param_3)) {
                                            do {
                                                *(ushort*)((param_5 + local_2c) * 2 + 0x1a58754
                                                    + (local_4c + local_30) * 400) = (ushort)param_4;
                                                local_30 = local_30 + 1;
                                            } while (local_30 < param_3);
                                        }
                                        local_2c = local_2c + 1;
                                    } while (local_2c < param_2);
                                }
                            } else {
                                _tileColor = param_5 & 1;
                                if ((int)_tileColor < param_2) {
                                    iVar5 = param_5 + _tileColor;
                                    iVar8 = ((param_2 - _tileColor) - 1 >> 1) + 1;
                                    do {
                                        if ((-1 < iVar5) && (iVar5 < iVar3 * param_2)) {
                                            iVar9 = 0;
                                            if (0 < param_3) {
                                                do {
                                                    *(ushort*)((iVar5 / local_54) * 2 + 0x1a58754
                                                        + ((local_4c + iVar9) / local_54) * 400) = (ushort)param_4;
                                                    iVar9 = iVar9 + 1;
                                                } while (iVar9 < param_3);
                                            }
                                        }
                                        iVar5 = iVar5 + 2;
                                        iVar8 = iVar8 + -1;
                                    } while (iVar8 != 0);
                                }
                            }
                            local_40 = local_40 + 1;
                            param_5 = param_5 + param_2;
                            local_24 = local_24 + -1;
                        } while (local_24 != 0);
                    }
                }
                local_3c = local_3c + param_3;
                local_4c = local_4c + param_3;
                local_50 = local_50 + local_20;
                param_1 = param_1 + 1;
            } while ((int)param_1 < iVar7);
        }
    }

}
}
