#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
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
#include "OpenSHC/Globals/DAT_00ed316c.hpp"
#include "OpenSHC/Globals/DAT_00ed3170.hpp"
#include "OpenSHC/Globals/DAT_00ed317c.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentlyRenderedSpriteID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_GMImageSizes.hpp"
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
#include "OpenSHC/Globals/DAT_RenderMap_YOffset.hpp"
#include "OpenSHC/Globals/DAT_RenderedUnitOwner.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"
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
        ushort* puVar1;
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
        bool bVar12;
        bool bVar13;
        bool bVar14;
        byte bVar15;
        int iVar16;
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
        int local_60;
        int local_5c;
        uint local_58;
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
        bool _flatView;
        int _viewportHeight;
        int viewportWidth;

        iVar31 = 0;
        iVar28 = 0;
        _displayLayerLogicalValue = 0;
        local_1c = 0;
        local_5c = 600;
        _flatView = false;
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
            _flatView = true;
        }
        if (this->viewportState.isZoomedOutUnk != 0) {
            iVar28 = 4;
            _zoomOffset = 4;
        }
        _vpWidthPlus1_1 = this->viewportState.viewportHeight + 1;
        this->viewportState.unknownScreenXRelated = iVar28 * 32 + 70;
        iVar28 = this->viewportState.viewportWidth + 0x2a;
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
        if (this->viewportState.field37_0x94 != 0) {
            if (this->viewportState.isZoomedOutUnk == 0) {
                iVar31 = 64;
                local_1c = 8;
            } else {
                iVar31 = 128;
                local_1c = 0x10;
            }
            DAT_RenderMap_DrawSomeY::instance = iVar31 + 8;
        }
        _yOffset_01
            = (int)(this->viewportState.viewportY + iVar31 + (this->viewportState.viewportY + iVar31 >> 0x1f & 0xfU))
            >> 4;
        iVar16 = ((int)(this->viewportState.viewportX + (this->viewportState.viewportX >> 0x1f & 0x1fU)) >> 5)
            + _visualTileOffset;
        /*
          ***
           This piece of logic together with the huge array in the ViewportState gets
           the tile the top left corner of the screen is showing, offset by some margin
           to the right, not sure why that applies
           ***
         */

        iVar2 = iVar16 + -2 + _yOffset_01 * 401;
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
            + (this->screenPointToTileNumber[_yOffset_01 * 0x191 + iVar16 + -8]
                - this
                    ->translationMatrix[this->tileTranslationMatrix_YComponent[this
                            ->screenPointToTileNumber[_yOffset_01 * 0x191 + iVar16 + -8]]]
                    .addXgetTile);
        this->viewportState.tileCenterY = iVar26
            + this->tileTranslationMatrix_YComponent[this->screenPointToTileNumber[_yOffset_01 * 0x191 + iVar16 + -8]];
        DAT_TextureRenderCoreObject::instance.isZoom2 = this->viewportState.isZoomedOutUnk;
        if (this->viewportState.isZoomedOutUnk == 0) {
            iVar16 = DAT_WindowAndDirectDraw::instance.resolutionY + 0x18;
        } else {
            iVar16 = DAT_WindowAndDirectDraw::instance.resolutionY * 2 + 0x20;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMapSurfaceHeightRange,
            DAT_TextureRenderCoreObject::ptr)(iVar31, iVar16);
        this->viewportState.ptrColor = (DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame
            + this->viewportState.currentCameraOffsetX + DAT_MouseState::instance.screenSpaceX
            + (this->viewportState.currentCameraOffsetY + DAT_MouseState::instance.screenSpaceY) * 0xfd8);
        this->viewportState.mouseRayBuildingID = 0;
        this->viewportState.mouseRayUnitID = 0;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        iVar31 = 1;
        if (1 < (int)DAT_UnitsState::instance.maxUnitCount) {
            psVar17 = &DAT_UnitsState::instance.units[1].drawX;
            do {
                if (psVar17[0x3c] != OpenSHC::Map::Units::ULS_INVISIBLE) {
                    *psVar17 = 0;
                    psVar17[1] = 0;
                    psVar17[2] = 0;
                    psVar17[3] = 0;
                }
                iVar31 = iVar31 + 1;
                psVar17 = psVar17 + 0x248;
            } while (iVar31 < (int)DAT_UnitsState::instance.maxUnitCount);
        }
        iVar31 = 1;
        if (1 < DAT_BuildingsState::instance.maxBuildingsCount) {
            psVar17 = &DAT_BuildingsState::instance.buildings[1].surfaceAreaUnk;
            do {
                *psVar17 = 0;
                iVar31 = iVar31 + 1;
                psVar17 = psVar17 + 0x196;
            } while (iVar31 < DAT_BuildingsState::instance.maxBuildingsCount);
        }
        while ((local_1c < iVar28
            && ((MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::renderUnits, this)(),
                local_1c < viewportWidth
                    || ((DAT_TileMapState::instance.LogicLayer[this->screenPointToTileNumber[_zoomOffset + iVar2]]
                            & 0x30)
                        == 0))))) {
            _vpWidthPlus1 = _viewportHeight + 1;
            DAT_RenderMap_DrawSomeX::instance = this->viewportState.unknownScreenXRelated;
            iVar31 = _zoomOffset;
            if (_vpWidthPlus1_1 == _vpWidthPlus1) {
                DAT_RenderMap_DrawSomeX::instance = this->viewportState.unknownScreenXRelated + 0x10;
                _vpWidthPlus1 = _viewportHeight;
            }
            for (; iVar31 < _vpWidthPlus1; iVar31 = iVar31 + 1) {
                iVar16 = this->screenPointToTileNumber[iVar31 + iVar2 + -8];
                DAT_00ed3148::instance = DAT_TileMapState::instance.LogicLayer[iVar16];
                if ((DAT_00ed3148::instance & 0x30) == 0) {
                    /*
                      draw every tile
                     */

                    DAT_GmImageAddressToBeRendered::instance = (uint)DAT_TileMapState::instance.GfxLayer[iVar16];
                    if ((iVar31 < 2) || (bVar13 = true, _vpWidthPlus1 + -2 <= iVar31)) {
                        bVar13 = false;
                    }
                    if (this->DAT_MapEditorDisplayLayer != 0) {
                        if (this->DAT_MapEditorDisplayLayer == 1) {
                            _displayLayerLogicalValue
                                = (uint)(short)DAT_TileMapState::instance.PathConnectionLayer[iVar16];
                        } else if (this->DAT_MapEditorDisplayLayer == 2) {
                            _displayLayerLogicalValue = (uint)(char)DAT_TileMapState::instance.PathLinkageLayer[iVar16];
                        }
                        if (_displayLayerLogicalValue != 0) {
                            if (this->DAT_MapEditorDisplayLayer == 2) {
                                _displayLayerLogicalValue = 0xff - (_displayLayerLogicalValue & 0xff);
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
                                if (0xff < (int)_displayLayerLogicalValue) {
                                    _displayLayerLogicalValue = _displayLayerLogicalValue - 0x100;
                                }
                                DAT_GmImageAddressToBeRendered::instance
                                    = GMTotalPicturesProcessed::instance[0x26] + 0x40 + _displayLayerLogicalValue;
                            } else {
                                _displayLayerLogicalValue = _displayLayerLogicalValue & 0x3f;
                                DAT_GmImageAddressToBeRendered::instance
                                    = GMTotalPicturesProcessed::instance[0x26] + _displayLayerLogicalValue;
                            }
                        }
                    }
                    _yOffset_01 = GMTotalPicturesProcessed::instance[0x9d];
                    local_58 = (uint)DAT_TileMapState::instance.EntityLayer[iVar16];
                    iVar23 = (int)DAT_TileMapState::instance.OrganismLayer[iVar16];
                    local_2c = 0;
                    DAT_00ed3154::instance = 0;
                    if ((DAT_00ed3148::instance & 0xa0108001) == 0) {
                    LAB_004e97e2:
                        uVar32 = (uint)DAT_TileMapState::instance.HeightLayer[iVar16];
                        if (((DAT_00ed3148::instance & 0x200) != 0)
                            && ((DAT_TileMapState::instance.MiscDisplayLayer[iVar16] & 0x3c0) != 0)) {
                            uVar32 = uVar32 - 8;
                        }
                        DAT_RenderMap_YOffset::instance = DAT_TileMapState::instance.heightBasedScreenYOffset[uVar32];
                        if (((DAT_TileMapState::instance.MiscDisplayLayer[iVar16] & 0x20) == 0)
                            || (DAT_TileMapState::instance.field93_0x5548c8 != 0)) {
                            DAT_00ed3154::instance = 0;
                        } else {
                            DAT_00ed3154::instance = 0x5a;
                        }
                        DAT_00ed3170::instance = (uint)DAT_TileMapState::instance.ShowHiLayer[iVar16];
                    } else if ((DAT_00ed3148::instance & 1) == 0) {
                        if ((DAT_00ed3148::instance & 0x100000) == 0) {
                            if (DAT_00ed3148::instance != 0xa0008000)
                                goto LAB_004e97e2;
                            DAT_RenderMap_YOffset::instance
                                = DAT_TileMapState::instance
                                      .heightBasedScreenYOffset[DAT_TileMapState::instance.HeightLayer[iVar16]];
                            DAT_00ed3170::instance = (uint)DAT_TileMapState::instance.ShowHiLayer[iVar16];
                            bVar15 = (byte)DAT_TileMapState::instance.RandomLayer[iVar16];
                            bVar19 = bVar15 & 7;
                            if (this->field55_0x18b764 != 0) {
                                DAT_TileMapState::instance.WallGFXLayer[iVar16]
                                    = DAT_TileMapState::instance.WallGFXLayer[iVar16] + 1;
                            }
                            DAT_00ed314c::instance = (uint)DAT_TileMapState::instance.WallGFXLayer[iVar16];
                            if ((bVar15 & 7) == 0) {
                                if (511 < DAT_00ed314c::instance) {
                                    DAT_TileMapState::instance.WallGFXLayer[iVar16] = 0;
                                    DAT_00ed314c::instance = 0;
                                }
                                DAT_GmImageAddressToBeRendered::instance
                                    = (int)(char)
                                          DAT_MapRenderDefinedData::instance.field615_0x724[DAT_00ed314c::instance]
                                    + (uint)DAT_TileMapState::instance.GfxLayer[iVar16];
                            } else {
                                if (bVar19 == 1) {
                                    if (0x1fe < DAT_00ed314c::instance) {
                                        DAT_TileMapState::instance.WallGFXLayer[iVar16] = 0;
                                        DAT_00ed314c::instance = 0;
                                    }
                                    bVar15 = DAT_MapRenderDefinedData::instance.field616_0x924[DAT_00ed314c::instance];
                                } else {
                                    if ((bVar19 != 4) && (bVar19 != 5)) {
                                        if (0x7e < DAT_00ed314c::instance) {
                                            DAT_TileMapState::instance.WallGFXLayer[iVar16] = 0;
                                            DAT_00ed314c::instance = 0;
                                        }
                                        DAT_GmImageAddressToBeRendered::instance
                                            = (int)(char)DAT_MapRenderDefinedData::instance
                                                  .field617_0xb24[DAT_00ed314c::instance]
                                            + (uint)DAT_TileMapState::instance.GfxLayer[iVar16];
                                        goto LAB_004e9845;
                                    }
                                    if (0xfe < DAT_00ed314c::instance) {
                                        DAT_TileMapState::instance.WallGFXLayer[iVar16] = 0;
                                        DAT_00ed314c::instance = 0;
                                    }
                                    bVar15 = DAT_MapRenderDefinedData::instance.field617_0xb24[DAT_00ed314c::instance];
                                }
                                DAT_GmImageAddressToBeRendered::instance
                                    = (int)(char)bVar15 + (uint)DAT_TileMapState::instance.GfxLayer[iVar16];
                            }
                        } else {
                            DAT_00ed3170::instance = (uint)DAT_TileMapState::instance.ShowHiLayer[iVar16];
                            DAT_RenderMap_YOffset::instance
                                = DAT_TileMapState::instance
                                      .heightBasedScreenYOffset[DAT_TileMapState::instance.HeightLayer[iVar16]];
                            bVar15 = DAT_TileMapState::instance.Logic2Layer[iVar16];
                            if ((bVar15 & 200) == 0) {
                                if ((bVar15 & 7) == 0) {
                                    if ((bVar15 & 0x10) == 0) {
                                        if ((bVar15 & 0x20) != 0) {
                                            bVar15 = (byte)DAT_TileMapState::instance.MiscDisplayLayer[iVar16];
                                            DAT_00ed314c::instance
                                                = (uint)(DAT_TileMapState::instance.WallGFXLayer[iVar16] >> 10)
                                                + this->unknownCounterUntil_0x10 / 2;
                                            uVar32 = DAT_00ed314c::instance & 0x80000007;
                                            if ((int)uVar32 < 0) {
                                                uVar32 = (uVar32 - 1 | 0xfffffff8) + 1;
                                            }
                                            DAT_GmImageAddressToBeRendered::instance
                                                = uVar32 + DAT_TileMapState::instance.GfxLayer[iVar16];
                                            goto LAB_004e96a7;
                                        }
                                    } else {
                                        DAT_00ed3154::instance
                                            = -(uint)((DAT_TileMapState::instance.MiscDisplayLayer[iVar16] & 0x20) != 0)
                                            & 0x5a;
                                        DAT_00ed314c::instance = (uint)DAT_TileMapState::instance.WallGFXLayer[iVar16]
                                            + this->unknownCounterUntil_0x10;
                                        uVar32 = DAT_00ed314c::instance & 0x8000000f;
                                        if ((int)uVar32 < 0) {
                                            uVar32 = (uVar32 - 1 | 0xfffffff0) + 1;
                                        }
                                        DAT_GmImageAddressToBeRendered::instance
                                            = uVar32 + DAT_TileMapState::instance.GfxLayer[iVar16];
                                    }
                                } else {
                                    bVar15 = (byte)DAT_TileMapState::instance.MiscDisplayLayer[iVar16];
                                    DAT_00ed314c::instance = (uint)DAT_TileMapState::instance.WallGFXLayer[iVar16]
                                        + this->unknownCounterUntil_0x10 / 2;
                                    uVar32 = DAT_00ed314c::instance & 0x80000007;
                                    if ((int)uVar32 < 0) {
                                        uVar32 = (uVar32 - 1 | 0xfffffff8) + 1;
                                    }
                                    DAT_GmImageAddressToBeRendered::instance
                                        = uVar32 + DAT_TileMapState::instance.GfxLayer[iVar16];
                                LAB_004e96a7:
                                    DAT_00ed3154::instance = -(uint)((bVar15 & 0x20) != 0) & 0x5a;
                                }
                            } else {
                                DAT_00ed3154::instance
                                    = -(uint)((DAT_TileMapState::instance.MiscDisplayLayer[iVar16] & 0x20) != 0) & 0x5a;
                                DAT_00ed314c::instance = (uint)DAT_TileMapState::instance.WallGFXLayer[iVar16]
                                    + this->unknownCounterUntil_0x10;
                                uVar32 = DAT_00ed314c::instance & 0x8000000f;
                                if ((int)uVar32 < 0) {
                                    uVar32 = (uVar32 - 1 | 0xfffffff0) + 1;
                                }
                                DAT_GmImageAddressToBeRendered::instance
                                    = uVar32 + DAT_TileMapState::instance.GfxLayer[iVar16];
                            }
                            MACRO_CALL_MEMBER(
                                OpenSHC::Audio::SFX::SFXState_Func::notifyAmbientSoundEvent, DAT_SFXState::ptr)(7);
                            _yOffset_01 = GMTotalPicturesProcessed::instance[0x9d];
                        }
                    } else {
                        uVar32 = (uint)(short)DAT_TileMapState::instance.RandomLayer[iVar16];
                        INT_00ed315c::instance = uVar32 & 0x7f;
                        DAT_00ed314c::instance = uVar32 & 0xf;
                        DAT_RenderMap_YOffset::instance = 0;
                        DAT_00ed3170::instance = 8;
                        if ((DAT_TileMapState::instance.Logic2Layer[iVar16] & 8) == 0) {
                            uVar10 = DAT_TileMapState::instance.MiscDisplayLayer[iVar16];
                            if ((char)uVar10 < '\0') {
                                DAT_GmImageAddressToBeRendered::instance
                                    = (uint)DAT_TileMapState::instance.GfxLayer[iVar16]
                                    + DAT_MapRenderDefinedData::instance.field205_0x4dc
                                          [(int)(this->unknownCounterUntil_0x24 + DAT_00ed314c::instance / 2) % 0xc];
                            } else if ((uVar10 & 0x40) == 0) {
                                if ((uVar10 & 0x100) == 0) {
                                    if ((uVar10 & 0x200) == 0) {
                                        DAT_00ed314c::instance = uVar32 & 7;
                                        piVar21 = this->landscapeSeaWhiteCapsAnimationFrames;
                                        _yOffset_01 = 9;
                                        do {
                                            if (iVar16 == piVar21[-60]) {
                                                local_2c = *piVar21 + 1 + (uVar32 & 3) * 8;
                                            }
                                            if (iVar16 == piVar21[-0x3b]) {
                                                local_2c = piVar21[1] + 1 + (uVar32 & 3) * 8;
                                            }
                                            if (iVar16 == piVar21[-0x3a]) {
                                                local_2c = piVar21[2] + 1 + (uVar32 & 3) * 8;
                                            }
                                            if (iVar16 == piVar21[-0x39]) {
                                                local_2c = piVar21[3] + 1 + (uVar32 & 3) * 8;
                                            }
                                            if (iVar16 == piVar21[-0x38]) {
                                                local_2c = piVar21[4] + 1 + (uVar32 & 3) * 8;
                                            }
                                            piVar21 = piVar21 + 5;
                                            _yOffset_01 = _yOffset_01 + -1;
                                        } while (_yOffset_01 != 0);
                                    }
                                } else {
                                    DAT_GmImageAddressToBeRendered::instance
                                        = (uint)DAT_TileMapState::instance.GfxLayer[iVar16]
                                        + DAT_MapRenderDefinedData::instance
                                                .field614_0x6a4[this->unknownCounterUntil_0x20]
                                            * 0x22;
                                }
                            } else {
                                uVar32 = (uint)DAT_TileMapState::instance.GfxLayer[iVar16];
                                if (uVar32 == GMTotalPicturesProcessed::instance[0xa6] + 0x5dcU) {
                                    uVar29 = this->unknownCounterUntil_0x24 + INT_00ed315c::instance & 0x8000001f;
                                    if ((int)uVar29 < 0) {
                                        uVar29 = (uVar29 - 1 | 0xffffffe0) + 1;
                                    }
                                    _yOffset_01 = (int)uVar29 / 6 + ((int)uVar29 >> 0x1f);
                                    if ((int)uVar29 < 0x12) {
                                        DAT_GmImageAddressToBeRendered::instance
                                            = uVar32 + (_yOffset_01 - ((int)uVar29 >> 0x1f)) * -6 + uVar29;
                                    } else {
                                    LAB_004e941f:
                                        _yOffset_01 = (_yOffset_01 >> 1) - (_yOffset_01 >> 0x1f);
                                    LAB_004e9428:
                                        DAT_GmImageAddressToBeRendered::instance
                                            = *(int*)((int)DAT_MapRenderDefinedData::ptr
                                                  + (uVar29 + _yOffset_01 * -0xc) * 4 + 0x4dc)
                                            + 0x5d0 + GMTotalPicturesProcessed::instance[0xa6];
                                    }
                                } else if (uVar32 == GMTotalPicturesProcessed::instance[0xa6] + 0x5e2U) {
                                    uVar29 = this->unknownCounterUntil_0x24 + INT_00ed315c::instance & 0x8000001f;
                                    if ((int)uVar29 < 0) {
                                        uVar29 = (uVar29 - 1 | 0xffffffe0) + 1;
                                    }
                                    _yOffset_01 = (int)uVar29 / 0xc;
                                    if (0x11 < (int)uVar29)
                                        goto LAB_004e9428;
                                    DAT_GmImageAddressToBeRendered::instance = uVar32 + _yOffset_01 * -0xc + uVar29;
                                } else if (uVar32 == GMTotalPicturesProcessed::instance[0xa6] + 0x5eeU) {
                                    uVar29 = this->unknownCounterUntil_0x24 + INT_00ed315c::instance & 0x8000001f;
                                    if ((int)uVar29 < 0) {
                                        uVar29 = (uVar29 - 1 | 0xffffffe0) + 1;
                                    }
                                    if (0x11 < (int)uVar29) {
                                        _yOffset_01 = (int)uVar29 / 6 + ((int)uVar29 >> 0x1f);
                                        goto LAB_004e941f;
                                    }
                                    DAT_GmImageAddressToBeRendered::instance
                                        = uVar32 + ((int)uVar29 / 0x12) * -0x12 + uVar29;
                                }
                            }
                        } else {
                            DAT_00ed3154::instance
                                = -(uint)((DAT_TileMapState::instance.MiscDisplayLayer[iVar16] & 0x20) != 0) & 0x5a;
                            DAT_00ed314c::instance = this->unknownCounterUntil_0x10 + DAT_00ed314c::instance;
                            if (0xf < (int)DAT_00ed314c::instance) {
                                DAT_00ed314c::instance = DAT_00ed314c::instance - 0x10;
                            }
                            DAT_GmImageAddressToBeRendered::instance
                                = DAT_TileMapState::instance.GfxLayer[iVar16] + DAT_00ed314c::instance;
                        }
                        MACRO_CALL_MEMBER(
                            OpenSHC::Audio::SFX::SFXState_Func::notifyAmbientSoundEvent, DAT_SFXState::ptr)(2);
                        _yOffset_01 = GMTotalPicturesProcessed::instance[0x9d];
                    }
                LAB_004e9845:
                    local_54 = (uint)DAT_TileMapState::instance.BuildingLayer[iVar16];
                    if (_flatView) {
                        DAT_RenderMap_YOffset::instance = 8;
                        if (this->DAT_MapEditorDisplayLayer == 0) {
                            uVar32 = (uint)(short)DAT_TileMapState::instance.RandomLayer[iVar16];
                            DAT_00ed314c::instance = uVar32 & 0xf;
                            DAT_00ed3170::instance = 0;
                            DAT_00ed3154::instance = 0;
                            if ((local_54 == 0) || ((DAT_00ed3148::instance & 0x40000000) != 0)) {
                                if ((DAT_00ed3148::instance & 0x100) == 0) {
                                    if ((DAT_00ed3148::instance & 0x80) != 0) {
                                        _yOffset_01 = (int)DAT_TileMapState::instance.OrganismLayer[iVar16];
                                        if (_yOffset_01 < 2000) {
                                            _yOffset_01 = MACRO_CALL_MEMBER(
                                                OpenSHC::Map::LandscapeState_Func::getRandomRockImageOffset,
                                                DAT_LandscapeState::ptr)((uVar32 & 3) + 1);
                                            DAT_GmImageAddressToBeRendered::instance
                                                = _yOffset_01 + -1 + GMTotalPicturesProcessed::instance[0x38];
                                        } else {
                                            _yOffset_01 = _yOffset_01 * 0x20;
                                            if (1 < *(short*)((int)&DAT_LandscapeState::instance.trees[0x636]
                                                                  .appleTreeColorVariation
                                                    + _yOffset_01 + 2)) {
                                                iVar26 = MACRO_CALL_MEMBER(
                                                    OpenSHC::Map::LandscapeState_Func::getRandomRockImageOffset,
                                                    DAT_LandscapeState::ptr)((uVar32 & 3) + 1);
                                                DAT_GmImageAddressToBeRendered::instance = iVar26 + -1
                                                    + GMTotalPicturesProcessed::instance[*(
                                                        short*)((int)&DAT_LandscapeState::instance.trees[0x636]
                                                                    .animationFrameUnk
                                                        + _yOffset_01 + 2)];
                                            }
                                        }
                                    }
                                } else if ((DAT_00ed3148::instance & 0x800) == 0) {
                                    if ((DAT_00ed3148::instance & 0x200) == 0) {
                                        if (DAT_TileMapState::instance.DamageLayer[iVar16] != 0) {
                                            DAT_00ed3148::instance = DAT_00ed3148::instance & 1;
                                            DAT_GmImageAddressToBeRendered::instance
                                                = (uVar32 & 1) + 0x2c + _yOffset_01;
                                        }
                                    } else {
                                        DAT_00ed3148::instance = DAT_00ed3148::instance & 1;
                                        if (DAT_TileMapState::instance.DamageLayer[iVar16] == 0) {
                                            DAT_GmImageAddressToBeRendered::instance
                                                = (uVar32 & 3) + 0x24 + _yOffset_01;
                                        } else {
                                            DAT_GmImageAddressToBeRendered::instance
                                                = (uVar32 & 1) + 0x2c + _yOffset_01;
                                        }
                                    }
                                } else {
                                    DAT_00ed3148::instance = DAT_00ed3148::instance & 1;
                                    if ((DAT_GmImageAddressToBeRendered::instance
                                            == GMTotalPicturesProcessed::instance[0xc] + 0x86U)
                                        || (DAT_GmImageAddressToBeRendered::instance
                                            == GMTotalPicturesProcessed::instance[0xc] + 0x88U)) {
                                        DAT_GmImageAddressToBeRendered::instance = _yOffset_01 + 0x2a;
                                    } else {
                                        DAT_GmImageAddressToBeRendered::instance = _yOffset_01 + 0x28;
                                    }
                                }
                            } else {
                                BVar8 = DAT_BuildingsState::instance.buildings[local_54].buildingType;
                                iVar26 = DAT_MapRenderDefinedData::instance.BuildingRenderSomeTypeArray[(short)BVar8];
                                if (iVar26 == 3) {
                                    uVar32 = (uint)((DAT_TileMapState::instance.MiscDisplayLayer[iVar16] & 4) != 0);
                                    if (BVar8 == OpenSHC::Map::Buildings::BT_WOODCUTTERSHUT) {
                                        DAT_GmImageAddressToBeRendered::instance = _yOffset_01 + 0x18 + uVar32;
                                    } else if (BVar8 == OpenSHC::Map::Buildings::BT_HUNTERSHUT) {
                                        DAT_GmImageAddressToBeRendered::instance = _yOffset_01 + 0x1a + uVar32;
                                    } else if (BVar8 == OpenSHC::Map::Buildings::BT_DAIRYFARM) {
                                        DAT_GmImageAddressToBeRendered::instance = _yOffset_01 + 0x1c + uVar32;
                                    } else {
                                        DAT_GmImageAddressToBeRendered::instance = _yOffset_01 + 0x1e + uVar32;
                                    }
                                } else if (-1 < iVar26) {
                                    DAT_GmImageAddressToBeRendered::instance
                                        = (uVar32 & 3) + _yOffset_01 + ((local_54 & 1) + iVar26 * 2) * 4;
                                }
                            }
                        } else {
                            DAT_00ed3170::instance = 0;
                            DAT_00ed3154::instance = 0;
                        }
                    }
                    DAT_RenderMap_ImageID::instance = (uint)DAT_TileMapState::instance.ConstructionGFXLayer[iVar16];
                    bVar12 = false;
                    bVar14 = false;
                    if (DAT_RenderMap_ImageID::instance == 0) {
                        if ((((DAT_00ed3148::instance & 0x4000) != 0)
                                && (DAT_TileMapState::instance.field159_0x5549b8 != 0))
                            && ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                                || (_yOffset_01
                                    = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile,
                                        DAT_TileMapState::ptr)(iVar16),
                                    DAT_GameState::instance.mapAndTime
                                            .playerTeams[DAT_TileMapState::instance.moats[_yOffset_01].owner]
                                        == DAT_GameState::instance.mapAndTime
                                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID])))) {
                            DAT_RenderMap_ImageID::instance = 0x39;
                            goto LAB_004e9b3c;
                        }
                    } else if ((DAT_TileMapState::instance.buildingPlacementFail == FALSE)
                        || ((DAT_TileMapState::instance.MiscDisplayLayer[iVar16] & 0x8000) != 0)) {
                        DAT_GmImageAddressToBeRendered::instance = DAT_RenderMap_ImageID::instance;
                        if (((DAT_00ed3148::instance & 0x100) != 0) && (!_flatView)) {
                            DAT_RenderMap_YOffset::instance
                                = DAT_TileMapState::instance
                                      .heightBasedScreenYOffset[DAT_TileMapState::instance.DefaultHeightLayer[iVar16]];
                        }
                    } else {
                    LAB_004e9b3c:
                        bVar12 = true;
                        bVar14 = true;
                    }
                    local_60 = (int)(short)DAT_TileMapState::instance.UnitLayer[iVar16];
                    if (((local_60 != 0) && (local_60 == DAT_UnitsState::instance.lastSelectedUnitID))
                        && (DAT_MenuModalComposition1::instance.activeModalDialogID
                            == OpenSHC::UI::Enums::MMT_DEBUG_DATA_UNIT_DATA)) {
                        DAT_GmImageAddressToBeRendered::instance
                            = ((byte)DAT_UnitsState::instance.units[local_60].moveDelay & 0x3f)
                            + GMTotalPicturesProcessed::instance[0x26];
                    }
                    if ((((DAT_00ed3148::instance & 8) != 0)
                            && ((DAT_TileMapState::instance.MiscDisplayLayer[iVar16] & 0x2000) == 0))
                        && (!_flatView)) {
                        DAT_RenderMap_YOffset::instance
                            = DAT_TileMapState::instance
                                  .heightBasedScreenYOffset[DAT_TileMapState::instance.HeightLayer[iVar16] + 4];
                    }
                    if (local_54 != 0) {
                        uVar9 = *this->viewportState.ptrColor;
                        *this->viewportState.ptrColor = COL_MAGENTA::instance.shortValue;
                    }
                    if (((DAT_00ed3170::instance != 0xff) && (bVar13))
                        && (MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderTerrainTilesCenterPiece)(), bVar12)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS,
                            (int)((int)(DAT_RenderMap_ImageID::instance)),
                            (int)((int)(DAT_RenderMap_DrawSomeX::instance)),
                            (int)((int)((DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance)
                                + DAT_RenderMap_DrawSomeY::instance)),
                            0x18);
                    }
                    if ((((DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance].direction != 0)
                             && (local_54 == 0))
                            && (bVar13))
                        && (!bVar12)) {
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
                            (int)((int)(((DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance) - _yOffset_01)
                                + DAT_RenderMap_DrawSomeY::instance)),
                            (int)((int)((char)DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance]
                                    .buildingWidth)),
                            _yOffset_01 + 7,
                            (ushort*)((int)(

                                (DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance] + 0x200
                                    + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))));
                    }
                    if (local_2c != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ANIM_WHITECAPS, local_2c,
                            (DAT_RenderMap_DrawSomeX::instance
                                - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[0xad].originX)
                                + 0xf,
                            (DAT_RenderMap_DrawSomeY::instance
                                - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[0xad].originY)
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
                    if (((DAT_00ed3148::instance & 0x201) == 0) && (local_54 == 0)) {
                        uVar10 = DAT_TileMapState::instance.MiscDisplayLayer[iVar16];
                        if (((uVar10 & 0x3c0) != 0)
                            && ((((DAT_RenderMap_ImageID::instance == 0
                                      || (((DAT_00ed3148::instance & 0x4000) != 0
                                          && (DAT_TileMapState::instance.field159_0x5549b8 != 0))))
                                     && ((DAT_00ed3148::instance & 0x30) == 0))
                                && (!_flatView)))) {
                            uVar32 = (uint)DAT_TileMapState::instance.WallGFXLayer[iVar16];
                            DAT_GmImageAddressToBeRendered::instance
                                = (uint)DAT_TileMapState::instance.AlphaGFXLayer[iVar16];
                            iVar26 = uVar32 - DAT_TileMapState::instance.heightBasedScreenYOffset[uVar32];
                            _yOffset_01 = DAT_RenderMap_DrawSomeX::instance;
                            if ((uVar10 & 0x40) == 0) {
                                if ((char)uVar10 < '\0') {
                                    _yOffset_01 = (int)DAT_GMImageHeaders::instance
                                                      .imh[DAT_GmImageAddressToBeRendered::instance
                                                          + GMTotalPicturesProcessed::instance[0x36] + -1]
                                                      .height;
                                    /*
                                      renders wall connections
                                     */

                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                          renderFunctionResponsibleForManyGameObjects,
                                        DAT_TextureRenderCoreObject::ptr)(DAT_RenderMap_DrawSomeX::instance,
                                        (int)((int)(((iVar26 - uVar32) - _yOffset_01) + DAT_00ed3154::instance + 0x62
                                            + DAT_RenderMap_DrawSomeY::instance)),
                                        (int)((int)(DAT_GMImageHeaders::instance
                                                .imh[DAT_GmImageAddressToBeRendered::instance
                                                    + GMTotalPicturesProcessed::instance[0x36] + -1]
                                                .width)),
                                        _yOffset_01 - iVar26,
                                        (ushort*)((int)(

                                            (DAT_GMImageOffsets::instance[GMTotalPicturesProcessed::instance[0x36] + -1
                                                 + DAT_GmImageAddressToBeRendered::instance]
                                                + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))));
                                    goto LAB_004e9e36;
                                }
                                if ((uVar10 & 0x100) == 0) {
                                    if ((uVar10 & 0x200) == 0)
                                        goto LAB_004e9e36;
                                    iVar26 = (iVar26 - uVar32) + DAT_00ed3154::instance + -1;
                                } else {
                                    iVar26 = (iVar26 - uVar32) + DAT_00ed3154::instance;
                                    _yOffset_01 = DAT_RenderMap_DrawSomeX::instance + 0x10;
                                }
                            } else {
                                iVar26 = (iVar26 - uVar32) + DAT_00ed3154::instance + 7;
                            }
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS,
                                (int)((int)(DAT_GmImageAddressToBeRendered::instance)), _yOffset_01,
                                (int)((int)(iVar26 + DAT_RenderMap_DrawSomeY::instance)));
                        }
                    }
                LAB_004e9e36:
                    _yOffset_01 = DAT_RenderMap_YOffset::instance;
                    uVar32 = (uint)DAT_TileMapState::instance.FloatingLayer[iVar16];
                    if (uVar32 != 0) {
                        if ((DAT_TileMapState::instance.refreshRelatedOne != 0) && (!_flatView)) {
                            if ((DAT_TileMapState::instance.LogicLayer[iVar16] & 0x10000000U) == 0) {
                                if ((DAT_TileMapState::instance.LogicLayer[iVar16] & 0x100U) != 0) {
                                    local_54 = (uint)DAT_TileMapState::instance.BuildingLayer[iVar16];
                                    if (local_54 == 0) {
                                        _yOffset_01 = DAT_RenderMap_YOffset::instance + 4;
                                    } else if (DAT_BuildingsState::instance.buildings[local_54].buildingType
                                        == OpenSHC::Map::Buildings::BT_WOODGATE1) {
                                        _yOffset_01 = DAT_RenderMap_YOffset::instance + 6;
                                    } else {
                                        _yOffset_01 = DAT_RenderMap_YOffset::instance + 0x14;
                                    }
                                }
                            } else {
                                local_54 = (uint)DAT_TileMapState::instance.BuildingLayer[iVar16];
                                iVar26 = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                    DAT_BuildingsState::ptr)(local_54);
                                _yOffset_01 = _yOffset_01 + iVar26;
                            }
                        }
                        do {
                            uVar29 = this->floatersArray[uVar32].variation;
                            if ((uVar29 & 2) != 0) {
                                if ((DAT_TileMapState::instance.MiscDisplayLayer[iVar16] & 0x10) == 0) {
                                    if ((uVar29 & 4) != 0) {
                                        DAT_RenderedUnitOwner::instance = ~-(uint)((uVar29 & 0x10) != 0)
                                            & DAT_GameSynchronyState::instance.currentPlayerSlotID;
                                        DAT_CurrentlyRenderedSpriteID::instance = this->floatersArray[uVar32].gmID;
                                        uVar29 = this->floatersArray[uVar32].variation;
                                    }
                                    if ((uVar29 & 0x20) == 0) {
                                        if ((uVar29 & 0xffff0000) == 0) {
                                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                DAT_TextureRenderCoreObject::ptr)((eGM)this->floatersArray[uVar32].gmID,
                                                this->floatersArray[uVar32].imageID,
                                                (int)((int)(this->floatersArray[uVar32].originX
                                                    + DAT_RenderMap_DrawSomeX::instance)),
                                                (int)((int)((this->floatersArray[uVar32].originY - _yOffset_01)
                                                    + DAT_RenderMap_DrawSomeY::instance)));
                                        } else {
                                            MACRO_CALL_MEMBER(
                                                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                                DAT_TextureRenderCoreObject::ptr)(
                                                (GmID)this->floatersArray[uVar32].gmID,
                                                this->floatersArray[uVar32].imageID,
                                                (int)((int)(this->floatersArray[uVar32].originX
                                                    + DAT_RenderMap_DrawSomeX::instance)),
                                                (int)((int)((this->floatersArray[uVar32].originY - _yOffset_01)
                                                    + DAT_RenderMap_DrawSomeY::instance)),
                                                (int)((int)(uVar29 >> 0x10)));
                                        }
                                    } else {
                                        iVar26 = this->floatersArray[uVar32].imageID;
                                        GVar11 = (GmID)this->floatersArray[uVar32].gmID;
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                            DAT_TextureRenderCoreObject::ptr)((GmID)GVar11, iVar26,
                                            (int)((int)(this->floatersArray[uVar32].originX
                                                + DAT_RenderMap_DrawSomeX::instance)),
                                            (int)((int)((this->floatersArray[uVar32].originY - _yOffset_01)
                                                + DAT_RenderMap_DrawSomeY::instance)),
                                            GVar11, ((int)uVar29 >> 0x10) + iVar26, 0);
                                    }
                                } else {
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::Rendering::ViewportRenderState_Func::scheduleUnitForBatchedRendering,
                                        this)(0,
                                        this->floatersArray[uVar32].originX + DAT_RenderMap_DrawSomeX::instance,
                                        (this->floatersArray[uVar32].originY - _yOffset_01)
                                            + DAT_RenderMap_DrawSomeY::instance,
                                        (undefined4)((int)(this->floatersArray[uVar32].imageID)),
                                        (undefined4)((int)(uVar29)),
                                        (undefined4)((int)(this->floatersArray[uVar32].gmID)), 0);
                                }
                            }
                            uVar32 = this->floatersArray[uVar32].id;
                        } while (uVar32 != 0);
                    }
                    _yOffset_01 = 0;
                    if (local_58 != 0) {
                        while ((iVar26 = DAT_RenderMap_YOffset::instance, _yOffset_01 = _yOffset_01 + 1,
                            _yOffset_01 < 10 && (DAT_EntityState::instance.entityArray[local_58].logicalState != 0))) {
                            if (((DAT_EntityState::instance.entityArray[local_58].graphicType2 != 0)
                                    && (((EVar3 = DAT_EntityState::instance.entityArray[local_58].entityType,
                                             EVar3 == OpenSHC::Map::Entities::EntityTypeInt__ET_CROW
                                                 || (EVar3 == OpenSHC::Map::Entities::ET_SEAGULLUnk))
                                        || (EVar3 == OpenSHC::Map::Entities::ET_COW_FLYING))))
                                && (DAT_EntityState::instance.entityArray[local_58].imageID != 0)) {
                                DAT_RenderedUnitOwner::instance
                                    = DAT_EntityState::instance.entityArray[local_58].colorUnk;
                                DAT_CurrentlyRenderedSpriteID::instance
                                    = (GmIDInt)DAT_EntityState::instance.entityArray[local_58].gmID;
                                if ((DAT_TileMapState::instance.LogicLayer[iVar16] & 0x10000000U) == 0) {
                                    if ((DAT_TileMapState::instance.LogicLayer[iVar16] & 0x100U) != 0) {
                                        local_54 = (uint)DAT_TileMapState::instance.BuildingLayer[iVar16];
                                        if (local_54 == 0) {
                                            iVar26 = DAT_RenderMap_YOffset::instance + 4;
                                        } else {
                                            iVar26 = DAT_RenderMap_YOffset::instance + 0x14;
                                        }
                                    }
                                } else {
                                    local_54 = (uint)DAT_TileMapState::instance.BuildingLayer[iVar16];
                                    iVar18 = MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                        DAT_BuildingsState::ptr)(local_54);
                                    iVar26 = iVar26 + iVar18;
                                }
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Rendering::ViewportRenderState_Func::scheduleUnitForBatchedRendering,
                                    this)(0xffffffff,
                                    ((int)DAT_EntityState::instance.entityArray[local_58].x1
                                        - (int)DAT_EntityState::instance.entityArray[local_58].originX)
                                        + DAT_RenderMap_DrawSomeX::instance,
                                    (((int)DAT_EntityState::instance.entityArray[local_58].y1
                                         - (int)DAT_EntityState::instance.entityArray[local_58].originY)
                                        - iVar26)
                                        + DAT_RenderMap_DrawSomeY::instance,
                                    (undefined4)((int)((int)DAT_EntityState::instance.entityArray[local_58].imageID)),
                                    0x14, 0, 0);
                            }
                            iVar26 = (int)DAT_EntityState::instance.entityArray[local_58].nextEntityOnThisTileByID;
                            if (((local_58 == iVar26) || (DAT_GameSynchronyState::instance.syncStatus != 0))
                                || (local_58 = iVar26, iVar26 == 0))
                                break;
                        }
                    }
                    local_58 = (uint)DAT_TileMapState::instance.EntityLayer[iVar16];
                    if (((local_54 != 0)
                            && (DAT_BuildingsState::instance.buildings[local_54].buildingType
                                == OpenSHC::Map::Buildings::BT_DRAWBRIDGE))
                        && ((!_flatView
                            && ((DAT_TileMapState::instance.refreshRelatedOne != 0
                                && ((DAT_TileMapState::instance.MiscDisplayLayer[iVar16] & 0xc) == 4)))))) {
                        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::renderGmOverlayBuilding2, this)(
                            local_54, (int)((int)(DAT_RenderMap_DrawSomeX::instance)),
                            (int)((int)(DAT_00ed3154::instance + DAT_RenderMap_DrawSomeY::instance)), iVar16);
                    }
                    /*
                      ------ BEGIN RENDER UNITS ------
                     */

                    if ((local_60 != 0)
                        && (MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::UnitsState_Func::triggerDesyncIfTileUnitLinkageInvalid,
                                DAT_UnitsState::ptr)(iVar16),
                            0 < local_60)) {
                        while (_yOffset_01 = DAT_RenderMap_DrawSomeX::instance,
                            DAT_UnitsState::instance.units[local_60].logicalState
                                != OpenSHC::Map::Units::ULS_INVISIBLE) {
                            DAT_CurrentlyRenderedSpriteID::instance
                                = (GmIDInt)DAT_UnitsState::instance.units[local_60].spriteID;
                            local_2c = 0;
                            if ((DAT_UnitsState::instance.units[local_60].unitType
                                    == OpenSHC::Map::Units::UT_A_ASSASSIN)
                                && (DAT_GameState::instance.mapAndTime
                                        .playerTeams[DAT_UnitsState::instance.units[local_60].owner]
                                    != DAT_GameState::instance.mapAndTime
                                        .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID])) {
                                iVar26 = DAT_UnitsState::instance.units[local_60].assassinsMicroDistanceToEnemyUnk;
                                if ((iVar26 < 160)
                                    || ((UVar4 = DAT_UnitsState::instance.units[local_60].state.generic,
                                        UVar4 == OpenSHC::Map::Units::States::US_MELEE_ATTACK
                                            || (UVar4 == OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL)))) {
                                    if ((120 < iVar26)
                                        && ((DAT_GameSynchronyState::instance.currentGameMode
                                                != OpenSHC::Game::GM_SOLITARY
                                            || (DAT_UnitsState::instance.units[local_60].idleCounterUnk < 0x961)))) {
                                        local_2c = 0x10;
                                    }
                                    goto LAB_004ea2c6;
                                }
                                if ((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                                    && (0x960 < DAT_UnitsState::instance.units[local_60].idleCounterUnk))
                                    goto LAB_004ea2c6;
                            } else {
                            LAB_004ea2c6:
                                if (DAT_UnitsState::instance.units[local_60].field40_0x5a == 0) {
                                    DAT_RenderedUnitOwner::instance
                                        = DAT_UnitsState::instance.units[local_60].calculatedOwnerPlayerIndex;
                                } else {
                                    DAT_RenderedUnitOwner::instance = 9;
                                }
                                iVar18 = GMTotalPicturesProcessed::instance[DAT_CurrentlyRenderedSpriteID::instance];
                                iVar27 = DAT_UnitsState::instance.units[local_60].gfxNumber;
                                iVar26 = iVar27 + -1 + iVar18;
                                iVar25 = DAT_RenderMap_YOffset::instance;
                                if (DAT_TileMapState::instance.refreshRelatedOne != 0) {
                                    if (_flatView) {
                                        iVar25 = ((int)(char)DAT_UnitsState::instance.units[local_60].negativeHeight
                                                     - (int)DAT_UnitsState::instance.units[local_60].buildingHeight)
                                            + DAT_RenderMap_YOffset::instance;
                                    } else {
                                        iVar25 = (uint)(byte)DAT_UnitsState::instance.units[local_60].padding_0x83[0]
                                            + (int)DAT_UnitsState::instance.units[local_60].terrainOrClimbHeight;
                                    }
                                }
                                sVar30 = DAT_UnitsState::instance.units[local_60].orientationRelatedPositionX;
                                sVar20 = DAT_UnitsState::instance.units[local_60].orientationRelatedPositionY;
                                DAT_UnitsState::instance.units[local_60].field308_0x41c
                                    = sVar30 + -6 + DAT_RenderMap_DrawSomeX::instance;
                                sVar30 = ((short)DAT_UnitsState::instance.units[local_60].field41_0x5c
                                             - DAT_UnitsState::instance.units[local_60].field22_0x2a)
                                    + (short)_yOffset_01 + sVar30;
                                bVar15 = DAT_UnitsState::instance.units[local_60].negativeHeight;
                                DAT_UnitsState::instance.units[local_60].field309_0x420
                                    = (sVar20 - iVar25) + -0xc + DAT_RenderMap_DrawSomeY::instance;
                                sVar24 = (short)DAT_UnitsState::instance.units[local_60].unknownV;
                                sVar5 = DAT_UnitsState::instance.units[local_60].field58_0x84;
                                sVar6 = DAT_UnitsState::instance.units[local_60].buildingHeight;
                                DAT_UnitsState::instance.units[local_60].drawX = sVar30;
                                sVar20 = (((sVar5 - sVar6) - (short)iVar25) - sVar24)
                                    + (short)DAT_RenderMap_DrawSomeY::instance + (short)(char)bVar15 + sVar20;
                                sVar5 = DAT_GMImageHeaders::instance.imh[iVar18 + iVar27 + -1].width;
                                DAT_UnitsState::instance.units[local_60].drawY = sVar20;
                                DAT_UnitsState::instance.units[local_60].drawWidth = sVar5;
                                if (bVar15 == 0) {
                                    sVar24 = DAT_GMImageHeaders::instance.imh[iVar18 + iVar27 + -1].height;
                                } else {
                                    sVar24 = (sVar24 - (char)bVar15) + 8;
                                }
                                _yOffset_01 = DAT_UnitsState::instance.units[local_60].vanish;
                                DAT_UnitsState::instance.units[local_60].drawHeight1 = sVar24;
                                if (_yOffset_01 == 0) {
                                    _yOffset_01 = DAT_UnitsState::instance.units[local_60].field43_0x64;
                                    if (_yOffset_01 == 1) {
                                    LAB_004ea49b:
                                        _yOffset_01 = 1;
                                    } else if (_yOffset_01 == 2) {
                                        _yOffset_01 = 0;
                                    } else {
                                        if (((DAT_TileMapState::instance.MiscDisplayLayer[iVar16] & 0x10) == 0)
                                            || (DAT_UnitsState::instance.units[local_60].field43_0x64 == -1)) {
                                            if ((DAT_00ed3148::instance & 0x400) == 0) {
                                                if ((DAT_UnitsState::instance.units[local_60].unitType
                                                        == OpenSHC::Map::Units::UT_A_ASSASSIN)
                                                    && (_yOffset_01 = DAT_UnitsState::instance.units[local_60].imageID2,
                                                        _yOffset_01 != 0)) {
                                                    sVar24 = DAT_UnitsState::instance.units[local_60].field59_0x86;
                                                    if (sVar24 < 0) {
                                                        local_c = 0;
                                                    } else {
                                                        local_c = (uint)sVar24;
                                                    }
                                                    iVar27 = (0x20 - local_2c) / 3;
                                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                          renderUnitAnimationWithBlendingUnk,
                                                        DAT_TextureRenderCoreObject::ptr)((int)sVar30,
                                                        (int)((
                                                            int)(DAT_UnitsState::instance.units[local_60].field59_0x86
                                                            + sVar20)),
                                                        (int)((int)(sVar5)),
                                                        (int)((int)(DAT_UnitsState::instance.units[local_60].drawHeight1
                                                            - local_c)),
                                                        (byte*)((int)((
                                                            DAT_GMImageOffsets::instance[_yOffset_01 + -1 + iVar18]
                                                            + (int)DAT_TextureRenderCoreObject::instance
                                                                .gmProcessedImageData))),
                                                        (0x10 - iVar27) * 2);
                                                    sVar30 = DAT_UnitsState::instance.units[local_60].drawYOffset;
                                                    if (sVar30 != 0) {
                                                        sVar20 = DAT_UnitsState::instance.units[local_60].field59_0x86;
                                                        if (sVar20 < 0) {
                                                            _yOffset_01 = 0;
                                                        } else {
                                                            _yOffset_01 = (int)sVar20;
                                                        }
                                                        MACRO_CALL_MEMBER(
                                                            OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                renderUnitAnimationWithBlendingUnk,
                                                            DAT_TextureRenderCoreObject::ptr)(
                                                            (int)DAT_UnitsState::instance.units[local_60].drawX,
                                                            (int)((int)(sVar20
                                                                + DAT_UnitsState::instance.units[local_60].drawY)),
                                                            (int)((int)(DAT_UnitsState::instance.units[local_60]
                                                                    .drawWidth)),
                                                            DAT_UnitsState::instance.units[local_60].drawHeight1
                                                                - _yOffset_01,
                                                            (byte*)((int)((
                                                                DAT_GMImageOffsets::instance
                                                                    [GMTotalPicturesProcessed::instance
                                                                            [DAT_CurrentlyRenderedSpriteID::instance]
                                                                        + -1 + (int)sVar30]
                                                                + (int)DAT_TextureRenderCoreObject::instance
                                                                    .gmProcessedImageData))),
                                                            0x20 - iVar27);
                                                    }
                                                }
                                                uVar9 = *this->viewportState.ptrColor;
                                                *this->viewportState.ptrColor = COL_MAGENTA::instance.shortValue;
                                                bVar15 = DAT_UnitsState::instance.units[local_60]
                                                             .disappearFadeAlphaCountdown;
                                                if (bVar15 == 0) {
                                                    if (DAT_UnitsState::instance.units[local_60].graphicSize == 4) {
                                                        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::
                                                                              renderAssassinClimbingOverlay,
                                                            this)(local_60);
                                                    }
                                                    sVar30 = DAT_UnitsState::instance.units[local_60].field59_0x86;
                                                    if (sVar30 < 0) {
                                                        _yOffset_01 = 0;
                                                    } else {
                                                        _yOffset_01 = (int)sVar30;
                                                    }
                                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                          renderUnitAnimationUnk,
                                                        DAT_TextureRenderCoreObject::ptr)(
                                                        (int)DAT_UnitsState::instance.units[local_60].drawX,
                                                        (int)((int)(sVar30
                                                            + DAT_UnitsState::instance.units[local_60].drawY)),
                                                        (int)((
                                                            int)(DAT_UnitsState::instance.units[local_60].drawWidth)),
                                                        DAT_UnitsState::instance.units[local_60].drawHeight1
                                                            - _yOffset_01,
                                                        (byte*)((int)((DAT_GMImageOffsets::instance[iVar26]
                                                            + (int)DAT_TextureRenderCoreObject::instance
                                                                .gmProcessedImageData))));
                                                    sVar30 = DAT_UnitsState::instance.units[local_60].graphicSize;
                                                    if ((sVar30 != 4) && (1 < sVar30)) {
                                                        DAT_CurrentlyRenderedSpriteID::instance
                                                            = (GmIDInt)DAT_UnitsState::instance.units[local_60].gmIDUnk;
                                                        DAT_RenderedUnitOwner::instance
                                                            = (uint)DAT_UnitsState::instance.units[local_60]
                                                                  .displayColorPlayerID;
                                                        _yOffset_01
                                                            = DAT_UnitsState::instance.units[local_60].imageIDUnk;
                                                        if (0 < _yOffset_01) {
                                                            sVar30
                                                                = DAT_UnitsState::instance.units[local_60].field60_0x88;
                                                            if (sVar30 < 0) {
                                                                iVar26 = 0;
                                                            } else {
                                                                iVar26 = (int)sVar30;
                                                            }
                                                            MACRO_CALL_MEMBER(
                                                                OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                    renderUnitAnimationUnk,
                                                                DAT_TextureRenderCoreObject::ptr)(
                                                                (int)DAT_UnitsState::instance.units[local_60].drawX,
                                                                (int)((int)(sVar30
                                                                    + DAT_UnitsState::instance.units[local_60].drawY)),
                                                                (int)((int)(DAT_UnitsState::instance.units[local_60]
                                                                        .drawWidth)),
                                                                DAT_UnitsState::instance.units[local_60].drawHeight1
                                                                    - iVar26,
                                                                (byte*)((
                                                                    int)((DAT_GMImageSizes::instance
                                                                              [GMTotalPicturesProcessed::instance
                                                                                      [DAT_CurrentlyRenderedSpriteID::
                                                                                              instance]
                                                                                  + _yOffset_01 + 0x1c51f]
                                                                    + (int)DAT_TextureRenderCoreObject::instance
                                                                        .gmProcessedImageData))));
                                                        }
                                                    }
                                                    if (2 < DAT_UnitsState::instance.units[local_60].graphicSize) {
                                                        _yOffset_01 = DAT_UnitsState::instance.units[local_60].imageID2;
                                                        if (0 < _yOffset_01) {
                                                            sVar30
                                                                = DAT_UnitsState::instance.units[local_60].drawYOffset;
                                                            if (sVar30 < 0) {
                                                                iVar26 = 0;
                                                            } else {
                                                                iVar26 = (int)sVar30;
                                                            }
                                                            MACRO_CALL_MEMBER(
                                                                OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                    renderUnitAnimationUnk,
                                                                DAT_TextureRenderCoreObject::ptr)(
                                                                (int)DAT_UnitsState::instance.units[local_60].drawX,
                                                                (int)((int)(sVar30
                                                                    + DAT_UnitsState::instance.units[local_60].drawY)),
                                                                (int)((int)(DAT_UnitsState::instance.units[local_60]
                                                                        .drawWidth)),
                                                                DAT_UnitsState::instance.units[local_60].drawHeight1
                                                                    - iVar26,
                                                                (byte*)((
                                                                    int)((DAT_GMImageSizes::instance
                                                                              [GMTotalPicturesProcessed::instance
                                                                                      [DAT_CurrentlyRenderedSpriteID::
                                                                                              instance]
                                                                                  + _yOffset_01 + 0x1c51f]
                                                                    + (int)DAT_TextureRenderCoreObject::instance
                                                                        .gmProcessedImageData))));
                                                        }
                                                        if (DAT_GameSynchronyState::instance.currentGameMode
                                                            != OpenSHC::Game::GM_SOLITARY) {
                                                            UVar7 = DAT_UnitsState::instance.units[local_60].unitType;
                                                            if ((UVar7 == OpenSHC::Map::Units::UT_S_TOWER)
                                                                && (DAT_UnitsState::instance.units[local_60].dying
                                                                    == 0)) {
                                                                _yOffset_01
                                                                    = (int)DAT_UnitsState::instance.units[local_60]
                                                                          .drawX;
                                                                iVar26 = (int)DAT_UnitsState::instance.units[local_60]
                                                                             .drawY;
                                                                switch (DAT_UnitsState::instance.units[local_60]
                                                                        .facingDirectionMapOrientationCorrected) {
                                                                case 0:
                                                                    _yOffset_01 = _yOffset_01 + 0x22;
                                                                    break;
                                                                case 1:
                                                                    _yOffset_01 = _yOffset_01 + 0x2f;
                                                                    iVar26 = iVar26 + -0xc;
                                                                    break;
                                                                case 2:
                                                                    _yOffset_01 = _yOffset_01 + 0x4b;
                                                                    iVar26 = iVar26 + -0x13;
                                                                    break;
                                                                case 3:
                                                                    _yOffset_01 = _yOffset_01 + 0x65;
                                                                    iVar26 = iVar26 + -10;
                                                                    break;
                                                                case 4:
                                                                    _yOffset_01 = _yOffset_01 + 0x70;
                                                                    iVar26 = iVar26 + 2;
                                                                    break;
                                                                case 5:
                                                                    _yOffset_01 = _yOffset_01 + 100;
                                                                    iVar26 = iVar26 + 0x14;
                                                                    break;
                                                                case 6:
                                                                    _yOffset_01 = _yOffset_01 + 0x46;
                                                                    iVar26 = iVar26 + 0x13;
                                                                    break;
                                                                case 7:
                                                                    _yOffset_01 = _yOffset_01 + 0x2c;
                                                                    iVar26 = iVar26 + 0x17;
                                                                }
                                                            } else {
                                                                if ((UVar7 != OpenSHC::Map::Units::UT_S_BATTERINGRAM)
                                                                    || (DAT_UnitsState::instance.units[local_60].dying
                                                                        != 0))
                                                                    goto LAB_004eadfa;
                                                                _yOffset_01
                                                                    = (int)DAT_UnitsState::instance.units[local_60]
                                                                          .drawX;
                                                                iVar26 = (int)DAT_UnitsState::instance.units[local_60]
                                                                             .drawY;
                                                                switch (DAT_UnitsState::instance.units[local_60]
                                                                        .facingDirectionMapOrientationCorrected) {
                                                                case 0:
                                                                case 1:
                                                                    _yOffset_01 = _yOffset_01 + 0x2c;
                                                                    iVar26 = iVar26 + -0x14;
                                                                    break;
                                                                case 2:
                                                                    _yOffset_01 = _yOffset_01 + 0x31;
                                                                    iVar26 = iVar26 + -0x11;
                                                                    break;
                                                                case 3:
                                                                    _yOffset_01 = _yOffset_01 + 0x29;
                                                                    iVar26 = iVar26 + -0xf;
                                                                    break;
                                                                case 4:
                                                                    _yOffset_01 = _yOffset_01 + 0x22;
                                                                    iVar26 = iVar26 + -0x11;
                                                                    break;
                                                                case 5:
                                                                case 6:
                                                                    _yOffset_01 = _yOffset_01 + 0x20;
                                                                    iVar26 = iVar26 + -0x14;
                                                                    break;
                                                                case 7:
                                                                    _yOffset_01 = _yOffset_01 + 0x28;
                                                                    iVar26 = iVar26 + -0x17;
                                                                }
                                                            }
                                                            DAT_RenderedUnitOwner::instance
                                                                = (uint)DAT_UnitsState::instance.units[local_60].owner;
                                                            DAT_CurrentlyRenderedSpriteID::instance
                                                                = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                                                            uVar32 = DAT_UnitsState::instance.units[local_60].fixedRng
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
                                                                (int)((int)(uVar32 / 2 + 1)), _yOffset_01, iVar26);
                                                        }
                                                    }
                                                LAB_004eadfa:
                                                    if (*this->viewportState.ptrColor
                                                        == COL_MAGENTA::instance.shortValue) {
                                                        *this->viewportState.ptrColor = uVar9;
                                                    } else {
                                                        this->viewportState.mouseRayUnitID = local_60;
                                                        this->viewportState.mouseRayBuildingID = 0;
                                                    }
                                                } else {
                                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                          renderUnitAnimationWithBlendingUnk,
                                                        DAT_TextureRenderCoreObject::ptr)(
                                                        (int)DAT_UnitsState::instance.units[local_60].drawX,
                                                        (int)((int)(DAT_UnitsState::instance.units[local_60].drawY)),
                                                        (int)((
                                                            int)(DAT_UnitsState::instance.units[local_60].drawWidth)),
                                                        (int)((
                                                            int)(DAT_UnitsState::instance.units[local_60].drawHeight1)),
                                                        (byte*)((int)((DAT_GMImageOffsets::instance[iVar26]
                                                            + (int)DAT_TextureRenderCoreObject::instance
                                                                .gmProcessedImageData))),
                                                        (int)((int)((char)bVar15)));
                                                    if (*this->viewportState.ptrColor
                                                        == COL_MAGENTA::instance.shortValue) {
                                                        *this->viewportState.ptrColor = uVar9;
                                                    } else {
                                                        this->viewportState.mouseRayUnitID = local_60;
                                                        this->viewportState.mouseRayBuildingID = 0;
                                                    }
                                                }
                                                if (((DAT_UnitsState::instance.units[local_60].isSelected != 0)
                                                        && (DAT_UnitsState::instance.units[local_60].usingTeleport
                                                            == 0))
                                                    && (DAT_UnitsState::instance.units[local_60]
                                                            .disappearFadeAlphaCountdown
                                                        == 0)) {
                                                    _yOffset_01
                                                        = (DAT_UnitsState::instance.units[local_60].drawWidth + -0x16)
                                                        / 2;
                                                    if (DAT_UnitsState::instance.units[local_60].unitType
                                                        == OpenSHC::Map::Units::UT_LORD) {
                                                        sVar30 = DAT_UnitsState::instance.units[local_60]
                                                                     .maxHealthRatingLord;
                                                        if (sVar30 == 0) {
                                                            iVar26 = DAT_UnitsState::instance.units[local_60]
                                                                         .someDrawYOffset
                                                                + -6
                                                                + (int)DAT_UnitsState::instance.units[local_60].drawY;
                                                            iVar27 = DAT_UnitsState::instance.units[local_60].drawX
                                                                + _yOffset_01;
                                                            iVar18 = DAT_UnitsState::instance.units[local_60].healthbar
                                                                + 0x11;
                                                        } else {
                                                            iVar26 = DAT_UnitsState::instance.units[local_60]
                                                                         .someDrawYOffset
                                                                + -8
                                                                + (int)DAT_UnitsState::instance.units[local_60].drawY;
                                                            iVar27 = DAT_UnitsState::instance.units[local_60].drawX
                                                                + _yOffset_01;
                                                            iVar18 = DAT_UnitsState::instance.units[local_60].healthbar
                                                                + 0xe4 + sVar30 * 0xb;
                                                        }
                                                    } else {
                                                        iVar26
                                                            = DAT_GameState::instance
                                                                  .playerDataArray
                                                                      [DAT_UnitsState::instance.units[local_60].owner]
                                                                  .fearFactorLevel;
                                                        if (iVar26 == 0) {
                                                            iVar26 = DAT_UnitsState::instance.units[local_60]
                                                                         .someDrawYOffset
                                                                + -6
                                                                + (int)DAT_UnitsState::instance.units[local_60].drawY;
                                                            iVar27 = DAT_UnitsState::instance.units[local_60].drawX
                                                                + _yOffset_01;
                                                            iVar18 = DAT_UnitsState::instance.units[local_60].healthbar
                                                                + 0x11;
                                                        } else {
                                                            if (iVar26 < 1) {
                                                                iVar18 = iVar26 * -0xb + 0xad;
                                                            } else {
                                                                iVar18 = iVar26 * 0xb + 0x76;
                                                            }
                                                            iVar26 = DAT_UnitsState::instance.units[local_60]
                                                                         .someDrawYOffset
                                                                + -8
                                                                + (int)DAT_UnitsState::instance.units[local_60].drawY;
                                                            iVar27 = DAT_UnitsState::instance.units[local_60].drawX
                                                                + _yOffset_01;
                                                            iVar18 = DAT_UnitsState::instance.units[local_60].healthbar
                                                                + iVar18;
                                                        }
                                                    }
                                                    MACRO_CALL_MEMBER(
                                                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                        DAT_TextureRenderCoreObject::ptr)(
                                                        OpenSHC::DE::SHCDE::GM_FLOATS, iVar18, iVar27, iVar26);
                                                    if (((DAT_UnitsState::instance.units[local_60].unitType
                                                             == OpenSHC::Map::Units::UT_A_ASSASSIN)
                                                            && (DAT_GameState::instance.mapAndTime.playerTeams
                                                                    [DAT_UnitsState::instance.units[local_60].owner]
                                                                == DAT_GameState::instance.mapAndTime
                                                                    .playerTeams[DAT_GameSynchronyState::instance
                                                                            .currentPlayerSlotID]))
                                                        && ((DAT_UnitsState::instance.units[local_60]
                                                                    .assassinsMicroDistanceToEnemyUnk
                                                                < 0xa1
                                                            || ((UVar4 = DAT_UnitsState::instance.units[local_60]
                                                                     .state.generic,
                                                                UVar4 == OpenSHC::Map::Units::States::US_MELEE_ATTACK
                                                                    || (UVar4
                                                                        == OpenSHC::Map::Units::States::
                                                                            US_MELEE_ATTACK_WALL)))))) {
                                                        MACRO_CALL_MEMBER(
                                                            OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                renderGMWithBlending,
                                                            DAT_TextureRenderCoreObject::ptr)(
                                                            OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x1bf,
                                                            DAT_UnitsState::instance.units[local_60].drawX + 2
                                                                + _yOffset_01,
                                                            (int)((int)(DAT_UnitsState::instance.units[local_60]
                                                                            .someDrawYOffset
                                                                + -0x1b
                                                                + DAT_UnitsState::instance.units[local_60].drawY)),
                                                            0x10);
                                                    }
                                                }
                                                if ((local_60 != 0)
                                                    && (sVar30 = DAT_UnitsState::instance.units[local_60].field46_0x6e,
                                                        sVar30 != 0)) {
                                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                          renderGMWithAlphaMask,
                                                        DAT_TextureRenderCoreObject::ptr)(
                                                        OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                                                        (int)((int)(sVar30 + 0xd4)),
                                                        (int)((int)(DAT_UnitsState::instance.units[local_60].drawX)),
                                                        (int)((int)(DAT_UnitsState::instance.units[local_60]
                                                                        .someDrawYOffset
                                                            + -0x36 + DAT_UnitsState::instance.units[local_60].drawY)),
                                                        OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                                                        (int)((int)(sVar30 + 0xdc)), 0);
                                                    DAT_UnitsState::instance.units[local_60].field46_0x6e = 0;
                                                }
                                                sVar30 = DAT_UnitsState::instance.units[local_60].field45_0x6c;
                                                if (sVar30 == 1) {
                                                    iVar26 = DAT_TileMapState::instance.field161_0x5549c0 + 0x30;
                                                    iVar18 = DAT_UnitsState::instance.units[local_60].someDrawYOffset
                                                        + -0x46 + (int)DAT_UnitsState::instance.units[local_60].drawY;
                                                    _yOffset_01 = DAT_UnitsState::instance.units[local_60].field22_0x2a
                                                        + -0x35 + (int)DAT_UnitsState::instance.units[local_60].drawX;
                                                    iVar27 = DAT_TileMapState::instance.field161_0x5549c0 + 0x20;
                                                } else if (sVar30 == 2) {
                                                    _yOffset_01 = 0;
                                                    iVar18 = 0;
                                                    switch (DAT_UnitsState::instance.units[local_60].unitType) {
                                                    case OpenSHC::Map::Units::UT_S_CATAPULT:
                                                        _yOffset_01 = 0x29;
                                                        iVar18 = 0x3a;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_TREBUCHET:
                                                    case OpenSHC::Map::Units::UT_S_TOWER:
                                                        _yOffset_01 = 0x4f;
                                                        iVar18 = 0x38;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_MANGONEL:
                                                        _yOffset_01 = 0x2b;
                                                        iVar18 = 0x23;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                                                        _yOffset_01 = 0x24;
                                                        iVar18 = 0x3d;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_SHIELD:
                                                        _yOffset_01 = -3;
                                                        iVar18 = 0x3c;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_BALLISTA:
                                                    case OpenSHC::Map::Units::UT_S_FBALLISTA:
                                                        iVar18 = 0x24;
                                                        _yOffset_01 = 0x13;
                                                    }
                                                    iVar26 = DAT_TileMapState::instance.field161_0x5549c0 + 0x84;
                                                    iVar18 = (DAT_UnitsState::instance.units[local_60].someDrawYOffset
                                                                 - iVar18)
                                                        + (int)DAT_UnitsState::instance.units[local_60].drawY;
                                                    _yOffset_01
                                                        = DAT_UnitsState::instance.units[local_60].drawX + _yOffset_01;
                                                    iVar27 = DAT_TileMapState::instance.field161_0x5549c0 + 0x74;
                                                } else {
                                                    if (sVar30 != 3)
                                                        goto LAB_004eb1be;
                                                    iVar18 = 0;
                                                    _yOffset_01 = 0;
                                                    switch (DAT_UnitsState::instance.units[local_60].unitType) {
                                                    case OpenSHC::Map::Units::UT_S_CATAPULT:
                                                        _yOffset_01 = 0x29;
                                                        iVar18 = 0x3a;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_TREBUCHET:
                                                    case OpenSHC::Map::Units::UT_S_TOWER:
                                                        _yOffset_01 = 0x4f;
                                                        iVar18 = 0x38;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_MANGONEL:
                                                        _yOffset_01 = 0x2b;
                                                        iVar18 = 0x23;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                                                        _yOffset_01 = 0x24;
                                                        iVar18 = 0x3d;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_SHIELD:
                                                        _yOffset_01 = -3;
                                                        iVar18 = 0x3c;
                                                        break;
                                                    case OpenSHC::Map::Units::UT_S_BALLISTA:
                                                    case OpenSHC::Map::Units::UT_S_FBALLISTA:
                                                        iVar18 = 0x24;
                                                        _yOffset_01 = 0x13;
                                                    }
                                                    iVar26 = DAT_TileMapState::instance.field161_0x5549c0 + 0xa4;
                                                    iVar18 = (DAT_UnitsState::instance.units[local_60].someDrawYOffset
                                                                 - iVar18)
                                                        + (int)DAT_UnitsState::instance.units[local_60].drawY;
                                                    _yOffset_01
                                                        = DAT_UnitsState::instance.units[local_60].drawX + _yOffset_01;
                                                    iVar27 = DAT_TileMapState::instance.field161_0x5549c0 + 0x94;
                                                }
                                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                      renderGMWithAlphaMask,
                                                    DAT_TextureRenderCoreObject::ptr)(
                                                    OpenSHC::IO::Graphics::GID_FLOATS_NEW, iVar27, _yOffset_01, iVar18,
                                                    OpenSHC::IO::Graphics::GID_FLOATS_NEW, iVar26, 0);
                                                DAT_UnitsState::instance.units[local_60].field45_0x6c = 0;
                                                goto LAB_004eb1be;
                                            }
                                            if ((DAT_BuildingsState::instance.buildings[local_54].buildingType
                                                    != OpenSHC::Map::Buildings::BT_TOWER2)
                                                || ((sVar24 = DAT_UnitsState::instance.units[local_60]
                                                         .facingDirectionMapOrientationCorrected,
                                                    sVar24 != 2 && (sVar24 != 6))))
                                                goto LAB_004ea49b;
                                            if ((DAT_UnitsState::instance.units[local_60].unitType
                                                    == OpenSHC::Map::Units::UT_A_ASSASSIN)
                                                && (_yOffset_01 = DAT_UnitsState::instance.units[local_60].imageID2,
                                                    _yOffset_01 != 0)) {
                                                sVar24 = DAT_UnitsState::instance.units[local_60].field59_0x86;
                                                if (sVar24 < 0) {
                                                    local_14 = 0;
                                                } else {
                                                    local_14 = (int)sVar24;
                                                }
                                                iVar27 = (0x20 - local_2c) / 3;
                                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                      renderUnitAnimationWithBlendingUnk,
                                                    DAT_TextureRenderCoreObject::ptr)((int)sVar30,
                                                    (int)((int)(DAT_UnitsState::instance.units[local_60].field59_0x86
                                                        + sVar20)),
                                                    (int)((int)(sVar5)),
                                                    DAT_UnitsState::instance.units[local_60].drawHeight1 - local_14,
                                                    (byte*)((
                                                        int)((DAT_GMImageOffsets::instance[_yOffset_01 + -1 + iVar18]
                                                        + (int)DAT_TextureRenderCoreObject::instance
                                                            .gmProcessedImageData))),
                                                    (0x10 - iVar27) * 2);
                                                sVar30 = DAT_UnitsState::instance.units[local_60].drawYOffset;
                                                if (sVar30 != 0) {
                                                    sVar20 = DAT_UnitsState::instance.units[local_60].field59_0x86;
                                                    if (sVar20 < 0) {
                                                        _yOffset_01 = 0;
                                                    } else {
                                                        _yOffset_01 = (int)sVar20;
                                                    }
                                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                          renderUnitAnimationWithBlendingUnk,
                                                        DAT_TextureRenderCoreObject::ptr)(
                                                        (int)DAT_UnitsState::instance.units[local_60].drawX,
                                                        (int)((int)(sVar20
                                                            + DAT_UnitsState::instance.units[local_60].drawY)),
                                                        (int)((
                                                            int)(DAT_UnitsState::instance.units[local_60].drawWidth)),
                                                        DAT_UnitsState::instance.units[local_60].drawHeight1
                                                            - _yOffset_01,
                                                        (byte*)((
                                                            int)((DAT_GMImageOffsets::instance
                                                                      [GMTotalPicturesProcessed::instance
                                                                              [DAT_CurrentlyRenderedSpriteID::instance]
                                                                          + -1 + (int)sVar30]
                                                            + (int)DAT_TextureRenderCoreObject::instance
                                                                .gmProcessedImageData))),
                                                        0x20 - iVar27);
                                                }
                                            }
                                            uVar9 = *this->viewportState.ptrColor;
                                            *this->viewportState.ptrColor = COL_MAGENTA::instance.shortValue;
                                            sVar30 = DAT_UnitsState::instance.units[local_60].field59_0x86;
                                            if (local_2c == 0) {
                                                if (sVar30 < 0) {
                                                    _yOffset_01 = 0;
                                                } else {
                                                    _yOffset_01 = (int)sVar30;
                                                }
                                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                      renderUnitAnimationUnk,
                                                    DAT_TextureRenderCoreObject::ptr)(
                                                    (int)DAT_UnitsState::instance.units[local_60].drawX,
                                                    (int)((
                                                        int)(sVar30 + DAT_UnitsState::instance.units[local_60].drawY)),
                                                    (int)((int)(DAT_UnitsState::instance.units[local_60].drawWidth)),
                                                    DAT_UnitsState::instance.units[local_60].drawHeight1 - _yOffset_01,
                                                    (byte*)((int)((DAT_GMImageOffsets::instance[iVar26]
                                                        + (int)DAT_TextureRenderCoreObject::instance
                                                            .gmProcessedImageData))));
                                            } else {
                                                if (sVar30 < 0) {
                                                    _yOffset_01 = 0;
                                                } else {
                                                    _yOffset_01 = (int)sVar30;
                                                }
                                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                      renderUnitAnimationWithBlendingUnk,
                                                    DAT_TextureRenderCoreObject::ptr)(
                                                    (int)DAT_UnitsState::instance.units[local_60].drawX,
                                                    (int)((
                                                        int)(sVar30 + DAT_UnitsState::instance.units[local_60].drawY)),
                                                    (int)((int)(DAT_UnitsState::instance.units[local_60].drawWidth)),
                                                    DAT_UnitsState::instance.units[local_60].drawHeight1 - _yOffset_01,
                                                    (byte*)((int)((DAT_GMImageOffsets::instance[iVar26]
                                                        + (int)DAT_TextureRenderCoreObject::instance
                                                            .gmProcessedImageData))),
                                                    local_2c);
                                            }
                                            sVar30 = DAT_UnitsState::instance.units[local_60].graphicSize;
                                            if ((sVar30 != 4) && (1 < sVar30)) {
                                                DAT_CurrentlyRenderedSpriteID::instance
                                                    = (GmIDInt)DAT_UnitsState::instance.units[local_60].gmIDUnk;
                                                DAT_RenderedUnitOwner::instance
                                                    = (uint)DAT_UnitsState::instance.units[local_60]
                                                          .displayColorPlayerID;
                                                _yOffset_01 = DAT_UnitsState::instance.units[local_60].imageIDUnk;
                                                if (0 < _yOffset_01) {
                                                    sVar30 = DAT_UnitsState::instance.units[local_60].field60_0x88;
                                                    if (sVar30 < 0) {
                                                        iVar26 = 0;
                                                    } else {
                                                        iVar26 = (int)sVar30;
                                                    }
                                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                          renderUnitAnimationUnk,
                                                        DAT_TextureRenderCoreObject::ptr)(
                                                        (int)DAT_UnitsState::instance.units[local_60].drawX,
                                                        (int)((int)(sVar30
                                                            + DAT_UnitsState::instance.units[local_60].drawY)),
                                                        (int)((
                                                            int)(DAT_UnitsState::instance.units[local_60].drawWidth)),
                                                        DAT_UnitsState::instance.units[local_60].drawHeight1 - iVar26,
                                                        (byte*)((
                                                            int)((DAT_GMImageSizes::instance
                                                                      [GMTotalPicturesProcessed::instance
                                                                              [DAT_CurrentlyRenderedSpriteID::instance]
                                                                          + _yOffset_01 + 0x1c51f]
                                                            + (int)DAT_TextureRenderCoreObject::instance
                                                                .gmProcessedImageData))));
                                                }
                                            }
                                            if (2 < DAT_UnitsState::instance.units[local_60].graphicSize) {
                                                _yOffset_01 = DAT_UnitsState::instance.units[local_60].imageID2;
                                                if (0 < _yOffset_01) {
                                                    sVar30 = DAT_UnitsState::instance.units[local_60].drawYOffset;
                                                    if (sVar30 < 0) {
                                                        iVar26 = 0;
                                                    } else {
                                                        iVar26 = (int)sVar30;
                                                    }
                                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                                          renderUnitAnimationUnk,
                                                        DAT_TextureRenderCoreObject::ptr)(
                                                        (int)DAT_UnitsState::instance.units[local_60].drawX,
                                                        (int)((int)(sVar30
                                                            + DAT_UnitsState::instance.units[local_60].drawY)),
                                                        (int)((
                                                            int)(DAT_UnitsState::instance.units[local_60].drawWidth)),
                                                        DAT_UnitsState::instance.units[local_60].drawHeight1 - iVar26,
                                                        (byte*)((
                                                            int)((DAT_GMImageSizes::instance
                                                                      [GMTotalPicturesProcessed::instance
                                                                              [DAT_CurrentlyRenderedSpriteID::instance]
                                                                          + _yOffset_01 + 0x1c51f]
                                                            + (int)DAT_TextureRenderCoreObject::instance
                                                                .gmProcessedImageData))));
                                                }
                                                if (DAT_GameSynchronyState::instance.currentGameMode
                                                    != OpenSHC::Game::GM_SOLITARY) {
                                                    UVar7 = DAT_UnitsState::instance.units[local_60].unitType;
                                                    if ((UVar7 == OpenSHC::Map::Units::UT_S_TOWER)
                                                        && (DAT_UnitsState::instance.units[local_60].dying == 0)) {
                                                        _yOffset_01
                                                            = (int)DAT_UnitsState::instance.units[local_60].drawX;
                                                        iVar26 = (int)DAT_UnitsState::instance.units[local_60].drawY;
                                                        switch (DAT_UnitsState::instance.units[local_60]
                                                                .facingDirectionMapOrientationCorrected) {
                                                        case 0:
                                                            _yOffset_01 = _yOffset_01 + 0x22;
                                                            break;
                                                        case 1:
                                                            _yOffset_01 = _yOffset_01 + 0x2f;
                                                            iVar26 = iVar26 + -0xc;
                                                            break;
                                                        case 2:
                                                            _yOffset_01 = _yOffset_01 + 0x4b;
                                                            iVar26 = iVar26 + -0x13;
                                                            break;
                                                        case 3:
                                                            _yOffset_01 = _yOffset_01 + 0x65;
                                                            iVar26 = iVar26 + -10;
                                                            break;
                                                        case 4:
                                                            _yOffset_01 = _yOffset_01 + 0x70;
                                                            iVar26 = iVar26 + 2;
                                                            break;
                                                        case 5:
                                                            _yOffset_01 = _yOffset_01 + 100;
                                                            iVar26 = iVar26 + 0x14;
                                                            break;
                                                        case 6:
                                                            _yOffset_01 = _yOffset_01 + 0x46;
                                                            iVar26 = iVar26 + 0x13;
                                                            break;
                                                        case 7:
                                                            _yOffset_01 = _yOffset_01 + 0x2c;
                                                            iVar26 = iVar26 + 0x17;
                                                        }
                                                    } else {
                                                        if ((UVar7 != OpenSHC::Map::Units::UT_S_BATTERINGRAM)
                                                            || (DAT_UnitsState::instance.units[local_60].dying != 0))
                                                            goto LAB_004ea966;
                                                        _yOffset_01
                                                            = (int)DAT_UnitsState::instance.units[local_60].drawX;
                                                        iVar26 = (int)DAT_UnitsState::instance.units[local_60].drawY;
                                                        switch (DAT_UnitsState::instance.units[local_60]
                                                                .facingDirectionMapOrientationCorrected) {
                                                        case 0:
                                                        case 1:
                                                            _yOffset_01 = _yOffset_01 + 0x2c;
                                                            iVar26 = iVar26 + -0x14;
                                                            break;
                                                        case 2:
                                                            _yOffset_01 = _yOffset_01 + 0x31;
                                                            iVar26 = iVar26 + -0x11;
                                                            break;
                                                        case 3:
                                                            _yOffset_01 = _yOffset_01 + 0x29;
                                                            iVar26 = iVar26 + -0xf;
                                                            break;
                                                        case 4:
                                                            _yOffset_01 = _yOffset_01 + 0x22;
                                                            iVar26 = iVar26 + -0x11;
                                                            break;
                                                        case 5:
                                                        case 6:
                                                            _yOffset_01 = _yOffset_01 + 0x20;
                                                            iVar26 = iVar26 + -0x14;
                                                            break;
                                                        case 7:
                                                            _yOffset_01 = _yOffset_01 + 0x28;
                                                            iVar26 = iVar26 + -0x17;
                                                        }
                                                    }
                                                    DAT_RenderedUnitOwner::instance
                                                        = (uint)DAT_UnitsState::instance.units[local_60].owner;
                                                    DAT_CurrentlyRenderedSpriteID::instance
                                                        = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                                                    uVar32 = DAT_UnitsState::instance.units[local_60].fixedRng
                                                            + DAT_GameState::instance.mapAndTime.totalGameTicksUnk
                                                        & 0x8000003f;
                                                    if ((int)uVar32 < 0) {
                                                        uVar32 = (uVar32 - 1 | 0xffffffc0) + 1;
                                                    }
                                                    MACRO_CALL_MEMBER(
                                                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                        DAT_TextureRenderCoreObject::ptr)(
                                                        OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL,
                                                        (int)((int)(uVar32 / 2 + 1)), _yOffset_01, iVar26);
                                                }
                                            }
                                        LAB_004ea966:
                                            if (*this->viewportState.ptrColor == COL_MAGENTA::instance.shortValue) {
                                                *this->viewportState.ptrColor = uVar9;
                                            } else {
                                                this->viewportState.mouseRayUnitID = local_60;
                                                this->viewportState.mouseRayBuildingID = 0;
                                            }
                                            goto LAB_004eb1be;
                                        }
                                        _yOffset_01 = 0;
                                    }
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::Rendering::ViewportRenderState_Func::scheduleUnitForBatchedRendering,
                                        this)(local_60, (undefined4)((int)((int)sVar30)),
                                        (undefined4)((int)((int)sVar20)), (undefined4)((int)((int)sVar5)),
                                        (undefined4)((int)((int)DAT_UnitsState::instance.units[local_60].drawHeight1)),
                                        (undefined4)((int)(DAT_GMImageOffsets::instance[iVar26]
                                            + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData)),
                                        _yOffset_01);
                                } else if (_yOffset_01 != 1) {
                                    if (local_2c == 0) {
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationUnk,
                                            DAT_TextureRenderCoreObject::ptr)((int)sVar30, (int)((int)(sVar20)),
                                            (int)((int)(sVar5)),
                                            (int)((int)(DAT_UnitsState::instance.units[local_60].drawHeight1)),
                                            (byte*)((int)((DAT_GMImageOffsets::instance[iVar26]
                                                + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))));
                                    } else {
                                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::
                                                              renderUnitAnimationWithBlendingUnk,
                                            DAT_TextureRenderCoreObject::ptr)((int)sVar30, (int)((int)(sVar20)),
                                            (int)((int)(sVar5)),
                                            (int)((int)(DAT_UnitsState::instance.units[local_60].drawHeight1)),
                                            (byte*)((int)((DAT_GMImageOffsets::instance[iVar26]
                                                + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))),
                                            local_2c);
                                    }
                                    _yOffset_01 = DAT_UnitsState::instance.units[local_60].vanish;
                                    if (1 < _yOffset_01) {
                                        DAT_UnitsState::instance.units[local_60].vanish = _yOffset_01 + -1;
                                    }
                                }
                            }
                        LAB_004eb1be:
                            local_60 = (int)(short)DAT_UnitsState::instance.units[local_60].nextUnitOnTheSameTile;
                            if ((DAT_GameSynchronyState::instance.syncStatus != 0) || (local_60 < 1))
                                break;
                        }
                    }
                    /*
                      ------ END RENDER UNITS ------
                     */

                    local_24 = 0;
                    _yOffset_01 = DAT_RenderMap_YOffset::instance;
                    if (local_58 != 0) {
                        do {
                            local_24 = local_24 + 1;
                            if ((9 < local_24) || (DAT_EntityState::instance.entityArray[local_58].logicalState == 0))
                                break;
                            if (DAT_EntityState::instance.entityArray[local_58].graphicType2 == 0)
                                goto LAB_004eb439;
                            DAT_CurrentlyRenderedSpriteID::instance
                                = (GmIDInt)DAT_EntityState::instance.entityArray[local_58].gmID;
                            if ((DAT_CurrentlyRenderedSpriteID::instance == OpenSHC::IO::Graphics::GID_BODY_FIRE)
                                || (DAT_CurrentlyRenderedSpriteID::instance
                                    == OpenSHC::IO::Graphics::GID_BODY_FIRE_2)) {
                                local_8 = local_8 + 1;
                                if ((DAT_EntityState::instance.entityArray[local_58].fireIntensity == 0)
                                    && (0x4f < local_8)) {
                                    if (local_8 < 200) {
                                        bVar15 = (byte)DAT_EntityState::instance.entityArray[local_58].rng_1 & 1;
                                    } else {
                                        bVar15 = (byte)DAT_EntityState::instance.entityArray[local_58].rng_1 & 3;
                                    }
                                    if (bVar15 != 0)
                                        break;
                                }
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Audio::SFX::SFXState_Func::notifyAmbientSoundEvent, DAT_SFXState::ptr)(5);
                                _yOffset_01 = DAT_RenderMap_YOffset::instance;
                            }
                            DAT_RenderedUnitOwner::instance = DAT_EntityState::instance.entityArray[local_58].colorUnk;
                            bVar12 = false;
                            iVar26 = (int)DAT_EntityState::instance.entityArray[local_58].height;
                            switch (DAT_CurrentlyRenderedSpriteID::instance) {
                            case OpenSHC::IO::Graphics::GID_ANIM_FLAGS:
                            case OpenSHC::IO::Graphics::GID_ANIM_CRUSADER_FLAG:
                                if (_flatView)
                                    goto LAB_004eb439;
                            case OpenSHC::IO::Graphics::GID_BODY_INFO:
                                bVar12 = true;
                            switchD_004eb2c9_caseD_76:
                                if ((DAT_TileMapState::instance.refreshRelatedOne == 0) || (_flatView)) {
                                    iVar26 = _yOffset_01;
                                }
                                if (!bVar12)
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
                                if ((DAT_EntityState::instance.entityArray[local_58].someCounter_OR_hitGround != 0)
                                    && ((DAT_TileMapState::instance.refreshRelatedOne == 0 || (_flatView)))) {
                                    iVar26 = _yOffset_01;
                                }
                                goto switchD_004eb2c9_caseD_4d;
                            case OpenSHC::IO::Graphics::GID_BODY_BRAZIER:
                                iVar18
                                    = iVar26 + 4 + (_yOffset_01 - (uint)DAT_TileMapState::instance.HeightLayer[iVar16]);
                                if (DAT_TileMapState::instance.refreshRelatedOne == 0) {
                                    iVar26 = _yOffset_01;
                                    if (DAT_TileMapState::instance.BuildingLayer[iVar16] != 0) {
                                        iVar26 = _yOffset_01 + 0x14;
                                    }
                                } else {
                                    iVar26 = _yOffset_01;
                                    if ((!_flatView)
                                        && (iVar26 = iVar18, DAT_TileMapState::instance.BuildingLayer[iVar16] != 0)) {
                                        iVar26 = iVar18 + -10;
                                    }
                                }
                                break;
                            case OpenSHC::IO::Graphics::GID_ANIM_HEADS:
                                iVar26
                                    = iVar26 + 7 + (_yOffset_01 - (uint)DAT_TileMapState::instance.HeightLayer[iVar16]);
                                uVar32 = DAT_TileMapState::instance.LogicLayer[iVar16] & 0x400000;
                                if (uVar32 != 0) {
                                    iVar26 = iVar26 + 0x12;
                                }
                                if (DAT_TileMapState::instance.refreshRelatedOne == 0) {
                                    iVar26 = _yOffset_01 + 0x14;
                                    if (DAT_TileMapState::instance.BuildingLayer[iVar16] == 0) {
                                        iVar26 = _yOffset_01;
                                    }
                                    if (uVar32 != 0) {
                                        iVar26 = iVar26 + 0x12;
                                    }
                                } else if (_flatView)
                                    goto LAB_004eb439;
                            }
                            if ((DAT_EntityState::instance.entityArray[local_58].field83_0xc0 == 0)
                                || (DAT_TextureRenderCoreObject::instance.isZoom2 == 0)) {
                                sVar30 = DAT_EntityState::instance.entityArray[local_58].unkMinusOne;
                                if (sVar30 < 0) {
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                        DAT_TextureRenderCoreObject::ptr)((GmID)DAT_CurrentlyRenderedSpriteID::instance,
                                        DAT_EntityState::instance.entityArray[local_58].graphicType2,
                                        (int)((int)((DAT_EntityState::instance.entityArray[local_58].x1
                                                        - DAT_EntityState::instance.entityArray[local_58].originX)
                                            + DAT_RenderMap_DrawSomeX::instance)),
                                        (int)((int)(((DAT_EntityState::instance.entityArray[local_58].y1
                                                         - DAT_EntityState::instance.entityArray[local_58].originY)
                                                        - iVar26)
                                            + DAT_RenderMap_DrawSomeY::instance)),
                                        (GmID)((int)(DAT_CurrentlyRenderedSpriteID::instance)),
                                        (int)((int)(DAT_EntityState::instance.entityArray[local_58].imageID)),
                                        (int)((int)(-1 - sVar30)));
                                    _yOffset_01 = DAT_RenderMap_YOffset::instance;
                                } else {
                                    _yOffset_01 = (int)DAT_EntityState::instance.entityArray[local_58].originY;
                                    if (sVar30 == 0) {
                                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                            DAT_TextureRenderCoreObject::ptr)(
                                            (eGM)DAT_CurrentlyRenderedSpriteID::instance,
                                            DAT_EntityState::instance.entityArray[local_58].graphicType2,
                                            (int)((int)((DAT_EntityState::instance.entityArray[local_58].x1
                                                            - DAT_EntityState::instance.entityArray[local_58].originX)
                                                + DAT_RenderMap_DrawSomeX::instance)),
                                            (int)((
                                                int)(((DAT_EntityState::instance.entityArray[local_58].y1 - _yOffset_01)
                                                         - iVar26)
                                                + DAT_RenderMap_DrawSomeY::instance)));
                                        _yOffset_01 = DAT_RenderMap_YOffset::instance;
                                    } else {
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                            DAT_TextureRenderCoreObject::ptr)(
                                            (GmID)DAT_CurrentlyRenderedSpriteID::instance,
                                            DAT_EntityState::instance.entityArray[local_58].graphicType2,
                                            (int)((int)((DAT_EntityState::instance.entityArray[local_58].x1
                                                            - DAT_EntityState::instance.entityArray[local_58].originX)
                                                + DAT_RenderMap_DrawSomeX::instance)),
                                            (int)((
                                                int)(((DAT_EntityState::instance.entityArray[local_58].y1 - _yOffset_01)
                                                         - iVar26)
                                                + DAT_RenderMap_DrawSomeY::instance)),
                                            (int)((int)(sVar30)));
                                        _yOffset_01 = DAT_RenderMap_YOffset::instance;
                                    }
                                }
                            LAB_004eb439:
                                iVar26 = (int)DAT_EntityState::instance.entityArray[local_58].nextEntityOnThisTileByID;
                                if ((local_58 == iVar26)
                                    || (local_58 = iVar26, DAT_GameSynchronyState::instance.syncStatus != 0))
                                    break;
                            } else {
                                local_58
                                    = (uint)DAT_EntityState::instance.entityArray[local_58].nextEntityOnThisTileByID;
                            }
                            if (local_58 == 0)
                                break;
                        } while (true);
                    }
                    local_58 = (uint)(byte)DAT_TileMapState::instance.EntityLayerLT25[iVar16];
                    _yOffset_01 = 0;
                    if (local_58 != 0) {
                        while (_yOffset_01 = _yOffset_01 + 1, _yOffset_01 < 10) {
                            if (DAT_EntityState::instance.entityArray[local_58].tile != iVar16) {
                                DAT_TileMapState::instance.EntityLayerLT25[iVar16] = '\0';
                                break;
                            }
                            if (DAT_EntityState::instance.entityArray[local_58].logicalState == 0)
                                break;
                            iVar26 = DAT_EntityState::instance.entityArray[local_58].graphicType2;
                            if (iVar26 == 0) {
                            LAB_004eb7db:
                                uVar32 = (uint)DAT_EntityState::instance.entityArray[local_58].nextEntityOnThisTileByID;
                                if ((local_58 == uVar32) || (DAT_GameSynchronyState::instance.syncStatus != 0))
                                    break;
                            } else {
                                DAT_CurrentlyRenderedSpriteID::instance
                                    = (GmIDInt)DAT_EntityState::instance.entityArray[local_58].gmID;
                                DAT_RenderedUnitOwner::instance
                                    = DAT_EntityState::instance.entityArray[local_58].colorUnk;
                                iVar18 = (int)DAT_EntityState::instance.entityArray[local_58].height;
                                if ((DAT_EntityState::instance.entityArray[local_58].field83_0xc0 == 0)
                                    || (DAT_TextureRenderCoreObject::instance.isZoom2 == 0)) {
                                    sVar30 = DAT_EntityState::instance.entityArray[local_58].unkMinusOne;
                                    if (sVar30 < 0) {
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                            DAT_TextureRenderCoreObject::ptr)(
                                            (GmID)DAT_CurrentlyRenderedSpriteID::instance, iVar26,
                                            (int)((int)((DAT_EntityState::instance.entityArray[local_58].x1
                                                            - DAT_EntityState::instance.entityArray[local_58].originX)
                                                + DAT_RenderMap_DrawSomeX::instance)),
                                            (int)((int)(((DAT_EntityState::instance.entityArray[local_58].y1
                                                             - DAT_EntityState::instance.entityArray[local_58].originY)
                                                            - iVar18)
                                                + DAT_RenderMap_DrawSomeY::instance)),
                                            (GmID)((int)(DAT_CurrentlyRenderedSpriteID::instance)),
                                            (int)((int)(DAT_EntityState::instance.entityArray[local_58].imageID)),
                                            (int)((int)(-1 - sVar30)));
                                    } else {
                                        iVar27 = (int)DAT_EntityState::instance.entityArray[local_58].originY;
                                        if (sVar30 == 0) {
                                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                DAT_TextureRenderCoreObject::ptr)(
                                                (eGM)DAT_CurrentlyRenderedSpriteID::instance, iVar26,
                                                (int)((
                                                    int)((DAT_EntityState::instance.entityArray[local_58].x1
                                                             - DAT_EntityState::instance.entityArray[local_58].originX)
                                                    + DAT_RenderMap_DrawSomeX::instance)),
                                                (int)((
                                                    int)(((DAT_EntityState::instance.entityArray[local_58].y1 - iVar27)
                                                             - iVar18)
                                                    + DAT_RenderMap_DrawSomeY::instance)));
                                        } else {
                                            MACRO_CALL_MEMBER(
                                                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                                DAT_TextureRenderCoreObject::ptr)(
                                                (GmID)DAT_CurrentlyRenderedSpriteID::instance, iVar26,
                                                (int)((
                                                    int)((DAT_EntityState::instance.entityArray[local_58].x1
                                                             - DAT_EntityState::instance.entityArray[local_58].originX)
                                                    + DAT_RenderMap_DrawSomeX::instance)),
                                                (int)((
                                                    int)(((DAT_EntityState::instance.entityArray[local_58].y1 - iVar27)
                                                             - iVar18)
                                                    + DAT_RenderMap_DrawSomeY::instance)),
                                                (int)((int)(sVar30)));
                                        }
                                    }
                                    sVar30 = DAT_EntityState::instance.entityArray[local_58].field83_0xc0;
                                    if (sVar30 != 0) {
                                        sVar20 = DAT_EntityState::instance.entityArray[local_58].unkMinusOne;
                                        EVar3 = DAT_EntityState::instance.entityArray[local_58].entityType;
                                        iVar27 = ((int)DAT_EntityState::instance.entityArray[local_58].x1
                                                     - (int)DAT_EntityState::instance.entityArray[local_58].originX)
                                            + DAT_RenderMap_DrawSomeX::instance;
                                        iVar18 = (((int)DAT_EntityState::instance.entityArray[local_58].y1
                                                      - (int)DAT_EntityState::instance.entityArray[local_58].originY)
                                                     - iVar18)
                                            + DAT_RenderMap_DrawSomeY::instance;
                                        DAT_TextManagerObject::instance.textSurfaceTarget
                                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                                        iVar26 = (int)sVar20;
                                        local_c = 0;
                                        if ((EVar3 == (OpenSHC::Map::Entities::EntityType)0x2a)
                                            || (EVar3 == (OpenSHC::Map::Entities::EntityType)0x2b)) {
                                            DAT_EntityState::instance.entityArray[local_58].unkMinusOne = sVar20 + -2;
                                            DAT_TextManagerObject::instance.field8_0x20 = 1;
                                            if (EVar3 == (OpenSHC::Map::Entities::EntityType)0x2b) {
                                                local_c = 0xff;
                                            }
                                        }
                                        if (iVar26 < 0) {
                                            iVar26 = 0;
                                        }
                                        DAT_CurrentlyRenderedSpriteID::instance
                                            = (GmIDInt)DAT_EntityState::instance.entityArray[local_58].field82_0xbe;
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                            DAT_TextureRenderCoreObject::ptr)(
                                            (GmID)DAT_CurrentlyRenderedSpriteID::instance, (int)((int)(sVar30)),
                                            DAT_EntityState::instance.entityArray[local_58].field86_0xc8 + iVar27,
                                            DAT_EntityState::instance.entityArray[local_58].field87_0xca + iVar18,
                                            iVar26);
                                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                                            DAT_TextManagerObject::ptr)(
                                            DAT_EntityState::instance.entityArray[local_58].displayValue,
                                            DAT_EntityState::instance.entityArray[local_58].field88_0xcc + iVar27,
                                            DAT_EntityState::instance.entityArray[local_58].field89_0xce + iVar18,
                                            OpenSHC::Text::TTA_LEFT, local_c, 0x12, FALSE, iVar26);
                                        DAT_TextManagerObject::instance.textSurfaceTarget
                                            = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                                        DAT_TextManagerObject::instance.field8_0x20 = 0;
                                    }
                                    goto LAB_004eb7db;
                                }
                                uVar32 = (uint)DAT_EntityState::instance.entityArray[local_58].nextEntityOnThisTileByID;
                            }
                            local_58 = uVar32;
                            if (uVar32 == 0)
                                break;
                        }
                    }
                    if ((iVar23 != 0) && (iVar23 < 2000)) {
                        DAT_CurrentlyRenderedSpriteID::instance
                            = (GmIDInt)DAT_LandscapeState::instance.trees[iVar23].treeTypeBasedValue1;
                        iVar26 = DAT_LandscapeState::instance.trees[iVar23].animationFrameUnk;
                        iVar18 = GMTotalPicturesProcessed::instance[DAT_CurrentlyRenderedSpriteID::instance];
                        _yOffset_01 = iVar18 + -1 + iVar26;
                        if ((0 < (int)DAT_CurrentlyRenderedSpriteID::instance)
                            && ((_yOffset_01 != 0 && (iVar26 != 0)))) {
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
                                    + 0xe,
                                (int)((int)(((DAT_RenderMap_DrawSomeY::instance
                                                 - DAT_LandscapeState::instance.trees[iVar23].gmOriginY)
                                                - DAT_RenderMap_YOffset::instance)
                                    + 6)),
                                (int)((int)(DAT_GMImageHeaders::instance.imh[iVar26 + iVar18 + -1].width)),
                                (int)((int)(DAT_GMImageHeaders::instance.imh[iVar26 + iVar18 + -1].height)),
                                (byte*)((int)((DAT_GMImageOffsets::instance[_yOffset_01]
                                    + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))));
                            DAT_TextureRenderCoreObject::instance.mbr_0x10 = 0;
                            if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR)
                                && (DAT_LandscapeState::instance.trees[iVar23].unknownDistanceRelatedToCrow != 0)) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_BODY_CROW,
                                    this->unknownCounterUntil_0x24 % 0xc + 0x49,
                                    (int)((int)(DAT_RenderMap_DrawSomeX::instance + -0x1e)),
                                    (int)((int)((DAT_RenderMap_DrawSomeY::instance - DAT_RenderMap_YOffset::instance)
                                        + -0xdc)));
                            }
                        }
                        MACRO_CALL_MEMBER(
                            OpenSHC::Audio::SFX::SFXState_Func::notifyAmbientSoundEvent, DAT_SFXState::ptr)(4);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Audio::SFX::SFXState_Func::notifyAmbientSoundEvent, DAT_SFXState::ptr)(8);
                    }
                    if (((DAT_00ed3170::instance != 0) && ((int)DAT_00ed3170::instance < 0xff)) && (bVar13)) {
                        uVar32 = (uint)(short)DAT_TileMapState::instance.MiscDisplayLayer[iVar16];
                        DAT_00ed317c::instance = uVar32 & 3;
                        if ((DAT_00ed3148::instance & 0x100) == 0) {
                            DAT_GmImageAddressToBeRendered::instance
                                = (uint)DAT_TileMapState::instance.PillarGFXLayer[iVar16];
                            if ((DAT_00ed3148::instance & 0x100000) == 0) {
                                DAT_00ed316c::instance = DAT_GmImageAddressToBeRendered::instance;
                                if ((uVar32 & 0x800) == 0) {
                                    MACRO_CALL(OpenSHC::Rendering_Func::BlitMapImageWithVerticalClip)();
                                } else {
                                    MACRO_CALL(OpenSHC::Rendering_Func::BlitMapImageWithVerticalClipAndYOffset)();
                                }
                                if (bVar14) {
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS,
                                        (int)((int)(DAT_RenderMap_ImageID::instance + 8)),
                                        (int)((int)(DAT_RenderMap_DrawSomeX::instance)),
                                        (int)((int)((DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance) + 9
                                            + DAT_RenderMap_DrawSomeY::instance)),
                                        0x18);
                                }
                            } else {
                                if (DAT_GmImageAddressToBeRendered::instance == 0x20) {
                                    DAT_GmImageAddressToBeRendered::instance
                                        = GMTotalPicturesProcessed::instance[9] + 0x1f;
                                } else {
                                    iVar16 = DAT_GmImageAddressToBeRendered::instance + this->unknownCounterUntil_0x10;
                                    if (0x32 < iVar16) {
                                        iVar16 = iVar16 + -0x10;
                                    }
                                    DAT_GmImageAddressToBeRendered::instance
                                        = iVar16 + -1 + GMTotalPicturesProcessed::instance[9];
                                    if ((0x20 < (int)DAT_00ed3170::instance)
                                        && ((int)(DAT_RenderMap_DrawSomeY::instance - DAT_00ed3170::instance)
                                            < local_5c + -0xa0)) {
                                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::notifyAmbientSoundEvent,
                                            DAT_SFXState::ptr)(6);
                                    }
                                }
                                DAT_00ed316c::instance = DAT_GmImageAddressToBeRendered::instance;
                                if ((uVar32 & 0x800) == 0)
                                    goto LAB_004eb9a4;
                                MACRO_CALL(OpenSHC::Rendering_Func::BlitMapImageWithVerticalClipAndYOffset)();
                            }
                        } else {
                            DAT_GmImageAddressToBeRendered::instance
                                = (uint)DAT_TileMapState::instance.WallGFXLayer[iVar16];
                            DAT_00ed316c::instance = DAT_GmImageAddressToBeRendered::instance;
                            if (local_54 != 0) {
                                DAT_00ed316c::instance = (uint)DAT_TileMapState::instance.PillarGFXLayer[iVar16];
                            }
                        LAB_004eb9a4:
                            MACRO_CALL(OpenSHC::Rendering_Func::BlitMapImageWithVerticalClip)();
                        }
                    }
                } else {
                    DAT_GmImageAddressToBeRendered::instance = GMTotalPicturesProcessed::instance[0x26] + 0x140;
                    DAT_RenderMap_YOffset::instance = 0;
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderTerrainTilesCenterPiece)();
                }
                DAT_RenderMap_DrawSomeX::instance = DAT_RenderMap_DrawSomeX::instance + 0x20;
            }
            iVar31 = _zoomOffset;
            if (_vpWidthPlus1 == _viewportHeight) {
                DAT_RenderMap_DrawSomeX::instance = this->viewportState.unknownScreenXRelated + 0x10;
                iVar16 = _viewportHeight;
            } else {
                iVar16 = _viewportHeight + 1;
                DAT_RenderMap_DrawSomeX::instance = this->viewportState.unknownScreenXRelated;
            }
            for (; iVar31 < iVar16; iVar31 = iVar31 + 1) {
                _yOffset_01 = this->screenPointToTileNumber[iVar31 + iVar2 + -8];
                DAT_00ed3148::instance = DAT_TileMapState::instance.LogicLayer[_yOffset_01];
                if ((DAT_00ed3148::instance & 0x30) == 0) {
                    if ((iVar31 < 2) || (bVar13 = true, iVar16 + -2 <= iVar31)) {
                        bVar13 = false;
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
                    if (_flatView) {
                        if (uVar29 == 0) {
                            if ((DAT_00ed3148::instance & 0x100) == 0) {
                                if ((((char)DAT_00ed3148::instance < '\0')
                                        && (1999 < DAT_TileMapState::instance.OrganismLayer[_yOffset_01]))
                                    && (iVar23 = DAT_TileMapState::instance.OrganismLayer[_yOffset_01] * 0x20,
                                        1 < *(short*)((int)&DAT_LandscapeState::instance.trees[0x636]
                                                          .appleTreeColorVariation
                                            + iVar23 + 2))) {
                                    iVar26
                                        = MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::getRandomRockImageOffset,
                                            DAT_LandscapeState::ptr)(
                                            ((byte)DAT_TileMapState::instance.RandomLayer[_yOffset_01] & 3) + 1);
                                    DAT_GmImageAddressToBeRendered::instance = iVar26 + -1
                                        + GMTotalPicturesProcessed::instance[*(
                                            short*)((int)&DAT_LandscapeState::instance.trees[0x636].animationFrameUnk
                                            + iVar23 + 2)];
                                }
                            } else if ((DAT_00ed3148::instance & 0x800) == 0) {
                                if ((DAT_00ed3148::instance & 0x200) != 0) {
                                    DAT_00ed3148::instance = DAT_00ed3148::instance & 1;
                                    DAT_GmImageAddressToBeRendered::instance = (DAT_00ed314c::instance & 3) + 0x24
                                        + GMTotalPicturesProcessed::instance[0x9d];
                                }
                            } else {
                                DAT_00ed3148::instance = DAT_00ed3148::instance & 1;
                                if ((DAT_GmImageAddressToBeRendered::instance
                                        == GMTotalPicturesProcessed::instance[0xc] + 0x86U)
                                    || (DAT_GmImageAddressToBeRendered::instance
                                        == GMTotalPicturesProcessed::instance[0xc] + 0x88U)) {
                                    DAT_GmImageAddressToBeRendered::instance
                                        = GMTotalPicturesProcessed::instance[0x9d] + 0x2a;
                                } else {
                                    DAT_GmImageAddressToBeRendered::instance
                                        = GMTotalPicturesProcessed::instance[0x9d] + 0x28;
                                }
                            }
                        } else {
                            BVar8 = DAT_BuildingsState::instance.buildings[uVar29].buildingType;
                            iVar23 = DAT_MapRenderDefinedData::instance.BuildingRenderSomeTypeArray[(short)BVar8];
                            if (iVar23 == 3) {
                                uVar22 = (uint)((*puVar1 & 4) != 0);
                                if (BVar8 == OpenSHC::Map::Buildings::BT_WOODCUTTERSHUT) {
                                    DAT_GmImageAddressToBeRendered::instance
                                        = uVar22 + 0x18 + GMTotalPicturesProcessed::instance[0x9d];
                                } else if (BVar8 == OpenSHC::Map::Buildings::BT_HUNTERSHUT) {
                                    DAT_GmImageAddressToBeRendered::instance
                                        = uVar22 + 0x1a + GMTotalPicturesProcessed::instance[0x9d];
                                } else if (BVar8 == OpenSHC::Map::Buildings::BT_DAIRYFARM) {
                                    DAT_GmImageAddressToBeRendered::instance
                                        = uVar22 + 0x1c + GMTotalPicturesProcessed::instance[0x9d];
                                } else {
                                    DAT_GmImageAddressToBeRendered::instance
                                        = uVar22 + 0x1e + GMTotalPicturesProcessed::instance[0x9d];
                                }
                            } else if (-1 < iVar23) {
                                DAT_GmImageAddressToBeRendered::instance = (DAT_00ed314c::instance & 3)
                                    + GMTotalPicturesProcessed::instance[0x9d] + ((uVar29 & 1) + iVar23 * 2) * 4;
                            }
                        }
                        DAT_RenderMap_YOffset::instance = 8;
                    }
                    if (uVar29 != 0) {
                        if (((local_1c < viewportWidth) && (bVar13)) && (4 < iVar31)) {
                            psVar17 = &DAT_BuildingsState::instance.buildings[uVar29].surfaceAreaUnk;
                            *psVar17 = *psVar17 + 1;
                        }
                        uVar9 = *this->viewportState.ptrColor;
                        *this->viewportState.ptrColor = COL_MAGENTA::instance.shortValue;
                        if ((DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance].direction != 0)
                            && (bVar13)) {
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
                                (int)((int)(((DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance) - iVar23)
                                    + DAT_RenderMap_DrawSomeY::instance)),
                                (int)((int)((
                                    char)DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance]
                                        .buildingWidth)),
                                iVar23 + 7,
                                (ushort*)((int)(

                                    (DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance] + 0x200
                                        + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))));
                        }
                        if ((!_flatView)
                            || (DAT_MapRenderDefinedData::instance.BuildingRenderSomeTypeArray
                                    [(short)DAT_BuildingsState::instance.buildings[uVar29].buildingType]
                                < 0)) {
                            if ((DAT_BuildingsState::instance.buildings[uVar29].buildingType
                                    == OpenSHC::Map::Buildings::BT_DRAWBRIDGE)
                                && ((DAT_TileMapState::instance.refreshRelatedOne != 0
                                    && (_yOffset_01
                                        == this->translationMatrix
                                                [(short)DAT_BuildingsState::instance.buildings[uVar29].y + 2]
                                                    .addXgetTile
                                            + 2 + (int)(short)DAT_BuildingsState::instance.buildings[uVar29].x)))) {
                                MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::renderBuildingAnimation,
                                    this)(uVar29, (int)((int)(DAT_RenderMap_DrawSomeX::instance + 0x10)),
                                    (int)((int)(DAT_00ed3154::instance + 0x18 + DAT_RenderMap_DrawSomeY::instance)),
                                    (undefined4)((int)(_yOffset_01)), 1);
                            }
                            uVar10 = *puVar1;
                            if ((uVar10 & 0xc) != 0) {
                                if (DAT_BuildingsState::instance.buildings[uVar29].buildingType
                                    == OpenSHC::Map::Buildings::BT_DRAWBRIDGE) {
                                    if (DAT_TileMapState::instance.refreshRelatedOne != 0) {
                                        if ((uVar10 & 0xc) == 0xc) {
                                            MACRO_CALL_MEMBER(
                                                OpenSHC::Rendering::ViewportRenderState_Func::renderBuildingAnimation,
                                                this)(uVar29, (int)((int)(DAT_RenderMap_DrawSomeX::instance + 0x10)),
                                                (int)((int)(DAT_00ed3154::instance + 0x28
                                                    + DAT_RenderMap_DrawSomeY::instance)),
                                                (undefined4)((int)(_yOffset_01)), 0);
                                        } else if ((uVar10 & 8) != 0) {
                                            MACRO_CALL_MEMBER(
                                                OpenSHC::Rendering::ViewportRenderState_Func::renderGmOverlayBuilding,
                                                this)(uVar29, (int)((int)(DAT_RenderMap_DrawSomeX::instance)),
                                                (int)((int)((DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance)
                                                    + DAT_RenderMap_DrawSomeY::instance)),
                                                _yOffset_01);
                                        }
                                    }
                                } else {
                                    iVar23 = (DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance)
                                        + DAT_RenderMap_DrawSomeY::instance;
                                    if ((uVar10 & 8) == 0) {
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::Rendering::ViewportRenderState_Func::renderGmOverlayBuilding2,
                                            this)(uVar29, (int)((int)(DAT_RenderMap_DrawSomeX::instance)), iVar23,
                                            _yOffset_01);
                                    } else {
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::Rendering::ViewportRenderState_Func::renderGmOverlayBuilding,
                                            this)(uVar29, (int)((int)(DAT_RenderMap_DrawSomeX::instance)), iVar23,
                                            _yOffset_01);
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
                    if (((DAT_00ed3148::instance & 8) != 0) && ((*puVar1 & 0x4000) != 0)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                            (int)((int)(DAT_TileMapState::instance.field161_0x5549c0)),
                            (int)((int)(DAT_RenderMap_DrawSomeX::instance + -0x23)),
                            (int)((int)((DAT_00ed3154::instance - DAT_RenderMap_YOffset::instance) + -0x4a
                                + DAT_RenderMap_DrawSomeY::instance)),
                            OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                            (int)((int)(DAT_TileMapState::instance.field161_0x5549c0 + 0x10)), 0);
                        *puVar1 = *puVar1 & 0xbfff;
                    }
                    iVar23 = DAT_RenderMap_YOffset::instance;
                    if (uVar32 != 0) {
                        if ((DAT_TileMapState::instance.refreshRelatedOne != 0) && (!_flatView)) {
                            if ((DAT_TileMapState::instance.LogicLayer[_yOffset_01] & 0x10000000U) == 0) {
                                if ((DAT_TileMapState::instance.LogicLayer[_yOffset_01] & 0x100U) != 0) {
                                    if (DAT_TileMapState::instance.BuildingLayer[_yOffset_01] == 0) {
                                        iVar23 = DAT_RenderMap_YOffset::instance + 4;
                                    } else if (DAT_BuildingsState::instance
                                                   .buildings[DAT_TileMapState::instance.BuildingLayer[_yOffset_01]]
                                                   .buildingType
                                        == OpenSHC::Map::Buildings::BT_WOODGATE1) {
                                        iVar23 = DAT_RenderMap_YOffset::instance + 6;
                                    } else {
                                        iVar23 = DAT_RenderMap_YOffset::instance + 0x14;
                                    }
                                }
                            } else {
                                iVar26 = MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                                    DAT_BuildingsState::ptr)(
                                    (int)DAT_TileMapState::instance.BuildingLayer[_yOffset_01]);
                                iVar23 = iVar23 + iVar26;
                            }
                        }
                        do {
                            uVar29 = this->floatersArray[uVar32].variation;
                            if ((uVar29 & 1) != 0) {
                                iVar26 = iVar23;
                                if (((((uVar29 & 8) != 0) && (DAT_TileMapState::instance.refreshRelatedOne != 0))
                                        && (!_flatView))
                                    && (iVar26 = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAt,
                                            DAT_TileMapState::ptr)(_yOffset_01, 0),
                                        iVar26 < 0)) {
                                    iVar26 = -1 - iVar26;
                                }
                                if ((*puVar1 & 0x10) == 0) {
                                    uVar29 = this->floatersArray[uVar32].variation;
                                    if ((uVar29 & 4) != 0) {
                                        DAT_RenderedUnitOwner::instance = ~-(uint)((uVar29 & 0x10) != 0)
                                            & DAT_GameSynchronyState::instance.currentPlayerSlotID;
                                        DAT_CurrentlyRenderedSpriteID::instance = this->floatersArray[uVar32].gmID;
                                        uVar29 = this->floatersArray[uVar32].variation;
                                    }
                                    if ((uVar29 & 0x20) == 0) {
                                        if ((uVar29 & 0xffff0000) == 0) {
                                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                DAT_TextureRenderCoreObject::ptr)((eGM)this->floatersArray[uVar32].gmID,
                                                this->floatersArray[uVar32].imageID,
                                                (int)((int)(this->floatersArray[uVar32].originX
                                                    + DAT_RenderMap_DrawSomeX::instance)),
                                                (int)((int)((this->floatersArray[uVar32].originY - iVar26)
                                                    + DAT_RenderMap_DrawSomeY::instance)));
                                        } else {
                                            MACRO_CALL_MEMBER(
                                                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                                DAT_TextureRenderCoreObject::ptr)(
                                                (GmID)this->floatersArray[uVar32].gmID,
                                                this->floatersArray[uVar32].imageID,
                                                (int)((int)(this->floatersArray[uVar32].originX
                                                    + DAT_RenderMap_DrawSomeX::instance)),
                                                (int)((int)((this->floatersArray[uVar32].originY - iVar26)
                                                    + DAT_RenderMap_DrawSomeY::instance)),
                                                (int)((int)(uVar29 >> 0x10)));
                                        }
                                    } else {
                                        iVar18 = this->floatersArray[uVar32].imageID;
                                        GVar11 = (GmID)this->floatersArray[uVar32].gmID;
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                            DAT_TextureRenderCoreObject::ptr)((GmID)GVar11, iVar18,
                                            (int)((int)(this->floatersArray[uVar32].originX
                                                + DAT_RenderMap_DrawSomeX::instance)),
                                            (int)((int)((this->floatersArray[uVar32].originY - iVar26)
                                                + DAT_RenderMap_DrawSomeY::instance)),
                                            GVar11, ((int)uVar29 >> 0x10) + iVar18, 0);
                                    }
                                } else {
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::Rendering::ViewportRenderState_Func::scheduleUnitForBatchedRendering,
                                        this)(0,
                                        this->floatersArray[uVar32].originX + DAT_RenderMap_DrawSomeX::instance,
                                        (this->floatersArray[uVar32].originY - iVar26)
                                            + DAT_RenderMap_DrawSomeY::instance,
                                        (undefined4)((int)(this->floatersArray[uVar32].imageID)),
                                        (undefined4)((int)(this->floatersArray[uVar32].variation)),
                                        (undefined4)((int)(this->floatersArray[uVar32].gmID)), 0);
                                }
                            }
                            uVar32 = this->floatersArray[uVar32].id;
                        } while (uVar32 != 0);
                    }
                    DAT_TileMapState::instance.ConstructionGFXLayer[_yOffset_01] = 0;
                    *puVar1 = *puVar1 & 0x7fff;
                }
                DAT_RenderMap_DrawSomeX::instance = DAT_RenderMap_DrawSomeX::instance + 0x20;
            }
            if (iVar16 == _viewportHeight) {
                _vpWidthPlus1_1 = _viewportHeight;
                local_c = 200;
                DAT_RenderMap_DrawSomeX::instance = this->viewportState.unknownScreenXRelated + 0x10;
            } else {
                _vpWidthPlus1_1 = _viewportHeight + 1;
                local_c = 0xc9;
                DAT_RenderMap_DrawSomeX::instance = this->viewportState.unknownScreenXRelated;
            }
            if ((!_flatView) && (local_48 = _zoomOffset, _zoomOffset < _vpWidthPlus1_1)) {
                local_20 = this->screenPointToTileNumber + _zoomOffset + iVar2 + -8;
                do {
                    iVar31 = *local_20;
                    DAT_GmImageAddressToBeRendered::instance = (uint)DAT_TileMapState::instance.AlphaGFXLayer[iVar31];
                    if ((DAT_GmImageAddressToBeRendered::instance != 0)
                        && ((DAT_TileMapState::instance.MiscDisplayLayer[iVar31] & 0x3c0) == 0)) {
                        if ((local_48 < 2) || (_vpWidthPlus1_1 + -2 <= local_48)) {
                            bVar13 = false;
                        } else {
                            bVar13 = true;
                        }
                        DAT_00ed3148::instance = DAT_TileMapState::instance.LogicLayer[iVar31];
                        if ((DAT_00ed3148::instance & 0x400) != 0) {
                            psVar17 = &DAT_BuildingsState::instance
                                           .buildings[DAT_TileMapState::instance.BuildingLayer[iVar31]]
                                           .tickRelatedVisuallyActiveIndicator;
                            sVar30 = *psVar17;
                            if (((0 < sVar30) && (sVar30 < 5)) && (bVar13)) {
                                DAT_00ed3170::instance = (uint)DAT_TileMapState::instance.ShowHiLayer[iVar31];
                                DAT_RenderMap_YOffset::instance
                                    = DAT_TileMapState::instance
                                          .heightBasedScreenYOffset[DAT_TileMapState::instance.HeightLayer[iVar31]];
                                MACRO_CALL(OpenSHC::Rendering_Func::ApplyBlending)(((int)sVar30 << 5) / 5);
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
                                        (int)((int)((char)DAT_GMImageHeaders::instance
                                                .imh[DAT_GmImageAddressToBeRendered::instance]
                                                .buildingWidth)),
                                        iVar31 + 7,
                                        (ushort*)((int)(

                                            (DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance]
                                                + 0x200
                                                + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))),
                                        (int)((int)((*psVar17 << 5) / 5)));
                                }
                            }
                        }
                    }
                    local_20 = local_20 + 1;
                    DAT_RenderMap_DrawSomeX::instance = DAT_RenderMap_DrawSomeX::instance + 0x20;
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
        if ((DAT_TileMapState::instance.mapSize == 0xa0)
            && (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_1024x768)) {
            if (this->viewportState.isZoomedOutUnk != 0) {
                if ((DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SIEGETOWER)
                    || (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD)) {
                    DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(0, 0x2cc, 0xfd8, 0x2cc, 0x1a);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(0, 0x2cd, 0xfd8, 0x2cd, 0x14);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(0, 0x2ce, 0xfd8, 0x2ce, 0xe);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(0, 0x2cf, 0xfd8, 0x2cf, 8);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
                        0, 0x2d0, 0xfd8, 0x7f1, (ushort)((int)(COL_BLACK::instance.shortValue)));
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
            viewportWidth = this->viewportState.currentCameraOffsetX + 0xa0 + DAT_MouseState::instance.screenSpaceX * 2;
        }
        if (this->viewportState.field0_0x0 != 0) {
            if (DAT_MouseState::instance.field68_0x1dc < 0x3e9) {
                if (DAT_MouseState::instance.field68_0x1dc != 1000) {
                    switch (DAT_MouseState::instance.field68_0x1dc) {
                    case 1:
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_CURSORS, 0x51,
                            viewportWidth
                                - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[0x6b].originX,
                            (_viewportHeight
                                - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[0x6b].originY)
                                + 0x2d);
                        break;
                    case 3:
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)((GmID)DAT_TileMapState::instance.field163_0x5549c8,
                            (int)((int)(DAT_TileMapState::instance.field162_0x5549c4 + 0x10
                                + DAT_TileMapState::instance.field161_0x5549c0)),
                            viewportWidth
                                - DAT_TextureRenderCoreObject::instance
                                    .gmFileHeaderColorpaletteArray[DAT_TileMapState::instance.field163_0x5549c8]
                                    .originX,
                            _viewportHeight
                                - DAT_TextureRenderCoreObject::instance
                                    .gmFileHeaderColorpaletteArray[DAT_TileMapState::instance.field163_0x5549c8]
                                    .originY,
                            0x15);
                    case 2:
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)((eGM)DAT_TileMapState::instance.field163_0x5549c8,
                            (int)((int)(DAT_TileMapState::instance.field162_0x5549c4
                                + DAT_TileMapState::instance.field161_0x5549c0)),
                            viewportWidth
                                - DAT_TextureRenderCoreObject::instance
                                    .gmFileHeaderColorpaletteArray[DAT_TileMapState::instance.field163_0x5549c8]
                                    .originX,
                            _viewportHeight
                                - DAT_TextureRenderCoreObject::instance
                                    .gmFileHeaderColorpaletteArray[DAT_TileMapState::instance.field163_0x5549c8]
                                    .originY);
                        break;
                    case 4:
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)((eGM)DAT_TileMapState::instance.field163_0x5549c8,
                            (int)((int)(DAT_TileMapState::instance.field162_0x5549c4)), viewportWidth + -8,
                            _viewportHeight + -8);
                        break;
                    case 5:
                        iVar28 = DAT_TileMapState::instance.field165_0x5549d0
                                % DAT_TileMapState::instance.field164_0x5549cc
                            + DAT_TileMapState::instance.field162_0x5549c4;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)((GmID)DAT_TileMapState::instance.field163_0x5549c8,
                            iVar28,
                            viewportWidth
                                - DAT_TextureRenderCoreObject::instance
                                    .gmFileHeaderColorpaletteArray[DAT_TileMapState::instance.field163_0x5549c8]
                                    .originX,
                            _viewportHeight
                                - DAT_TextureRenderCoreObject::instance
                                    .gmFileHeaderColorpaletteArray[DAT_TileMapState::instance.field163_0x5549c8]
                                    .originY,
                            (GmID)((int)(DAT_TileMapState::instance.field163_0x5549c8)),
                            DAT_TileMapState::instance.field164_0x5549cc + iVar28, 0);
                    }
                    goto switchD_004ec5fa_default;
                }
                DAT_TextureRenderCoreObject::instance.isZoom2 = 0;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x7b, iVar31 + 0x1c, iVar28 + 4);
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    "(", iVar31 + 0x3c, iVar28 + 7, OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 0x12, FALSE, 0);
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
                if (DAT_MouseState::instance.field68_0x1dc != 0x3e9)
                    goto switchD_004ec5fa_default;
                DAT_TextureRenderCoreObject::instance.isZoom2 = 0;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x7e, iVar31 + 0x1c, iVar28 + 4);
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    "(", iVar31 + 0x3c, iVar28 + 7, OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 0x12, FALSE, 0);
                _numberToDisplay
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .currentResources[2]
                    - DAT_TileMapState::instance.wallPlacementCost;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                _numberToDisplay, iVar31 + 0x3c, iVar28 + 7, OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                ")", iVar31 + 0x3c, iVar28 + 7, OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 0x12, TRUE, 0);
            DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        }
    switchD_004ec5fa_default:
        DAT_MouseState::instance.field68_0x1dc = -1;
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::clearAllFloatingLayerElements, this)();
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMapSurfaceHeightRangeUnk,
            DAT_TextureRenderCoreObject::ptr)();
        DAT_TextureRenderCoreObject::instance.isZoom2 = 0;
        DAT_TileMapState::instance.field159_0x5549b8 = 0;
        return;
    switchD_004eb2c9_caseD_4d:
        MACRO_CALL_MEMBER(OpenSHC::Rendering::ViewportRenderState_Func::scheduleUnitForBatchedRendering, this)(
            0xffffffff,
            ((int)DAT_EntityState::instance.entityArray[local_58].x1
                - (int)DAT_EntityState::instance.entityArray[local_58].originX)
                + DAT_RenderMap_DrawSomeX::instance,
            (((int)DAT_EntityState::instance.entityArray[local_58].y1
                 - (int)DAT_EntityState::instance.entityArray[local_58].originY)
                - iVar26)
                + DAT_RenderMap_DrawSomeY::instance,
            (undefined4)((int)(DAT_EntityState::instance.entityArray[local_58].graphicType2)),
            (undefined4)((int)((int)DAT_EntityState::instance.entityArray[local_58].unkMinusOne)),
            (undefined4)((int)((int)DAT_EntityState::instance.entityArray[local_58].imageID)), 0);
        _yOffset_01 = DAT_RenderMap_YOffset::instance;
        goto LAB_004eb439;
    }

}
}
