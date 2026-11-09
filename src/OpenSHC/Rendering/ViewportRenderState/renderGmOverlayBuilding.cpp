#include "../ViewportRenderState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentlyRenderedSpriteID.hpp"
#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_GmImageAddressToBeRendered.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_RenderedUnitOwner.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace Rendering {

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::IO::Graphics::GmID;
    using OpenSHC::Map::MapType2;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Buildings::BuildingTypeShort;
    using OpenSHC::UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004E3980
    void ViewportRenderState::renderGmOverlayBuilding(int tileIndex, int xUnk, int yUnk, int param_4)
    {
        short sVar1;
        BuildingTypeShort buildingType;
        uint uVar8;
        int iVar9;
        int iVar10;
        int frame;
        GmID overlayGmID;
        eGM gmID;
        GmID maskGmID;
        int local_18;
        int local_14;
        int local_10;
        int local_8;
        int local_4;

        DAT_RenderedUnitOwner::instance = DAT_BuildingsState::instance.buildings[tileIndex].playerColorUnk;
        local_18 = 0;
        local_14 = 0;
        if (DAT_BuildingsState::instance.buildings[tileIndex].displayOwnerFlag != 0) {
            sVar1 = DAT_BuildingsState::instance.buildings[tileIndex].tickRelatedVisuallyActiveIndicator;
            if (sVar1 <= 0) {
                frame = 0;
            } else if (sVar1 >= 5) {
                frame = 0;
            } else {
                frame = 32 - sVar1 * 32 / 5;
                if (frame == 32) {
                    frame = 0;
                }
            }
            buildingType = DAT_BuildingsState::instance.buildings[tileIndex].buildingType;
            if (buildingType == OpenSHC::Map::Buildings::BT_CAMPGROUND) {
                if (DAT_BuildingsState::instance.buildings[tileIndex].owner
                    == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOAT_POP_CIRC, frame,
                        (xUnk - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[85].originX) - 5,
                        (yUnk - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[85].originY) - 89,
                        OpenSHC::IO::Graphics::GID_FLOAT_POP_CIRC, frame + 101, 0);
                }
            } else {
                int slot = 0;
                if (DAT_TileMapState::instance.disableElevationRendering != 0) {
                    return;
                }
                switch (buildingType) {
                case OpenSHC::Map::Buildings::BT_WOODCUTTERSHUT:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = 189;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 39, yUnk - 103);
                    }
                    DAT_GmImageAddressToBeRendered::instance
                        = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_WOODCUTTER;
                    if (DAT_GmImageAddressToBeRendered::instance != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationUnk,
                            DAT_TextureRenderCoreObject::ptr)(xUnk - 35, yUnk - 57,
                            DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance].width,
                            DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance].height,
                            DAT_TextureRenderCoreObject::instance.gmProcessedImageData
                                + DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance]);
                    }
                    DAT_GmImageAddressToBeRendered::instance
                        = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite2;
                    if (DAT_GmImageAddressToBeRendered::instance != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationUnk,
                            DAT_TextureRenderCoreObject::ptr)(xUnk - 56, yUnk - 70,
                            DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance].width,
                            DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance].height,
                            DAT_TextureRenderCoreObject::instance.gmProcessedImageData
                                + DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance]);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_INN:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = 189;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 69, yUnk - 149);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_INN;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ANIM_INN, frame,
                            DAT_BuildingsState::instance.buildings[tileIndex].spriteOffetX + xUnk,
                            DAT_BuildingsState::instance.buildings[tileIndex].spriteOffetY + yUnk);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite2;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ANIM_INN, frame,
                            DAT_BuildingsState::instance.buildings[tileIndex].spriteOffetX + xUnk,
                            DAT_BuildingsState::instance.buildings[tileIndex].spriteOffetY + yUnk);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite3;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ANIM_INN, frame,
                            DAT_BuildingsState::instance.buildings[tileIndex].spriteOffetX + xUnk,
                            DAT_BuildingsState::instance.buildings[tileIndex].spriteOffetY + yUnk);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite4;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ANIM_INN, frame,
                            DAT_BuildingsState::instance.buildings[tileIndex].spriteOffetX + xUnk,
                            DAT_BuildingsState::instance.buildings[tileIndex].spriteOffetY + yUnk);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_CHOPPINGBLOCK:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_CHOPPING_BLOCK;
                    DAT_RenderedUnitOwner::instance = 0;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_CHOPPING_BLOCK, frame, xUnk - 35, yUnk - 76);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_OILSMELTER:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = 189;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk + 3, yUnk - 125);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_BOILED_OIL;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_OIL_ANIMS, frame, xUnk - 35, yUnk - 62);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite2;
                    if (frame != 0) {
                        if (frame > 122) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_OIL_ANIMS, frame, xUnk - 35, yUnk - 102);
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_OIL_ANIMS, frame, xUnk - 35, yUnk - 100);
                        }
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_QUARRY:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = 189;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 38, yUnk - 60);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                    DAT_RenderedUnitOwner::instance = 1;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_QUARRY;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_QUARRY_ANIMS, frame, xUnk + 12, yUnk - 140);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite2;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_QUARRY_ANIMS, frame, xUnk - 49, yUnk - 136);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite3;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_QUARRY_ANIMS, frame, xUnk - 32, yUnk - 107);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite4;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_QUARRY_ANIMS, frame, xUnk - 95, yUnk - 111);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_DRAWBRIDGE:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk + 7, yUnk - 124);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite4;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 51, yUnk - 126);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_IRONMINE:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = 189;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 39, yUnk - 33);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite2;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_IRON_MINER;
                    if (frame != 0) {
                        short const minerPose = DAT_BuildingsState::instance.buildings[tileIndex].field_0x11a;
                        if (minerPose == 0) {
                            local_18 = -31;
                            local_14 = -88;
                        } else if (minerPose == 1 || minerPose == 2) {
                            local_14 = -157;
                            local_18 = -26;
                        }
                        if (DAT_BuildingsState::instance.buildings[tileIndex].field_0x11a == 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_MINE_ANIMS, frame, local_18 + xUnk, local_14 + yUnk);
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_IRON_MINER, frame,
                                local_18 + xUnk, local_14 + yUnk,
                                DAT_BuildingsState::instance.buildings[tileIndex].field_0x292);
                        }
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite4;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_MINE_ANIMS, frame, xUnk - 31, yUnk - 89);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage1;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_MINE_ANIMS, frame, xUnk - 23, yUnk - 54);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                    if (frame != 0) {
                        short const minerState = DAT_BuildingsState::instance.buildings[tileIndex].state;
                        int offsetX;
                        int offsetY;
                        if (minerState == 0) {
                            offsetX = -35;
                            offsetY = -70;
                        } else if (minerState == 1) {
                            offsetX = -35;
                            offsetY = -56;
                        } else if (minerState == 2) {
                            offsetX = -35;
                            offsetY = -70;
                        } else if (minerState == 3) {
                            offsetX = -35;
                            offsetY = -78;
                        } else if (minerState == 4) {
                            offsetX = -35;
                            offsetY = -89;
                        } else if (minerState == 5) {
                            offsetX = -35;
                            offsetY = -89;
                        } else {
                            offsetX = -51;
                            offsetY = -70;
                        }
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_MINE_ANIMS, frame, offsetX + xUnk, offsetY + yUnk);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite3;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_MINE_ANIMS, frame, xUnk - 51, yUnk - 84);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_PITCHRIG:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk + 12, yUnk - 80);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_HUNTERSHUT:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = 189;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 37, yUnk - 86);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_HUNTER;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_HUNTER_ANIMS, frame, xUnk - 35, yUnk - 60);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_MILL: {
                    int millImage = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = 189;
                    if (millImage != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, millImage, xUnk - 38, yUnk - 114);
                    }
                    millImage = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_WINDMILL;
                    if (millImage != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_WINDMILL_ANIMS, millImage, xUnk - 78, yUnk - 259);
                    }
                    millImage = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite2;
                    if (millImage != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::IO::Graphics::GID_ANIM_WINDMILL, millImage, xUnk - 78, yUnk - 259, frame);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite3;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_WINDMILL_ANIMS, frame, xUnk - 78, yUnk - 208);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite4;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_WINDMILL_ANIMS, frame, xUnk - 89, yUnk - 292);
                    }
                    break;
                }
                case OpenSHC::Map::Buildings::BT_BAKERY:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = 189;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 37, yUnk - 123);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = 66;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_WORKSHOP_BAKER_ANIMS, frame, xUnk - 20, yUnk - 95);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite2;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_SMOKE_30X30;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::IO::Graphics::GID_SMOKE_30X30, frame, xUnk - 4, yUnk - 140, 16);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_BREWERY:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = 189;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 37, yUnk - 123);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                    DAT_RenderedUnitOwner::instance = 2;
                    DAT_CurrentlyRenderedSpriteID::instance = 51;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_WORKSHOP_BREW_ANIMS, frame, xUnk - 60, yUnk - 68);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite2;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_SMOKE_30X30;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::IO::Graphics::GID_SMOKE_30X30, frame, xUnk + 7, yUnk - 124, 16);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_BLACKSMITH:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = 189;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 37, yUnk - 123);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                    DAT_RenderedUnitOwner::instance = 2;
                    DAT_CurrentlyRenderedSpriteID::instance = 58;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_WORKSHOP_SMITH_ANIMS, frame, xUnk - 35, yUnk - 73);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite2;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_SMOKE_30X30;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::IO::Graphics::GID_SMOKE_30X30, frame, xUnk + 3, yUnk - 124, 16);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_POLETURNER:
                case OpenSHC::Map::Buildings::BT_TANNER:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 37, yUnk - 128);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_FLETCHER:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 37, yUnk - 130);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_ARMOURER:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 37, yUnk - 137);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_WHEATFARM:
                case OpenSHC::Map::Buildings::BT_HOPFARM:
                case OpenSHC::Map::Buildings::BT_APPLEFARM:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 55, yUnk - 109);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_DAIRYFARM:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = 189;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 55, yUnk - 109);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FARMER;
                    if (frame != 0) {
                        sVar1 = DAT_BuildingsState::instance.buildings[tileIndex].renderBlendStrength;
                        if (DAT_BuildingsState::instance.buildings[tileIndex].field_0x11a == 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_FARMER_ANIMS, frame, xUnk - 35, yUnk - 81);
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::IO::Graphics::GID_ANIM_FARMER, frame, xUnk - 35, yUnk - 81, sVar1);
                        }
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite2;
                    if (frame != 0) {
                        sVar1 = DAT_BuildingsState::instance.buildings[tileIndex].renderBlendStrength;
                        if (DAT_BuildingsState::instance.buildings[tileIndex].field_0x11a == 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_FARMER_ANIMS, frame, xUnk - 35, yUnk - 81);
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::IO::Graphics::GID_ANIM_FARMER, frame, xUnk - 35, yUnk - 81, sVar1);
                        }
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite3;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_FARMER_ANIMS, frame, xUnk - 35, yUnk - 81);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite4;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_FARMER_ANIMS, frame, xUnk - 35, yUnk - 81);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_STABLES:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = 189;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 18, yUnk - 99);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite4;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_STABLES;
                    if (frame != 0) {
                        short const blend = DAT_BuildingsState::instance.buildings[tileIndex].renderBlendStrength;
                        if (frame < 38) {
                            if (blend != 0) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::IO::Graphics::GID_ANIM_STABLES, frame, xUnk - 80, yUnk - 107, blend);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_STABLE_ANIMS, frame, xUnk - 80, yUnk - 107);
                            }
                        } else {
                            if (blend != 0) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::IO::Graphics::GID_ANIM_STABLES, frame, xUnk - 80, yUnk - 107, blend);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_STABLE_ANIMS, frame, xUnk - 103, yUnk - 100);
                            }
                        }
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite3;
                    if (frame != 0) {
                        short const blend = DAT_BuildingsState::instance.buildings[tileIndex].renderBlendStrength;
                        if (frame < 38) {
                            if (blend != 0) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::IO::Graphics::GID_ANIM_STABLES, frame, xUnk - 58, yUnk - 96, blend);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_STABLE_ANIMS, frame, xUnk - 58, yUnk - 96);
                            }
                        } else {
                            if (blend != 0) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::IO::Graphics::GID_ANIM_STABLES, frame, xUnk - 58, yUnk - 96, blend);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_STABLE_ANIMS, frame, xUnk - 81, yUnk - 83);
                            }
                        }
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite2;
                    if (frame != 0) {
                        short const blend = DAT_BuildingsState::instance.buildings[tileIndex].renderBlendStrength;
                        if (frame < 38) {
                            if (blend != 0) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::IO::Graphics::GID_ANIM_STABLES, frame, xUnk - 36, yUnk - 85, blend);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_STABLE_ANIMS, frame, xUnk - 36, yUnk - 85);
                            }
                        } else {
                            if (blend != 0) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::IO::Graphics::GID_ANIM_STABLES, frame, xUnk - 36, yUnk - 85, blend);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_STABLE_ANIMS, frame, xUnk - 55, yUnk - 74);
                            }
                        }
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                    if (frame != 0) {
                        short const blend = DAT_BuildingsState::instance.buildings[tileIndex].renderBlendStrength;
                        if (frame < 38) {
                            if (blend != 0) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::IO::Graphics::GID_ANIM_STABLES, frame, xUnk - 14, yUnk - 74, blend);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_STABLE_ANIMS, frame, xUnk - 14, yUnk - 74);
                            }
                            // the second image of the pair
                            short const blend2 = DAT_BuildingsState::instance.buildings[tileIndex].renderBlendStrength;
                            if (blend2 != 0) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::IO::Graphics::GID_ANIM_STABLES, 38, xUnk - 13, yUnk - 73, blend2);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_STABLE_ANIMS, 38, xUnk - 2, yUnk - 73);
                            }
                        } else {
                            if (blend != 0) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::IO::Graphics::GID_ANIM_STABLES, frame, xUnk - 14, yUnk - 74, blend);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_STABLE_ANIMS, frame, xUnk - 33, yUnk - 63);
                            }
                        }
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_GRANARY:
                    for (slot = 0; slot < 16; slot++) {
                        if (DAT_BuildingsState::instance.buildings[tileIndex].tileRefs[slot] == param_4) {
                            break;
                        }
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                    if ((iVar9 != 0) && (slot == 0)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1,
                            (xUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1].width
                                    / 2)
                                + 15,
                            (yUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1]
                                    .height)
                                - 5,
                            frame);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite3;
                    if ((iVar9 != 0) && (slot == 1)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite3,
                            (xUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1].width
                                    / 2)
                                + 15,
                            (yUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1]
                                    .height)
                                - 5,
                            frame);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage2;
                    if ((iVar9 != 0) && (slot == 2)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage2,
                            (xUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1].width
                                    / 2)
                                + 15,
                            (yUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1]
                                    .height)
                                - 5,
                            frame);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage6;
                    if ((iVar9 != 0) && (slot == 3)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage6,
                            (xUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1].width
                                    / 2)
                                + 15,
                            (yUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1]
                                    .height)
                                - 5,
                            frame);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite2;
                    if ((iVar9 != 0) && (slot == 4)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite2,
                            (xUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1].width
                                    / 2)
                                + 15,
                            (yUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1]
                                    .height)
                                - 5,
                            frame);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite4;
                    if ((iVar9 != 0) && (slot == 5)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite4,
                            (xUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1].width
                                    / 2)
                                + 15,
                            (yUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1]
                                    .height)
                                - 5,
                            frame);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage4;
                    if ((iVar9 != 0) && (slot == 6)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage4,
                            (xUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1].width
                                    / 2)
                                + 15,
                            (yUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1]
                                    .height)
                                - 5,
                            frame);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage9;
                    if ((iVar9 != 0) && (slot == 7)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage9,
                            (xUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1].width
                                    / 2)
                                + 15,
                            (yUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1]
                                    .height)
                                - 5,
                            frame);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage1;
                    if ((iVar9 != 0) && (slot == 8)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage1,
                            (xUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1].width
                                    / 2)
                                + 15,
                            (yUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1]
                                    .height)
                                - 5,
                            frame);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage3;
                    if ((iVar9 != 0) && (slot == 9)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage3,
                            (xUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1].width
                                    / 2)
                                + 15,
                            (yUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1]
                                    .height)
                                - 5,
                            frame);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage7;
                    if ((iVar9 != 0) && (slot == 10)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage7,
                            (xUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1].width
                                    / 2)
                                + 15,
                            (yUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1]
                                    .height)
                                - 5,
                            frame);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    if ((iVar9 != 0) && (slot == 11)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID,
                            (xUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1].width
                                    / 2)
                                + 15,
                            (yUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1]
                                    .height)
                                - 5,
                            frame);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage5;
                    if ((iVar9 != 0) && (slot == 12)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage5,
                            (xUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1].width
                                    / 2)
                                + 15,
                            (yUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1]
                                    .height)
                                - 5,
                            frame);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage8;
                    if ((iVar9 != 0) && (slot == 13)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage8,
                            (xUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1].width
                                    / 2)
                                + 15,
                            (yUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1]
                                    .height)
                                - 5,
                            frame);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].flagSlot.overlayImage;
                    if ((iVar9 != 0) && (slot == 14)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].flagSlot.overlayImage,
                            (xUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1].width
                                    / 2)
                                + 15,
                            (yUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1]
                                    .height)
                                - 5,
                            frame);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage10;
                    if ((iVar9 != 0) && (slot == 15)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS, iVar9,
                            (xUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1].width
                                    / 2)
                                + 15,
                            (yUnk
                                - DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[28] + iVar9 - 1]
                                    .height)
                                - 5,
                            frame);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_ARMORY: {
                    for (; slot < 16; slot++) {
                        if (DAT_BuildingsState::instance.buildings[tileIndex].tileRefs[slot] == param_4) {
                            break;
                        }
                    }
                    iVar9 = 0;
                    local_10 = 0;
                    local_18 = 0;
                    local_14 = 0;
                    local_4 = 0;
                    switch (DAT_TileMapState::instance.mapOrientation) {
                    case 0:
                        iVar9 = 5;
                        local_4 = 0;
                        local_10 = 7;
                        local_18 = 13;
                        local_14 = 15;
                        break;
                    case 2:
                        iVar9 = 4;
                        local_4 = 3;
                        local_10 = 6;
                        local_18 = 12;
                        local_14 = 14;
                        break;
                    case 4:
                        iVar9 = 0;
                        local_4 = 15;
                        local_10 = 2;
                        local_18 = 8;
                        local_14 = 10;
                        break;
                    case 6:
                        local_4 = 12;
                        iVar9 = 1;
                        local_10 = 3;
                        local_18 = 9;
                        local_14 = 11;
                    }
                    iVar10 = 0;
                    if (slot == iVar9) {
                        iVar10 = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage1;
                    } else if (slot == local_10) {
                        iVar10 = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage3;
                    } else if (slot == local_18) {
                        iVar10 = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage9;
                    } else if (slot == local_14) {
                        iVar10 = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    }
                    if (32 <= iVar10) {
                        iVar10 = 0;
                        overlayGmID = OpenSHC::IO::Graphics::GID_ANIM_GOODS;
                        local_8 = 0;
                    } else {
                        overlayGmID = OpenSHC::IO::Graphics::GID_ANIM_SHIELDS;
                        local_8 = -10;
                        iVar10 = DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[104].originY;
                    }
                    int blendFrame = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage1;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = overlayGmID;
                    if ((blendFrame != 0) && (slot == iVar9)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(overlayGmID,
                            DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage1,
                            (xUnk
                                - DAT_GMImageHeaders::instance
                                        .imh[blendFrame + GMFirstPictureIndex::instance[overlayGmID] - 1]
                                        .width
                                    / 2)
                                + 15 + local_8,
                            (yUnk
                                - DAT_GMImageHeaders::instance
                                    .imh[blendFrame + GMFirstPictureIndex::instance[overlayGmID] - 1]
                                    .height)
                                - 15 + iVar10,
                            frame);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage3;
                    if ((iVar9 != 0) && (slot == local_10)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(overlayGmID,
                            DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage3,
                            (xUnk
                                - DAT_GMImageHeaders::instance
                                        .imh[iVar9 + GMFirstPictureIndex::instance[overlayGmID] - 1]
                                        .width
                                    / 2)
                                + 15 + local_8,
                            (yUnk
                                - DAT_GMImageHeaders::instance
                                    .imh[iVar9 + GMFirstPictureIndex::instance[overlayGmID] - 1]
                                    .height)
                                - 15 + iVar10,
                            frame);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage9;
                    if ((iVar9 != 0) && (slot == local_18)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(overlayGmID,
                            DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage9,
                            (xUnk
                                - DAT_GMImageHeaders::instance
                                        .imh[iVar9 + GMFirstPictureIndex::instance[overlayGmID] - 1]
                                        .width
                                    / 2)
                                + 15 + local_8,
                            (yUnk
                                - DAT_GMImageHeaders::instance
                                    .imh[iVar9 + GMFirstPictureIndex::instance[overlayGmID] - 1]
                                    .height)
                                - 15 + iVar10,
                            frame);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    if ((iVar9 != 0) && (slot == local_14)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(overlayGmID, iVar9,
                            (xUnk
                                - DAT_GMImageHeaders::instance
                                        .imh[iVar9 + GMFirstPictureIndex::instance[overlayGmID] - 1]
                                        .width
                                    / 2)
                                + 15 + local_8,
                            (yUnk
                                - DAT_GMImageHeaders::instance
                                    .imh[iVar9 + GMFirstPictureIndex::instance[overlayGmID] - 1]
                                    .height)
                                - 15 + iVar10,
                            frame);
                    }
                    if (param_4 == DAT_BuildingsState::instance.buildings[tileIndex].tileRefs[local_4]) {
                        DAT_RenderedUnitOwner::instance
                            = DAT_BuildingsState::instance.buildings[tileIndex].playerColorUnk;
                        frame = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage8;
                        DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                        if (frame != 0) {
                            DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 38, yUnk - 136);
                            break;
                        }
                    }
                    break;
                }
                case OpenSHC::Map::Buildings::BT_STONEKEEP:
                    if ((DAT_BuildingsState::instance.buildings[tileIndex].useOffsetGraphics == 0)
                        && (frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1,
                            frame != 0)) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 96, yUnk - 143);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_STRONGHOLD:
                    if ((DAT_BuildingsState::instance.buildings[tileIndex].useOffsetGraphics == 0)
                        && (frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1,
                            frame != 0)) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 159, yUnk - 298);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 7, yUnk - 193);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite2;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 96, yUnk - 193);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite3;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk + 3, yUnk - 91);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite4;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 51, yUnk - 91);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage1;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_BODY_GATE, frame, xUnk + 17, yUnk - 94);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage2;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_BODY_GATE, frame, xUnk - 86, yUnk - 94);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk + 5, yUnk - 178);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite2;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 64, yUnk - 177);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite3;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 13, yUnk - 83);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite4;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 35, yUnk - 83);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage1;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_BODY_GATE, frame, xUnk, yUnk - 88);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage2;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_BODY_GATE, frame, xUnk - 70, yUnk - 88);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_WOODGATE1:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk + 3, yUnk - 110);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite2;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 32, yUnk - 106);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite3;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 32, yUnk - 70);
                    }
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite4;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk + 8, yUnk - 71);
                    }
                    if (DAT_BuildingsState::instance.buildings[tileIndex].useOffsetGraphics == 0) {
                        frame = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage1;
                        if (frame != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk + 17, yUnk - 55);
                        }
                        frame = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage2;
                        if (frame != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 21, yUnk - 55);
                            break;
                        }
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_TOWER1:
                    if (DAT_BuildingsState::instance.buildings[tileIndex].useOffsetGraphics == 0) {
                        frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                        if (frame != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 33, yUnk - 320);
                        }
                        frame = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage2;
                        if (frame != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 34, yUnk - 379);
                            break;
                        }
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_TOWER2:
                    if (DAT_BuildingsState::instance.buildings[tileIndex].useOffsetGraphics == 0) {
                        frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                        if (frame != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 48, yUnk - 194);
                        }
                        frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite3;
                        if (frame != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 41, yUnk - 147);
                        }
                        frame = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage1;
                        if (frame != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 2, yUnk - 140);
                            break;
                        }
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_TOWER3:
                    if (DAT_BuildingsState::instance.buildings[tileIndex].useOffsetGraphics == 0) {
                        frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                        if (frame != 0) {
                            /*
                              crenellations
                             */

                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 63, yUnk - 225);
                        }
                        frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite3;
                        if (frame != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 41, yUnk - 150);
                        }
                        frame = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage1;
                        if (frame != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk + 13, yUnk - 147);
                            break;
                        }
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_TOWER4:
                    if (DAT_BuildingsState::instance.buildings[tileIndex].useOffsetGraphics == 0) {
                        frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                        if (frame != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 77, yUnk - 246);
                        }
                        frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite3;
                        if (frame != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 57, yUnk - 154);
                        }
                        frame = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage1;
                        if (frame != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk + 15, yUnk - 150);
                        }
                        frame = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage2;
                        if (frame != 0) {
                            /*
                              roof
                             */

                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 77, yUnk - 315);
                        }
                        frame = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage3;
                        if (frame != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 77, yUnk - 276);
                            break;
                        }
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_TOWER5:
                    if (DAT_BuildingsState::instance.buildings[tileIndex].useOffsetGraphics == 0) {
                        frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite1;
                        if (frame != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 76, yUnk - 260);
                        }
                        frame = DAT_BuildingsState::instance.buildings[tileIndex].extraAnimationSprite3;
                        if (frame != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk - 50, yUnk - 157);
                        }
                        frame = DAT_BuildingsState::instance.buildings[tileIndex].extraOverlayImage1;
                        if (frame != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, frame, xUnk + 16, yUnk - 151);
                            break;
                        }
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_MARKETPLACE:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 39, yUnk - 106);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_CHAPEL:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 38, yUnk - 124);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_CHURCH:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 9, yUnk - 151);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_CATHEDRAL:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 13, yUnk - 202);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_APOTHECARY:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk + 5, yUnk - 177);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_ENGINEERSGUILD:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 51, yUnk - 114);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_TUNNELERSGUILD:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 54, yUnk - 119);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_MERCENARYPOST:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 37, yUnk - 107);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_BARRACKS:
                    frame = DAT_BuildingsState::instance.buildings[tileIndex].overlayImageID;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (frame != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, frame, xUnk - 37, yUnk - 117);
                    }
                    break;
                }
            }
        }
        frame = DAT_BuildingDefinedData::instance
                    .BuildingHeights[DAT_BuildingsState::instance.buildings[tileIndex].buildingType];
        int barXOffset = 0;
        int barYOffset = 0;
        if (frame == 0) {
            uVar8 = DAT_BuildingsState::instance.buildings[tileIndex].widthOrHeight;
            barXOffset = uVar8 << 5;
            barYOffset = uVar8 << 4;
        }
        if ((((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU)
                 && (tileIndex == DAT_BuildingsState::instance.menuSelectedBuildingID))
                || ((tileIndex == DAT_BuildingsState::instance.selectedBuildingID
                    && (DAT_BuildingsState::instance.selectedBuildingUID
                        == DAT_BuildingsState::instance.buildings[tileIndex].uid))))
            && (sVar1 = DAT_BuildingsState::instance.buildings[tileIndex].maxHealth,
                sVar1 != 0
                    && (DAT_BuildingsState::instance.buildings[tileIndex].buildingType
                        != OpenSHC::Map::Buildings::BT_MANORHOUSE))
            && DAT_BuildingsState::instance.buildings[tileIndex].buildingType != OpenSHC::Map::Buildings::BT_STONEKEEP
            && DAT_BuildingsState::instance.buildings[tileIndex].buildingType != OpenSHC::Map::Buildings::BT_STRONGHOLD
            && DAT_BuildingsState::instance.buildings[tileIndex].buildingType != OpenSHC::Map::Buildings::BT_KEEPFOUR
            && DAT_BuildingsState::instance.buildings[tileIndex].buildingType != OpenSHC::Map::Buildings::BT_KEEPFIVE
            && DAT_BuildingsState::instance.buildings[tileIndex].buildingType
                != OpenSHC::Map::Buildings::BT_CAMPGROUND) {
            int const healthPercent
                = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHealthPercentage,
                    DAT_DirectionAlgorithmState::ptr)(
                    DAT_BuildingsState::instance.buildings[tileIndex].currentHealth, sVar1);
            switch (DAT_BuildingsState::instance.buildings[tileIndex].buildingType) {
            case OpenSHC::Map::Buildings::BT_TOWER2:
                barYOffset = barYOffset + 80;
                break;
            case OpenSHC::Map::Buildings::BT_TOWER3:
            case OpenSHC::Map::Buildings::BT_TOWER4:
                barYOffset = barYOffset + 90;
                break;
            case OpenSHC::Map::Buildings::BT_TOWER5:
                barYOffset = barYOffset + 100;
                break;
            case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                barYOffset = barYOffset + 30;
                break;
            case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                barYOffset = barYOffset + 20;
                break;
            case OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED:
                barYOffset = barYOffset - 30;
                break;
            }
            int const healthImage = healthPercent / 10;
            if (healthImage >= 0 && healthImage <= 10) {
                buildingType = DAT_BuildingsState::instance.buildings[tileIndex].buildingType;
                if ((buildingType == OpenSHC::Map::Buildings::BT_GRANARY)
                    || (buildingType == OpenSHC::Map::Buildings::BT_ARMORY)) {
                    int healthSlot;
                    for (healthSlot = 0; healthSlot < 16; healthSlot++) {
                        if (DAT_BuildingsState::instance.buildings[tileIndex].tileRefs[healthSlot] == param_4) {
                            break;
                        }
                    }
                    if (((DAT_TileMapState::instance.mapOrientation == 0) && (healthSlot == 15))
                        || ((DAT_TileMapState::instance.mapOrientation == 2) && (healthSlot == 12))
                        || ((DAT_TileMapState::instance.mapOrientation == 4) && (healthSlot == 0))
                        || ((DAT_TileMapState::instance.mapOrientation == 6) && (healthSlot == 3))) {
                        frame = (yUnk - frame) - barYOffset;
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_FLOATS, healthImage + 17, xUnk + 4, frame - 12);
                    }
                } else {
                    frame = (yUnk - frame) - barYOffset;
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_FLOATS, healthImage + 17, xUnk + 4, frame - 12);
                }
            }
        }
        if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk)
            || (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_SIEGE)) {
            if (DAT_BuildingsState::instance.buildings[tileIndex].sleeping) {
                int const animationTick = (DAT_TileMapState::instance.cursorOverlayAnimationFrame - 1) % 8;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOAT_POP_CIRC, animationTick + 203,
                    xUnk - 35,
                    yUnk
                        - DAT_BuildingDefinedData::instance
                            .BuildingHeights[DAT_BuildingsState::instance.buildings[tileIndex].buildingType]
                        - barYOffset - 42,
                    OpenSHC::IO::Graphics::GID_FLOAT_POP_CIRC, animationTick + 211, 0);
            } else if (DAT_BuildingsState::instance.buildings[tileIndex].currentlyNeededEmployeeCount != 0
                && DAT_GameCore::instance.field_0x108 != 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                    DAT_TileMapState::instance.cursorOverlayAnimationFrame + 280, xUnk - 35,
                    yUnk
                        - DAT_BuildingDefinedData::instance
                            .BuildingHeights[DAT_BuildingsState::instance.buildings[tileIndex].buildingType]
                        - barYOffset - 42,
                    OpenSHC::IO::Graphics::GID_FLOATS_NEW, DAT_TileMapState::instance.cursorOverlayAnimationFrame + 296,
                    0);
            }
        }
        short const bannerState = DAT_BuildingsState::instance.buildings[tileIndex].field_0xc2;
        if (bannerState == 1) {
            int const maskImage = DAT_TileMapState::instance.cursorOverlayAnimationFrame + 16;
            int const overlayImage = DAT_TileMapState::instance.cursorOverlayAnimationFrame;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW, overlayImage, xUnk - 35,
                yUnk
                    - DAT_BuildingDefinedData::instance
                        .BuildingHeights[DAT_BuildingsState::instance.buildings[tileIndex].buildingType]
                    - barXOffset - 42,
                OpenSHC::IO::Graphics::GID_FLOATS_NEW, maskImage, 0);
            DAT_BuildingsState::instance.buildings[tileIndex].field_0xc2 = 0;
        } else if (bannerState == 2) {
            int const maskImage = DAT_TileMapState::instance.cursorOverlayAnimationFrame + 132;
            int const overlayImage = DAT_TileMapState::instance.cursorOverlayAnimationFrame + 116;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW, overlayImage, xUnk - 35,
                yUnk
                    - DAT_BuildingDefinedData::instance
                        .BuildingHeights[DAT_BuildingsState::instance.buildings[tileIndex].buildingType]
                    - barXOffset - 42,
                OpenSHC::IO::Graphics::GID_FLOATS_NEW, maskImage, 0);
            DAT_BuildingsState::instance.buildings[tileIndex].field_0xc2 = 0;
        }
    }

}
}
