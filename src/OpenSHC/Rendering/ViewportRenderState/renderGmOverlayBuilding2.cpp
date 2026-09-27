#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
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

    // FUNCTION: STRONGHOLDCRUSADER 0x004E2AD0
    void ViewportRenderState::renderGmOverlayBuilding2(int buildingID, int screenX, int screenY, int tile)

    {
        BuildingTypeShort buildingType;
        uint animationTick;
        int renderX;
        int renderY;
        int renderBaseY;
        GmID gmID;
        GmID maskGmID;

        int heightOffset = 0;
        if (DAT_BuildingDefinedData::instance
                .BuildingHeights[DAT_BuildingsState::instance.buildings[buildingID].buildingType]
            == 0) {
            heightOffset = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight << 5;
        }
        if ((int)DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight <= 2) {
            int healthBarYOffset = 0;
            short maxHealth;
            if ((((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU)
                     && (buildingID == DAT_BuildingsState::instance.menuSelectedBuildingID))
                    || ((buildingID == DAT_BuildingsState::instance.field28_0x18e05c
                        && (DAT_BuildingsState::instance.field29_0x18e060
                            == DAT_BuildingsState::instance.buildings[buildingID].uid))))
                && (maxHealth = DAT_BuildingsState::instance.buildings[buildingID].maxHealth, maxHealth != 0)) {
                if ((int)maxHealth == 0) {
                    renderY = 100;
                } else {
                    renderY = (DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 100) / (int)maxHealth;
                }
                buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
                if (buildingType == OpenSHC::Map::Buildings::BT_GALLOWS) {
                    healthBarYOffset = 0x50;
                } else if (buildingType == OpenSHC::Map::Buildings::BT_TOWER1) {
                    healthBarYOffset = 0x1e;
                } else if (buildingType == OpenSHC::Map::Buildings::BT_GIBBET) {
                    healthBarYOffset = 0x50;
                }
                if ((uint)(renderY / 10) < 0xb) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_FLOATS, renderY / 10 + 0x11,
                        screenX + 4,
                        ((screenY
                             - DAT_BuildingDefinedData::instance
                                 .BuildingHeights[DAT_BuildingsState::instance.buildings[buildingID].buildingType])
                            - healthBarYOffset)
                            + -0xc);
                }
            }
            if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk)
                || (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_SIEGE)) {
                if (DAT_BuildingsState::instance.buildings[buildingID].sleeping != false) {
                    animationTick = DAT_TileMapState::instance.field161_0x5549c0 - 1U & 0x80000007;
                    if ((int)animationTick < 0) {
                        animationTick = (animationTick - 1 | 0xfffffff8) + 1;
                    }
                    renderY = animationTick + 0xd3;
                    maskGmID = OpenSHC::IO::Graphics::GID_FLOAT_POP_CIRC;
                    renderBaseY
                        = (screenY
                              - DAT_BuildingDefinedData::instance
                                  .BuildingHeights[DAT_BuildingsState::instance.buildings[buildingID].buildingType])
                        - heightOffset;
                    renderX = animationTick + 0xcb;
                    gmID = OpenSHC::IO::Graphics::GID_FLOAT_POP_CIRC;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(
                        gmID, renderX, screenX + -0x23, renderBaseY + -0x2a, maskGmID, renderY, 0);
                } else {
                    if ((DAT_BuildingsState::instance.buildings[buildingID].currentlyNeededEmployeeCount != 0)
                        && (DAT_GameCore::instance.field63_0x108 != 0)) {
                        renderY = DAT_TileMapState::instance.field161_0x5549c0 + 0x128;
                        maskGmID = OpenSHC::IO::Graphics::GID_FLOATS_NEW;
                        renderBaseY
                            = (screenY
                                  - DAT_BuildingDefinedData::instance
                                      .BuildingHeights[DAT_BuildingsState::instance.buildings[buildingID].buildingType])
                            - heightOffset;
                        renderX = DAT_TileMapState::instance.field161_0x5549c0 + 0x118;
                        gmID = OpenSHC::IO::Graphics::GID_FLOATS_NEW;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(
                            gmID, renderX, screenX + -0x23, renderBaseY + -0x2a, maskGmID, renderY, 0);
                    }
                }
            }
            short bannerState = DAT_BuildingsState::instance.buildings[buildingID].field68_0xc2;
            if (bannerState == 1) {
                renderY = DAT_TileMapState::instance.field161_0x5549c0 + 0x10;
                renderX = DAT_TileMapState::instance.field161_0x5549c0;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW, renderX, screenX + -0x23,
                    ((screenY
                         - DAT_BuildingDefinedData::instance
                             .BuildingHeights[DAT_BuildingsState::instance.buildings[buildingID].buildingType])
                        - heightOffset)
                        + -0x2a,
                    OpenSHC::IO::Graphics::GID_FLOATS_NEW, renderY, 0);
                DAT_BuildingsState::instance.buildings[buildingID].field68_0xc2 = 0;
            } else if (bannerState == 2) {
                renderY = DAT_TileMapState::instance.field161_0x5549c0 + 0x84;
                renderX = DAT_TileMapState::instance.field161_0x5549c0 + 0x74;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW, renderX, screenX + -0x23,
                    ((screenY
                         - DAT_BuildingDefinedData::instance
                             .BuildingHeights[DAT_BuildingsState::instance.buildings[buildingID].buildingType])
                        - heightOffset)
                        + -0x2a,
                    OpenSHC::IO::Graphics::GID_FLOATS_NEW, renderY, 0);
                DAT_BuildingsState::instance.buildings[buildingID].field68_0xc2 = 0;
            }
        }
        int frame;
        if (DAT_BuildingsState::instance.buildings[buildingID].field62_0xb0 == 0) {
            switch (DAT_BuildingsState::instance.buildings[buildingID].buildingType) {
            case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                if ((DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 5)
                        / (int)DAT_BuildingsState::instance.buildings[buildingID].maxHealth
                    != 5) {
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field33_0x6c;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x4f, screenY + -0x4c);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field34_0x70;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x24, screenY + -0x66);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field35_0x74;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x2b, screenY + -0x29);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field36_0x78;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x40, screenY + -0x76);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field37_0x7c;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x24, screenY + -0x66);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].ownerFlagFrame;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x35, screenY + -0x3b);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field39_0x84;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x48, screenY + -0x57);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field40_0x88;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x4f, screenY + -0x73);
                    }
                }
                break;
            case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                if ((DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 5)
                        / (int)DAT_BuildingsState::instance.buildings[buildingID].maxHealth
                    != 5) {
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field33_0x6c;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x14, screenY + -0x58);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field34_0x70;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x2f, screenY + -0x54);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field35_0x74;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x11, screenY + -0x20);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field36_0x78;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x17, screenY + -0x67);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field37_0x7c;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0xf, screenY + -0x27);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].ownerFlagFrame;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x38, screenY + -0x2d);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field39_0x84;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x19, screenY + -0x4c);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field40_0x88;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x3a, screenY + -0x7c);
                    }
                }
                break;
            case OpenSHC::Map::Buildings::BT_TOWER1:
                if ((DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 5)
                        / (int)DAT_BuildingsState::instance.buildings[buildingID].maxHealth
                    != 5) {
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field33_0x6c;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0xf, screenY + -0x42);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field34_0x70;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0xd, screenY + -0xb2);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field35_0x74;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -9, screenY + -0xfc);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field36_0x78;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX, screenY + -0x6c);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field37_0x7c;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0xd, screenY + -0xbd);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].ownerFlagFrame;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0xf, screenY + -0xd9);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field39_0x84;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 8, screenY + -0x31);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field40_0x88;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0xb, screenY + -0x5a);
                    }
                }
                break;
            case OpenSHC::Map::Buildings::BT_TOWER2:
                if ((DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 5)
                        / (int)DAT_BuildingsState::instance.buildings[buildingID].maxHealth
                    != 5) {
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field33_0x6c;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -9, screenY + -0x3b);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field34_0x70;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x31, screenY + -0x2d);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field35_0x74;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x2b, screenY + -0x24);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field36_0x78;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x19, screenY + -0x45);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field37_0x7c;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x26, screenY + -0x55);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].ownerFlagFrame;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x16, screenY + -0x24);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field39_0x84;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x10, screenY + -0x16);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field40_0x88;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x32, screenY + -0x5e);
                    }
                }
                break;
            case OpenSHC::Map::Buildings::BT_TOWER3:
                if ((DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 5)
                        / (int)DAT_BuildingsState::instance.buildings[buildingID].maxHealth
                    != 5) {
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field33_0x6c;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x39, screenY + -0x60);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field34_0x70;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x13, screenY + -0x16);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field35_0x74;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x23, screenY + -0x83);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field36_0x78;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x19, screenY + -0x81);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field37_0x7c;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x31, screenY + -0x2f);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].ownerFlagFrame;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x2e, screenY + -0x60);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field39_0x84;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x10, screenY + -0x6a);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field40_0x88;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x20, screenY + -0x5b);
                    }
                }
                break;
            case OpenSHC::Map::Buildings::BT_TOWER4:
                if ((DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 5)
                        / (int)DAT_BuildingsState::instance.buildings[buildingID].maxHealth
                    != 5) {
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field33_0x6c;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x41, screenY + -0x9f);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field34_0x70;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x25, screenY + -0x61);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field35_0x74;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x4b, screenY + -0x41);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field36_0x78;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x41, screenY + -0x45);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field37_0x7c;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x26, screenY + -0x73);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].ownerFlagFrame;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x13, screenY + -0x3b);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field39_0x84;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x36, screenY + -0x8b);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field40_0x88;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x42, screenY + -0x6e);
                    }
                }
                break;
            case OpenSHC::Map::Buildings::BT_TOWER5:
                if ((DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 5)
                        / (int)DAT_BuildingsState::instance.buildings[buildingID].maxHealth
                    != 5) {
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field33_0x6c;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x33, screenY + -0x7f);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field34_0x70;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 4, screenY + -0x5b);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field35_0x74;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x29, screenY + -0x7a);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field36_0x78;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x21, screenY + -0x45);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field37_0x7c;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x28, screenY + -0x59);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].ownerFlagFrame;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + 0x16, screenY + -0x37);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field39_0x84;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CRACKS, frame, screenX + -0x16, screenY + -0x84);
                    }
                    frame = DAT_BuildingsState::instance.buildings[buildingID].field40_0x88;
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
            frame = DAT_BuildingsState::instance.buildings[buildingID].field39_0x84;
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
        if (DAT_TileMapState::instance.field93_0x5548c8 != 0) {
            return;
        }
        DAT_CurrentlyRenderedSpriteID::instance = (GmID)DAT_BuildingsState::instance.buildings[buildingID].spriteID2;
        buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
        DAT_RenderedUnitOwner::instance = 0;
        if (((buildingType == OpenSHC::Map::Buildings::BT_KILLINGPIT)
                && (DAT_BuildingsState::instance.buildings[buildingID].owner
                    != DAT_GameSynchronyState::instance.currentPlayerSlotID))
            && (DAT_BuildingsState::instance.buildings[buildingID].state < 1)) {
            DAT_RenderedUnitOwner::instance = 0;
            return;
        }
        if ((buildingType == OpenSHC::Map::Buildings::BT_DRAWBRIDGE)
            && (MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::temporarySaveMapSurfaceHeightRangeUnk,
                    DAT_TextureRenderCoreObject::ptr)(),
                DAT_BuildingsState::instance.buildings[buildingID].drawBridgeState1 == 0)) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setMapSurfaceHeightRange,
                DAT_TextureRenderCoreObject::ptr)(screenY - 0x17U & ((int)(screenY - 0x17U) < 0) - 1, 0x81c);
        }
        frame = 0;
        buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
        if (buildingType == OpenSHC::Map::Buildings::BT_TOWER2) {
            if (DAT_BuildingsState::instance.buildings[buildingID].field62_0xb0 == 0) {
                frame = DAT_BuildingsState::instance.buildings[buildingID].field21_0x3c;
                if (frame != 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, screenX + -0x24, screenY + -0x78);
                }
                frame = DAT_BuildingsState::instance.buildings[buildingID].field23_0x44;
                renderY = screenY + -0x71;
                renderX = screenX + 0x20;
                gmID = OpenSHC::IO::Graphics::GID_ANIM_CASTLE;
            }
        } else if (buildingType == OpenSHC::Map::Buildings::BT_TOWER3) {
            if (DAT_BuildingsState::instance.buildings[buildingID].field62_0xb0 == 0) {
                frame = DAT_BuildingsState::instance.buildings[buildingID].field21_0x3c;
                if (frame != 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, screenX + -0x24, screenY + -0x77);
                }
                frame = DAT_BuildingsState::instance.buildings[buildingID].field23_0x44;
                renderY = screenY + -0x77;
                renderX = screenX + 0x2e;
                gmID = OpenSHC::IO::Graphics::GID_ANIM_CASTLE;
            }
        } else if (buildingType == OpenSHC::Map::Buildings::BT_TOWER4) {
            if (DAT_BuildingsState::instance.buildings[buildingID].field62_0xb0 == 0) {
                frame = DAT_BuildingsState::instance.buildings[buildingID].field21_0x3c;
                if (frame != 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, screenX + -0x34, screenY + -0x82);
                }
                frame = DAT_BuildingsState::instance.buildings[buildingID].field23_0x44;
                renderY = screenY + -0x7d;
                renderX = screenX + 0x30;
                gmID = OpenSHC::IO::Graphics::GID_ANIM_CASTLE;
            }
        } else if (buildingType == OpenSHC::Map::Buildings::BT_TOWER5) {
            if (DAT_BuildingsState::instance.buildings[buildingID].field62_0xb0 == 0) {
                frame = DAT_BuildingsState::instance.buildings[buildingID].field21_0x3c;
                if (frame != 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, screenX + -0x33, screenY + -0x82);
                }
                frame = DAT_BuildingsState::instance.buildings[buildingID].field23_0x44;
                renderY = screenY + -0x7c;
                renderX = screenX + 0x31;
                gmID = OpenSHC::IO::Graphics::GID_ANIM_CASTLE;
            }
        } else {
            DAT_RenderedUnitOwner::instance = DAT_BuildingsState::instance.buildings[buildingID].playerColorUnk;
            short blendStrength = DAT_BuildingsState::instance.buildings[buildingID].field66_0xbe;
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
                renderY = DAT_BuildingsState::instance.buildings[buildingID].spriteOffetY + screenY;
                frame = DAT_BuildingsState::instance.buildings[buildingID].animationFrame;
                renderX = DAT_BuildingsState::instance.buildings[buildingID].spriteOffetX + screenX;
                gmID = (GmID)DAT_CurrentlyRenderedSpriteID::instance;
            }
        }
        if (frame != 0) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)((eGM)gmID, frame, renderX, renderY);
        }
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingType == OpenSHC::Map::Buildings::BT_DRAWBRIDGE) {
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::restoreMapSurfaceHeightRangeFromTemporaryUnk,
                DAT_TextureRenderCoreObject::ptr)();
        }
        return;
    }

}
}
