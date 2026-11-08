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
                if (healthImage >= 0 && healthImage <= 10) {
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
                    int const animationTick = (DAT_TileMapState::instance.cursorOverlayAnimationFrame - 1) % 8;
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
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 79, screenY - 76);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage6;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 36, screenY - 102);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage7;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 43, screenY - 41);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 64, screenY - 118);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 36, screenY - 102);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 53, screenY - 59);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].overlayImageID;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 72, screenY - 87);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage10;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 79, screenY - 115);
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
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 20, screenY - 88);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage6;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 47, screenY - 84);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage7;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 17, screenY - 32);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 23, screenY - 103);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 15, screenY - 39);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 56, screenY - 45);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].overlayImageID;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 25, screenY - 76);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage10;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 58, screenY - 124);
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
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 15, screenY - 66);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage6;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 13, screenY - 178);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage7;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 9, screenY - 252);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX, screenY - 108);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 13, screenY - 189);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 15, screenY - 217);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].overlayImageID;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 8, screenY - 49);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage10;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 11, screenY - 90);
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
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 9, screenY - 59);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage6;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 49, screenY - 45);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage7;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 43, screenY - 36);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 25, screenY - 69);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 38, screenY - 85);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 22, screenY - 36);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].overlayImageID;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 16, screenY - 22);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage10;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 50, screenY - 94);
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
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 57, screenY - 96);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage6;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 19, screenY - 22);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage7;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 35, screenY - 131);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 25, screenY - 129);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 49, screenY - 47);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 46, screenY - 96);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].overlayImageID;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 16, screenY - 106);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage10;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 32, screenY - 91);
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
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 65, screenY - 159);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage6;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 37, screenY - 97);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage7;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 75, screenY - 65);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 65, screenY - 69);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 38, screenY - 115);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 19, screenY - 59);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].overlayImageID;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 54, screenY - 139);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage10;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 66, screenY - 110);
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
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 51, screenY - 127);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage6;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 4, screenY - 91);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage7;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 41, screenY - 122);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 33, screenY - 69);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 40, screenY - 89);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 22, screenY - 55);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].overlayImageID;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX - 22, screenY - 132);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage10;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 58, screenY - 66);
                    }
                }
            }
        }
        if ((DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag != 0)
            && (DAT_BuildingsState::instance.buildings[buildingID].buildingType
                == OpenSHC::Map::Buildings::BT_OXTETHER)) {
            DAT_RenderedUnitOwner::instance = DAT_BuildingsState::instance.buildings[buildingID].playerColorUnk;
            frame = DAT_BuildingsState::instance.buildings[buildingID].overlayImageID;
            DAT_CurrentlyRenderedSpriteID::instance = 189;
            if (frame != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, screenX - 30, screenY - 67);
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
        if (buildingType == OpenSHC::Map::Buildings::BT_KILLINGPIT
            && DAT_BuildingsState::instance.buildings[buildingID].owner
                != DAT_GameSynchronyState::instance.currentPlayerSlotID
            && DAT_BuildingsState::instance.buildings[buildingID].state < 1) {
            return;
        }
        // the field, not buildingType: testing the local lets MSVC jump the killing-pit paths past this check
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
                    DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY + screenY, blendStrength);
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
