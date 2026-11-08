#include "../ViewportRenderState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/IO/Graphics/GmIDInt.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Entities/EntityTypeShort.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/States/UnitStateShort.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_00ed3148.hpp"
#include "OpenSHC/Globals/DAT_00ed314c.hpp"
#include "OpenSHC/Globals/DAT_00ed3154.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentlyRenderedSpriteID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_GmImageAddressToBeRendered.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_MapRenderDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_DrawSomeX.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_DrawSomeY.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_ImageID.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_RowsLeft.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_SecondBlitImageIndex.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_WhatToDraw.hpp"
#include "OpenSHC/Globals/DAT_RenderMap_YOffset.hpp"
#include "OpenSHC/Globals/DAT_RenderedUnitOwner.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"
#include "OpenSHC/Globals/INT_00ed315c.hpp"

namespace OpenSHC {
namespace Rendering {

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::IO::Graphics::GmID;
    using OpenSHC::IO::Graphics::GmIDInt;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Buildings::BuildingTypeShort;
    using OpenSHC::Map::Entities::EntityType;
    using OpenSHC::Map::Entities::EntityTypeShort;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::UnitTypeShort;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::Map::Units::States::UnitStateShort;
    using OpenSHC::Rendering::ScreenResolutionEnum;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
    using OpenSHC::UI::Enums::MenuModalType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004E8CF0
    void ViewportRenderState::renderMap()
    {
        short* puVar1;
        int iVar2;
        EntityTypeShort EVar3;
        UnitStateShort UVar4;
        short sVar5;
        short sVar6;
        UnitTypeShort UVar7;
        BuildingTypeShort BVar8;
        ushort uVar9;
        ushort uVar10;
        GmID GVar11;
        int bVar12;
        int bVar13;
        int bVar14;
        byte bVar15;
        int layerTileIndex;
        short* psVar17;
        int iVar18;
        byte bVar19;
        short sVar20;
        int _visualTileOffset;
        int* piVar21;
        uint uVar22;
        int iVar23;
        int _numberToDisplay;
        short sVar24;
        int iVar25;
        int iVar26;
        int iVar27;
        int iVar28;
        uint uVar29;
        short sVar30;
        int iVar31;
        uint uVar32;
        int unitID;
        int local_5c;
        uint entityID;
        uint local_54;
        int _vpWidthPlus1_1;
        int local_48;
        uint _displayLayerLogicalValue;
        int _zoomOffset;
        int local_2c;
        int local_24;
        int* local_20;
        int local_1c;
        int local_14;
        uint local_c;
        int local_8;
        int _vpWidthPlus1;
        int _tile;
        int tileIndex;
        int _yOffset_01;
        int _flatView;
        int _viewportHeight;
        int viewportWidth;

        iVar31 = 0;
        iVar28 = 0;
        _displayLayerLogicalValue = 0;
        local_1c = 0;
        local_5c = 600;
        _flatView = 0;
        local_8 = 0;
        _zoomOffset = 0;
        uVar9 = 0;
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768) {
            local_5c = 768;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x1024) {
            local_5c = 1024;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x1200) {
            local_5c = 1200;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1280x720) {
            local_5c = 720;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1440x900) {
            local_5c = 900;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1080) {
            local_5c = 1080;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1920x1200) {
            local_5c = 1200;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1440) {
            local_5c = 1440;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_2560x1600) {
            local_5c = 1600;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1366x768) {
            local_5c = 768;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1680x1050) {
            local_5c = 1050;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1600x900) {
            local_5c = 900;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1360x768) {
            local_5c = 768;
        } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x600) {
            local_5c = 600;
        }
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::updateWaterAnimationFrames, this)();
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::assignRandomTiles, this)();
        viewportWidth = this->viewportState.viewportWidth;
        _viewportHeight = this->viewportState.viewportHeight;
        if ((DAT_TileMapState::instance.flatViewToggleValue1 != 0)
            && (DAT_TileMapState::instance.flatViewToggleValue2 != 0)) {
            _flatView = 1;
        }
        if (this->viewportState.isZoomedOutUnk != 0) {
            iVar28 = 4;
            _zoomOffset = 4;
        }
        _vpWidthPlus1_1 = this->viewportState.viewportHeight + 1;
        this->viewportState.unknownScreenXRelated = iVar28 * 32 + 70;
        iVar28 = this->viewportState.viewportWidth + 42;
        DAT_RenderMap_DrawSomeY::instance = 8;
        if (DAT_TileMapState::instance.mapOrientation == 0) {
        LAB_004e8e99:
            _visualTileOffset = 8;
        } else if (DAT_TileMapState::instance.mapOrientation == 6) {
            _visualTileOffset = 80408;
        } else if (DAT_TileMapState::instance.mapOrientation == 4) {
            _visualTileOffset = 160808;
        } else {
            _visualTileOffset = 241208;
            if (DAT_TileMapState::instance.mapOrientation != 2)
                goto LAB_004e8e99;
        }
        if (this->viewportState.field_0x94 != 0) {
            if (this->viewportState.isZoomedOutUnk == 0) {
                iVar31 = 64;
                local_1c = 8;
            } else {
                iVar31 = 128;
                local_1c = 16;
            }
            DAT_RenderMap_DrawSomeY::instance = iVar31 + 8;
        }
        _yOffset_01
            = (int)(this->viewportState.viewportY + iVar31 + (this->viewportState.viewportY + iVar31 >> 0x1f & 0xfU))
            >> 4;
        layerTileIndex = (this->viewportState.viewportX / 32) + _visualTileOffset;
        /*
          ***
           This piece of logic together with the huge array in the ViewportState gets
           the tile the top left corner of the screen is showing, offset by some margin
           to the right, not sure why that applies
           ***
         */

        iVar2 = layerTileIndex - 2 + _yOffset_01 * 401;
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::resetBatchedRender, this)();
        if (DAT_TileMapState::instance.mapOrientation == 6) {
            iVar26 = -this->viewportState.someYOffset;
            iVar23 = this->viewportState.someXOffset;
        } else if (DAT_TileMapState::instance.mapOrientation == 4) {
            iVar23 = -this->viewportState.someYOffset;
            iVar26 = -this->viewportState.someXOffset;
        } else {
            iVar23 = this->viewportState.someYOffset;
            iVar26 = this->viewportState.someXOffset;
            if (DAT_TileMapState::instance.mapOrientation == 2) {
                iVar23 = -this->viewportState.someXOffset;
                iVar26 = this->viewportState.someYOffset;
            }
        }
        this->viewportState.tileCenterX = iVar23
            + (this->screenPointToTileNumber[_yOffset_01 * 401 + layerTileIndex]
                - this
                    ->translationMatrix[this->tileTranslationMatrix_YComponent[this
                            ->screenPointToTileNumber[_yOffset_01 * 401 + layerTileIndex]]]
                    .addXgetTile);
        this->viewportState.tileCenterY = iVar26
            + this->tileTranslationMatrix_YComponent[this->screenPointToTileNumber[_yOffset_01 * 401 + layerTileIndex]];
        DAT_TextureRenderCoreObject::instance.isZoom2 = this->viewportState.isZoomedOutUnk;
        if (this->viewportState.isZoomedOutUnk == 0) {
            layerTileIndex = DAT_WindowAndDirectDraw::instance.resolutionY + 24;
        } else {
            layerTileIndex = DAT_WindowAndDirectDraw::instance.resolutionY * 2 + 32;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMapSurfaceHeightRange,
            DAT_TextureRenderCoreObject::ptr)(iVar31, layerTileIndex);
        this->viewportState.ptrColor = (DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame
            + this->viewportState.currentCameraOffsetX + DAT_MouseState::instance.screenSpaceX
            + (this->viewportState.currentCameraOffsetY + DAT_MouseState::instance.screenSpaceY) * 4056);
        this->viewportState.mouseRayBuildingID = 0;
        this->viewportState.mouseRayUnitID = 0;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        iVar31 = 1;
        if (1 < DAT_UnitsState::instance.maxUnitCount) {
            psVar17 = &DAT_UnitsState::instance.units[1].drawX;
            do {
                if (psVar17[60] != OpenSHC::Map::Units::ULS_INVISIBLE) {
                    *psVar17 = 0;
                    psVar17[1] = 0;
                    psVar17[2] = 0;
                    psVar17[3] = 0;
                }
                iVar31 = iVar31 + 1;
                psVar17 = psVar17 + 584;
            } while (iVar31 < DAT_UnitsState::instance.maxUnitCount);
        }
        iVar31 = 1;
        if (1 < DAT_BuildingsState::instance.maxBuildingsCount) {
            psVar17 = &DAT_BuildingsState::instance.buildings[1].surfaceAreaUnk;
            do {
                *psVar17 = 0;
                iVar31 = iVar31 + 1;
                psVar17 = psVar17 + 406;
            } while (iVar31 < DAT_BuildingsState::instance.maxBuildingsCount);
        }
        while (local_1c < iVar28
            && (MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::renderUnits, this)(),
                local_1c < viewportWidth
                    || ((DAT_TileMapState::instance.LogicLayer[this->screenPointToTileNumber[_zoomOffset + iVar2 + 8]]
                            & (Map::LogicHelpers::L_BORDER | Map::LogicHelpers::L_BORDER_EDGE))
                        == 0))) {
            _vpWidthPlus1 = _viewportHeight + 1;
            DAT_RenderMap_DrawSomeX::instance = this->viewportState.unknownScreenXRelated;
            iVar31 = _zoomOffset;
            if (_vpWidthPlus1_1 == _vpWidthPlus1) {
                DAT_RenderMap_DrawSomeX::instance = this->viewportState.unknownScreenXRelated + 16;
                _vpWidthPlus1 = _viewportHeight;
            }
            for (; iVar31 < _vpWidthPlus1; iVar31 = iVar31 + 1) {
                layerTileIndex = this->screenPointToTileNumber[iVar31 + iVar2];
                DAT_00ed3148::instance = DAT_TileMapState::instance.LogicLayer[layerTileIndex];
                if ((DAT_00ed3148::instance & 0x30) != 0) {
                    DAT_GmImageAddressToBeRendered::instance = GMFirstPictureIndex::instance[38] + 320;
                    DAT_RenderMap_YOffset::instance = 0;
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderTerrainTilesCenterPiece)();
                } else {
                    /*
                      draw every tile
                     */

                    DAT_GmImageAddressToBeRendered::instance
                        = (uint)DAT_TileMapState::instance.GfxLayer[layerTileIndex];
                    if ((iVar31 < 2) || (bVar13 = 1, _vpWidthPlus1 - 2 <= iVar31)) {
                        bVar13 = 0;
                    }
                    if (this->DAT_MapEditorDisplayLayer != 0) {
                        if (this->DAT_MapEditorDisplayLayer == 1) {
                            _displayLayerLogicalValue
                                = (uint)(short)DAT_TileMapState::instance.PathConnectionLayer[layerTileIndex];
                        } else if (this->DAT_MapEditorDisplayLayer == 2) {
                            _displayLayerLogicalValue
                                = (uint)(char)DAT_TileMapState::instance.PathLinkageLayer[layerTileIndex];
                        }
                        if (_displayLayerLogicalValue != 0) {
                            if (this->DAT_MapEditorDisplayLayer == 2) {
                                _displayLayerLogicalValue = 255 - (_displayLayerLogicalValue & 0xff);
                                if (DAT_TileMapState::instance.mapOrientation == 2) {
                                    _yOffset_01 = 6;
                                LAB_004e91cc:
                                    bVar15 = MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::rotateByteLeft,
                                        DAT_DirectionAlgorithmState::ptr)((byte)_displayLayerLogicalValue, _yOffset_01);
                                    _displayLayerLogicalValue = (uint)bVar15;
                                } else {
                                    if (DAT_TileMapState::instance.mapOrientation == 4) {
                                        _yOffset_01 = 4;
                                        goto LAB_004e91cc;
                                    }
                                    if (DAT_TileMapState::instance.mapOrientation == 6) {
                                        _yOffset_01 = 2;
                                        goto LAB_004e91cc;
                                    }
                                }
                                if (255 < (int)_displayLayerLogicalValue) {
                                    _displayLayerLogicalValue = _displayLayerLogicalValue - 256;
                                }
                                DAT_GmImageAddressToBeRendered::instance
                                    = GMFirstPictureIndex::instance[38] + 64 + _displayLayerLogicalValue;
                            } else {
                                _displayLayerLogicalValue = _displayLayerLogicalValue & 0x3f;
                                DAT_GmImageAddressToBeRendered::instance
                                    = GMFirstPictureIndex::instance[38] + _displayLayerLogicalValue;
                            }
                        }
                    }
                    _yOffset_01 = GMFirstPictureIndex::instance[157];
                    entityID = (uint)DAT_TileMapState::instance.EntityLayer[layerTileIndex];
                    iVar23 = DAT_TileMapState::instance.OrganismLayer[layerTileIndex];
                    local_2c = 0;
                    DAT_00ed3154::instance = 0;
                    if ((DAT_00ed3148::instance & 0xa0108001) != 0) {
                        if ((DAT_00ed3148::instance & 1) != 0) {
                            uVar32 = (uint)(short)DAT_TileMapState::instance.RandomLayer[layerTileIndex];
                            INT_00ed315c::instance = uVar32 & 0x7f;
                            DAT_00ed314c::instance = uVar32 & 0xf;
                            DAT_RenderMap_YOffset::instance = 0;
                            DAT_RenderMap_RowsLeft::instance = 8;
                            if ((DAT_TileMapState::instance.Logic2Layer[layerTileIndex] & 8) != 0) {
                                DAT_00ed3154::instance
                                    = -(uint)((DAT_TileMapState::instance.MiscDisplayLayer[layerTileIndex] & 0x20) != 0)
                                    & 0x5a;
                                DAT_00ed314c::instance = this->unknownCounterUntil_0x10 + DAT_00ed314c::instance;
                                if (15 < DAT_00ed314c::instance) {
                                    DAT_00ed314c::instance = DAT_00ed314c::instance - 16;
                                }
                                DAT_GmImageAddressToBeRendered::instance
                                    = DAT_TileMapState::instance.GfxLayer[layerTileIndex] + DAT_00ed314c::instance;
                            } else {
                                uVar10 = DAT_TileMapState::instance.MiscDisplayLayer[layerTileIndex];
                                if ((char)uVar10 < '\0') {
                                    DAT_GmImageAddressToBeRendered::instance
                                        = (uint)DAT_TileMapState::instance.GfxLayer[layerTileIndex]
                                        + DAT_MapRenderDefinedData::instance
                                              .field_0x4dc[(this->unknownCounterUntil_0x24 + DAT_00ed314c::instance / 2)
                                                  % 12];
                                } else if ((uVar10 & 0x40) != 0) {
                                    uVar32 = (uint)DAT_TileMapState::instance.GfxLayer[layerTileIndex];
                                    if (uVar32 == GMFirstPictureIndex::instance[166] + 1500U) {
                                        uVar29 = this->unknownCounterUntil_0x24 + INT_00ed315c::instance & 0x8000001f;
                                        if ((int)uVar29 < 0) {
                                            uVar29 = (uVar29 - 1 | 0xffffffe0) + 1;
                                        }
                                        _yOffset_01 = (int)uVar29 / 6 + ((int)uVar29 >> 0x1f);
                                        if ((int)uVar29 < 18) {
                                            DAT_GmImageAddressToBeRendered::instance
                                                = uVar32 + (_yOffset_01 - ((int)uVar29 >> 0x1f)) * -6 + uVar29;
                                        } else {
                                        LAB_004e941f:
                                            _yOffset_01 = (_yOffset_01 >> 1) - (_yOffset_01 >> 0x1f);
                                        LAB_004e9428:
                                            DAT_GmImageAddressToBeRendered::instance
                                                = *(int*)((int)DAT_MapRenderDefinedData::ptr
                                                      + (uVar29 + _yOffset_01 * -12) * 4 + 1244)
                                                + 1488 + GMFirstPictureIndex::instance[166];
                                        }
                                    } else if (uVar32 == GMFirstPictureIndex::instance[166] + 1506U) {
                                        uVar29 = this->unknownCounterUntil_0x24 + INT_00ed315c::instance & 0x8000001f;
                                        if ((int)uVar29 < 0) {
                                            uVar29 = (uVar29 - 1 | 0xffffffe0) + 1;
                                        }
                                        _yOffset_01 = (int)uVar29 / 12;
                                        if (17 < (int)uVar29)
                                            goto LAB_004e9428;
                                        DAT_GmImageAddressToBeRendered::instance = uVar32 + _yOffset_01 * -12 + uVar29;
                                    } else if (uVar32 == GMFirstPictureIndex::instance[166] + 1518U) {
                                        uVar29 = this->unknownCounterUntil_0x24 + INT_00ed315c::instance & 0x8000001f;
                                        if ((int)uVar29 < 0) {
                                            uVar29 = (uVar29 - 1 | 0xffffffe0) + 1;
                                        }
                                        if (17 < (int)uVar29) {
                                            _yOffset_01 = (int)uVar29 / 6 + ((int)uVar29 >> 0x1f);
                                            goto LAB_004e941f;
                                        }
                                        DAT_GmImageAddressToBeRendered::instance
                                            = uVar32 + ((int)uVar29 / 18) * -18 + uVar29;
                                    }
                                } else {
                                    if ((uVar10 & 0x100) != 0) {
                                        DAT_GmImageAddressToBeRendered::instance
                                            = (uint)DAT_TileMapState::instance.GfxLayer[layerTileIndex]
                                            + DAT_MapRenderDefinedData::instance
                                                    .field_0x6a4[this->unknownCounterUntil_0x20]
                                                * 34;
                                    } else {
                                        if ((uVar10 & 0x200) == 0) {
                                            DAT_00ed314c::instance = uVar32 & 7;
                                            piVar21 = this->landscapeSeaWhiteCapsAnimationFrames;
                                            _yOffset_01 = 9;
                                            do {
                                                if (layerTileIndex == piVar21[-60]) {
                                                    local_2c = *piVar21 + 1 + (uVar32 & 3) * 8;
                                                }
                                                if (layerTileIndex == piVar21[-59]) {
                                                    local_2c = piVar21[1] + 1 + (uVar32 & 3) * 8;
                                                }
                                                if (layerTileIndex == piVar21[-58]) {
                                                    local_2c = piVar21[2] + 1 + (uVar32 & 3) * 8;
                                                }
                                                if (layerTileIndex == piVar21[-57]) {
                                                    local_2c = piVar21[3] + 1 + (uVar32 & 3) * 8;
                                                }
                                                if (layerTileIndex == piVar21[-56]) {
                                                    local_2c = piVar21[4] + 1 + (uVar32 & 3) * 8;
                                                }
                                                piVar21 = piVar21 + 5;
                                                _yOffset_01 = _yOffset_01 - 1;
                                            } while (_yOffset_01 != 0);
                                        }
                                    }
                                }
                            }
                            MACRO_CALL_MEMBER(
                                OpenSHC::Audio::SFX::SFXState_Func::notifyAmbientSoundEvent, DAT_SFXState::ptr)(2);
                            _yOffset_01 = GMFirstPictureIndex::instance[157];
                        } else if ((DAT_00ed3148::instance & 0x100000) != 0) {
                            DAT_RenderMap_RowsLeft::instance
                                = (uint)DAT_TileMapState::instance.ShowHiLayer[layerTileIndex];
                            DAT_RenderMap_YOffset::instance
                                = DAT_TileMapState::instance
                                      .heightBasedScreenYOffset[DAT_TileMapState::instance.HeightLayer[layerTileIndex]];
                            bVar15 = DAT_TileMapState::instance.Logic2Layer[layerTileIndex];
                            if ((bVar15 & 200) != 0) {
                                DAT_00ed3154::instance
                                    = -(uint)((DAT_TileMapState::instance.MiscDisplayLayer[layerTileIndex] & 0x20) != 0)
                                    & 0x5a;
                                DAT_00ed314c::instance = (uint)DAT_TileMapState::instance.WallGFXLayer[layerTileIndex]
                                    + this->unknownCounterUntil_0x10;
                                uVar32 = DAT_00ed314c::instance & 0x8000000f;
                                if ((int)uVar32 < 0) {
                                    uVar32 = (uVar32 - 1 | 0xfffffff0) + 1;
                                }
                                DAT_GmImageAddressToBeRendered::instance
                                    = uVar32 + DAT_TileMapState::instance.GfxLayer[layerTileIndex];
                            } else {
                                if ((bVar15 & 7) != 0) {
                                    bVar15 = (byte)DAT_TileMapState::instance.MiscDisplayLayer[layerTileIndex];
                                    DAT_00ed314c::instance
                                        = (uint)DAT_TileMapState::instance.WallGFXLayer[layerTileIndex]
                                        + this->unknownCounterUntil_0x10 / 2;
                                    uVar32 = DAT_00ed314c::instance & 0x80000007;
                                    if ((int)uVar32 < 0) {
                                        uVar32 = (uVar32 - 1 | 0xfffffff8) + 1;
                                    }
                                    DAT_GmImageAddressToBeRendered::instance
                                        = uVar32 + DAT_TileMapState::instance.GfxLayer[layerTileIndex];
                                LAB_004e96a7:
                                    DAT_00ed3154::instance = -(uint)((bVar15 & 0x20) != 0) & 0x5a;
                                } else {
                                    if ((bVar15 & 0x10) != 0) {
                                        DAT_00ed3154::instance
                                            = -(uint)((DAT_TileMapState::instance.MiscDisplayLayer[layerTileIndex]
                                                          & 0x20)
                                                  != 0)
                                            & 0x5a;
                                        DAT_00ed314c::instance
                                            = (uint)DAT_TileMapState::instance.WallGFXLayer[layerTileIndex]
                                            + this->unknownCounterUntil_0x10;
                                        uVar32 = DAT_00ed314c::instance & 0x8000000f;
                                        if ((int)uVar32 < 0) {
                                            uVar32 = (uVar32 - 1 | 0xfffffff0) + 1;
                                        }
                                        DAT_GmImageAddressToBeRendered::instance
                                            = uVar32 + DAT_TileMapState::instance.GfxLayer[layerTileIndex];
                                    } else {
                                        if ((bVar15 & 0x20) != 0) {
                                            bVar15 = (byte)DAT_TileMapState::instance.MiscDisplayLayer[layerTileIndex];
                                            DAT_00ed314c::instance
                                                = (uint)(DAT_TileMapState::instance.WallGFXLayer[layerTileIndex] >> 10)
                                                + this->unknownCounterUntil_0x10 / 2;
                                            uVar32 = DAT_00ed314c::instance & 0x80000007;
                                            if ((int)uVar32 < 0) {
                                                uVar32 = (uVar32 - 1 | 0xfffffff8) + 1;
                                            }
                                            DAT_GmImageAddressToBeRendered::instance
                                                = uVar32 + DAT_TileMapState::instance.GfxLayer[layerTileIndex];
                                            goto LAB_004e96a7;
                                        }
                                    }
                                }
                            }
                            MACRO_CALL_MEMBER(
                                OpenSHC::Audio::SFX::SFXState_Func::notifyAmbientSoundEvent, DAT_SFXState::ptr)(7);
                            _yOffset_01 = GMFirstPictureIndex::instance[157];
                        } else if (DAT_00ed3148::instance == 0xa0008000) {
                            DAT_RenderMap_YOffset::instance
                                = DAT_TileMapState::instance
                                      .heightBasedScreenYOffset[DAT_TileMapState::instance.HeightLayer[layerTileIndex]];
                            DAT_RenderMap_RowsLeft::instance
                                = (uint)DAT_TileMapState::instance.ShowHiLayer[layerTileIndex];
                            bVar15 = (byte)DAT_TileMapState::instance.RandomLayer[layerTileIndex];
                            bVar19 = bVar15 & 7;
                            if (this->field_0x18b764 != 0) {
                                DAT_TileMapState::instance.WallGFXLayer[layerTileIndex]
                                    = DAT_TileMapState::instance.WallGFXLayer[layerTileIndex] + 1;
                            }
                            DAT_00ed314c::instance = (uint)DAT_TileMapState::instance.WallGFXLayer[layerTileIndex];
                            if ((bVar15 & 7) != 0) {
                                if (bVar19 == 1) {
                                    if (510 < DAT_00ed314c::instance) {
                                        DAT_TileMapState::instance.WallGFXLayer[layerTileIndex] = 0;
                                        DAT_00ed314c::instance = 0;
                                    }
                                    bVar15 = DAT_MapRenderDefinedData::instance.field_0x924[DAT_00ed314c::instance];
                                } else {
                                    if ((bVar19 != 4) && (bVar19 != 5)) {
                                        if (126 < DAT_00ed314c::instance) {
                                            DAT_TileMapState::instance.WallGFXLayer[layerTileIndex] = 0;
                                            DAT_00ed314c::instance = 0;
                                        }
                                        DAT_GmImageAddressToBeRendered::instance
                                            = (int)(char)
                                                  DAT_MapRenderDefinedData::instance.field_0xb24[DAT_00ed314c::instance]
                                            + (uint)DAT_TileMapState::instance.GfxLayer[layerTileIndex];
                                        goto LAB_004e9845;
                                    }
                                    if (254 < DAT_00ed314c::instance) {
                                        DAT_TileMapState::instance.WallGFXLayer[layerTileIndex] = 0;
                                        DAT_00ed314c::instance = 0;
                                    }
                                    bVar15 = DAT_MapRenderDefinedData::instance.field_0xb24[DAT_00ed314c::instance];
                                }
                                DAT_GmImageAddressToBeRendered::instance
                                    = (int)(char)bVar15 + (uint)DAT_TileMapState::instance.GfxLayer[layerTileIndex];
                            } else {
                                if (511 < DAT_00ed314c::instance) {
                                    DAT_TileMapState::instance.WallGFXLayer[layerTileIndex] = 0;
                                    DAT_00ed314c::instance = 0;
                                }
                                DAT_GmImageAddressToBeRendered::instance
                                    = (int)(char)DAT_MapRenderDefinedData::instance.field_0x724[DAT_00ed314c::instance]
                                    + (uint)DAT_TileMapState::instance.GfxLayer[layerTileIndex];
                            }
                        } else {
                            uVar32 = (uint)DAT_TileMapState::instance.HeightLayer[layerTileIndex];
                            if ((DAT_00ed3148::instance & 0x200) != 0
                                && (DAT_TileMapState::instance.MiscDisplayLayer[layerTileIndex] & 0x3c0) != 0) {
                                uVar32 = uVar32 - 8;
                            }
                            DAT_RenderMap_YOffset::instance
                                = DAT_TileMapState::instance.heightBasedScreenYOffset[uVar32];
                            if ((DAT_TileMapState::instance.MiscDisplayLayer[layerTileIndex] & 0x20) == 0
                                || DAT_TileMapState::instance.disableElevationRendering != 0) {
                                DAT_00ed3154::instance = 0;
                            } else {
                                DAT_00ed3154::instance = 90;
                            }
                            DAT_RenderMap_RowsLeft::instance
                                = (uint)DAT_TileMapState::instance.ShowHiLayer[layerTileIndex];
                        }
                    } else {
                        uVar32 = (uint)DAT_TileMapState::instance.HeightLayer[layerTileIndex];
                        if ((DAT_00ed3148::instance & 0x200) != 0
                            && (DAT_TileMapState::instance.MiscDisplayLayer[layerTileIndex] & 0x3c0) != 0) {
                            uVar32 = uVar32 - 8;
                        }
                        DAT_RenderMap_YOffset::instance = DAT_TileMapState::instance.heightBasedScreenYOffset[uVar32];
                        if ((DAT_TileMapState::instance.MiscDisplayLayer[layerTileIndex] & 0x20) == 0
                            || DAT_TileMapState::instance.disableElevationRendering != 0) {
                            DAT_00ed3154::instance = 0;
                        } else {
                            DAT_00ed3154::instance = 90;
                        }
                        DAT_RenderMap_RowsLeft::instance = (uint)DAT_TileMapState::instance.ShowHiLayer[layerTileIndex];
                    }
                LAB_004e9845:
                    local_54 = (uint)DAT_TileMapState::instance.BuildingLayer[layerTileIndex];
                    if (_flatView != 0) {
                        DAT_RenderMap_YOffset::instance = 8;
                        if (this->DAT_MapEditorDisplayLayer == 0) {
                            uVar32 = (uint)(short)DAT_TileMapState::instance.RandomLayer[layerTileIndex];
                            DAT_00ed314c::instance = uVar32 & 0xf;
                            DAT_RenderMap_RowsLeft::instance = 0;
                            DAT_00ed3154::instance = 0;
                            if (local_54 == 0 || (DAT_00ed3148::instance & 0x40000000) != 0) {
                                if ((DAT_00ed3148::instance & 0x100) == 0) {
                                    if ((DAT_00ed3148::instance & 0x80) != 0) {
                                        _yOffset_01 = DAT_TileMapState::instance.OrganismLayer[layerTileIndex];
                                        if (_yOffset_01 < 2000) {
                                            _yOffset_01 = MACRO_CALL_MEMBER(
                                                OpenSHC::Map::LandscapeState_Func::getRandomRockImageOffset,
                                                DAT_LandscapeState::ptr)((uVar32 & 3) + 1);
                                            DAT_GmImageAddressToBeRendered::instance
                                                = _yOffset_01 - 1 + GMFirstPictureIndex::instance[56];
                                        } else {
                                            _yOffset_01 = _yOffset_01 * 32;
                                            if (1 < *(short*)((int)&DAT_LandscapeState::instance.trees[1590]
                                                                  .appleTreeColorVariation
                                                    + _yOffset_01 + 2)) {
                                                iVar26 = MACRO_CALL_MEMBER(
                                                    OpenSHC::Map::LandscapeState_Func::getRandomRockImageOffset,
                                                    DAT_LandscapeState::ptr)((uVar32 & 3) + 1);
                                                DAT_GmImageAddressToBeRendered::instance = iVar26 - 1
                                                    + GMFirstPictureIndex::instance[*(
                                                        short*)((int)&DAT_LandscapeState::instance.trees[1590]
                                                                    .animationFrameUnk
                                                        + _yOffset_01 + 2)];
                                            }
                                        }
                                    }
                                } else if ((DAT_00ed3148::instance & 0x800) != 0) {
                                    DAT_00ed3148::instance = DAT_00ed3148::instance & 1;
                                    if ((DAT_GmImageAddressToBeRendered::instance
                                            == GMFirstPictureIndex::instance[12] + 134U)
                                        || (DAT_GmImageAddressToBeRendered::instance
                                            == GMFirstPictureIndex::instance[12] + 136U)) {
                                        DAT_GmImageAddressToBeRendered::instance = _yOffset_01 + 42;
                                    } else {
                                        DAT_GmImageAddressToBeRendered::instance = _yOffset_01 + 40;
                                    }
                                } else {
                                    if ((DAT_00ed3148::instance & 0x200) != 0) {
                                        DAT_00ed3148::instance = DAT_00ed3148::instance & 1;
                                        if (DAT_TileMapState::instance.DamageLayer[layerTileIndex] == 0) {
                                            DAT_GmImageAddressToBeRendered::instance = (uVar32 & 3) + 36 + _yOffset_01;
                                        } else {
                                            DAT_GmImageAddressToBeRendered::instance = (uVar32 & 1) + 44 + _yOffset_01;
                                        }
                                    } else {
                                        if (DAT_TileMapState::instance.DamageLayer[layerTileIndex] != 0) {
                                            DAT_00ed3148::instance = DAT_00ed3148::instance & 1;
                                            DAT_GmImageAddressToBeRendered::instance = (uVar32 & 1) + 44 + _yOffset_01;
                                        }
                                    }
                                }
                            } else {
                                BVar8 = DAT_BuildingsState::instance.buildings[local_54].buildingType;
                                iVar26 = DAT_MapRenderDefinedData::instance.BuildingRenderSomeTypeArray[(short)BVar8];
                                if (iVar26 == 3) {
                                    uVar32 = (uint)((DAT_TileMapState::instance.MiscDisplayLayer[layerTileIndex] & 4)
                                        != 0);
                                    if (BVar8 == OpenSHC::Map::Buildings::BT_WOODCUTTERSHUT) {
                                        DAT_GmImageAddressToBeRendered::instance = _yOffset_01 + 24 + uVar32;
                                    } else if (BVar8 == OpenSHC::Map::Buildings::BT_HUNTERSHUT) {
                                        DAT_GmImageAddressToBeRendered::instance = _yOffset_01 + 26 + uVar32;
                                    } else if (BVar8 == OpenSHC::Map::Buildings::BT_DAIRYFARM) {
                                        DAT_GmImageAddressToBeRendered::instance = _yOffset_01 + 28 + uVar32;
                                    } else {
                                        DAT_GmImageAddressToBeRendered::instance = _yOffset_01 + 30 + uVar32;
                                    }
                                } else if (-1 < iVar26) {
                                    DAT_GmImageAddressToBeRendered::instance
                                        = (uVar32 & 3) + _yOffset_01 + ((local_54 & 1) + iVar26 * 2) * 4;
                                }
                            }
                        } else {
                            DAT_RenderMap_RowsLeft::instance = 0;
                            DAT_00ed3154::instance = 0;
                        }
                    }
                    DAT_RenderMap_ImageID::instance
                        = (uint)DAT_TileMapState::instance.ConstructionGFXLayer[layerTileIndex];
                    bVar12 = 0;
                    bVar14 = 0;
                    if (DAT_RenderMap_ImageID::instance == 0) {
                        if ((DAT_00ed3148::instance & 0x4000) != 0 && DAT_TileMapState::instance.field_0x5549b8 != 0
                            && (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                                || (_yOffset_01
                                    = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile,
                                        DAT_TileMapState::ptr)(layerTileIndex),
                                    DAT_GameState::instance.mapAndTime
                                            .playerTeams[DAT_TileMapState::instance.moats[_yOffset_01].owner]
                                        == DAT_GameState::instance.mapAndTime
                                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]))) {
                            DAT_RenderMap_ImageID::instance = 57;
                            goto LAB_004e9b3c;
                        }
                    } else if (DAT_TileMapState::instance.buildingPlacementFail == FALSE
                        || (DAT_TileMapState::instance.MiscDisplayLayer[layerTileIndex] & 0x8000) != 0) {
                        DAT_GmImageAddressToBeRendered::instance = DAT_RenderMap_ImageID::instance;
                        if ((DAT_00ed3148::instance & 0x100) != 0 && _flatView == 0) {
                            DAT_RenderMap_YOffset::instance
                                = DAT_TileMapState::instance.heightBasedScreenYOffset[DAT_TileMapState::instance
                                        .DefaultHeightLayer[layerTileIndex]];
                        }
                    } else {
                    LAB_004e9b3c:
                        bVar12 = 1;
                        bVar14 = 1;
                    }
                    unitID = (int)(short)DAT_TileMapState::instance.UnitLayer[layerTileIndex];
                    if (unitID != 0 && unitID == DAT_UnitsState::instance.lastSelectedUnitID
                        && DAT_MenuModalComposition1::instance.activeModalDialogID
                            == OpenSHC::UI::Enums::MMT_DEBUG_DATA_UNIT_DATA) {
                        DAT_GmImageAddressToBeRendered::instance
                            = ((byte)DAT_UnitsState::instance.units[unitID].moveDelay & 0x3f)
                            + GMFirstPictureIndex::instance[38];
                    }
                    if ((DAT_00ed3148::instance & 8) != 0
                        && (DAT_TileMapState::instance.MiscDisplayLayer[layerTileIndex] & 0x2000) == 0
                        && _flatView == 0) {
                        DAT_RenderMap_YOffset::instance
                            = DAT_TileMapState::instance
                                  .heightBasedScreenYOffset[DAT_TileMapState::instance.HeightLayer[layerTileIndex] + 4];
                    }
                    if (local_54 != 0) {
                        uVar9 = *this->viewportState.ptrColor;
                        *this->viewportState.ptrColor = COL_MAGENTA::instance.shortValue;
                    }
                    if (DAT_RenderMap_RowsLeft::instance != 0xff && bVar13 != 0
                        && (MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderTerrainTilesCenterPiece)(), bVar12 != 0)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS,
                            DAT_RenderMap_ImageID::instance, DAT_RenderMap_DrawSomeX::instance,
                            (DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance)
                                + DAT_RenderMap_DrawSomeY::instance,
                            24);
                    }
                    if (DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance].direction != 0
                        && local_54 == 0 && bVar13 != 0 && bVar12 == 0) {
                        _yOffset_01 = (int)DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance]
                                          .tileOffset;
                        /*
                          renders preview of selected object
                         */

                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderFunctionResponsibleForManyGameObjects,
                            DAT_TextureRenderCoreObject::ptr)(
                            (char)DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance]
                                    .horizontalOffsetImage
                                + DAT_RenderMap_DrawSomeX::instance,
                            (int)(((DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance) - _yOffset_01)
                                + DAT_RenderMap_DrawSomeY::instance),
                            (int)((char)DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance]
                                    .buildingWidth),
                            _yOffset_01 + 7,
                            (ushort*)((int)(

                                (DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance] + 512
                                    + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))));
                    }
                    if (local_2c != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ANIM_WHITECAPS, local_2c,
                            (DAT_RenderMap_DrawSomeX::instance
                                - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[173].originX)
                                + 15,
                            (DAT_RenderMap_DrawSomeY::instance
                                - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[173].originY)
                                + 7);
                    }
                    if (local_54 != 0) {
                        if (*this->viewportState.ptrColor == COL_MAGENTA::instance.shortValue) {
                            *this->viewportState.ptrColor = uVar9;
                        } else {
                            this->viewportState.mouseRayUnitID = 0;
                            this->viewportState.mouseRayBuildingID = local_54;
                        }
                    }
                    if ((DAT_00ed3148::instance & 0x201) == 0 && local_54 == 0) {
                        uVar10 = DAT_TileMapState::instance.MiscDisplayLayer[layerTileIndex];
                        if ((uVar10 & 0x3c0) != 0
                            && (DAT_RenderMap_ImageID::instance == 0
                                || (((DAT_00ed3148::instance & 0x4000) != 0
                                    && (DAT_TileMapState::instance.field_0x5549b8 != 0))))
                            && (DAT_00ed3148::instance & 0x30) == 0 && _flatView == 0) {
                            uVar32 = (uint)DAT_TileMapState::instance.WallGFXLayer[layerTileIndex];
                            DAT_GmImageAddressToBeRendered::instance
                                = (uint)DAT_TileMapState::instance.AlphaGFXLayer[layerTileIndex];
                            iVar26 = uVar32 - DAT_TileMapState::instance.heightBasedScreenYOffset[uVar32];
                            _yOffset_01 = DAT_RenderMap_DrawSomeX::instance;
                            if ((uVar10 & 0x40) != 0) {
                                iVar26 = (iVar26 - uVar32) + DAT_00ed3154::instance + 7;
                            } else {
                                if ((char)uVar10 < '\0') {
                                    _yOffset_01 = (int)DAT_GMImageHeaders::instance
                                                      .imh[DAT_GmImageAddressToBeRendered::instance
                                                          + GMFirstPictureIndex::instance[54] - 1]
                                                      .height;
                                    /*
                                      renders wall connections
                                     */

                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                          renderFunctionResponsibleForManyGameObjects,
                                        DAT_TextureRenderCoreObject::ptr)(DAT_RenderMap_DrawSomeX::instance,
                                        (int)(((iVar26 - uVar32) - _yOffset_01) + DAT_00ed3154::instance + 98
                                            + DAT_RenderMap_DrawSomeY::instance),
                                        DAT_GMImageHeaders::instance
                                            .imh[DAT_GmImageAddressToBeRendered::instance
                                                + GMFirstPictureIndex::instance[54] - 1]
                                            .width,
                                        _yOffset_01 - iVar26,
                                        (ushort*)((int)(

                                            (DAT_GMImageOffsets::instance[GMFirstPictureIndex::instance[54] - 1
                                                 + DAT_GmImageAddressToBeRendered::instance]
                                                + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))));
                                    goto LAB_004e9e36;
                                }
                                if ((uVar10 & 0x100) != 0) {
                                    iVar26 = (iVar26 - uVar32) + DAT_00ed3154::instance;
                                    _yOffset_01 = DAT_RenderMap_DrawSomeX::instance + 16;
                                } else {
                                    if ((uVar10 & 0x200) == 0)
                                        goto LAB_004e9e36;
                                    iVar26 = (iVar26 - uVar32) + DAT_00ed3154::instance - 1;
                                }
                            }
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS,
                                DAT_GmImageAddressToBeRendered::instance, _yOffset_01,
                                (int)(iVar26 + DAT_RenderMap_DrawSomeY::instance));
                        }
                    }
                LAB_004e9e36:
                    _yOffset_01 = DAT_RenderMap_YOffset::instance;
                    uVar32 = (uint)DAT_TileMapState::instance.FloatingLayer[layerTileIndex];
                    if (uVar32 != 0) {
                        if ((DAT_TileMapState::instance.refreshRelatedOne != 0) && (_flatView == 0)) {
                            if ((DAT_TileMapState::instance.LogicLayer[layerTileIndex]
                                    & Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE)
                                != 0) {
                                local_54 = (uint)DAT_TileMapState::instance.BuildingLayer[layerTileIndex];
                                iVar26 = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                    DAT_BuildingsState::ptr)(local_54);
                                _yOffset_01 = _yOffset_01 + iVar26;
                            } else {
                                if ((DAT_TileMapState::instance.LogicLayer[layerTileIndex]
                                        & Map::LogicHelpers::L_WALL_OR_GATEHOUSE)
                                    != 0) {
                                    local_54 = (uint)DAT_TileMapState::instance.BuildingLayer[layerTileIndex];
                                    if (local_54 == 0) {
                                        _yOffset_01 = DAT_RenderMap_YOffset::instance + 4;
                                    } else if (DAT_BuildingsState::instance.buildings[local_54].buildingType
                                        == OpenSHC::Map::Buildings::BT_WOODGATE1) {
                                        _yOffset_01 = DAT_RenderMap_YOffset::instance + 6;
                                    } else {
                                        _yOffset_01 = DAT_RenderMap_YOffset::instance + 20;
                                    }
                                }
                            }
                        }
                        do {
                            uVar29 = this->floatersArray[uVar32].variation;
                            if ((uVar29 & 2) != 0) {
                                if ((DAT_TileMapState::instance.MiscDisplayLayer[layerTileIndex] & 0x10) != 0) {
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::Rendering::ViewportRenderState_Func::scheduleUnitForBatchedRendering,
                                        this)(0,
                                        this->floatersArray[uVar32].originX + DAT_RenderMap_DrawSomeX::instance,
                                        (this->floatersArray[uVar32].originY - _yOffset_01)
                                            + DAT_RenderMap_DrawSomeY::instance,
                                        (undefined4)(this->floatersArray[uVar32].imageID), (undefined4)((int)(uVar29)),
                                        (undefined4)((int)(this->floatersArray[uVar32].gmID)), 0);
                                } else {
                                    if ((uVar29 & 4) != 0) {
                                        DAT_RenderedUnitOwner::instance = ~-(uint)((uVar29 & 0x10) != 0)
                                            & DAT_GameSynchronyState::instance.currentPlayerSlotID;
                                        DAT_CurrentlyRenderedSpriteID::instance = this->floatersArray[uVar32].gmID;
                                        uVar29 = this->floatersArray[uVar32].variation;
                                    }
                                    if ((uVar29 & 0x20) != 0) {
                                        iVar26 = this->floatersArray[uVar32].imageID;
                                        GVar11 = (GmID)this->floatersArray[uVar32].gmID;
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                            DAT_TextureRenderCoreObject::ptr)((GmID)GVar11, iVar26,
                                            this->floatersArray[uVar32].originX + DAT_RenderMap_DrawSomeX::instance,
                                            (int)((this->floatersArray[uVar32].originY - _yOffset_01)
                                                + DAT_RenderMap_DrawSomeY::instance),
                                            GVar11, ((int)uVar29 >> 0x10) + iVar26, 0);
                                    } else {
                                        if ((uVar29 & 0xffff0000) != 0) {
                                            MACRO_CALL_MEMBER(
                                                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                                DAT_TextureRenderCoreObject::ptr)(
                                                (GmID)this->floatersArray[uVar32].gmID,
                                                this->floatersArray[uVar32].imageID,
                                                this->floatersArray[uVar32].originX + DAT_RenderMap_DrawSomeX::instance,
                                                (int)((this->floatersArray[uVar32].originY - _yOffset_01)
                                                    + DAT_RenderMap_DrawSomeY::instance),
                                                (int)(uVar29 >> 0x10));
                                        } else {
                                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                DAT_TextureRenderCoreObject::ptr)((eGM)this->floatersArray[uVar32].gmID,
                                                this->floatersArray[uVar32].imageID,
                                                this->floatersArray[uVar32].originX + DAT_RenderMap_DrawSomeX::instance,
                                                (int)((this->floatersArray[uVar32].originY - _yOffset_01)
                                                    + DAT_RenderMap_DrawSomeY::instance));
                                        }
                                    }
                                }
                            }
                            uVar32 = this->floatersArray[uVar32].id;
                        } while (uVar32 != 0);
                    }
                    _yOffset_01 = 0;
                    if (entityID != 0) {
                        while ((iVar26 = DAT_RenderMap_YOffset::instance, _yOffset_01 = _yOffset_01 + 1,
                            _yOffset_01 < 10 && (DAT_EntityState::instance.entityArray[entityID].logicalState != 0))) {
                            if (DAT_EntityState::instance.entityArray[entityID].graphicType2 != 0
                                && ((EVar3 = DAT_EntityState::instance.entityArray[entityID].entityType,
                                        EVar3 == OpenSHC::Map::Entities::EntityTypeInt__ET_CROW
                                            || (EVar3 == OpenSHC::Map::Entities::ET_SEAGULLUnk))
                                    || (EVar3 == OpenSHC::Map::Entities::ET_COW_FLYING))
                                && DAT_EntityState::instance.entityArray[entityID].imageID != 0) {
                                DAT_RenderedUnitOwner::instance
                                    = DAT_EntityState::instance.entityArray[entityID].colorUnk;
                                DAT_CurrentlyRenderedSpriteID::instance
                                    = (GmIDInt)DAT_EntityState::instance.entityArray[entityID].gmID;
                                if ((DAT_TileMapState::instance.LogicLayer[layerTileIndex]
                                        & Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE)
                                    != 0) {
                                    local_54 = (uint)DAT_TileMapState::instance.BuildingLayer[layerTileIndex];
                                    iVar18 = MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                        DAT_BuildingsState::ptr)(local_54);
                                    iVar26 = iVar26 + iVar18;
                                } else {
                                    if ((DAT_TileMapState::instance.LogicLayer[layerTileIndex]
                                            & Map::LogicHelpers::L_WALL_OR_GATEHOUSE)
                                        != 0) {
                                        local_54 = (uint)DAT_TileMapState::instance.BuildingLayer[layerTileIndex];
                                        if (local_54 == 0) {
                                            iVar26 = DAT_RenderMap_YOffset::instance + 4;
                                        } else {
                                            iVar26 = DAT_RenderMap_YOffset::instance + 20;
                                        }
                                    }
                                }
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Rendering::ViewportRenderState_Func::scheduleUnitForBatchedRendering,
                                    this)(4294967295,
                                    (DAT_EntityState::instance.entityArray[entityID].x1
                                        - DAT_EntityState::instance.entityArray[entityID].originX)
                                        + DAT_RenderMap_DrawSomeX::instance,
                                    ((DAT_EntityState::instance.entityArray[entityID].y1
                                         - DAT_EntityState::instance.entityArray[entityID].originY)
                                        - iVar26)
                                        + DAT_RenderMap_DrawSomeY::instance,
                                    (undefined4)(DAT_EntityState::instance.entityArray[entityID].imageID), 20, 0, 0);
                            }
                            iVar26 = DAT_EntityState::instance.entityArray[entityID].nextEntityOnThisTileByID;
                            if (entityID == iVar26 || DAT_GameSynchronyState::instance.syncStatus != 0
                                || (entityID = iVar26, iVar26 == 0))
                                break;
                        }
                    }
                    entityID = (uint)DAT_TileMapState::instance.EntityLayer[layerTileIndex];
                    if (local_54 != 0
                        && DAT_BuildingsState::instance.buildings[local_54].buildingType
                            == OpenSHC::Map::Buildings::BT_DRAWBRIDGE
                        && _flatView == 0 && DAT_TileMapState::instance.refreshRelatedOne != 0
                        && (DAT_TileMapState::instance.MiscDisplayLayer[layerTileIndex] & 0xc) == 4) {
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::renderGmOverlayBuilding2, this)(
                            local_54, DAT_RenderMap_DrawSomeX::instance,
                            DAT_00ed3154::instance + DAT_RenderMap_DrawSomeY::instance, layerTileIndex);
                    }
                    /*
                      ------ BEGIN RENDER UNITS ------
                     */

                    if ((unitID != 0)
                        && (MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::UnitsState_Func::triggerDesyncIfTileUnitLinkageInvalid,
                                DAT_UnitsState::ptr)(layerTileIndex),
                            0 < unitID)) {
                        while (_yOffset_01 = DAT_RenderMap_DrawSomeX::instance,
                            DAT_UnitsState::instance.units[unitID].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE) {
                            DAT_CurrentlyRenderedSpriteID::instance
                                = (GmIDInt)DAT_UnitsState::instance.units[unitID].spriteID;
                            local_2c = 0;
                            if ((DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_A_ASSASSIN)
                                && (DAT_GameState::instance.mapAndTime
                                        .playerTeams[DAT_UnitsState::instance.units[unitID].owner]
                                    != DAT_GameState::instance.mapAndTime
                                        .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID])) {
                                iVar26 = DAT_UnitsState::instance.units[unitID].assassinsMicroDistanceToEnemyUnk;
                                if (iVar26 <= 160
                                    || (UVar4 = DAT_UnitsState::instance.units[unitID].state.generic,
                                        UVar4 == OpenSHC::Map::Units::States::US_MELEE_ATTACK
                                            || (UVar4 == OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL))) {
                                    if (120 < iVar26
                                        && (DAT_GameSynchronyState::instance.currentGameMode
                                                != OpenSHC::Game::GM_SOLITARY
                                            || (DAT_UnitsState::instance.units[unitID].idleCounterUnk < 2401))) {
                                        local_2c = 16;
                                    }
                                    goto LAB_004ea2c6;
                                }
                                if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                                    && (2400 < DAT_UnitsState::instance.units[unitID].idleCounterUnk))
                                    goto LAB_004ea2c6;
                            } else {
                            LAB_004ea2c6:
                                if (DAT_UnitsState::instance.units[unitID].field_0x5a == 0) {
                                    DAT_RenderedUnitOwner::instance
                                        = DAT_UnitsState::instance.units[unitID].calculatedOwnerPlayerIndex;
                                } else {
                                    DAT_RenderedUnitOwner::instance = 9;
                                }
                                iVar18 = GMFirstPictureIndex::instance[DAT_CurrentlyRenderedSpriteID::instance];
                                iVar27 = DAT_UnitsState::instance.units[unitID].gfxNumber;
                                iVar26 = iVar27 - 1 + iVar18;
                                iVar25 = DAT_RenderMap_YOffset::instance;
                                if (DAT_TileMapState::instance.refreshRelatedOne != 0) {
                                    if (_flatView != 0) {
                                        iVar25 = ((int)(char)DAT_UnitsState::instance.units[unitID].negativeHeight
                                                     - DAT_UnitsState::instance.units[unitID].buildingHeight)
                                            + DAT_RenderMap_YOffset::instance;
                                    } else {
                                        iVar25 = (uint)(byte)DAT_UnitsState::instance.units[unitID].field_0x83
                                            + DAT_UnitsState::instance.units[unitID].terrainOrClimbHeight;
                                    }
                                }
                                sVar30 = DAT_UnitsState::instance.units[unitID].orientationRelatedPositionX;
                                sVar20 = DAT_UnitsState::instance.units[unitID].orientationRelatedPositionY;
                                DAT_UnitsState::instance.units[unitID].field_0x41c
                                    = sVar30 - 6 + DAT_RenderMap_DrawSomeX::instance;
                                sVar30 = ((short)DAT_UnitsState::instance.units[unitID].field_0x5c
                                             - DAT_UnitsState::instance.units[unitID].field_0x2a)
                                    + (short)_yOffset_01 + sVar30;
                                bVar15 = DAT_UnitsState::instance.units[unitID].negativeHeight;
                                DAT_UnitsState::instance.units[unitID].field_0x420
                                    = (sVar20 - iVar25) - 12 + DAT_RenderMap_DrawSomeY::instance;
                                sVar24 = (short)DAT_UnitsState::instance.units[unitID].unknownV;
                                sVar5 = DAT_UnitsState::instance.units[unitID].field_0x84;
                                sVar6 = DAT_UnitsState::instance.units[unitID].buildingHeight;
                                DAT_UnitsState::instance.units[unitID].drawX = sVar30;
                                sVar20 = (((sVar5 - sVar6) - (short)iVar25) - sVar24)
                                    + (short)DAT_RenderMap_DrawSomeY::instance + (short)(char)bVar15 + sVar20;
                                sVar5 = DAT_GMImageHeaders::instance.imh[iVar18 + iVar27 - 1].width;
                                DAT_UnitsState::instance.units[unitID].drawY = sVar20;
                                DAT_UnitsState::instance.units[unitID].drawWidth = sVar5;
                                if (bVar15 == 0) {
                                    sVar24 = DAT_GMImageHeaders::instance.imh[iVar18 + iVar27 - 1].height;
                                } else {
                                    sVar24 = (sVar24 - (char)bVar15) + 8;
                                }
                                _yOffset_01 = DAT_UnitsState::instance.units[unitID].vanish;
                                DAT_UnitsState::instance.units[unitID].drawHeight1 = sVar24;
                                if (_yOffset_01 == 0) {
                                    _yOffset_01 = DAT_UnitsState::instance.units[unitID].field_0x64;
                                    if (_yOffset_01 == 1) {
                                    LAB_004ea49b:
                                        _yOffset_01 = 1;
                                    } else if (_yOffset_01 == 2) {
                                        _yOffset_01 = 0;
                                    } else {
                                        if ((DAT_TileMapState::instance.MiscDisplayLayer[layerTileIndex] & 0x10) == 0
                                            || DAT_UnitsState::instance.units[unitID].field_0x64 == -1) {
                                            if ((DAT_00ed3148::instance & 0x400) == 0) {
                                                if ((DAT_UnitsState::instance.units[unitID].unitType
                                                        == OpenSHC::Map::Units::UT_A_ASSASSIN)
                                                    && (_yOffset_01 = DAT_UnitsState::instance.units[unitID].imageID2,
                                                        _yOffset_01 != 0)) {
                                                    sVar24 = DAT_UnitsState::instance.units[unitID].field_0x86;
                                                    if (sVar24 < 0) {
                                                        local_c = 0;
                                                    } else {
                                                        local_c = (uint)sVar24;
                                                    }
                                                    iVar27 = (32 - local_2c) / 3;
                                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                          renderUnitAnimationWithBlendingUnk,
                                                        DAT_TextureRenderCoreObject::ptr)(sVar30,
                                                        DAT_UnitsState::instance.units[unitID].field_0x86 + sVar20,
                                                        sVar5,
                                                        (int)(DAT_UnitsState::instance.units[unitID].drawHeight1
                                                            - local_c),
                                                        (byte*)((
                                                            int)((DAT_GMImageOffsets::instance[_yOffset_01 - 1 + iVar18]
                                                            + (int)DAT_TextureRenderCoreObject::instance
                                                                .gmProcessedImageData))),
                                                        (16 - iVar27) * 2);
                                                    sVar30 = DAT_UnitsState::instance.units[unitID].drawYOffset;
                                                    if (sVar30 != 0) {
                                                        sVar20 = DAT_UnitsState::instance.units[unitID].field_0x86;
                                                        if (sVar20 < 0) {
                                                            _yOffset_01 = 0;
                                                        } else {
                                                            _yOffset_01 = sVar20;
                                                        }
                                                        MACRO_CALL_MEMBER(
                                                            OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                renderUnitAnimationWithBlendingUnk,
                                                            DAT_TextureRenderCoreObject::ptr)(
                                                            DAT_UnitsState::instance.units[unitID].drawX,
                                                            sVar20 + DAT_UnitsState::instance.units[unitID].drawY,
                                                            DAT_UnitsState::instance.units[unitID].drawWidth,
                                                            DAT_UnitsState::instance.units[unitID].drawHeight1
                                                                - _yOffset_01,
                                                            (byte*)((int)((
                                                                DAT_GMImageOffsets::instance
                                                                    [GMFirstPictureIndex::instance
                                                                            [DAT_CurrentlyRenderedSpriteID::instance]
                                                                        - 1 + sVar30]
                                                                + (int)DAT_TextureRenderCoreObject::instance
                                                                    .gmProcessedImageData))),
                                                            32 - iVar27);
                                                    }
                                                }
                                                uVar9 = *this->viewportState.ptrColor;
                                                *this->viewportState.ptrColor = COL_MAGENTA::instance.shortValue;
                                                bVar15 = DAT_UnitsState::instance.units[unitID]
                                                             .disappearFadeAlphaCountdown;
                                                if (bVar15 == 0) {
                                                    if (DAT_UnitsState::instance.units[unitID].graphicSize == 4) {
                                                        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::
                                                                              renderAssassinClimbingOverlay,
                                                            this)(unitID);
                                                    }
                                                    sVar30 = DAT_UnitsState::instance.units[unitID].field_0x86;
                                                    if (sVar30 < 0) {
                                                        _yOffset_01 = 0;
                                                    } else {
                                                        _yOffset_01 = sVar30;
                                                    }
                                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                          renderUnitAnimationUnk,
                                                        DAT_TextureRenderCoreObject::ptr)(
                                                        DAT_UnitsState::instance.units[unitID].drawX,
                                                        sVar30 + DAT_UnitsState::instance.units[unitID].drawY,
                                                        DAT_UnitsState::instance.units[unitID].drawWidth,
                                                        DAT_UnitsState::instance.units[unitID].drawHeight1
                                                            - _yOffset_01,
                                                        (byte*)((int)((DAT_GMImageOffsets::instance[iVar26]
                                                            + (int)DAT_TextureRenderCoreObject::instance
                                                                .gmProcessedImageData))));
                                                    sVar30 = DAT_UnitsState::instance.units[unitID].graphicSize;
                                                    if ((sVar30 != 4) && (1 < sVar30)) {
                                                        DAT_CurrentlyRenderedSpriteID::instance
                                                            = (GmIDInt)DAT_UnitsState::instance.units[unitID].gmIDUnk;
                                                        DAT_RenderedUnitOwner::instance
                                                            = (uint)DAT_UnitsState::instance.units[unitID]
                                                                  .displayColorPlayerID;
                                                        _yOffset_01 = DAT_UnitsState::instance.units[unitID].imageIDUnk;
                                                        if (0 < _yOffset_01) {
                                                            sVar30 = DAT_UnitsState::instance.units[unitID].field_0x88;
                                                            if (sVar30 < 0) {
                                                                iVar26 = 0;
                                                            } else {
                                                                iVar26 = sVar30;
                                                            }
                                                            MACRO_CALL_MEMBER(
                                                                OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                    renderUnitAnimationUnk,
                                                                DAT_TextureRenderCoreObject::ptr)(
                                                                DAT_UnitsState::instance.units[unitID].drawX,
                                                                sVar30 + DAT_UnitsState::instance.units[unitID].drawY,
                                                                DAT_UnitsState::instance.units[unitID].drawWidth,
                                                                DAT_UnitsState::instance.units[unitID].drawHeight1
                                                                    - iVar26,
                                                                (byte*)((
                                                                    int)((DAT_GMImageOffsets::instance
                                                                              [GMFirstPictureIndex::instance
                                                                                      [DAT_CurrentlyRenderedSpriteID::
                                                                                              instance]
                                                                                  + _yOffset_01 - 1]
                                                                    + (int)DAT_TextureRenderCoreObject::instance
                                                                        .gmProcessedImageData))));
                                                        }
                                                    }
                                                    if (2 < DAT_UnitsState::instance.units[unitID].graphicSize) {
                                                        _yOffset_01 = DAT_UnitsState::instance.units[unitID].imageID2;
                                                        if (0 < _yOffset_01) {
                                                            sVar30 = DAT_UnitsState::instance.units[unitID].drawYOffset;
                                                            if (sVar30 < 0) {
                                                                iVar26 = 0;
                                                            } else {
                                                                iVar26 = sVar30;
                                                            }
                                                            MACRO_CALL_MEMBER(
                                                                OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                    renderUnitAnimationUnk,
                                                                DAT_TextureRenderCoreObject::ptr)(
                                                                DAT_UnitsState::instance.units[unitID].drawX,
                                                                sVar30 + DAT_UnitsState::instance.units[unitID].drawY,
                                                                DAT_UnitsState::instance.units[unitID].drawWidth,
                                                                DAT_UnitsState::instance.units[unitID].drawHeight1
                                                                    - iVar26,
                                                                (byte*)((
                                                                    int)((DAT_GMImageOffsets::instance
                                                                              [GMFirstPictureIndex::instance
                                                                                      [DAT_CurrentlyRenderedSpriteID::
                                                                                              instance]
                                                                                  + _yOffset_01 - 1]
                                                                    + (int)DAT_TextureRenderCoreObject::instance
                                                                        .gmProcessedImageData))));
                                                        }
                                                        if (DAT_GameSynchronyState::instance.currentGameMode
                                                            != OpenSHC::Game::GM_SOLITARY) {
                                                            UVar7 = DAT_UnitsState::instance.units[unitID].unitType;
                                                            if ((UVar7 == OpenSHC::Map::Units::UT_S_TOWER)
                                                                && (DAT_UnitsState::instance.units[unitID].dying
                                                                    == 0)) {
                                                                _yOffset_01
                                                                    = DAT_UnitsState::instance.units[unitID].drawX;
                                                                iVar26 = DAT_UnitsState::instance.units[unitID].drawY;
                                                                switch (DAT_UnitsState::instance.units[unitID]
                                                                        .facingDirectionMapOrientationCorrected) {
                                                                case 0:
                                                                    _yOffset_01 = _yOffset_01 + 34;
                                                                    break;
                                                                case 1:
                                                                    _yOffset_01 = _yOffset_01 + 47;
                                                                    iVar26 = iVar26 - 12;
                                                                    break;
                                                                case 2:
                                                                    _yOffset_01 = _yOffset_01 + 75;
                                                                    iVar26 = iVar26 - 19;
                                                                    break;
                                                                case 3:
                                                                    _yOffset_01 = _yOffset_01 + 101;
                                                                    iVar26 = iVar26 - 10;
                                                                    break;
                                                                case 4:
                                                                    _yOffset_01 = _yOffset_01 + 112;
                                                                    iVar26 = iVar26 + 2;
                                                                    break;
                                                                case 5:
                                                                    _yOffset_01 = _yOffset_01 + 100;
                                                                    iVar26 = iVar26 + 20;
                                                                    break;
                                                                case 6:
                                                                    _yOffset_01 = _yOffset_01 + 70;
                                                                    iVar26 = iVar26 + 19;
                                                                    break;
                                                                case 7:
                                                                    _yOffset_01 = _yOffset_01 + 44;
                                                                    iVar26 = iVar26 + 23;
                                                                }
                                                            } else {
                                                                if ((UVar7 != OpenSHC::Map::Units::UT_S_BATTERINGRAM)
                                                                    || (DAT_UnitsState::instance.units[unitID].dying
                                                                        != 0))
                                                                    goto LAB_004eadfa;
                                                                _yOffset_01
                                                                    = DAT_UnitsState::instance.units[unitID].drawX;
                                                                iVar26 = DAT_UnitsState::instance.units[unitID].drawY;
                                                                switch (DAT_UnitsState::instance.units[unitID]
                                                                        .facingDirectionMapOrientationCorrected) {
                                                                case 0:
                                                                case 1:
                                                                    _yOffset_01 = _yOffset_01 + 44;
                                                                    iVar26 = iVar26 - 20;
                                                                    break;
                                                                case 2:
                                                                    _yOffset_01 = _yOffset_01 + 49;
                                                                    iVar26 = iVar26 - 17;
                                                                    break;
                                                                case 3:
                                                                    _yOffset_01 = _yOffset_01 + 41;
                                                                    iVar26 = iVar26 - 15;
                                                                    break;
                                                                case 4:
                                                                    _yOffset_01 = _yOffset_01 + 34;
                                                                    iVar26 = iVar26 - 17;
                                                                    break;
                                                                case 5:
                                                                case 6:
                                                                    _yOffset_01 = _yOffset_01 + 32;
                                                                    iVar26 = iVar26 - 20;
                                                                    break;
                                                                case 7:
                                                                    _yOffset_01 = _yOffset_01 + 40;
                                                                    iVar26 = iVar26 - 23;
                                                                }
                                                            }
                                                            DAT_RenderedUnitOwner::instance
                                                                = (uint)DAT_UnitsState::instance.units[unitID].owner;
                                                            DAT_CurrentlyRenderedSpriteID::instance
                                                                = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                                                            uVar32 = DAT_UnitsState::instance.units[unitID].fixedRng
                                                                    + DAT_GameState::instance.mapAndTime
                                                                          .totalGameTicksUnk
                                                                & 0x8000003f;
                                                            if ((int)uVar32 < 0) {
                                                                uVar32 = (uVar32 - 1 | 0xffffffc0) + 1;
                                                            }
                                                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::
                                                                                  TextureRenderCore_Func::renderGM,
                                                                DAT_TextureRenderCoreObject::ptr)(
                                                                OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL,
                                                                (int)(uVar32 / 2 + 1), _yOffset_01, iVar26);
                                                        }
                                                    }
                                                LAB_004eadfa:
                                                    if (*this->viewportState.ptrColor
                                                        == COL_MAGENTA::instance.shortValue) {
                                                        *this->viewportState.ptrColor = uVar9;
                                                    } else {
                                                        this->viewportState.mouseRayUnitID = unitID;
                                                        this->viewportState.mouseRayBuildingID = 0;
                                                    }
                                                } else {
                                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                          renderUnitAnimationWithBlendingUnk,
                                                        DAT_TextureRenderCoreObject::ptr)(
                                                        DAT_UnitsState::instance.units[unitID].drawX,
                                                        DAT_UnitsState::instance.units[unitID].drawY,
                                                        DAT_UnitsState::instance.units[unitID].drawWidth,
                                                        (int)((
                                                            int)(DAT_UnitsState::instance.units[unitID].drawHeight1)),
                                                        (byte*)((int)((DAT_GMImageOffsets::instance[iVar26]
                                                            + (int)DAT_TextureRenderCoreObject::instance
                                                                .gmProcessedImageData))),
                                                        (int)((char)bVar15));
                                                    if (*this->viewportState.ptrColor
                                                        == COL_MAGENTA::instance.shortValue) {
                                                        *this->viewportState.ptrColor = uVar9;
                                                    } else {
                                                        this->viewportState.mouseRayUnitID = unitID;
                                                        this->viewportState.mouseRayBuildingID = 0;
                                                    }
                                                }
                                                if (DAT_UnitsState::instance.units[unitID].isSelected != 0
                                                    && DAT_UnitsState::instance.units[unitID].usingTeleport == 0
                                                    && DAT_UnitsState::instance.units[unitID]
                                                            .disappearFadeAlphaCountdown
                                                        == 0) {
                                                    _yOffset_01
                                                        = (DAT_UnitsState::instance.units[unitID].drawWidth - 22) / 2;
                                                    if (DAT_UnitsState::instance.units[unitID].unitType
                                                        == OpenSHC::Map::Units::UT_LORD) {
                                                        sVar30 = DAT_UnitsState::instance.units[unitID]
                                                                     .maxHealthRatingLord;
                                                        if (sVar30 == 0) {
                                                            iVar26
                                                                = DAT_UnitsState::instance.units[unitID].someDrawYOffset
                                                                - 6 + DAT_UnitsState::instance.units[unitID].drawY;
                                                            iVar27 = DAT_UnitsState::instance.units[unitID].drawX
                                                                + _yOffset_01;
                                                            iVar18
                                                                = DAT_UnitsState::instance.units[unitID].healthbar + 17;
                                                        } else {
                                                            iVar26
                                                                = DAT_UnitsState::instance.units[unitID].someDrawYOffset
                                                                - 8 + DAT_UnitsState::instance.units[unitID].drawY;
                                                            iVar27 = DAT_UnitsState::instance.units[unitID].drawX
                                                                + _yOffset_01;
                                                            iVar18 = DAT_UnitsState::instance.units[unitID].healthbar
                                                                + 228 + sVar30 * 11;
                                                        }
                                                    } else {
                                                        iVar26 = DAT_GameState::instance
                                                                     .playerDataArray
                                                                         [DAT_UnitsState::instance.units[unitID].owner]
                                                                     .fearFactorLevel;
                                                        if (iVar26 == 0) {
                                                            iVar26
                                                                = DAT_UnitsState::instance.units[unitID].someDrawYOffset
                                                                - 6 + DAT_UnitsState::instance.units[unitID].drawY;
                                                            iVar27 = DAT_UnitsState::instance.units[unitID].drawX
                                                                + _yOffset_01;
                                                            iVar18
                                                                = DAT_UnitsState::instance.units[unitID].healthbar + 17;
                                                        } else {
                                                            if (iVar26 < 1) {
                                                                iVar18 = iVar26 * -11 + 173;
                                                            } else {
                                                                iVar18 = iVar26 * 11 + 118;
                                                            }
                                                            iVar26
                                                                = DAT_UnitsState::instance.units[unitID].someDrawYOffset
                                                                - 8 + DAT_UnitsState::instance.units[unitID].drawY;
                                                            iVar27 = DAT_UnitsState::instance.units[unitID].drawX
                                                                + _yOffset_01;
                                                            iVar18 = DAT_UnitsState::instance.units[unitID].healthbar
                                                                + iVar18;
                                                        }
                                                    }
                                                    MACRO_CALL_MEMBER(
                                                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                        DAT_TextureRenderCoreObject::ptr)(
                                                        OpenSHC::DE::SHCDE::GM_FLOATS, iVar18, iVar27, iVar26);
                                                    if (DAT_UnitsState::instance.units[unitID].unitType
                                                            == OpenSHC::Map::Units::UT_A_ASSASSIN
                                                        && DAT_GameState::instance.mapAndTime.playerTeams
                                                                [DAT_UnitsState::instance.units[unitID].owner]
                                                            == DAT_GameState::instance.mapAndTime.playerTeams
                                                                [DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                                        && (DAT_UnitsState::instance.units[unitID]
                                                                    .assassinsMicroDistanceToEnemyUnk
                                                                < 161
                                                            || ((UVar4
                                                                = DAT_UnitsState::instance.units[unitID].state.generic,
                                                                UVar4 == OpenSHC::Map::Units::States::US_MELEE_ATTACK
                                                                    || (UVar4
                                                                        == OpenSHC::Map::Units::States::
                                                                            US_MELEE_ATTACK_WALL))))) {
                                                        MACRO_CALL_MEMBER(
                                                            OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                renderGMWithBlending,
                                                            DAT_TextureRenderCoreObject::ptr)(
                                                            OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 447,
                                                            DAT_UnitsState::instance.units[unitID].drawX + 2
                                                                + _yOffset_01,
                                                            DAT_UnitsState::instance.units[unitID].someDrawYOffset - 27
                                                                + DAT_UnitsState::instance.units[unitID].drawY,
                                                            16);
                                                    }
                                                }
                                                if ((unitID != 0)
                                                    && (sVar30 = DAT_UnitsState::instance.units[unitID].field_0x6e,
                                                        sVar30 != 0)) {
                                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                          renderGMWithAlphaMask,
                                                        DAT_TextureRenderCoreObject::ptr)(
                                                        OpenSHC::IO::Graphics::GID_FLOATS_NEW, sVar30 + 212,
                                                        DAT_UnitsState::instance.units[unitID].drawX,
                                                        DAT_UnitsState::instance.units[unitID].someDrawYOffset - 54
                                                            + DAT_UnitsState::instance.units[unitID].drawY,
                                                        OpenSHC::IO::Graphics::GID_FLOATS_NEW, sVar30 + 220, 0);
                                                    DAT_UnitsState::instance.units[unitID].field_0x6e = 0;
                                                }
                                                sVar30 = DAT_UnitsState::instance.units[unitID].field_0x6c;
                                                if (sVar30 == 1) {
                                                    iVar26
                                                        = DAT_TileMapState::instance.cursorOverlayAnimationFrame + 48;
                                                    iVar18 = DAT_UnitsState::instance.units[unitID].someDrawYOffset - 70
                                                        + DAT_UnitsState::instance.units[unitID].drawY;
                                                    _yOffset_01 = DAT_UnitsState::instance.units[unitID].field_0x2a - 53
                                                        + DAT_UnitsState::instance.units[unitID].drawX;
                                                    iVar27
                                                        = DAT_TileMapState::instance.cursorOverlayAnimationFrame + 32;
                                                } else if (sVar30 == 2) {
                                                    _yOffset_01 = 0;
                                                    iVar18 = 0;
                                                    switch (DAT_UnitsState::instance.units[unitID].unitType) {
                                                    case OpenSHC::Map::Units::UT_S_CATAPULT:
                                                        _yOffset_01 = 41;
                                                        iVar18 = 58;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_TREBUCHET:
                                                    case OpenSHC::Map::Units::UT_S_TOWER:
                                                        _yOffset_01 = 79;
                                                        iVar18 = 56;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_MANGONEL:
                                                        _yOffset_01 = 43;
                                                        iVar18 = 35;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                                                        _yOffset_01 = 36;
                                                        iVar18 = 61;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_SHIELD:
                                                        _yOffset_01 = -3;
                                                        iVar18 = 60;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_BALLISTA:
                                                    case OpenSHC::Map::Units::UT_S_FBALLISTA:
                                                        iVar18 = 36;
                                                        _yOffset_01 = 19;
                                                    }
                                                    iVar26
                                                        = DAT_TileMapState::instance.cursorOverlayAnimationFrame + 132;
                                                    iVar18 = (DAT_UnitsState::instance.units[unitID].someDrawYOffset
                                                                 - iVar18)
                                                        + DAT_UnitsState::instance.units[unitID].drawY;
                                                    _yOffset_01
                                                        = DAT_UnitsState::instance.units[unitID].drawX + _yOffset_01;
                                                    iVar27
                                                        = DAT_TileMapState::instance.cursorOverlayAnimationFrame + 116;
                                                } else {
                                                    if (sVar30 != 3)
                                                        goto LAB_004eb1be;
                                                    iVar18 = 0;
                                                    _yOffset_01 = 0;
                                                    switch (DAT_UnitsState::instance.units[unitID].unitType) {
                                                    case OpenSHC::Map::Units::UT_S_CATAPULT:
                                                        _yOffset_01 = 41;
                                                        iVar18 = 58;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_TREBUCHET:
                                                    case OpenSHC::Map::Units::UT_S_TOWER:
                                                        _yOffset_01 = 79;
                                                        iVar18 = 56;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_MANGONEL:
                                                        _yOffset_01 = 43;
                                                        iVar18 = 35;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                                                        _yOffset_01 = 36;
                                                        iVar18 = 61;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_SHIELD:
                                                        _yOffset_01 = -3;
                                                        iVar18 = 60;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_BALLISTA:
                                                    case OpenSHC::Map::Units::UT_S_FBALLISTA:
                                                        iVar18 = 36;
                                                        _yOffset_01 = 19;
                                                    }
                                                    iVar26
                                                        = DAT_TileMapState::instance.cursorOverlayAnimationFrame + 164;
                                                    iVar18 = (DAT_UnitsState::instance.units[unitID].someDrawYOffset
                                                                 - iVar18)
                                                        + DAT_UnitsState::instance.units[unitID].drawY;
                                                    _yOffset_01
                                                        = DAT_UnitsState::instance.units[unitID].drawX + _yOffset_01;
                                                    iVar27
                                                        = DAT_TileMapState::instance.cursorOverlayAnimationFrame + 148;
                                                }
                                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                      renderGMWithAlphaMask,
                                                    DAT_TextureRenderCoreObject::ptr)(
                                                    OpenSHC::IO::Graphics::GID_FLOATS_NEW, iVar27, _yOffset_01, iVar18,
                                                    OpenSHC::IO::Graphics::GID_FLOATS_NEW, iVar26, 0);
                                                DAT_UnitsState::instance.units[unitID].field_0x6c = 0;
                                                goto LAB_004eb1be;
                                            }
                                            if (DAT_BuildingsState::instance.buildings[local_54].buildingType
                                                    != OpenSHC::Map::Buildings::BT_TOWER2
                                                || (sVar24 = DAT_UnitsState::instance.units[unitID]
                                                        .facingDirectionMapOrientationCorrected,
                                                    sVar24 != 2 && (sVar24 != 6)))
                                                goto LAB_004ea49b;
                                            if ((DAT_UnitsState::instance.units[unitID].unitType
                                                    == OpenSHC::Map::Units::UT_A_ASSASSIN)
                                                && (_yOffset_01 = DAT_UnitsState::instance.units[unitID].imageID2,
                                                    _yOffset_01 != 0)) {
                                                sVar24 = DAT_UnitsState::instance.units[unitID].field_0x86;
                                                if (sVar24 < 0) {
                                                    local_14 = 0;
                                                } else {
                                                    local_14 = sVar24;
                                                }
                                                iVar27 = (32 - local_2c) / 3;
                                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                      renderUnitAnimationWithBlendingUnk,
                                                    DAT_TextureRenderCoreObject::ptr)(sVar30,
                                                    DAT_UnitsState::instance.units[unitID].field_0x86 + sVar20, sVar5,
                                                    DAT_UnitsState::instance.units[unitID].drawHeight1 - local_14,
                                                    (byte*)((
                                                        int)((DAT_GMImageOffsets::instance[_yOffset_01 - 1 + iVar18]
                                                        + (int)DAT_TextureRenderCoreObject::instance
                                                            .gmProcessedImageData))),
                                                    (16 - iVar27) * 2);
                                                sVar30 = DAT_UnitsState::instance.units[unitID].drawYOffset;
                                                if (sVar30 != 0) {
                                                    sVar20 = DAT_UnitsState::instance.units[unitID].field_0x86;
                                                    if (sVar20 < 0) {
                                                        _yOffset_01 = 0;
                                                    } else {
                                                        _yOffset_01 = sVar20;
                                                    }
                                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                          renderUnitAnimationWithBlendingUnk,
                                                        DAT_TextureRenderCoreObject::ptr)(
                                                        DAT_UnitsState::instance.units[unitID].drawX,
                                                        sVar20 + DAT_UnitsState::instance.units[unitID].drawY,
                                                        DAT_UnitsState::instance.units[unitID].drawWidth,
                                                        DAT_UnitsState::instance.units[unitID].drawHeight1
                                                            - _yOffset_01,
                                                        (byte*)((
                                                            int)((DAT_GMImageOffsets::instance
                                                                      [GMFirstPictureIndex::instance
                                                                              [DAT_CurrentlyRenderedSpriteID::instance]
                                                                          - 1 + sVar30]
                                                            + (int)DAT_TextureRenderCoreObject::instance
                                                                .gmProcessedImageData))),
                                                        32 - iVar27);
                                                }
                                            }
                                            uVar9 = *this->viewportState.ptrColor;
                                            *this->viewportState.ptrColor = COL_MAGENTA::instance.shortValue;
                                            sVar30 = DAT_UnitsState::instance.units[unitID].field_0x86;
                                            if (local_2c == 0) {
                                                if (sVar30 < 0) {
                                                    _yOffset_01 = 0;
                                                } else {
                                                    _yOffset_01 = sVar30;
                                                }
                                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                      renderUnitAnimationUnk,
                                                    DAT_TextureRenderCoreObject::ptr)(
                                                    DAT_UnitsState::instance.units[unitID].drawX,
                                                    sVar30 + DAT_UnitsState::instance.units[unitID].drawY,
                                                    DAT_UnitsState::instance.units[unitID].drawWidth,
                                                    DAT_UnitsState::instance.units[unitID].drawHeight1 - _yOffset_01,
                                                    (byte*)((int)((DAT_GMImageOffsets::instance[iVar26]
                                                        + (int)DAT_TextureRenderCoreObject::instance
                                                            .gmProcessedImageData))));
                                            } else {
                                                if (sVar30 < 0) {
                                                    _yOffset_01 = 0;
                                                } else {
                                                    _yOffset_01 = sVar30;
                                                }
                                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                      renderUnitAnimationWithBlendingUnk,
                                                    DAT_TextureRenderCoreObject::ptr)(
                                                    DAT_UnitsState::instance.units[unitID].drawX,
                                                    sVar30 + DAT_UnitsState::instance.units[unitID].drawY,
                                                    DAT_UnitsState::instance.units[unitID].drawWidth,
                                                    DAT_UnitsState::instance.units[unitID].drawHeight1 - _yOffset_01,
                                                    (byte*)((int)((DAT_GMImageOffsets::instance[iVar26]
                                                        + (int)DAT_TextureRenderCoreObject::instance
                                                            .gmProcessedImageData))),
                                                    local_2c);
                                            }
                                            sVar30 = DAT_UnitsState::instance.units[unitID].graphicSize;
                                            if ((sVar30 != 4) && (1 < sVar30)) {
                                                DAT_CurrentlyRenderedSpriteID::instance
                                                    = (GmIDInt)DAT_UnitsState::instance.units[unitID].gmIDUnk;
                                                DAT_RenderedUnitOwner::instance
                                                    = (uint)DAT_UnitsState::instance.units[unitID].displayColorPlayerID;
                                                _yOffset_01 = DAT_UnitsState::instance.units[unitID].imageIDUnk;
                                                if (0 < _yOffset_01) {
                                                    sVar30 = DAT_UnitsState::instance.units[unitID].field_0x88;
                                                    if (sVar30 < 0) {
                                                        iVar26 = 0;
                                                    } else {
                                                        iVar26 = sVar30;
                                                    }
                                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                          renderUnitAnimationUnk,
                                                        DAT_TextureRenderCoreObject::ptr)(
                                                        DAT_UnitsState::instance.units[unitID].drawX,
                                                        sVar30 + DAT_UnitsState::instance.units[unitID].drawY,
                                                        DAT_UnitsState::instance.units[unitID].drawWidth,
                                                        DAT_UnitsState::instance.units[unitID].drawHeight1 - iVar26,
                                                        (byte*)((
                                                            int)((DAT_GMImageOffsets::instance
                                                                      [GMFirstPictureIndex::instance
                                                                              [DAT_CurrentlyRenderedSpriteID::instance]
                                                                          + _yOffset_01 - 1]
                                                            + (int)DAT_TextureRenderCoreObject::instance
                                                                .gmProcessedImageData))));
                                                }
                                            }
                                            if (2 < DAT_UnitsState::instance.units[unitID].graphicSize) {
                                                _yOffset_01 = DAT_UnitsState::instance.units[unitID].imageID2;
                                                if (0 < _yOffset_01) {
                                                    sVar30 = DAT_UnitsState::instance.units[unitID].drawYOffset;
                                                    if (sVar30 < 0) {
                                                        iVar26 = 0;
                                                    } else {
                                                        iVar26 = sVar30;
                                                    }
                                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                          renderUnitAnimationUnk,
                                                        DAT_TextureRenderCoreObject::ptr)(
                                                        DAT_UnitsState::instance.units[unitID].drawX,
                                                        sVar30 + DAT_UnitsState::instance.units[unitID].drawY,
                                                        DAT_UnitsState::instance.units[unitID].drawWidth,
                                                        DAT_UnitsState::instance.units[unitID].drawHeight1 - iVar26,
                                                        (byte*)((
                                                            int)((DAT_GMImageOffsets::instance
                                                                      [GMFirstPictureIndex::instance
                                                                              [DAT_CurrentlyRenderedSpriteID::instance]
                                                                          + _yOffset_01 - 1]
                                                            + (int)DAT_TextureRenderCoreObject::instance
                                                                .gmProcessedImageData))));
                                                }
                                                if (DAT_GameSynchronyState::instance.currentGameMode
                                                    != OpenSHC::Game::GM_SOLITARY) {
                                                    UVar7 = DAT_UnitsState::instance.units[unitID].unitType;
                                                    if ((UVar7 == OpenSHC::Map::Units::UT_S_TOWER)
                                                        && (DAT_UnitsState::instance.units[unitID].dying == 0)) {
                                                        _yOffset_01 = DAT_UnitsState::instance.units[unitID].drawX;
                                                        iVar26 = DAT_UnitsState::instance.units[unitID].drawY;
                                                        switch (DAT_UnitsState::instance.units[unitID]
                                                                .facingDirectionMapOrientationCorrected) {
                                                        case 0:
                                                            _yOffset_01 = _yOffset_01 + 34;
                                                            break;
                                                        case 1:
                                                            _yOffset_01 = _yOffset_01 + 47;
                                                            iVar26 = iVar26 - 12;
                                                            break;
                                                        case 2:
                                                            _yOffset_01 = _yOffset_01 + 75;
                                                            iVar26 = iVar26 - 19;
                                                            break;
                                                        case 3:
                                                            _yOffset_01 = _yOffset_01 + 101;
                                                            iVar26 = iVar26 - 10;
                                                            break;
                                                        case 4:
                                                            _yOffset_01 = _yOffset_01 + 112;
                                                            iVar26 = iVar26 + 2;
                                                            break;
                                                        case 5:
                                                            _yOffset_01 = _yOffset_01 + 100;
                                                            iVar26 = iVar26 + 20;
                                                            break;
                                                        case 6:
                                                            _yOffset_01 = _yOffset_01 + 70;
                                                            iVar26 = iVar26 + 19;
                                                            break;
                                                        case 7:
                                                            _yOffset_01 = _yOffset_01 + 44;
                                                            iVar26 = iVar26 + 23;
                                                        }
                                                    } else {
                                                        if ((UVar7 != OpenSHC::Map::Units::UT_S_BATTERINGRAM)
                                                            || (DAT_UnitsState::instance.units[unitID].dying != 0))
                                                            goto LAB_004ea966;
                                                        _yOffset_01 = DAT_UnitsState::instance.units[unitID].drawX;
                                                        iVar26 = DAT_UnitsState::instance.units[unitID].drawY;
                                                        switch (DAT_UnitsState::instance.units[unitID]
                                                                .facingDirectionMapOrientationCorrected) {
                                                        case 0:
                                                        case 1:
                                                            _yOffset_01 = _yOffset_01 + 44;
                                                            iVar26 = iVar26 - 20;
                                                            break;
                                                        case 2:
                                                            _yOffset_01 = _yOffset_01 + 49;
                                                            iVar26 = iVar26 - 17;
                                                            break;
                                                        case 3:
                                                            _yOffset_01 = _yOffset_01 + 41;
                                                            iVar26 = iVar26 - 15;
                                                            break;
                                                        case 4:
                                                            _yOffset_01 = _yOffset_01 + 34;
                                                            iVar26 = iVar26 - 17;
                                                            break;
                                                        case 5:
                                                        case 6:
                                                            _yOffset_01 = _yOffset_01 + 32;
                                                            iVar26 = iVar26 - 20;
                                                            break;
                                                        case 7:
                                                            _yOffset_01 = _yOffset_01 + 40;
                                                            iVar26 = iVar26 - 23;
                                                        }
                                                    }
                                                    DAT_RenderedUnitOwner::instance
                                                        = (uint)DAT_UnitsState::instance.units[unitID].owner;
                                                    DAT_CurrentlyRenderedSpriteID::instance
                                                        = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                                                    uVar32 = DAT_UnitsState::instance.units[unitID].fixedRng
                                                            + DAT_GameState::instance.mapAndTime.totalGameTicksUnk
                                                        & 0x8000003f;
                                                    if ((int)uVar32 < 0) {
                                                        uVar32 = (uVar32 - 1 | 0xffffffc0) + 1;
                                                    }
                                                    MACRO_CALL_MEMBER(
                                                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                        DAT_TextureRenderCoreObject::ptr)(
                                                        OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, (int)(uVar32 / 2 + 1),
                                                        _yOffset_01, iVar26);
                                                }
                                            }
                                        LAB_004ea966:
                                            if (*this->viewportState.ptrColor == COL_MAGENTA::instance.shortValue) {
                                                *this->viewportState.ptrColor = uVar9;
                                            } else {
                                                this->viewportState.mouseRayUnitID = unitID;
                                                this->viewportState.mouseRayBuildingID = 0;
                                            }
                                            goto LAB_004eb1be;
                                        }
                                        _yOffset_01 = 0;
                                    }
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::Rendering::ViewportRenderState_Func::scheduleUnitForBatchedRendering,
                                        this)(unitID, (undefined4)(sVar30), (undefined4)(sVar20), (undefined4)(sVar5),
                                        (undefined4)(DAT_UnitsState::instance.units[unitID].drawHeight1),
                                        (undefined4)((int)(DAT_GMImageOffsets::instance[iVar26]
                                            + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData)),
                                        _yOffset_01);
                                } else if (_yOffset_01 != 1) {
                                    if (local_2c == 0) {
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationUnk,
                                            DAT_TextureRenderCoreObject::ptr)(sVar30, sVar20, sVar5,
                                            DAT_UnitsState::instance.units[unitID].drawHeight1,
                                            (byte*)((int)((DAT_GMImageOffsets::instance[iVar26]
                                                + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))));
                                    } else {
                                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                              renderUnitAnimationWithBlendingUnk,
                                            DAT_TextureRenderCoreObject::ptr)(sVar30, sVar20, sVar5,
                                            DAT_UnitsState::instance.units[unitID].drawHeight1,
                                            (byte*)((int)((DAT_GMImageOffsets::instance[iVar26]
                                                + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))),
                                            local_2c);
                                    }
                                    _yOffset_01 = DAT_UnitsState::instance.units[unitID].vanish;
                                    if (1 < _yOffset_01) {
                                        DAT_UnitsState::instance.units[unitID].vanish = _yOffset_01 - 1;
                                    }
                                }
                            }
                        LAB_004eb1be:
                            unitID = (int)(short)DAT_UnitsState::instance.units[unitID].nextUnitOnTheSameTile;
                            if ((DAT_GameSynchronyState::instance.syncStatus != 0) || (unitID < 1))
                                break;
                        }
                    }
                    /*
                      ------ END RENDER UNITS ------
                     */

                    local_24 = 0;
                    _yOffset_01 = DAT_RenderMap_YOffset::instance;
                    if (entityID != 0) {
                        do {
                            local_24 = local_24 + 1;
                            if ((9 < local_24) || (DAT_EntityState::instance.entityArray[entityID].logicalState == 0))
                                break;
                            if (DAT_EntityState::instance.entityArray[entityID].graphicType2 == 0)
                                goto LAB_004eb439;
                            DAT_CurrentlyRenderedSpriteID::instance
                                = (GmIDInt)DAT_EntityState::instance.entityArray[entityID].gmID;
                            if ((DAT_CurrentlyRenderedSpriteID::instance == OpenSHC::IO::Graphics::GID_BODY_FIRE)
                                || (DAT_CurrentlyRenderedSpriteID::instance
                                    == OpenSHC::IO::Graphics::GID_BODY_FIRE_2)) {
                                local_8 = local_8 + 1;
                                if ((DAT_EntityState::instance.entityArray[entityID].fireIntensity == 0)
                                    && (79 < local_8)) {
                                    if (local_8 < 200) {
                                        bVar15 = (byte)DAT_EntityState::instance.entityArray[entityID].rng_1 & 1;
                                    } else {
                                        bVar15 = (byte)DAT_EntityState::instance.entityArray[entityID].rng_1 & 3;
                                    }
                                    if (bVar15 != 0)
                                        break;
                                }
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Audio::SFX::SFXState_Func::notifyAmbientSoundEvent, DAT_SFXState::ptr)(5);
                                _yOffset_01 = DAT_RenderMap_YOffset::instance;
                            }
                            DAT_RenderedUnitOwner::instance = DAT_EntityState::instance.entityArray[entityID].colorUnk;
                            bVar12 = 0;
                            iVar26 = DAT_EntityState::instance.entityArray[entityID].height;
                            switch (DAT_CurrentlyRenderedSpriteID::instance) {
                            case OpenSHC::IO::Graphics::GID_ANIM_FLAGS:
                            case OpenSHC::IO::Graphics::GID_ANIM_CRUSADER_FLAG:
                                if (_flatView != 0)
                                    goto LAB_004eb439;
                            case OpenSHC::IO::Graphics::GID_BODY_INFO:
                                bVar12 = 1;
                            switchD_004eb2c9_caseD_76:
                                if ((DAT_TileMapState::instance.refreshRelatedOne == 0) || (_flatView != 0)) {
                                    iVar26 = _yOffset_01;
                                }
                                if (bVar12 == 0)
                                    goto switchD_004eb2c9_caseD_4d;
                                break;
                            default:
                                goto switchD_004eb2c9_caseD_4d;
                            case OpenSHC::IO::Graphics::GID_BODY_FIRE:
                            case OpenSHC::IO::Graphics::GID_BODY_DISEASE:
                            case OpenSHC::IO::Graphics::GID_BLAST_3:
                            case OpenSHC::IO::Graphics::GID_BODY_FIRE_2:
                                goto switchD_004eb2c9_caseD_76;
                            case OpenSHC::IO::Graphics::GID_BODY_MISSILE_COW:
                                if (DAT_EntityState::instance.entityArray[entityID].someCounter_OR_hitGround != 0
                                    && (DAT_TileMapState::instance.refreshRelatedOne == 0 || (_flatView != 0))) {
                                    iVar26 = _yOffset_01;
                                }
                                goto switchD_004eb2c9_caseD_4d;
                            case OpenSHC::IO::Graphics::GID_BODY_BRAZIER:
                                iVar18 = iVar26 + 4
                                    + (_yOffset_01 - (uint)DAT_TileMapState::instance.HeightLayer[layerTileIndex]);
                                if (DAT_TileMapState::instance.refreshRelatedOne == 0) {
                                    iVar26 = _yOffset_01;
                                    if (DAT_TileMapState::instance.BuildingLayer[layerTileIndex] != 0) {
                                        iVar26 = _yOffset_01 + 20;
                                    }
                                } else {
                                    iVar26 = _yOffset_01;
                                    if ((_flatView == 0)
                                        && (iVar26 = iVar18,
                                            DAT_TileMapState::instance.BuildingLayer[layerTileIndex] != 0)) {
                                        iVar26 = iVar18 - 10;
                                    }
                                }
                                break;
                            case OpenSHC::IO::Graphics::GID_ANIM_HEADS:
                                iVar26 = iVar26 + 7
                                    + (_yOffset_01 - (uint)DAT_TileMapState::instance.HeightLayer[layerTileIndex]);
                                uVar32 = DAT_TileMapState::instance.LogicLayer[layerTileIndex]
                                    & Map::LogicHelpers::L_CRENEL_VARIATIONUnk;
                                if (uVar32 != 0) {
                                    iVar26 = iVar26 + 18;
                                }
                                if (DAT_TileMapState::instance.refreshRelatedOne == 0) {
                                    iVar26 = _yOffset_01 + 20;
                                    if (DAT_TileMapState::instance.BuildingLayer[layerTileIndex] == 0) {
                                        iVar26 = _yOffset_01;
                                    }
                                    if (uVar32 != 0) {
                                        iVar26 = iVar26 + 18;
                                    }
                                } else if (_flatView != 0)
                                    goto LAB_004eb439;
                            }
                            if ((DAT_EntityState::instance.entityArray[entityID].field_0xc0 == 0)
                                || (DAT_TextureRenderCoreObject::instance.isZoom2 == 0)) {
                                sVar30 = DAT_EntityState::instance.entityArray[entityID].unkMinusOne;
                                if (sVar30 < 0) {
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                        DAT_TextureRenderCoreObject::ptr)((GmID)DAT_CurrentlyRenderedSpriteID::instance,
                                        DAT_EntityState::instance.entityArray[entityID].graphicType2,
                                        (DAT_EntityState::instance.entityArray[entityID].x1
                                            - DAT_EntityState::instance.entityArray[entityID].originX)
                                            + DAT_RenderMap_DrawSomeX::instance,
                                        (int)(((DAT_EntityState::instance.entityArray[entityID].y1
                                                   - DAT_EntityState::instance.entityArray[entityID].originY)
                                                  - iVar26)
                                            + DAT_RenderMap_DrawSomeY::instance),
                                        (GmID)(DAT_CurrentlyRenderedSpriteID::instance),
                                        DAT_EntityState::instance.entityArray[entityID].imageID, -1 - sVar30);
                                    _yOffset_01 = DAT_RenderMap_YOffset::instance;
                                } else {
                                    _yOffset_01 = DAT_EntityState::instance.entityArray[entityID].originY;
                                    if (sVar30 == 0) {
                                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                            DAT_TextureRenderCoreObject::ptr)(
                                            (eGM)DAT_CurrentlyRenderedSpriteID::instance,
                                            DAT_EntityState::instance.entityArray[entityID].graphicType2,
                                            (DAT_EntityState::instance.entityArray[entityID].x1
                                                - DAT_EntityState::instance.entityArray[entityID].originX)
                                                + DAT_RenderMap_DrawSomeX::instance,
                                            (int)((
                                                int)(((DAT_EntityState::instance.entityArray[entityID].y1 - _yOffset_01)
                                                         - iVar26)
                                                + DAT_RenderMap_DrawSomeY::instance)));
                                        _yOffset_01 = DAT_RenderMap_YOffset::instance;
                                    } else {
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                            DAT_TextureRenderCoreObject::ptr)(
                                            (GmID)DAT_CurrentlyRenderedSpriteID::instance,
                                            DAT_EntityState::instance.entityArray[entityID].graphicType2,
                                            (DAT_EntityState::instance.entityArray[entityID].x1
                                                - DAT_EntityState::instance.entityArray[entityID].originX)
                                                + DAT_RenderMap_DrawSomeX::instance,
                                            (int)((
                                                int)(((DAT_EntityState::instance.entityArray[entityID].y1 - _yOffset_01)
                                                         - iVar26)
                                                + DAT_RenderMap_DrawSomeY::instance)),
                                            sVar30);
                                        _yOffset_01 = DAT_RenderMap_YOffset::instance;
                                    }
                                }
                            LAB_004eb439:
                                iVar26 = DAT_EntityState::instance.entityArray[entityID].nextEntityOnThisTileByID;
                                if ((entityID == iVar26)
                                    || (entityID = iVar26, DAT_GameSynchronyState::instance.syncStatus != 0))
                                    break;
                            } else {
                                entityID
                                    = (uint)DAT_EntityState::instance.entityArray[entityID].nextEntityOnThisTileByID;
                            }
                            if (entityID == 0)
                                break;
                        } while (true);
                    }
                    entityID = (uint)(byte)DAT_TileMapState::instance.EntityLayerLT25[layerTileIndex];
                    _yOffset_01 = 0;
                    if (entityID != 0) {
                        while (_yOffset_01 = _yOffset_01 + 1, _yOffset_01 < 10) {
                            if (DAT_EntityState::instance.entityArray[entityID].tile != layerTileIndex) {
                                DAT_TileMapState::instance.EntityLayerLT25[layerTileIndex] = '\0';
                                break;
                            }
                            if (DAT_EntityState::instance.entityArray[entityID].logicalState == 0)
                                break;
                            iVar26 = DAT_EntityState::instance.entityArray[entityID].graphicType2;
                            if (iVar26 == 0) {
                            LAB_004eb7db:
                                uVar32 = (uint)DAT_EntityState::instance.entityArray[entityID].nextEntityOnThisTileByID;
                                if ((entityID == uVar32) || (DAT_GameSynchronyState::instance.syncStatus != 0))
                                    break;
                            } else {
                                DAT_CurrentlyRenderedSpriteID::instance
                                    = (GmIDInt)DAT_EntityState::instance.entityArray[entityID].gmID;
                                DAT_RenderedUnitOwner::instance
                                    = DAT_EntityState::instance.entityArray[entityID].colorUnk;
                                iVar18 = DAT_EntityState::instance.entityArray[entityID].height;
                                if ((DAT_EntityState::instance.entityArray[entityID].field_0xc0 == 0)
                                    || (DAT_TextureRenderCoreObject::instance.isZoom2 == 0)) {
                                    sVar30 = DAT_EntityState::instance.entityArray[entityID].unkMinusOne;
                                    if (sVar30 < 0) {
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                            DAT_TextureRenderCoreObject::ptr)(
                                            (GmID)DAT_CurrentlyRenderedSpriteID::instance, iVar26,
                                            (DAT_EntityState::instance.entityArray[entityID].x1
                                                - DAT_EntityState::instance.entityArray[entityID].originX)
                                                + DAT_RenderMap_DrawSomeX::instance,
                                            (int)(((DAT_EntityState::instance.entityArray[entityID].y1
                                                       - DAT_EntityState::instance.entityArray[entityID].originY)
                                                      - iVar18)
                                                + DAT_RenderMap_DrawSomeY::instance),
                                            (GmID)(DAT_CurrentlyRenderedSpriteID::instance),
                                            DAT_EntityState::instance.entityArray[entityID].imageID, -1 - sVar30);
                                    } else {
                                        iVar27 = DAT_EntityState::instance.entityArray[entityID].originY;
                                        if (sVar30 == 0) {
                                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                DAT_TextureRenderCoreObject::ptr)(
                                                (eGM)DAT_CurrentlyRenderedSpriteID::instance, iVar26,
                                                (int)((
                                                    int)((DAT_EntityState::instance.entityArray[entityID].x1
                                                             - DAT_EntityState::instance.entityArray[entityID].originX)
                                                    + DAT_RenderMap_DrawSomeX::instance)),
                                                (int)((
                                                    int)(((DAT_EntityState::instance.entityArray[entityID].y1 - iVar27)
                                                             - iVar18)
                                                    + DAT_RenderMap_DrawSomeY::instance)));
                                        } else {
                                            MACRO_CALL_MEMBER(
                                                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                                DAT_TextureRenderCoreObject::ptr)(
                                                (GmID)DAT_CurrentlyRenderedSpriteID::instance, iVar26,
                                                (int)((
                                                    int)((DAT_EntityState::instance.entityArray[entityID].x1
                                                             - DAT_EntityState::instance.entityArray[entityID].originX)
                                                    + DAT_RenderMap_DrawSomeX::instance)),
                                                (int)((
                                                    int)(((DAT_EntityState::instance.entityArray[entityID].y1 - iVar27)
                                                             - iVar18)
                                                    + DAT_RenderMap_DrawSomeY::instance)),
                                                sVar30);
                                        }
                                    }
                                    sVar30 = DAT_EntityState::instance.entityArray[entityID].field_0xc0;
                                    if (sVar30 != 0) {
                                        sVar20 = DAT_EntityState::instance.entityArray[entityID].unkMinusOne;
                                        EVar3 = DAT_EntityState::instance.entityArray[entityID].entityType;
                                        iVar27 = (DAT_EntityState::instance.entityArray[entityID].x1
                                                     - DAT_EntityState::instance.entityArray[entityID].originX)
                                            + DAT_RenderMap_DrawSomeX::instance;
                                        iVar18 = ((DAT_EntityState::instance.entityArray[entityID].y1
                                                      - DAT_EntityState::instance.entityArray[entityID].originY)
                                                     - iVar18)
                                            + DAT_RenderMap_DrawSomeY::instance;
                                        DAT_TextManagerObject::instance.textSurfaceTarget
                                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                                        iVar26 = sVar20;
                                        local_c = 0;
                                        if ((EVar3 == (OpenSHC::Map::Entities::EntityType)42)
                                            || (EVar3 == (OpenSHC::Map::Entities::EntityType)43)) {
                                            DAT_EntityState::instance.entityArray[entityID].unkMinusOne = sVar20 - 2;
                                            DAT_TextManagerObject::instance.field_0x20 = 1;
                                            if (EVar3 == (OpenSHC::Map::Entities::EntityType)43) {
                                                local_c = 255;
                                            }
                                        }
                                        if (iVar26 < 0) {
                                            iVar26 = 0;
                                        }
                                        DAT_CurrentlyRenderedSpriteID::instance
                                            = (GmIDInt)DAT_EntityState::instance.entityArray[entityID].field_0xbe;
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                            DAT_TextureRenderCoreObject::ptr)(
                                            (GmID)DAT_CurrentlyRenderedSpriteID::instance, sVar30,
                                            DAT_EntityState::instance.entityArray[entityID].field_0xc8 + iVar27,
                                            DAT_EntityState::instance.entityArray[entityID].field_0xca + iVar18,
                                            iVar26);
                                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                                            DAT_TextManagerObject::ptr)(
                                            DAT_EntityState::instance.entityArray[entityID].displayValue,
                                            DAT_EntityState::instance.entityArray[entityID].field_0xcc + iVar27,
                                            DAT_EntityState::instance.entityArray[entityID].field_0xce + iVar18,
                                            OpenSHC::Text::TTA_LEFT, local_c, 18, FALSE, iVar26);
                                        DAT_TextManagerObject::instance.textSurfaceTarget
                                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                                        DAT_TextManagerObject::instance.field_0x20 = 0;
                                    }
                                    goto LAB_004eb7db;
                                }
                                uVar32 = (uint)DAT_EntityState::instance.entityArray[entityID].nextEntityOnThisTileByID;
                            }
                            entityID = uVar32;
                            if (uVar32 == 0)
                                break;
                        }
                    }
                    if ((iVar23 != 0) && (iVar23 < 2000)) {
                        DAT_CurrentlyRenderedSpriteID::instance
                            = (GmIDInt)DAT_LandscapeState::instance.trees[iVar23].treeTypeBasedValue1;
                        iVar26 = DAT_LandscapeState::instance.trees[iVar23].animationFrameUnk;
                        iVar18 = GMFirstPictureIndex::instance[DAT_CurrentlyRenderedSpriteID::instance];
                        _yOffset_01 = iVar18 - 1 + iVar26;
                        if (0 < DAT_CurrentlyRenderedSpriteID::instance && _yOffset_01 != 0 && iVar26 != 0) {
                            DAT_RenderedUnitOwner::instance
                                = DAT_LandscapeState::instance.trees[iVar23].appleTreeColorVariation;
                            DAT_TextureRenderCoreObject::instance.mbr_0x10 = 1;
                            /*
                              renders trees
                             */

                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationUnk,
                                DAT_TextureRenderCoreObject::ptr)(
                                (DAT_RenderMap_DrawSomeX::instance
                                    - DAT_LandscapeState::instance.trees[iVar23].gmOriginX)
                                    + 14,
                                ((DAT_RenderMap_DrawSomeY::instance
                                     - DAT_LandscapeState::instance.trees[iVar23].gmOriginY)
                                    - DAT_RenderMap_YOffset::instance)
                                    + 6,
                                DAT_GMImageHeaders::instance.imh[iVar26 + iVar18 - 1].width,
                                DAT_GMImageHeaders::instance.imh[iVar26 + iVar18 - 1].height,
                                (byte*)((int)((DAT_GMImageOffsets::instance[_yOffset_01]
                                    + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))));
                            DAT_TextureRenderCoreObject::instance.mbr_0x10 = 0;
                            if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                                && (DAT_LandscapeState::instance.trees[iVar23].unknownDistanceRelatedToCrow != 0)) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_BODY_CROW,
                                    this->unknownCounterUntil_0x24 % 12 + 73, DAT_RenderMap_DrawSomeX::instance - 30,
                                    (DAT_RenderMap_DrawSomeY::instance - DAT_RenderMap_YOffset::instance) - 220);
                            }
                        }
                        MACRO_CALL_MEMBER(
                            OpenSHC::Audio::SFX::SFXState_Func::notifyAmbientSoundEvent, DAT_SFXState::ptr)(4);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Audio::SFX::SFXState_Func::notifyAmbientSoundEvent, DAT_SFXState::ptr)(8);
                    }
                    if (DAT_RenderMap_RowsLeft::instance != 0 && DAT_RenderMap_RowsLeft::instance < 255
                        && bVar13 != 0) {
                        uVar32 = (uint)(short)DAT_TileMapState::instance.MiscDisplayLayer[layerTileIndex];
                        DAT_RenderMap_WhatToDraw::instance = uVar32 & 3;
                        if ((DAT_00ed3148::instance & 0x100) != 0) {
                            DAT_GmImageAddressToBeRendered::instance
                                = (uint)DAT_TileMapState::instance.WallGFXLayer[layerTileIndex];
                            DAT_RenderMap_SecondBlitImageIndex::instance = DAT_GmImageAddressToBeRendered::instance;
                            if (local_54 != 0) {
                                DAT_RenderMap_SecondBlitImageIndex::instance
                                    = (uint)DAT_TileMapState::instance.PillarGFXLayer[layerTileIndex];
                            }
                        LAB_004eb9a4:
                            MACRO_CALL(OpenSHC::Rendering_Func::BlitMapImageWithVerticalClip)();
                        } else {
                            DAT_GmImageAddressToBeRendered::instance
                                = (uint)DAT_TileMapState::instance.PillarGFXLayer[layerTileIndex];
                            if ((DAT_00ed3148::instance & 0x100000) != 0) {
                                if (DAT_GmImageAddressToBeRendered::instance == 32) {
                                    DAT_GmImageAddressToBeRendered::instance = GMFirstPictureIndex::instance[9] + 31;
                                } else {
                                    layerTileIndex
                                        = DAT_GmImageAddressToBeRendered::instance + this->unknownCounterUntil_0x10;
                                    if (50 < layerTileIndex) {
                                        layerTileIndex = layerTileIndex - 16;
                                    }
                                    DAT_GmImageAddressToBeRendered::instance
                                        = layerTileIndex - 1 + GMFirstPictureIndex::instance[9];
                                    if (32 < DAT_RenderMap_RowsLeft::instance
                                        && (DAT_RenderMap_DrawSomeY::instance - DAT_RenderMap_RowsLeft::instance)
                                            < local_5c - 160) {
                                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::notifyAmbientSoundEvent,
                                            DAT_SFXState::ptr)(6);
                                    }
                                }
                                DAT_RenderMap_SecondBlitImageIndex::instance = DAT_GmImageAddressToBeRendered::instance;
                                if ((uVar32 & 0x800) == 0)
                                    goto LAB_004eb9a4;
                                MACRO_CALL(OpenSHC::Rendering_Func::BlitMapImageWithVerticalClipAndYOffset)();
                            } else {
                                DAT_RenderMap_SecondBlitImageIndex::instance = DAT_GmImageAddressToBeRendered::instance;
                                if ((uVar32 & 0x800) != 0) {
                                    MACRO_CALL(OpenSHC::Rendering_Func::BlitMapImageWithVerticalClipAndYOffset)();
                                } else {
                                    MACRO_CALL(OpenSHC::Rendering_Func::BlitMapImageWithVerticalClip)();
                                }
                                if (bVar14 != 0) {
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS,
                                        DAT_RenderMap_ImageID::instance + 8, DAT_RenderMap_DrawSomeX::instance,
                                        (DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance) + 9
                                            + DAT_RenderMap_DrawSomeY::instance,
                                        24);
                                }
                            }
                        }
                    }
                }
                DAT_RenderMap_DrawSomeX::instance = DAT_RenderMap_DrawSomeX::instance + 32;
            }
            iVar31 = _zoomOffset;
            if (_vpWidthPlus1 == _viewportHeight) {
                DAT_RenderMap_DrawSomeX::instance = this->viewportState.unknownScreenXRelated + 16;
                layerTileIndex = _viewportHeight;
            } else {
                layerTileIndex = _viewportHeight + 1;
                DAT_RenderMap_DrawSomeX::instance = this->viewportState.unknownScreenXRelated;
            }
            for (; iVar31 < layerTileIndex; iVar31 = iVar31 + 1) {
                _yOffset_01 = this->screenPointToTileNumber[iVar31 + iVar2];
                DAT_00ed3148::instance = DAT_TileMapState::instance.LogicLayer[_yOffset_01];
                if ((DAT_00ed3148::instance & 0x30) == 0) {
                    if ((iVar31 < 2) || (bVar13 = 1, layerTileIndex - 2 <= iVar31)) {
                        bVar13 = 0;
                    }
                    uVar32 = (uint)DAT_TileMapState::instance.FloatingLayer[_yOffset_01];
                    DAT_RenderMap_ImageID::instance
                        = (uint)DAT_TileMapState::instance.ConstructionGFXLayer[_yOffset_01];
                    DAT_GmImageAddressToBeRendered::instance = (uint)DAT_TileMapState::instance.GfxLayer[_yOffset_01];
                    if (DAT_RenderMap_ImageID::instance != 0) {
                        DAT_GmImageAddressToBeRendered::instance = DAT_RenderMap_ImageID::instance;
                    }
                    DAT_RenderMap_YOffset::instance
                        = DAT_TileMapState::instance
                              .heightBasedScreenYOffset[DAT_TileMapState::instance.HeightLayer[_yOffset_01]];
                    puVar1 = DAT_TileMapState::instance.MiscDisplayLayer + _yOffset_01;
                    uVar29 = (uint)DAT_TileMapState::instance.BuildingLayer[_yOffset_01];
                    DAT_00ed3154::instance = -(uint)((*puVar1 & 0x20) != 0) & 0x5a;
                    if (_flatView != 0) {
                        if (uVar29 == 0) {
                            if ((DAT_00ed3148::instance & 0x100) == 0) {
                                if ((char)DAT_00ed3148::instance < '\0'
                                    && 1999 < DAT_TileMapState::instance.OrganismLayer[_yOffset_01]
                                    && (iVar23 = DAT_TileMapState::instance.OrganismLayer[_yOffset_01] * 32,
                                        1 < *(short*)((int)&DAT_LandscapeState::instance.trees[1590]
                                                          .appleTreeColorVariation
                                            + iVar23 + 2))) {
                                    iVar26
                                        = MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::getRandomRockImageOffset,
                                            DAT_LandscapeState::ptr)(
                                            ((byte)DAT_TileMapState::instance.RandomLayer[_yOffset_01] & 3) + 1);
                                    DAT_GmImageAddressToBeRendered::instance = iVar26 - 1
                                        + GMFirstPictureIndex::instance[*(
                                            short*)((int)&DAT_LandscapeState::instance.trees[1590].animationFrameUnk
                                            + iVar23 + 2)];
                                }
                            } else if ((DAT_00ed3148::instance & 0x800) != 0) {
                                DAT_00ed3148::instance = DAT_00ed3148::instance & 1;
                                if ((DAT_GmImageAddressToBeRendered::instance
                                        == GMFirstPictureIndex::instance[12] + 134U)
                                    || (DAT_GmImageAddressToBeRendered::instance
                                        == GMFirstPictureIndex::instance[12] + 136U)) {
                                    DAT_GmImageAddressToBeRendered::instance = GMFirstPictureIndex::instance[157] + 42;
                                } else {
                                    DAT_GmImageAddressToBeRendered::instance = GMFirstPictureIndex::instance[157] + 40;
                                }
                            } else {
                                if ((DAT_00ed3148::instance & 0x200) != 0) {
                                    DAT_00ed3148::instance = DAT_00ed3148::instance & 1;
                                    DAT_GmImageAddressToBeRendered::instance
                                        = (DAT_00ed314c::instance & 3) + 36 + GMFirstPictureIndex::instance[157];
                                }
                            }
                        } else {
                            BVar8 = DAT_BuildingsState::instance.buildings[uVar29].buildingType;
                            iVar23 = DAT_MapRenderDefinedData::instance.BuildingRenderSomeTypeArray[(short)BVar8];
                            if (iVar23 == 3) {
                                uVar22 = (uint)((*puVar1 & 4) != 0);
                                if (BVar8 == OpenSHC::Map::Buildings::BT_WOODCUTTERSHUT) {
                                    DAT_GmImageAddressToBeRendered::instance
                                        = uVar22 + 24 + GMFirstPictureIndex::instance[157];
                                } else if (BVar8 == OpenSHC::Map::Buildings::BT_HUNTERSHUT) {
                                    DAT_GmImageAddressToBeRendered::instance
                                        = uVar22 + 26 + GMFirstPictureIndex::instance[157];
                                } else if (BVar8 == OpenSHC::Map::Buildings::BT_DAIRYFARM) {
                                    DAT_GmImageAddressToBeRendered::instance
                                        = uVar22 + 28 + GMFirstPictureIndex::instance[157];
                                } else {
                                    DAT_GmImageAddressToBeRendered::instance
                                        = uVar22 + 30 + GMFirstPictureIndex::instance[157];
                                }
                            } else if (-1 < iVar23) {
                                DAT_GmImageAddressToBeRendered::instance = (DAT_00ed314c::instance & 3)
                                    + GMFirstPictureIndex::instance[157] + ((uVar29 & 1) + iVar23 * 2) * 4;
                            }
                        }
                        DAT_RenderMap_YOffset::instance = 8;
                    }
                    if (uVar29 != 0) {
                        if (local_1c < viewportWidth && bVar13 != 0 && 4 < iVar31) {
                            DAT_BuildingsState::instance.buildings[uVar29].surfaceAreaUnk
                                = DAT_BuildingsState::instance.buildings[uVar29].surfaceAreaUnk + 1;
                        }
                        uVar9 = *this->viewportState.ptrColor;
                        *this->viewportState.ptrColor = COL_MAGENTA::instance.shortValue;
                        if ((DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance].direction != 0)
                            && (bVar13 != 0)) {
                            iVar23 = (int)DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance]
                                         .tileOffset;
                            /*
                              renders building sprite ontop of tilemap
                             */

                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                  renderFunctionResponsibleForManyGameObjects,
                                DAT_TextureRenderCoreObject::ptr)(
                                (char)DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance]
                                        .horizontalOffsetImage
                                    + DAT_RenderMap_DrawSomeX::instance,
                                ((DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance) - iVar23)
                                    + DAT_RenderMap_DrawSomeY::instance,
                                (int)((char)DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance]
                                        .buildingWidth),
                                iVar23 + 7,
                                (ushort*)((int)(

                                    (DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance] + 512
                                        + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))));
                        }
                        if ((_flatView == 0)
                            || (DAT_MapRenderDefinedData::instance.BuildingRenderSomeTypeArray
                                    [(short)DAT_BuildingsState::instance.buildings[uVar29].buildingType]
                                < 0)) {
                            if (DAT_BuildingsState::instance.buildings[uVar29].buildingType
                                    == OpenSHC::Map::Buildings::BT_DRAWBRIDGE
                                && DAT_TileMapState::instance.refreshRelatedOne != 0
                                && _yOffset_01
                                    == this->translationMatrix[(short)DAT_BuildingsState::instance.buildings[uVar29].y
                                               + 2]
                                            .addXgetTile
                                        + 2 + (int)(short)DAT_BuildingsState::instance.buildings[uVar29].x) {
                                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::renderBuildingAnimation,
                                    this)(uVar29, DAT_RenderMap_DrawSomeX::instance + 16,
                                    DAT_00ed3154::instance + 24 + DAT_RenderMap_DrawSomeY::instance,
                                    (undefined4)((int)(_yOffset_01)), 1);
                            }
                            uVar10 = *puVar1;
                            if ((uVar10 & 0xc) != 0) {
                                if (DAT_BuildingsState::instance.buildings[uVar29].buildingType
                                    == OpenSHC::Map::Buildings::BT_DRAWBRIDGE) {
                                    if (DAT_TileMapState::instance.refreshRelatedOne != 0) {
                                        if ((uVar10 & 0xc) == 12) {
                                            MACRO_CALL_MEMBER(
                                                OpenSHC::Rendering::ViewportRenderState_Func::renderBuildingAnimation,
                                                this)(uVar29, DAT_RenderMap_DrawSomeX::instance + 16,
                                                DAT_00ed3154::instance + 40 + DAT_RenderMap_DrawSomeY::instance,
                                                (undefined4)((int)(_yOffset_01)), 0);
                                        } else if ((uVar10 & 8) != 0) {
                                            MACRO_CALL_MEMBER(
                                                OpenSHC::Rendering::ViewportRenderState_Func::renderGmOverlayBuilding,
                                                this)(uVar29, DAT_RenderMap_DrawSomeX::instance,
                                                (DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance)
                                                    + DAT_RenderMap_DrawSomeY::instance,
                                                _yOffset_01);
                                        }
                                    }
                                } else {
                                    iVar23 = (DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance)
                                        + DAT_RenderMap_DrawSomeY::instance;
                                    if ((uVar10 & 8) != 0) {
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::Rendering::ViewportRenderState_Func::renderGmOverlayBuilding,
                                            this)(uVar29, DAT_RenderMap_DrawSomeX::instance, iVar23, _yOffset_01);
                                    } else {
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::Rendering::ViewportRenderState_Func::renderGmOverlayBuilding2,
                                            this)(uVar29, DAT_RenderMap_DrawSomeX::instance, iVar23, _yOffset_01);
                                    }
                                }
                            }
                        }
                        if (*this->viewportState.ptrColor == COL_MAGENTA::instance.shortValue) {
                            *this->viewportState.ptrColor = uVar9;
                        } else {
                            this->viewportState.mouseRayUnitID = 0;
                            this->viewportState.mouseRayBuildingID = uVar29;
                        }
                    }
                    if ((DAT_00ed3148::instance & 8) != 0 && (*puVar1 & 0x4000) != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                            DAT_TileMapState::instance.cursorOverlayAnimationFrame,
                            DAT_RenderMap_DrawSomeX::instance - 35,
                            (DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance) - 74
                                + DAT_RenderMap_DrawSomeY::instance,
                            OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                            DAT_TileMapState::instance.cursorOverlayAnimationFrame + 16, 0);
                        *puVar1 = *puVar1 & 0xbfff;
                    }
                    iVar23 = DAT_RenderMap_YOffset::instance;
                    if (uVar32 != 0) {
                        if ((DAT_TileMapState::instance.refreshRelatedOne != 0) && (_flatView == 0)) {
                            if ((DAT_TileMapState::instance.LogicLayer[_yOffset_01]
                                    & Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE)
                                != 0) {
                                iVar26 = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                    DAT_BuildingsState::ptr)(DAT_TileMapState::instance.BuildingLayer[_yOffset_01]);
                                iVar23 = iVar23 + iVar26;
                            } else {
                                if ((DAT_TileMapState::instance.LogicLayer[_yOffset_01]
                                        & Map::LogicHelpers::L_WALL_OR_GATEHOUSE)
                                    != 0) {
                                    if (DAT_TileMapState::instance.BuildingLayer[_yOffset_01] == 0) {
                                        iVar23 = DAT_RenderMap_YOffset::instance + 4;
                                    } else if (DAT_BuildingsState::instance
                                                   .buildings[DAT_TileMapState::instance.BuildingLayer[_yOffset_01]]
                                                   .buildingType
                                        == OpenSHC::Map::Buildings::BT_WOODGATE1) {
                                        iVar23 = DAT_RenderMap_YOffset::instance + 6;
                                    } else {
                                        iVar23 = DAT_RenderMap_YOffset::instance + 20;
                                    }
                                }
                            }
                        }
                        do {
                            uVar29 = this->floatersArray[uVar32].variation;
                            if ((uVar29 & 1) != 0) {
                                iVar26 = iVar23;
                                if ((uVar29 & 8) != 0 && DAT_TileMapState::instance.refreshRelatedOne != 0
                                    && _flatView == 0
                                    && (iVar26 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAt,
                                            DAT_TileMapState::ptr)(_yOffset_01, 0),
                                        iVar26 < 0)) {
                                    iVar26 = -1 - iVar26;
                                }
                                if ((*puVar1 & 0x10) != 0) {
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::Rendering::ViewportRenderState_Func::scheduleUnitForBatchedRendering,
                                        this)(0,
                                        this->floatersArray[uVar32].originX + DAT_RenderMap_DrawSomeX::instance,
                                        (this->floatersArray[uVar32].originY - iVar26)
                                            + DAT_RenderMap_DrawSomeY::instance,
                                        (undefined4)(this->floatersArray[uVar32].imageID),
                                        (undefined4)(this->floatersArray[uVar32].variation),
                                        (undefined4)((int)(this->floatersArray[uVar32].gmID)), 0);
                                } else {
                                    uVar29 = this->floatersArray[uVar32].variation;
                                    if ((uVar29 & 4) != 0) {
                                        DAT_RenderedUnitOwner::instance = ~-(uint)((uVar29 & 0x10) != 0)
                                            & DAT_GameSynchronyState::instance.currentPlayerSlotID;
                                        DAT_CurrentlyRenderedSpriteID::instance = this->floatersArray[uVar32].gmID;
                                        uVar29 = this->floatersArray[uVar32].variation;
                                    }
                                    if ((uVar29 & 0x20) != 0) {
                                        iVar18 = this->floatersArray[uVar32].imageID;
                                        GVar11 = (GmID)this->floatersArray[uVar32].gmID;
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                            DAT_TextureRenderCoreObject::ptr)((GmID)GVar11, iVar18,
                                            this->floatersArray[uVar32].originX + DAT_RenderMap_DrawSomeX::instance,
                                            (int)((this->floatersArray[uVar32].originY - iVar26)
                                                + DAT_RenderMap_DrawSomeY::instance),
                                            GVar11, ((int)uVar29 >> 0x10) + iVar18, 0);
                                    } else {
                                        if ((uVar29 & 0xffff0000) != 0) {
                                            MACRO_CALL_MEMBER(
                                                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                                DAT_TextureRenderCoreObject::ptr)(
                                                (GmID)this->floatersArray[uVar32].gmID,
                                                this->floatersArray[uVar32].imageID,
                                                this->floatersArray[uVar32].originX + DAT_RenderMap_DrawSomeX::instance,
                                                (int)((this->floatersArray[uVar32].originY - iVar26)
                                                    + DAT_RenderMap_DrawSomeY::instance),
                                                (int)(uVar29 >> 0x10));
                                        } else {
                                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                DAT_TextureRenderCoreObject::ptr)((eGM)this->floatersArray[uVar32].gmID,
                                                this->floatersArray[uVar32].imageID,
                                                this->floatersArray[uVar32].originX + DAT_RenderMap_DrawSomeX::instance,
                                                (int)((this->floatersArray[uVar32].originY - iVar26)
                                                    + DAT_RenderMap_DrawSomeY::instance));
                                        }
                                    }
                                }
                            }
                            uVar32 = this->floatersArray[uVar32].id;
                        } while (uVar32 != 0);
                    }
                    DAT_TileMapState::instance.ConstructionGFXLayer[_yOffset_01] = 0;
                    *puVar1 = *puVar1 & 0x7fff;
                }
                DAT_RenderMap_DrawSomeX::instance = DAT_RenderMap_DrawSomeX::instance + 32;
            }
            if (layerTileIndex == _viewportHeight) {
                _vpWidthPlus1_1 = _viewportHeight;
                local_c = 200;
                DAT_RenderMap_DrawSomeX::instance = this->viewportState.unknownScreenXRelated + 16;
            } else {
                _vpWidthPlus1_1 = _viewportHeight + 1;
                local_c = 201;
                DAT_RenderMap_DrawSomeX::instance = this->viewportState.unknownScreenXRelated;
            }
            if ((_flatView == 0) && (local_48 = _zoomOffset, _zoomOffset < _vpWidthPlus1_1)) {
                local_20 = this->screenPointToTileNumber + _zoomOffset + iVar2;
                do {
                    iVar31 = *local_20;
                    DAT_GmImageAddressToBeRendered::instance = (uint)DAT_TileMapState::instance.AlphaGFXLayer[iVar31];
                    if (DAT_GmImageAddressToBeRendered::instance != 0
                        && (DAT_TileMapState::instance.MiscDisplayLayer[iVar31] & 0x3c0) == 0) {
                        if ((local_48 < 2) || (_vpWidthPlus1_1 - 2 <= local_48)) {
                            bVar13 = 0;
                        } else {
                            bVar13 = 1;
                        }
                        DAT_00ed3148::instance = DAT_TileMapState::instance.LogicLayer[iVar31];
                        if ((DAT_00ed3148::instance & 0x400) != 0) {
                            psVar17 = &DAT_BuildingsState::instance
                                           .buildings[DAT_TileMapState::instance.BuildingLayer[iVar31]]
                                           .tickRelatedVisuallyActiveIndicator;
                            sVar30 = *psVar17;
                            if (0 < sVar30 && sVar30 < 5 && bVar13 != 0) {
                                DAT_RenderMap_RowsLeft::instance = (uint)DAT_TileMapState::instance.ShowHiLayer[iVar31];
                                DAT_RenderMap_YOffset::instance
                                    = DAT_TileMapState::instance
                                          .heightBasedScreenYOffset[DAT_TileMapState::instance.HeightLayer[iVar31]];
                                MACRO_CALL(OpenSHC::Rendering_Func::ApplyBlending)((sVar30 << 5) / 5);
                                if (DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance].direction
                                    != 0) {
                                    iVar31 = (int)DAT_GMImageHeaders::instance
                                                 .imh[DAT_GmImageAddressToBeRendered::instance]
                                                 .tileOffset;
                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                          renderInterfaceOrBuildingOccupationArea,
                                        DAT_TextureRenderCoreObject::ptr)(
                                        (char)DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance]
                                                .horizontalOffsetImage
                                            + DAT_RenderMap_DrawSomeX::instance,
                                        (DAT_RenderMap_DrawSomeY::instance - DAT_RenderMap_YOffset::instance) - iVar31,
                                        (int)((char)DAT_GMImageHeaders::instance
                                                .imh[DAT_GmImageAddressToBeRendered::instance]
                                                .buildingWidth),
                                        iVar31 + 7,
                                        (ushort*)((int)(

                                            (DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance]
                                                + 512
                                                + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))),
                                        (int)((*psVar17 << 5) / 5));
                                }
                            }
                        }
                    }
                    local_20 = local_20 + 1;
                    DAT_RenderMap_DrawSomeX::instance = DAT_RenderMap_DrawSomeX::instance + 32;
                    local_48 = local_48 + 1;
                } while (local_48 < _vpWidthPlus1_1);
            }
            iVar2 = iVar2 + local_c;
            DAT_RenderMap_DrawSomeY::instance = DAT_RenderMap_DrawSomeY::instance + 8;
            local_1c = local_1c + 1;
        }
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::renderUnits, this)();
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::renderUnits, this)();
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::renderUnits, this)();
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::renderUnits, this)();
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::renderUnits, this)();
        if ((DAT_TileMapState::instance.mapSize == 160)
            && (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768)) {
            if (this->viewportState.isZoomedOutUnk != 0) {
                if ((DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SIEGETOWER)
                    || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD)) {
                    DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(0, 716, 4056, 716, 26);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(0, 717, 4056, 717, 20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(0, 718, 4056, 718, 14);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(0, 719, 4056, 719, 8);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                        DAT_PencilRenderCore::ptr)(0, 720, 4056, 2033, (ushort)(COL_BLACK::instance.shortValue));
                    DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                }
                goto LAB_004ec57a;
            }
        LAB_004ec582:
            iVar31 = this->viewportState.currentCameraOffsetX + DAT_MouseState::instance.screenSpaceX;
            iVar28 = this->viewportState.currentCameraOffsetY + DAT_MouseState::instance.screenSpaceY;
            _viewportHeight = iVar28;
            viewportWidth = iVar31;
        } else {
        LAB_004ec57a:
            if (this->viewportState.isZoomedOutUnk == 0)
                goto LAB_004ec582;
            iVar28 = this->viewportState.currentCameraOffsetY + DAT_MouseState::instance.screenSpaceY;
            iVar31 = this->viewportState.currentCameraOffsetX + DAT_MouseState::instance.screenSpaceX;
            _viewportHeight = this->viewportState.currentCameraOffsetY + DAT_MouseState::instance.screenSpaceY * 2;
            viewportWidth = this->viewportState.currentCameraOffsetX + 160 + DAT_MouseState::instance.screenSpaceX * 2;
        }
        if (this->viewportState.field_0x0 != 0) {
            if (DAT_MouseState::instance.field_0x1dc < 1001) {
                if (DAT_MouseState::instance.field_0x1dc != 1000) {
                    switch (DAT_MouseState::instance.field_0x1dc) {
                    case 1:
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_CURSORS, 81,
                            viewportWidth
                                - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[107].originX,
                            (_viewportHeight
                                - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[107].originY)
                                + 45);
                        break;
                    case 3:
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)((GmID)DAT_TileMapState::instance.cursorOverlayGmID,
                            (int)(DAT_TileMapState::instance.cursorOverlayImageBase + 16
                                + DAT_TileMapState::instance.cursorOverlayAnimationFrame),
                            viewportWidth
                                - DAT_TextureRenderCoreObject::instance
                                    .gmFileHeaderColorpaletteArray[DAT_TileMapState::instance.cursorOverlayGmID]
                                    .originX,
                            _viewportHeight
                                - DAT_TextureRenderCoreObject::instance
                                    .gmFileHeaderColorpaletteArray[DAT_TileMapState::instance.cursorOverlayGmID]
                                    .originY,
                            21);
                    case 2:
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)((eGM)DAT_TileMapState::instance.cursorOverlayGmID,
                            (int)(DAT_TileMapState::instance.cursorOverlayImageBase
                                + DAT_TileMapState::instance.cursorOverlayAnimationFrame),
                            viewportWidth
                                - DAT_TextureRenderCoreObject::instance
                                    .gmFileHeaderColorpaletteArray[DAT_TileMapState::instance.cursorOverlayGmID]
                                    .originX,
                            _viewportHeight
                                - DAT_TextureRenderCoreObject::instance
                                    .gmFileHeaderColorpaletteArray[DAT_TileMapState::instance.cursorOverlayGmID]
                                    .originY);
                        break;
                    case 4:
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)((eGM)DAT_TileMapState::instance.cursorOverlayGmID,
                            (int)(DAT_TileMapState::instance.cursorOverlayImageBase), viewportWidth - 8,
                            _viewportHeight - 8);
                        break;
                    case 5:
                        iVar28 = DAT_TileMapState::instance.flagAnimationFrame
                                % DAT_TileMapState::instance.flagAnimationDivisor
                            + DAT_TileMapState::instance.cursorOverlayImageBase;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)((GmID)DAT_TileMapState::instance.cursorOverlayGmID,
                            iVar28,
                            viewportWidth
                                - DAT_TextureRenderCoreObject::instance
                                    .gmFileHeaderColorpaletteArray[DAT_TileMapState::instance.cursorOverlayGmID]
                                    .originX,
                            _viewportHeight
                                - DAT_TextureRenderCoreObject::instance
                                    .gmFileHeaderColorpaletteArray[DAT_TileMapState::instance.cursorOverlayGmID]
                                    .originY,
                            (GmID)((int)(DAT_TileMapState::instance.cursorOverlayGmID)),
                            DAT_TileMapState::instance.flagAnimationDivisor + iVar28, 0);
                    }
                    goto switchD_004ec5fa_default;
                }
                DAT_TextureRenderCoreObject::instance.isZoom2 = 0;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 123, iVar31 + 28, iVar28 + 4);
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    "(", iVar31 + 60, iVar28 + 7, OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 18, FALSE, 0);
                if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {
                    _numberToDisplay
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .startResources[4]
                        - DAT_TileMapState::instance.wallPlacementCost;
                } else {
                    _numberToDisplay
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .currentResources[4]
                        - DAT_TileMapState::instance.wallPlacementCost;
                }
            } else {
                if (DAT_MouseState::instance.field_0x1dc != 1001)
                    goto switchD_004ec5fa_default;
                DAT_TextureRenderCoreObject::instance.isZoom2 = 0;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 126, iVar31 + 28, iVar28 + 4);
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    "(", iVar31 + 60, iVar28 + 7, OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 18, FALSE, 0);
                _numberToDisplay
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .currentResources[2]
                    - DAT_TileMapState::instance.wallPlacementCost;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                _numberToDisplay, iVar31 + 60, iVar28 + 7, OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                ")", iVar31 + 60, iVar28 + 7, OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 18, TRUE, 0);
            DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        }
    switchD_004ec5fa_default:
        DAT_MouseState::instance.field_0x1dc = -1;
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::clearAllFloatingLayerElements, this)();
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMapSurfaceHeightRangeUnk,
            DAT_TextureRenderCoreObject::ptr)();
        DAT_TextureRenderCoreObject::instance.isZoom2 = 0;
        DAT_TileMapState::instance.field_0x5549b8 = 0;
        return;
    switchD_004eb2c9_caseD_4d:
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::scheduleUnitForBatchedRendering, this)(
            4294967295,
            (DAT_EntityState::instance.entityArray[entityID].x1
                - DAT_EntityState::instance.entityArray[entityID].originX)
                + DAT_RenderMap_DrawSomeX::instance,
            ((DAT_EntityState::instance.entityArray[entityID].y1
                 - DAT_EntityState::instance.entityArray[entityID].originY)
                - iVar26)
                + DAT_RenderMap_DrawSomeY::instance,
            (undefined4)(DAT_EntityState::instance.entityArray[entityID].graphicType2),
            (undefined4)(DAT_EntityState::instance.entityArray[entityID].unkMinusOne),
            (undefined4)(DAT_EntityState::instance.entityArray[entityID].imageID), 0);
        _yOffset_01 = DAT_RenderMap_YOffset::instance;
        goto LAB_004eb439;
    }

}
}
