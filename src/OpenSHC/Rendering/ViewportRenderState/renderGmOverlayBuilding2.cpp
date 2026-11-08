#include "../ViewportRenderState.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentlyRenderedSpriteID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_RenderedUnitOwner.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Rendering {

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::IO::Graphics::GmID;
    using OpenSHC::Map::MapType2;
    using OpenSHC::Map::Buildings::Building;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Buildings::BuildingTypeShort;
    using OpenSHC::UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004E2AD0
    void ViewportRenderState::renderGmOverlayBuilding2(int buildingID, int screenX, int screenY, int tile)
    {
        BuildingTypeShort buildingType;

        int heightOffset = 0;
        if (DAT_BuildingDefinedData::instance
                .BuildingHeights[DAT_BuildingsState::instance.buildings[buildingID].buildingType]
            == 0) {
            heightOffset = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight << 5;
        }
        if ((int)DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight <= 2) {
            int healthBarYOffset = 0;
            if ((((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU)
                     && (buildingID == DAT_BuildingsState::instance.menuSelectedBuildingID))
                    || ((buildingID == DAT_BuildingsState::instance.selectedBuildingID
                        && (DAT_BuildingsState::instance.selectedBuildingUID
                            == DAT_BuildingsState::instance.buildings[buildingID].uid))))
                && DAT_BuildingsState::instance.buildings[buildingID].maxHealth != 0) {
                int const maxHealth = DAT_BuildingsState::instance.buildings[buildingID].maxHealth;
                int healthPercent;
                if (maxHealth == 0) {
                    healthPercent = 100;
                } else {
                    healthPercent
                        = (DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 100) / maxHealth;
                }
                int const healthImage = healthPercent / 10;
                switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
                case OpenSHC::Map::Buildings::BT_GALLOWS:
                case OpenSHC::Map::Buildings::BT_GIBBET:
                    healthBarYOffset = 80;
                    break;
                case OpenSHC::Map::Buildings::BT_TOWER1:
                    healthBarYOffset = 30;
                    break;
                }
                if ((uint)healthImage <= 10) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_FLOATS, healthImage + 17, screenX + 4,
                        screenY
                            - DAT_BuildingDefinedData::instance
                                .BuildingHeights[DAT_BuildingsState::instance.buildings[buildingID].buildingType]
                            - healthBarYOffset - 12);
                }
            }
            if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk)
                || (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_SIEGE)) {
                if (DAT_BuildingsState::instance.buildings[buildingID].sleeping) {
                    int const animationTick = ((int)DAT_TileMapState::instance.cursorOverlayAnimationFrame - 1) % 8;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOAT_POP_CIRC,
                        animationTick + 203, screenX - 35,
                        screenY
                            - DAT_BuildingDefinedData::instance
                                .BuildingHeights[DAT_BuildingsState::instance.buildings[buildingID].buildingType]
                            - heightOffset - 42,
                        OpenSHC::IO::Graphics::GID_FLOAT_POP_CIRC, animationTick + 211, 0);
                } else if (DAT_BuildingsState::instance.buildings[buildingID].currentlyNeededEmployeeCount != 0
                    && DAT_GameCore::instance.field_0x108 != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                        DAT_TileMapState::instance.cursorOverlayAnimationFrame + 280, screenX - 35,
                        screenY
                            - DAT_BuildingDefinedData::instance
                                .BuildingHeights[DAT_BuildingsState::instance.buildings[buildingID].buildingType]
                            - heightOffset - 42,
                        OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                        DAT_TileMapState::instance.cursorOverlayAnimationFrame + 296, 0);
                }
            }
            short const bannerState = DAT_BuildingsState::instance.buildings[buildingID].field_0xc2;
            if (bannerState == 1) {
                int const maskImage = DAT_TileMapState::instance.cursorOverlayAnimationFrame + 16;
                int const overlayImage = DAT_TileMapState::instance.cursorOverlayAnimationFrame;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW, overlayImage, screenX - 35,
                    screenY
                        - DAT_BuildingDefinedData::instance
                            .BuildingHeights[DAT_BuildingsState::instance.buildings[buildingID].buildingType]
                        - heightOffset - 42,
                    OpenSHC::IO::Graphics::GID_FLOATS_NEW, maskImage, 0);
                DAT_BuildingsState::instance.buildings[buildingID].field_0xc2 = 0;
            } else if (bannerState == 2) {
                int const maskImage = DAT_TileMapState::instance.cursorOverlayAnimationFrame + 132;
                int const overlayImage = DAT_TileMapState::instance.cursorOverlayAnimationFrame + 116;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW, overlayImage, screenX - 35,
                    screenY
                        - DAT_BuildingDefinedData::instance
                            .BuildingHeights[DAT_BuildingsState::instance.buildings[buildingID].buildingType]
                        - heightOffset - 42,
                    OpenSHC::IO::Graphics::GID_FLOATS_NEW, maskImage, 0);
                DAT_BuildingsState::instance.buildings[buildingID].field_0xc2 = 0;
            }
        }
        int frame;
        if (DAT_BuildingsState::instance.buildings[buildingID].useOffsetGraphics == 0) {
            switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
            case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                if (5
                        - (DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 5)
                            / DAT_BuildingsState::instance.buildings[buildingID].maxHealth
                    != 0) {
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage5;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x4f, screenY + -0x4c);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage6;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x24, screenY + -0x66);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage7;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x2b, screenY + -0x29);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x40, screenY + -0x76);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x24, screenY + -0x66);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x35, screenY + -0x3b);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].overlayImageID;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x48, screenY + -0x57);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage10;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x4f, screenY + -0x73);
                    }
                }
                break;
            case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                if (5
                        - (DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 5)
                            / DAT_BuildingsState::instance.buildings[buildingID].maxHealth
                    != 0) {
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage5;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x14, screenY + -0x58);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage6;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x2f, screenY + -0x54);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage7;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x11, screenY + -0x20);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x17, screenY + -0x67);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0xf, screenY + -0x27);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x38, screenY + -0x2d);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].overlayImageID;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x19, screenY + -0x4c);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage10;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x3a, screenY + -0x7c);
                    }
                }
                break;
            case OpenSHC::Map::Buildings::BT_TOWER1:
                if (5
                        - (DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 5)
                            / DAT_BuildingsState::instance.buildings[buildingID].maxHealth
                    != 0) {
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage5;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0xf, screenY + -0x42);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage6;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0xd, screenY + -0xb2);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage7;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -9, screenY + -0xfc);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX, screenY + -0x6c);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0xd, screenY + -0xbd);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0xf, screenY + -0xd9);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].overlayImageID;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 8, screenY + -0x31);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage10;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0xb, screenY + -0x5a);
                    }
                }
                break;
            case OpenSHC::Map::Buildings::BT_TOWER2:
                if (5
                        - (DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 5)
                            / DAT_BuildingsState::instance.buildings[buildingID].maxHealth
                    != 0) {
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage5;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -9, screenY + -0x3b);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage6;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x31, screenY + -0x2d);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage7;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x2b, screenY + -0x24);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x19, screenY + -0x45);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x26, screenY + -0x55);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x16, screenY + -0x24);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].overlayImageID;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x10, screenY + -0x16);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage10;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x32, screenY + -0x5e);
                    }
                }
                break;
            case OpenSHC::Map::Buildings::BT_TOWER3:
                if (5
                        - (DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 5)
                            / DAT_BuildingsState::instance.buildings[buildingID].maxHealth
                    != 0) {
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage5;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x39, screenY + -0x60);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage6;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x13, screenY + -0x16);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage7;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x23, screenY + -0x83);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x19, screenY + -0x81);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x31, screenY + -0x2f);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x2e, screenY + -0x60);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].overlayImageID;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x10, screenY + -0x6a);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage10;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x20, screenY + -0x5b);
                    }
                }
                break;
            case OpenSHC::Map::Buildings::BT_TOWER4:
                if (5
                        - (DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 5)
                            / DAT_BuildingsState::instance.buildings[buildingID].maxHealth
                    != 0) {
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage5;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x41, screenY + -0x9f);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage6;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x25, screenY + -0x61);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage7;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x4b, screenY + -0x41);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x41, screenY + -0x45);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x26, screenY + -0x73);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x13, screenY + -0x3b);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].overlayImageID;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x36, screenY + -0x8b);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage10;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x42, screenY + -0x6e);
                    }
                }
                break;
            case OpenSHC::Map::Buildings::BT_TOWER5:
                if (5
                        - (DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 5)
                            / DAT_BuildingsState::instance.buildings[buildingID].maxHealth
                    != 0) {
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage5;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x33, screenY + -0x7f);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage6;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 4, screenY + -0x5b);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage7;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x29, screenY + -0x7a);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x21, screenY + -0x45);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x28, screenY + -0x59);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x16, screenY + -0x37);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].overlayImageID;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x16, screenY + -0x84);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage10;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x3a, screenY + -0x42);
                    }
                }
            }
        }
        if ((DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag != 0)
            && (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == OpenSHC::Map::Buildings::BT_OXTETHER)) {
            DAT_RenderedUnitOwner::instance = DAT_BuildingsState::instance.buildings[buildingID].playerColorUnk;
            frame = DAT_BuildingsState::instance.buildings[buildingID].overlayImageID;
            DAT_CurrentlyRenderedSpriteID::instance = 0xbd;
            if (frame != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, screenX + -0x1e, screenY + -0x43);
            }
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].renderAnimation == 0) {
            return;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].animationFrame == 0) {
            return;
        }
        if (DAT_TileMapState::instance.disableElevationRendering != 0) {
            return;
        }
        DAT_CurrentlyRenderedSpriteID::instance = (GmID)DAT_BuildingsState::instance.buildings[buildingID].spriteID2;
        buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
        DAT_RenderedUnitOwner::instance = 0;
        // the field, not buildingType: testing the local lets MSVC jump the killing-pit paths past this check
        if (buildingType == OpenSHC::Map::Buildings::BT_KILLINGPIT
            && DAT_BuildingsState::instance.buildings[buildingID].owner
                != DAT_GameSynchronyState::instance.currentPlayerSlotID
            && DAT_BuildingsState::instance.buildings[buildingID].state < 1) {
            return;
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_DRAWBRIDGE) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::temporarySaveMapSurfaceHeightRangeUnk,
                DAT_TextureRenderCoreObject::ptr)();
            if (DAT_BuildingsState::instance.buildings[buildingID].drawBridgeState1 == 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMapSurfaceHeightRange,
                    DAT_TextureRenderCoreObject::ptr)(screenY - 23 < 0 ? 0 : screenY - 23, 2076);
            }
        }
        buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
        if (buildingType == OpenSHC::Map::Buildings::BT_TOWER2) {
            if (DAT_BuildingsState::instance.buildings[buildingID].useOffsetGraphics == 0) {
                int frame = DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2;
                if (frame != 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, screenX - 36, screenY - 120);
                }
                frame = DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite4;
                if (frame != 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, screenX + 32, screenY - 113);
                }
            }
        } else if (buildingType == OpenSHC::Map::Buildings::BT_TOWER3) {
            if (DAT_BuildingsState::instance.buildings[buildingID].useOffsetGraphics == 0) {
                int frame = DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2;
                if (frame != 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, screenX - 36, screenY - 119);
                }
                frame = DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite4;
                if (frame != 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, screenX + 46, screenY - 119);
                }
            }
        } else if (buildingType == OpenSHC::Map::Buildings::BT_TOWER4) {
            if (DAT_BuildingsState::instance.buildings[buildingID].useOffsetGraphics == 0) {
                int frame = DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2;
                if (frame != 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, screenX - 52, screenY - 130);
                }
                frame = DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite4;
                if (frame != 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, screenX + 48, screenY - 125);
                }
            }
        } else if (buildingType == OpenSHC::Map::Buildings::BT_TOWER5) {
            if (DAT_BuildingsState::instance.buildings[buildingID].useOffsetGraphics == 0) {
                int frame = DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2;
                if (frame != 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, screenX - 51, screenY - 130);
                }
                frame = DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite4;
                if (frame != 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, screenX + 49, screenY - 124);
                }
            }
        } else {
            DAT_RenderedUnitOwner::instance = DAT_BuildingsState::instance.buildings[buildingID].playerColorUnk;
            short blendStrength = DAT_BuildingsState::instance.buildings[buildingID].renderBlendStrength;
            DAT_CurrentlyRenderedSpriteID::instance
                = (GmID)DAT_BuildingsState::instance.buildings[buildingID].spriteID2;
            if (blendStrength != 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)((GmID)DAT_CurrentlyRenderedSpriteID::instance,
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame,
                    DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX + screenX,
                    DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY + screenY,
                    (int)((int)(blendStrength)));
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)((eGM)DAT_CurrentlyRenderedSpriteID::instance,
                    DAT_BuildingsState::instance.buildings[buildingID].animationFrame,
                    DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX + screenX,
                    DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY + screenY);
            }
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_DRAWBRIDGE) {
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::restoreMapSurfaceHeightRangeFromTemporaryUnk,
                DAT_TextureRenderCoreObject::ptr)();
        }
    }

}
}
