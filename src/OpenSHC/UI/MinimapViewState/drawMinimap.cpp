#include "../MinimapViewState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/States/UnitStateShort.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MiniMapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Game::GameMode;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::UnitTypeShort;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::Map::Units::States::UnitStateShort;

    /*
      WARNING: Restarted to delay deadcode elimination for space: ram
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004B66C0
    void MinimapViewState::drawMinimap(int xPos, int yPos, int width, int height, uint flags, int xOffset, int yOffset,
        int widthFactor, int heightFactor, int param_10)
    {
        UnitStateShort UVar1;
        ushort uVar2;
        short sVar3;
        bool bVar4;
        int iVar5;
        int iVar6;
        int iVar7;
        int iVar8;
        int iVar9;
        int iVar10;
        int _unitID;
        uint uVar11;
        int iVar12;
        int iVar13;
        int _owner;
        int iVar14;
        int iVar15;
        int local_4c;
        int local_44;
        int* _tile;
        uint local_34;
        int local_30;
        int local_2c;
        uint local_24;
        int _mapSize;
        int local_1c;
        int local_18;
        uint _isRGB16;
        int local_10;
        int local_c;
        int local_8;
        short _player;
        UnitTypeShort _unitType;
        int _viewportWidth;
        iVar5 = height;
        local_8 = 1;
        bVar4 = true;
        local_c = 8;
        local_18 = width;
        local_4c = 0;
        local_24 = 0;
        _mapSize = DAT_TileMapState::instance.mapSize;
        if (DAT_TileMapState::instance.mapSize == 0) {
            _mapSize = 400;
        }
        iVar12 = 400 - _mapSize;
        if (width < 200) {
            iVar14 = (int)(iVar12 + (iVar12 >> 0x1f & 3U)) >> 2;
            local_2c = iVar12 / 2 + 2;
            iVar13 = 400 - iVar12 / 2;
            iVar6 = iVar13 / 2 + -2;
            local_30 = iVar14 + 1;
        } else {
            local_2c = iVar12 / 2;
            iVar13 = 400 - local_2c;
            iVar14 = (int)(iVar12 + (iVar12 >> 0x1f & 3U)) >> 2;
            iVar6 = iVar13 / 2;
            local_30 = iVar14;
        }
        if (DAT_MiniMapDefinedData::instance.field92_0x2c0 != DAT_TileMapState::instance.mapOrientation) {
            /*
              this is run when you first? load a map
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setTileColorsDependingOnMapSize, this)(0, 100);
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setMapPropertyDependingOnMapSize, this)(0, 100);
            DAT_MiniMapDefinedData::instance.field92_0x2c0 = DAT_TileMapState::instance.mapOrientation;
        }
        if (this->field14_0x38 != 0) {
            if (this->field13_0x34 == 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setTileColorsDependingOnMapSize, this)(0, 2);
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setMapPropertyDependingOnMapSize, this)(
                    this->field13_0x34, 2);
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::TileMapState_Func::collectCliffEdgeTilesForClimbData, DAT_TileMapState::ptr)();
                this->field13_0x34 = this->field13_0x34 + 2;
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setTileColorsDependingOnMapSize, this)(
                    this->field13_0x34, 2);
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setMapPropertyDependingOnMapSize, this)(
                    this->field13_0x34, 2);
                this->field13_0x34 = this->field13_0x34 + 2;
                if (99 < (int)this->field13_0x34) {
                    this->field14_0x38 = this->field14_0x38 + -1;
                    if (this->field14_0x38 < 1) {
                        this->field14_0x38 = 0;
                    } else {
                        this->field13_0x34 = 0;
                    }
                }
            }
        }
        _viewportWidth = DAT_ViewportRenderState::instance.viewportState.viewportHeight;
        if ((flags & 4) == 0) {
            this->oneOrTwo = 1;
        } else {
            this->oneOrTwo = 2;
            local_8 = 2;
        }
        /*
          200
         */
        if (DAT_TileMapState::instance.mapSize < 200) {
            local_4c = 100;
            local_24 = 100;
        }
        this->width = width;
        this->heightFactor = heightFactor;
        this->x = xPos;
        this->y = yPos;
        this->height = height;
        this->widthFactor = widthFactor;
        iVar7 = DAT_ViewportRenderState::instance.viewportState.viewportHeight + -5;
        local_1c = (iVar7 * widthFactor) / this->oneOrTwo + -1 + widthFactor / local_8;
        local_44 = (DAT_ViewportRenderState::instance.viewportState.viewportWidth * heightFactor) / local_8 + -1;
        iVar8 = (width / widthFactor) * local_8;
        iVar9 = (height / heightFactor) * local_8;
        _isRGB16 = (uint)(DAT_WindowAndDirectDraw::instance.colorBitMode == 1381);
        local_10 = xOffset;
        iVar10 = _mapSize / 2;
        if (iVar10 < iVar8) {
            iVar14 = iVar14 - (iVar8 - iVar10) / 2;
            this->field4_0x10 = iVar12 / 2 - (iVar9 - _mapSize) / 2;
            local_10 = xOffset - iVar7 / 2;
            yOffset = yOffset - DAT_ViewportRenderState::instance.viewportState.viewportWidth / 2;
            bVar4 = local_10 < local_30;
            if (bVar4) {
                local_1c = (iVar10 * widthFactor) / local_8;
                local_10 = local_30;
            }
            bVar4 = !bVar4;
            xOffset = iVar14;
            if (yOffset < local_2c) {
                local_44 = (_mapSize * heightFactor) / local_8;
                yOffset = local_2c;
                bVar4 = false;
            }
        } else {
            iVar12 = yOffset;
            if ((flags & 1) != 0) {
                iVar12 = yOffset - iVar9 / 2;
                local_10 = xOffset - iVar7 / 2;
                yOffset = yOffset - DAT_ViewportRenderState::instance.viewportState.viewportWidth / 2;
                xOffset = xOffset - iVar8 / 2;
            }
            iVar14 = local_30;
            if ((xOffset < local_30) || (iVar14 = iVar6 - iVar8, iVar14 < xOffset)) {
                xOffset = iVar14;
            }
            this->field4_0x10 = local_2c;
            if ((local_2c <= iVar12) && (iVar14 = (iVar13 - iVar9) + -1, this->field4_0x10 = iVar12, iVar14 < iVar12)) {
                this->field4_0x10 = iVar14;
            }
            if ((local_10 < local_30)
                || (local_30 = (iVar6 - DAT_ViewportRenderState::instance.viewportState.viewportHeight) + 5,
                    local_30 < local_10)) {
                local_10 = local_30;
            }
            if (yOffset < local_2c) {
                yOffset = local_2c;
            } else {
                iVar12 = (iVar13 - DAT_ViewportRenderState::instance.viewportState.viewportWidth) + -1;
                if (iVar12 < yOffset) {
                    yOffset = iVar12;
                }
            }
        }
        this->field5_0x14 = xOffset;
        iVar6 = ((local_10 - xOffset) * widthFactor) / local_8 + xPos;
        iVar12 = ((yOffset - this->field4_0x10) * heightFactor) / local_8 + yPos;
        iVar13 = DAT_ViewportRenderState::instance.viewportState.viewportHeight + 1;
        iVar14 = this->field4_0x10 / 2;
        if (DAT_TileMapState::instance.mapOrientation == 0) {
            local_c = 8;
        } else if (DAT_TileMapState::instance.mapOrientation == 6) {
            local_c = 80408;
        } else if (DAT_TileMapState::instance.mapOrientation == 4) {
            local_c = 0x27428;
        } else if (DAT_TileMapState::instance.mapOrientation == 2) {
            local_c = 241208;
        }
        iVar7 = (xOffset * widthFactor) / local_8;
        local_c = local_c + 1 + iVar14 * 0x191 + xOffset;
        if (param_10 < 1) {
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::setupPencilSurface, DAT_PencilRenderCore::ptr)();
        } else {
            DAT_PencilRenderCore::instance.surfacePtr = (ushort*)this->loadedMiniMap;
            DAT_PencilRenderCore::instance.horizontalByteSize = 400;
            this->DAT_SomeMiniMapCounterTill4 = 0;
        }
        xOffset = iVar7;
        if (param_10 != 0) {
            if (DAT_TileMapState::instance.mapSize == 160) {
                local_18 = width + -5;
                xPos = xPos + 3;
            } else if (DAT_TileMapState::instance.mapSize == 200) {
                xPos = xPos + 3;
                xOffset = iVar7 + 1;
                local_18 = width + -4;
            }
        }
        iVar7 = (int)DAT_PencilRenderCore::instance.surfacePtr
            + yPos * DAT_PencilRenderCore::instance.horizontalByteSize + xPos * 2;
        iVar14 = (xOffset - local_4c) * 2 + 0x1a31654 + (iVar14 * heightFactor - local_24) * 400;
        do {
            iVar15 = 0;
            iVar10 = local_18;
            do {
                *(undefined2*)(iVar7 + iVar15) = *(undefined2*)(iVar14 + iVar15);
                iVar15 = iVar15 + 2;
                iVar10 = iVar10 + -1;
            } while (iVar10 != 0);
            iVar14 = iVar14 + 400;
            iVar7 = iVar7 + DAT_PencilRenderCore::instance.horizontalByteSize;
            height = height + -1;
        } while (height != 0);
        if (((param_10 != 0) && (DAT_TileMapState::instance.mapSize != 160))
            && (DAT_TileMapState::instance.mapSize == 200)) {
            xPos = xPos + -2;
        }
        _mapSize = iVar13;
        if (DAT_GameCore::instance.altRToggleMinimapHideWildlife == 0) {
            if (0 < iVar9) {
                local_34 = 0;
                local_4c = iVar9;
                do {
                    if (_mapSize == iVar13) {
                        _mapSize = _viewportWidth;
                        iVar14 = widthFactor / 2;
                        param_10 = 200;
                    } else {
                        iVar14 = 0;
                        param_10 = 0xc9;
                        _mapSize = iVar13;
                    }
                    if (((local_8 != 2) || ((local_34 & 1) == 0)) && (xOffset = -2, -2 < iVar8)) {
                        local_24 = iVar14 + widthFactor * -2;
                        _tile = DAT_ViewportRenderState::instance.screenPointToTileNumber + local_c + -10;
                        do {
                            _unitID = (int)(short)DAT_TileMapState::instance.UnitLayer[*_tile];
                            if ((_unitID != 0)
                                || ((local_8 == 2
                                    && (_unitID = (int)(short)
                                            DAT_TileMapState::instance.UnitLayer[DAT_ViewportRenderState::instance
                                                    .screenPointToTileNumber[xOffset + param_10 + local_c + -8]],
                                        _unitID != 0)))) {
                                _player = DAT_UnitsState::instance.units[_unitID].owner;
                                if (_player == 0) {
                                    (*(short*)&height)
                                        = *(ushort*)((int)(DAT_MiniMapDefinedData::instance.PlayerColorColors + 2)
                                            + _isRGB16 * 2);
                                } else {
                                    if (DAT_UnitsState::instance.units[_unitID].isSelectable_OR_matchTime == 0) {
                                    LAB_004b6cb0:
                                        _owner = (int)_player;
                                    } else {
                                        _unitType = DAT_UnitsState::instance.units[_unitID].unitType;
                                        if (_unitType == OpenSHC::Map::Units::UT_E_KNIGHT) {
                                        LAB_004b6ca7:
                                            _owner = (int)DAT_UnitsState::instance.units[_unitID].displayColorPlayerID;
                                        } else {
                                            if (_unitType == OpenSHC::Map::Units::UT_S_TOWER)
                                                goto LAB_004b6cb0;
                                            if (_unitType == OpenSHC::Map::Units::UT_A_HARCHER)
                                                goto LAB_004b6ca7;
                                            _owner = DAT_UnitsState::instance.units[_unitID].calculatedOwnerPlayerIndex;
                                        }
                                    }
                                    if (_owner < 1) {
                                        _owner = 1;
                                    }
                                    switch (DAT_UnitsState::instance.units[_unitID].unitType) {
                                    case OpenSHC::Map::Units::UT_S_CATAPULT:
                                    case OpenSHC::Map::Units::UT_S_TREBUCHET:
                                    case OpenSHC::Map::Units::UT_S_MANGONEL:
                                    case OpenSHC::Map::Units::UT_S_TOWER:
                                    case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                                    case OpenSHC::Map::Units::UT_S_SHIELD:
                                    case OpenSHC::Map::Units::UT_S_BALLISTA:
                                    case OpenSHC::Map::Units::UT_S_FBALLISTA:
                                        (*(short*)&height)
                                            = DAT_MiniMapDefinedData::instance
                                                  .PlayerColorColors[this->DAT_SomeMiniMapCounterTill4
                                                      + DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[_owner]
                                                          * 4][_isRGB16];
                                        break;
                                    default:
                                        (*(short*)&height)
                                            = DAT_MiniMapDefinedData::instance.PlayerColorColors
                                                  [DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[_owner] * 4]
                                                  [_isRGB16];
                                        break;
                                    case OpenSHC::Map::Units::UT_COW:
                                    case OpenSHC::Map::Units::UT_HUNTERDOG:
                                    case OpenSHC::Map::Units::UT_CHICKEN:
                                        (*(short*)&height)
                                            = *(ushort*)((int)(DAT_MiniMapDefinedData::instance.PlayerColorColors + 2)
                                                + _isRGB16 * 2);
                                        break;
                                    case OpenSHC::Map::Units::UT_A_ASSASSIN:
                                        (*(short*)&height)
                                            = DAT_MiniMapDefinedData::instance.PlayerColorColors
                                                  [DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[_owner] * 4]
                                                  [_isRGB16];
                                        if ((((DAT_GameState::instance.mapAndTime.playerTeams[_player]
                                                  != DAT_GameState::instance.mapAndTime.playerTeams
                                                      [DAT_GameSynchronyState::instance.currentPlayerSlotID])
                                                 && (160 < DAT_UnitsState::instance.units[_unitID]
                                                         .assassinsMicroDistanceToEnemyUnk))
                                                && (UVar1 = DAT_UnitsState::instance.units[_unitID].state.generic,
                                                    UVar1 != OpenSHC::Map::Units::States::US_MELEE_ATTACK))
                                            && ((UVar1 != OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL
                                                && ((DAT_GameSynchronyState::instance.currentGameMode
                                                        != OpenSHC::Game::GM_SOLITARY
                                                    || (DAT_UnitsState::instance.units[_unitID].idleCounterUnk
                                                        < 0x961))))))
                                            goto LAB_004b6eb4;
                                    }
                                }
                                if (local_8 == 1) {
                                    local_30 = 0;
                                    if (0 < widthFactor) {
                                        do {
                                            iVar14 = local_24 + xPos + local_30;
                                            if (((xPos <= iVar14) && (iVar14 < iVar8 * widthFactor + xPos))
                                                && (local_2c = 0, 0 < heightFactor)) {
                                                do {
                                                    *(ushort*)((int)DAT_PencilRenderCore::instance.surfacePtr
                                                        + (local_34 + yPos + local_2c)
                                                            * DAT_PencilRenderCore::instance.horizontalByteSize
                                                        + (local_24 + xPos + local_30) * 2) = (ushort)height;
                                                    local_2c = local_2c + 1;
                                                } while (local_2c < heightFactor);
                                            }
                                            local_30 = local_30 + 1;
                                        } while (local_30 < widthFactor);
                                    }
                                } else {
                                    uVar11 = local_24 & 1;
                                    if ((int)uVar11 < widthFactor) {
                                        iVar14 = local_24 + uVar11;
                                        iVar7 = ((widthFactor - uVar11) - 1 >> 1) + 1;
                                        do {
                                            if ((-1 < iVar14) && (iVar14 < iVar8 * widthFactor)) {
                                                iVar9 = 0;
                                                if (0 < heightFactor) {
                                                    do {
                                                        *(ushort*)((int)DAT_PencilRenderCore::instance.surfacePtr
                                                            + ((int)(local_34 + iVar9) / local_8 + yPos)
                                                                * DAT_PencilRenderCore::instance.horizontalByteSize
                                                            + (iVar14 / local_8 + xPos) * 2) = (ushort)height;
                                                        iVar9 = iVar9 + 1;
                                                    } while (iVar9 < heightFactor);
                                                }
                                            }
                                            iVar14 = iVar14 + 2;
                                            iVar7 = iVar7 + -1;
                                        } while (iVar7 != 0);
                                    }
                                }
                            }
                        LAB_004b6eb4:
                            _tile = _tile + 1;
                            local_24 = local_24 + widthFactor;
                            xOffset = xOffset + 1;
                        } while (xOffset < iVar8);
                    }
                    local_34 = local_34 + heightFactor;
                    local_c = local_c + param_10;
                    local_4c = local_4c + -1;
                } while (local_4c != 0);
            }
        } else {
            uVar2
                = DAT_MiniMapDefinedData::instance
                      .PlayerColorColors[DAT_BlendingDefinedData::instance
                                             .PlayerSlotUnitColor[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          * 4][_isRGB16];
            (*(short*)&local_4c) = 0;
            iVar14 = 1;
            do {
                if (DAT_GameState::instance.mapAndTime.playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    != DAT_GameState::instance.mapAndTime.playerTeams[iVar14]) {
                    (*(short*)&local_4c)
                        = DAT_MiniMapDefinedData::instance
                              .PlayerColorColors[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[iVar14] * 4]
                                                [_isRGB16];
                    break;
                }
                iVar14 = iVar14 + 1;
            } while (iVar14 < 9);
            if (0 < iVar9) {
                local_34 = 0;
                iVar14 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                _isRGB16 = iVar9;
                do {
                    if (_mapSize == iVar13) {
                        _mapSize = _viewportWidth;
                        iVar7 = widthFactor / 2;
                        param_10 = 200;
                    } else {
                        iVar7 = 0;
                        param_10 = 0xc9;
                        _mapSize = iVar13;
                    }
                    if (((local_8 != 2) || ((local_34 & 1) == 0)) && (xOffset = -2, -2 < iVar8)) {
                        local_24 = iVar7 + widthFactor * -2;
                        _tile = DAT_ViewportRenderState::instance.screenPointToTileNumber + local_c + -10;
                        do {
                            iVar7 = (int)(short)DAT_TileMapState::instance.UnitLayer[*_tile];
                            if (((iVar7 != 0)
                                    || ((local_8 == 2
                                        && (iVar7 = (int)(short)
                                                DAT_TileMapState::instance.UnitLayer[DAT_ViewportRenderState::instance
                                                        .screenPointToTileNumber[xOffset + param_10 + local_c + -8]],
                                            iVar7 != 0))))
                                && (sVar3 = DAT_UnitsState::instance.units[iVar7].owner, sVar3 != 0)) {
                                switch (DAT_UnitsState::instance.units[iVar7].unitType) {
                                case OpenSHC::Map::Units::UT_COW:
                                case OpenSHC::Map::Units::UT_HUNTERDOG:
                                case OpenSHC::Map::Units::UT_CHICKEN:
                                    break;
                                default:
                                switchD_004b702c_caseD_35:
                                    (*(short*)&height) = uVar2;
                                    if (DAT_GameState::instance.mapAndTime.playerTeams[iVar14]
                                        != DAT_GameState::instance.mapAndTime.playerTeams[sVar3]) {
                                        (*(short*)&height) = (ushort)local_4c;
                                    }
                                    if (local_8 == 1) {
                                        local_30 = 0;
                                        if (0 < widthFactor) {
                                            do {
                                                iVar14 = local_24 + xPos + local_30;
                                                if (((xPos <= iVar14) && (iVar14 < iVar8 * widthFactor + xPos))
                                                    && (local_2c = 0, 0 < heightFactor)) {
                                                    do {
                                                        *(ushort*)((int)DAT_PencilRenderCore::instance.surfacePtr
                                                            + (local_34 + yPos + local_2c)
                                                                * DAT_PencilRenderCore::instance.horizontalByteSize
                                                            + (local_24 + xPos + local_30) * 2) = (ushort)height;
                                                        local_2c = local_2c + 1;
                                                    } while (local_2c < heightFactor);
                                                }
                                                local_30 = local_30 + 1;
                                                iVar14 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                                            } while (local_30 < widthFactor);
                                        }
                                    } else {
                                        uVar11 = local_24 & 1;
                                        if ((int)uVar11 < widthFactor) {
                                            iVar7 = local_24 + uVar11;
                                            iVar9 = ((widthFactor - uVar11) - 1 >> 1) + 1;
                                            do {
                                                if ((-1 < iVar7) && (iVar7 < iVar8 * widthFactor)) {
                                                    iVar14 = 0;
                                                    if (0 < heightFactor) {
                                                        do {
                                                            *(ushort*)((int)DAT_PencilRenderCore::instance.surfacePtr
                                                                + ((int)(local_34 + iVar14) / local_8 + yPos)
                                                                    * DAT_PencilRenderCore::instance.horizontalByteSize
                                                                + (iVar7 / local_8 + xPos) * 2) = (ushort)height;
                                                            iVar14 = iVar14 + 1;
                                                        } while (iVar14 < heightFactor);
                                                    }
                                                }
                                                iVar7 = iVar7 + 2;
                                                iVar9 = iVar9 + -1;
                                                iVar14 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                                            } while (iVar9 != 0);
                                        }
                                    }
                                    break;
                                case OpenSHC::Map::Units::UT_A_ASSASSIN:
                                    if (((((DAT_GameState::instance.mapAndTime.playerTeams[sVar3]
                                               == DAT_GameState::instance.mapAndTime.playerTeams[iVar14])
                                              || (DAT_UnitsState::instance.units[iVar7].assassinsMicroDistanceToEnemyUnk
                                                  < 160))
                                             || (UVar1 = DAT_UnitsState::instance.units[iVar7].state.generic,
                                                 UVar1 == OpenSHC::Map::Units::States::US_MELEE_ATTACK))
                                            || (UVar1 == OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL))
                                        || ((DAT_GameSynchronyState::instance.currentGameMode
                                                == OpenSHC::Game::GM_SOLITARY
                                            && (0x960 < DAT_UnitsState::instance.units[iVar7].idleCounterUnk))))
                                        goto switchD_004b702c_caseD_35;
                                }
                            }
                            _tile = _tile + 1;
                            local_24 = local_24 + widthFactor;
                            xOffset = xOffset + 1;
                        } while (xOffset < iVar8);
                    }
                    local_34 = local_34 + heightFactor;
                    local_c = local_c + param_10;
                    _isRGB16 = _isRGB16 + -1;
                } while (_isRGB16 != 0);
            }
        }
        /*
          draws viewport lines
         */
        if (((flags & 2) != 0) && (bVar4)) {
            if (iVar6 < xPos) {
                if (local_18 + xPos <= local_1c + iVar6) {}
                local_1c = local_1c + (iVar6 - xPos);
                iVar6 = xPos;
            } else if (local_18 + xPos <= iVar6 + local_1c) {
                local_1c = (local_18 - iVar6) + -1 + xPos;
            }
            if (iVar12 < yPos) {
                if (iVar5 + yPos <= iVar12 + local_44) {}
                local_44 = local_44 + (iVar12 - yPos);
                iVar12 = yPos;
            } else if (yPos + iVar5 <= iVar12 + local_44) {
                local_44 = (iVar5 - iVar12) + yPos;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                iVar6, iVar12, local_1c + iVar6, iVar12 + local_44, 0xffff);
        }
    }

}
}
