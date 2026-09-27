#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
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
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Rendering {

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::IO::Graphics::GmID;
    using OpenSHC::Map::MapType2;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Buildings::BuildingTypeShort;
    using OpenSHC::UI::Enums::MenuViewType;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */

    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x004E3980
    void ViewportRenderState::renderGmOverlayBuilding(int tileIndex, int xUnk, int yUnk, int param_4)

    {
        short sVar1;
        BuildingTypeShort BVar2;
        int iVar3;
        int iVar4;
        int iVar5;
        int iVar6;
        int* piVar7;
        uint uVar8;
        int iVar9;
        int iVar10;
        int iVar11;
        GmID GVar12;
        eGM gmID;
        GmID maskGmID;
        int local_18;
        int local_14;
        int local_10;
        int local_8;
        int local_4;

        iVar5 = yUnk;
        iVar4 = xUnk;
        DAT_RenderedUnitOwner::instance = DAT_BuildingsState::instance.buildings[tileIndex].playerColorUnk;
        local_18 = 0;
        local_14 = 0;
        if (DAT_BuildingsState::instance.buildings[tileIndex].displayOwnerFlag != 0) {
            sVar1 = DAT_BuildingsState::instance.buildings[tileIndex].tickRelatedVisuallyActiveIndicator;
            if (((sVar1 < 1) || (4 < sVar1)) || (iVar11 = 0x20 - ((int)sVar1 << 5) / 5, iVar11 == 0x20)) {
                iVar11 = 0;
            }
            BVar2 = DAT_BuildingsState::instance.buildings[tileIndex].buildingType;
            if (BVar2 == OpenSHC::Map::Buildings::BT_CAMPGROUND) {
                if (DAT_BuildingsState::instance.buildings[tileIndex].owner
                    == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOAT_POP_CIRC, iVar11,
                        (xUnk - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[0x55].originX) + -5,
                        (yUnk - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[0x55].originY)
                            + -0x59,
                        OpenSHC::IO::Graphics::GID_FLOAT_POP_CIRC, iVar11 + 0x65, 0);
                }
            } else {
                iVar6 = 0;
                if (DAT_TileMapState::instance.field93_0x5548c8 != 0) {
                    return;
                }
                switch (BVar2) {
                case OpenSHC::Map::Buildings::BT_WOODCUTTERSHUT:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = 0xbd;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, iVar11, xUnk + -0x27, yUnk + -0x67);
                    }
                    DAT_GmImageAddressToBeRendered::instance
                        = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_WOODCUTTER;
                    if (DAT_GmImageAddressToBeRendered::instance != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationUnk,
                            DAT_TextureRenderCoreObject::ptr)(xUnk + -0x23, yUnk + -0x39,
                            (int)((
                                int)(DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance].width)),
                            (int)((int)(DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance]
                                    .height)),
                            (byte*)((int)((DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance]
                                + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))));
                    }
                    DAT_GmImageAddressToBeRendered::instance
                        = DAT_BuildingsState::instance.buildings[tileIndex].field21_0x3c;
                    if (DAT_GmImageAddressToBeRendered::instance != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationUnk,
                            DAT_TextureRenderCoreObject::ptr)(xUnk + -0x38, yUnk + -0x46,
                            (int)((
                                int)(DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance].width)),
                            (int)((int)(DAT_GMImageHeaders::instance.imh[DAT_GmImageAddressToBeRendered::instance]
                                    .height)),
                            (byte*)((int)((DAT_GMImageOffsets::instance[DAT_GmImageAddressToBeRendered::instance]
                                + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))));
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_IRONMINE:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = 0xbd;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, iVar11, xUnk + -0x27, yUnk + -0x21);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field21_0x3c;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_IRON_MINER;
                    if (iVar11 != 0) {
                        sVar1 = DAT_BuildingsState::instance.buildings[tileIndex].field117_0x11a;
                        if (sVar1 == 0) {
                            local_18 = -0x1f;
                            local_14 = -0x58;
                        } else if ((sVar1 == 1) || (sVar1 == 2)) {
                            local_14 = -0x9d;
                            local_18 = -0x1a;
                        }
                        if (sVar1 == 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_MINE_ANIMS, iVar11, local_18 + xUnk, local_14 + yUnk);
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_IRON_MINER, iVar11,
                                local_18 + xUnk, local_14 + yUnk,
                                (int)((int)((uint)DAT_BuildingsState::instance.buildings[tileIndex].field208_0x292)));
                        }
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field23_0x44;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_MINE_ANIMS, iVar11, xUnk + -0x1f, yUnk + -0x59);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field29_0x5c;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_MINE_ANIMS, iVar11, xUnk + -0x17, yUnk + -0x36);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                    if (iVar11 != 0) {
                        sVar1 = DAT_BuildingsState::instance.buildings[tileIndex].state;
                        if (sVar1 == 0) {
                            iVar6 = -0x23;
                            iVar9 = -0x46;
                        } else if (sVar1 == 1) {
                            iVar6 = -0x23;
                            iVar9 = -0x38;
                        } else {
                            if (sVar1 == 2) {
                                iVar6 = -0x23;
                                iVar9 = -0x46;
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_MINE_ANIMS, iVar11, iVar6 + xUnk, iVar9 + yUnk);
                                iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field22_0x40;
                                if (iVar11 != 0) {
                                    iVar6 = yUnk + -0x54;
                                    iVar9 = xUnk + -0x33;
                                    gmID = OpenSHC::DE::SHCDE::GM_MINE_ANIMS;
                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                        DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                                }
                                break;
                            }
                            if (sVar1 == 3) {
                                iVar6 = -0x23;
                                iVar9 = -0x4e;
                            } else if (sVar1 == 4) {
                                iVar6 = -0x23;
                                iVar9 = -0x59;
                            } else {
                                if (sVar1 != 5) {
                                    iVar6 = -0x33;
                                    iVar9 = -0x46;
                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                        DAT_TextureRenderCoreObject::ptr)(
                                        OpenSHC::DE::SHCDE::GM_MINE_ANIMS, iVar11, iVar6 + xUnk, iVar9 + yUnk);
                                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field22_0x40;
                                    if (iVar11 != 0) {
                                        iVar6 = yUnk + -0x54;
                                        iVar9 = xUnk + -0x33;
                                        gmID = OpenSHC::DE::SHCDE::GM_MINE_ANIMS;
                                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                                    }
                                    break;
                                }
                                iVar6 = -0x23;
                                iVar9 = -0x59;
                            }
                        }
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_MINE_ANIMS, iVar11, iVar6 + xUnk, iVar9 + yUnk);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field22_0x40;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x54;
                        iVar9 = xUnk + -0x33;
                        gmID = OpenSHC::DE::SHCDE::GM_MINE_ANIMS;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_PITCHRIG:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x50;
                        iVar9 = xUnk + 0xc;
                        DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                        gmID = OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_HUNTERSHUT:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = 0xbd;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, iVar11, xUnk + -0x25, yUnk + -0x56);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_HUNTER;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x3c;
                        iVar9 = xUnk + -0x23;
                        gmID = OpenSHC::DE::SHCDE::GM_HUNTER_ANIMS;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_MERCENARYPOST:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x6b;
                        iVar9 = xUnk + -0x25;
                        DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                        gmID = OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_BARRACKS:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x75;
                        iVar9 = xUnk + -0x25;
                        DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                        gmID = OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_ARMORY:
                    piVar7 = &DAT_BuildingsState::instance.buildings[tileIndex].tileRef2;
                    do {
                        if (piVar7[-1] == param_4)
                            break;
                        if (*piVar7 == param_4) {
                            iVar6 = iVar6 + 1;
                            break;
                        }
                        if (piVar7[1] == param_4) {
                            iVar6 = iVar6 + 2;
                            break;
                        }
                        if (piVar7[2] == param_4) {
                            iVar6 = iVar6 + 3;
                            break;
                        }
                        iVar6 = iVar6 + 4;
                        piVar7 = piVar7 + 4;
                    } while (iVar6 < 0x10);
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
                        local_18 = 0xd;
                        local_14 = 0xf;
                        break;
                    case 2:
                        iVar9 = 4;
                        local_4 = 3;
                        local_10 = 6;
                        local_18 = 0xc;
                        local_14 = 0xe;
                        break;
                    case 4:
                        iVar9 = 0;
                        local_4 = 0xf;
                        local_10 = 2;
                        local_18 = 8;
                        local_14 = 10;
                        break;
                    case 6:
                        local_4 = 0xc;
                        iVar9 = 1;
                        local_10 = 3;
                        local_18 = 9;
                        local_14 = 0xb;
                    }
                    iVar10 = 0;
                    if (iVar6 == iVar9) {
                        iVar10 = DAT_BuildingsState::instance.buildings[tileIndex].field29_0x5c;
                    } else if (iVar6 == local_10) {
                        iVar10 = DAT_BuildingsState::instance.buildings[tileIndex].shouldRenderSomeOverlay;
                    } else if (iVar6 == local_18) {
                        iVar10 = DAT_BuildingsState::instance.buildings[tileIndex].field37_0x7c;
                    } else if (iVar6 == local_14) {
                        iVar10 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    }
                    if (0x20 <= iVar10) {
                        iVar10 = 0;
                        GVar12 = OpenSHC::IO::Graphics::GID_ANIM_GOODS;
                        local_8 = 0;
                    } else {
                        GVar12 = OpenSHC::IO::Graphics::GID_ANIM_SHIELDS;
                        local_8 = -10;
                        iVar10 = DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[0x68].originY;
                    }
                    iVar3 = DAT_BuildingsState::instance.buildings[tileIndex].field29_0x5c;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = GVar12;
                    if ((iVar3 != 0) && (iVar6 == iVar9)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(GVar12,
                            DAT_BuildingsState::instance.buildings[tileIndex].field29_0x5c,
                            (xUnk
                                - (int)DAT_GMImageHeaders::instance
                                        .imh[iVar3 + GMTotalPicturesProcessed::instance[GVar12] + -1]
                                        .width
                                    / 2)
                                + 0xf + local_8,
                            (yUnk
                                - DAT_GMImageHeaders::instance
                                    .imh[iVar3 + GMTotalPicturesProcessed::instance[GVar12] + -1]
                                    .height)
                                + -0xf + iVar10,
                            iVar11);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].shouldRenderSomeOverlay;
                    if ((iVar9 != 0) && (iVar6 == local_10)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(GVar12,
                            DAT_BuildingsState::instance.buildings[tileIndex].shouldRenderSomeOverlay,
                            (xUnk
                                - (int)DAT_GMImageHeaders::instance
                                        .imh[iVar9 + GMTotalPicturesProcessed::instance[GVar12] + -1]
                                        .width
                                    / 2)
                                + 0xf + local_8,
                            (yUnk
                                - DAT_GMImageHeaders::instance
                                    .imh[iVar9 + GMTotalPicturesProcessed::instance[GVar12] + -1]
                                    .height)
                                + -0xf + iVar10,
                            iVar11);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].field37_0x7c;
                    if ((iVar9 != 0) && (iVar6 == local_18)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(GVar12,
                            DAT_BuildingsState::instance.buildings[tileIndex].field37_0x7c,
                            (xUnk
                                - (int)DAT_GMImageHeaders::instance
                                        .imh[iVar9 + GMTotalPicturesProcessed::instance[GVar12] + -1]
                                        .width
                                    / 2)
                                + 0xf + local_8,
                            (yUnk
                                - DAT_GMImageHeaders::instance
                                    .imh[iVar9 + GMTotalPicturesProcessed::instance[GVar12] + -1]
                                    .height)
                                + -0xf + iVar10,
                            iVar11);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    if ((iVar9 != 0) && (iVar6 == local_14)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(GVar12, iVar9,
                            (xUnk
                                - (int)DAT_GMImageHeaders::instance
                                        .imh[iVar9 + GMTotalPicturesProcessed::instance[GVar12] + -1]
                                        .width
                                    / 2)
                                + 0xf + local_8,
                            (yUnk
                                - DAT_GMImageHeaders::instance
                                    .imh[iVar9 + GMTotalPicturesProcessed::instance[GVar12] + -1]
                                    .height)
                                + -0xf + iVar10,
                            iVar11);
                    }
                    if (param_4
                        == *(int*)(DAT_BuildingsState::instance.buildings[tileIndex].workers + local_4 * 2 + 8)) {
                        DAT_RenderedUnitOwner::instance
                            = DAT_BuildingsState::instance.buildings[tileIndex].playerColorUnk;
                        iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field36_0x78;
                        DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                        if (iVar11 != 0) {
                            iVar6 = yUnk + -0x88;
                            iVar9 = xUnk + -0x26;
                            DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                            gmID = OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL;
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                            break;
                        }
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_FLETCHER:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x82;
                        iVar9 = xUnk + -0x25;
                        DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                        gmID = OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_BLACKSMITH:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = 0xbd;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, iVar11, xUnk + -0x25, yUnk + -0x7b);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                    DAT_RenderedUnitOwner::instance = 2;
                    DAT_CurrentlyRenderedSpriteID::instance = 0x3a;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_WORKSHOP_SMITH_ANIMS, iVar11, xUnk + -0x23, yUnk + -0x49);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field21_0x3c;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_SMOKE_30X30;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::IO::Graphics::GID_SMOKE_30X30, iVar11, xUnk + 3, yUnk + -0x7c, 0x10);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_POLETURNER:
                case OpenSHC::Map::Buildings::BT_TANNER:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x80;
                        iVar9 = xUnk + -0x25;
                        DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                        gmID = OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_ARMOURER:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x89;
                        iVar9 = xUnk + -0x25;
                        DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                        gmID = OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_BAKERY:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = 0xbd;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, iVar11, xUnk + -0x25, yUnk + -0x7b);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = 0x42;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_WORKSHOP_BAKER_ANIMS, iVar11, xUnk + -0x14, yUnk + -0x5f);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field21_0x3c;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_SMOKE_30X30;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::IO::Graphics::GID_SMOKE_30X30, iVar11, xUnk + -4, yUnk + -0x8c, 0x10);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_BREWERY:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = 0xbd;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, iVar11, xUnk + -0x25, yUnk + -0x7b);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                    DAT_RenderedUnitOwner::instance = 2;
                    DAT_CurrentlyRenderedSpriteID::instance = 0x33;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_WORKSHOP_BREW_ANIMS, iVar11, xUnk + -0x3c, yUnk + -0x44);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field21_0x3c;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_SMOKE_30X30;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::IO::Graphics::GID_SMOKE_30X30, iVar11, xUnk + 7, yUnk + -0x7c, 0x10);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_GRANARY:
                    iVar6 = 0;
                    piVar7 = &DAT_BuildingsState::instance.buildings[tileIndex].tileRef2;
                    do {
                        if (piVar7[-1] == param_4)
                            break;
                        if (*piVar7 == param_4) {
                            iVar6 = iVar6 + 1;
                            break;
                        }
                        if (piVar7[1] == param_4) {
                            iVar6 = iVar6 + 2;
                            break;
                        }
                        if (piVar7[2] == param_4) {
                            iVar6 = iVar6 + 3;
                            break;
                        }
                        iVar6 = iVar6 + 4;
                        piVar7 = piVar7 + 4;
                    } while (iVar6 < 0x10);
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                    if ((iVar9 != 0) && (iVar6 == 0)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38,
                            (int)((int)((xUnk
                                            - DAT_GMImageHeaders::instance
                                                    .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                    .width
                                                / 2)
                                + 0xf)),
                            (int)((int)((yUnk
                                            - DAT_GMImageHeaders::instance
                                                .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                .height)
                                + -5)),
                            iVar11);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].field22_0x40;
                    if ((iVar9 != 0) && (iVar6 == 1)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].field22_0x40,
                            (int)((int)((xUnk
                                            - DAT_GMImageHeaders::instance
                                                    .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                    .width
                                                / 2)
                                + 0xf)),
                            (int)((int)((yUnk
                                            - DAT_GMImageHeaders::instance
                                                .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                .height)
                                + -5)),
                            iVar11);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].shouldRenderRoof;
                    if ((iVar9 != 0) && (iVar6 == 2)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].shouldRenderRoof,
                            (int)((int)((xUnk
                                            - DAT_GMImageHeaders::instance
                                                    .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                    .width
                                                / 2)
                                + 0xf)),
                            (int)((int)((yUnk
                                            - DAT_GMImageHeaders::instance
                                                .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                .height)
                                + -5)),
                            iVar11);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].field34_0x70;
                    if ((iVar9 != 0) && (iVar6 == 3)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].field34_0x70,
                            (int)((int)((xUnk
                                            - DAT_GMImageHeaders::instance
                                                    .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                    .width
                                                / 2)
                                + 0xf)),
                            (int)((int)((yUnk
                                            - DAT_GMImageHeaders::instance
                                                .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                .height)
                                + -5)),
                            iVar11);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].field21_0x3c;
                    if ((iVar9 != 0) && (iVar6 == 4)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].field21_0x3c,
                            (int)((int)((xUnk
                                            - DAT_GMImageHeaders::instance
                                                    .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                    .width
                                                / 2)
                                + 0xf)),
                            (int)((int)((yUnk
                                            - DAT_GMImageHeaders::instance
                                                .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                .height)
                                + -5)),
                            iVar11);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].field23_0x44;
                    if ((iVar9 != 0) && (iVar6 == 5)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].field23_0x44,
                            (int)((int)((xUnk
                                            - DAT_GMImageHeaders::instance
                                                    .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                    .width
                                                / 2)
                                + 0xf)),
                            (int)((int)((yUnk
                                            - DAT_GMImageHeaders::instance
                                                .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                .height)
                                + -5)),
                            iVar11);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].field32_0x68;
                    if ((iVar9 != 0) && (iVar6 == 6)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].field32_0x68,
                            (int)((int)((xUnk
                                            - DAT_GMImageHeaders::instance
                                                    .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                    .width
                                                / 2)
                                + 0xf)),
                            (int)((int)((yUnk
                                            - DAT_GMImageHeaders::instance
                                                .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                .height)
                                + -5)),
                            iVar11);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].field37_0x7c;
                    if ((iVar9 != 0) && (iVar6 == 7)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].field37_0x7c,
                            (int)((int)((xUnk
                                            - DAT_GMImageHeaders::instance
                                                    .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                    .width
                                                / 2)
                                + 0xf)),
                            (int)((int)((yUnk
                                            - DAT_GMImageHeaders::instance
                                                .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                .height)
                                + -5)),
                            iVar11);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].field29_0x5c;
                    if ((iVar9 != 0) && (iVar6 == 8)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].field29_0x5c,
                            (int)((int)((xUnk
                                            - DAT_GMImageHeaders::instance
                                                    .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                    .width
                                                / 2)
                                + 0xf)),
                            (int)((int)((yUnk
                                            - DAT_GMImageHeaders::instance
                                                .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                .height)
                                + -5)),
                            iVar11);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].shouldRenderSomeOverlay;
                    if ((iVar9 != 0) && (iVar6 == 9)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].shouldRenderSomeOverlay,
                            (int)((int)((xUnk
                                            - DAT_GMImageHeaders::instance
                                                    .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                    .width
                                                / 2)
                                + 0xf)),
                            (int)((int)((yUnk
                                            - DAT_GMImageHeaders::instance
                                                .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                .height)
                                + -5)),
                            iVar11);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].field35_0x74;
                    if ((iVar9 != 0) && (iVar6 == 10)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].field35_0x74,
                            (int)((int)((xUnk
                                            - DAT_GMImageHeaders::instance
                                                    .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                    .width
                                                / 2)
                                + 0xf)),
                            (int)((int)((yUnk
                                            - DAT_GMImageHeaders::instance
                                                .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                .height)
                                + -5)),
                            iVar11);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    if ((iVar9 != 0) && (iVar6 == 0xb)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84,
                            (int)((int)((xUnk
                                            - DAT_GMImageHeaders::instance
                                                    .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                    .width
                                                / 2)
                                + 0xf)),
                            (int)((int)((yUnk
                                            - DAT_GMImageHeaders::instance
                                                .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                .height)
                                + -5)),
                            iVar11);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].field33_0x6c;
                    if ((iVar9 != 0) && (iVar6 == 0xc)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].field33_0x6c,
                            (int)((int)((xUnk
                                            - DAT_GMImageHeaders::instance
                                                    .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                    .width
                                                / 2)
                                + 0xf)),
                            (int)((int)((yUnk
                                            - DAT_GMImageHeaders::instance
                                                .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                .height)
                                + -5)),
                            iVar11);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].field36_0x78;
                    if ((iVar9 != 0) && (iVar6 == 0xd)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].field36_0x78,
                            (int)((int)((xUnk
                                            - DAT_GMImageHeaders::instance
                                                    .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                    .width
                                                / 2)
                                + 0xf)),
                            (int)((int)((yUnk
                                            - DAT_GMImageHeaders::instance
                                                .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                .height)
                                + -5)),
                            iVar11);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].ownerFlagFrame;
                    if ((iVar9 != 0) && (iVar6 == 0xe)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS,
                            DAT_BuildingsState::instance.buildings[tileIndex].ownerFlagFrame,
                            (int)((int)((xUnk
                                            - DAT_GMImageHeaders::instance
                                                    .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                    .width
                                                / 2)
                                + 0xf)),
                            (int)((int)((yUnk
                                            - DAT_GMImageHeaders::instance
                                                .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                .height)
                                + -5)),
                            iVar11);
                    }
                    iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].field40_0x88;
                    if ((iVar9 != 0) && (iVar6 == 0xf)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_GOODS, iVar9,
                            (int)((int)((xUnk
                                            - DAT_GMImageHeaders::instance
                                                    .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                    .width
                                                / 2)
                                + 0xf)),
                            (int)((int)((yUnk
                                            - DAT_GMImageHeaders::instance
                                                .imh[GMTotalPicturesProcessed::instance[0x1c] + iVar9 + -1]
                                                .height)
                                + -5)),
                            iVar11);
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_QUARRY:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = 0xbd;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, iVar11, xUnk + -0x26, yUnk + -0x3c);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                    DAT_RenderedUnitOwner::instance = 1;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_QUARRY;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_QUARRY_ANIMS, iVar11, xUnk + 0xc, yUnk + -0x8c);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field21_0x3c;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_QUARRY_ANIMS, iVar11, xUnk + -0x31, yUnk + -0x88);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field22_0x40;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_QUARRY_ANIMS, iVar11, xUnk + -0x20, yUnk + -0x6b);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field23_0x44;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x6f;
                        iVar9 = xUnk + -0x5f;
                        gmID = OpenSHC::DE::SHCDE::GM_QUARRY_ANIMS;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_INN:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = 0xbd;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, iVar11, xUnk + -0x45, yUnk + -0x95);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_INN;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ANIM_INN, iVar11,
                            DAT_BuildingsState::instance.buildings[tileIndex].spriteOffetX + xUnk,
                            DAT_BuildingsState::instance.buildings[tileIndex].spriteOffetY + yUnk);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field21_0x3c;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ANIM_INN, iVar11,
                            DAT_BuildingsState::instance.buildings[tileIndex].spriteOffetX + xUnk,
                            DAT_BuildingsState::instance.buildings[tileIndex].spriteOffetY + yUnk);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field22_0x40;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ANIM_INN, iVar11,
                            DAT_BuildingsState::instance.buildings[tileIndex].spriteOffetX + xUnk,
                            DAT_BuildingsState::instance.buildings[tileIndex].spriteOffetY + yUnk);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field23_0x44;
                    if (iVar11 != 0) {
                        iVar6 = DAT_BuildingsState::instance.buildings[tileIndex].spriteOffetY + yUnk;
                        iVar9 = DAT_BuildingsState::instance.buildings[tileIndex].spriteOffetX + xUnk;
                        gmID = OpenSHC::DE::SHCDE::GM_ANIM_INN;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_APOTHECARY:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0xb1;
                        iVar9 = xUnk + 5;
                        DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                        gmID = OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_ENGINEERSGUILD:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x72;
                        iVar9 = xUnk + -0x33;
                        DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                        gmID = OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_TUNNELERSGUILD:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x77;
                        iVar9 = xUnk + -0x36;
                        DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                        gmID = OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_MARKETPLACE:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x6a;
                        iVar9 = xUnk + -0x27;
                        DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                        gmID = OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_OILSMELTER:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = 0xbd;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, iVar11, xUnk + 3, yUnk + -0x7d);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_BOILED_OIL;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_OIL_ANIMS, iVar11, xUnk + -0x23, yUnk + -0x3e);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field21_0x3c;
                    if (iVar11 != 0) {
                        iVar9 = xUnk + -0x23;
                        if (iVar11 < 0x7b) {
                            iVar6 = yUnk + -100;
                            gmID = OpenSHC::DE::SHCDE::GM_OIL_ANIMS;
                        } else {
                            iVar6 = yUnk + -0x66;
                            gmID = OpenSHC::DE::SHCDE::GM_OIL_ANIMS;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_WHEATFARM:
                case OpenSHC::Map::Buildings::BT_HOPFARM:
                case OpenSHC::Map::Buildings::BT_APPLEFARM:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x6d;
                        iVar9 = xUnk + -0x37;
                        DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                        gmID = OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_DAIRYFARM:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = 0xbd;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, iVar11, xUnk + -0x37, yUnk + -0x6d);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FARMER;
                    if (iVar11 != 0) {
                        sVar1 = DAT_BuildingsState::instance.buildings[tileIndex].field66_0xbe;
                        if (sVar1 == 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_FARMER_ANIMS, iVar11, xUnk + -0x23, yUnk + -0x51);
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_FARMER, iVar11,
                                xUnk + -0x23, yUnk + -0x51, (int)((int)(sVar1)));
                        }
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field21_0x3c;
                    if (iVar11 != 0) {
                        sVar1 = DAT_BuildingsState::instance.buildings[tileIndex].field66_0xbe;
                        if (sVar1 == 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_FARMER_ANIMS, iVar11, xUnk + -0x23, yUnk + -0x51);
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_FARMER, iVar11,
                                xUnk + -0x23, yUnk + -0x51, (int)((int)(sVar1)));
                        }
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field22_0x40;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_FARMER_ANIMS, iVar11, xUnk + -0x23, yUnk + -0x51);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field23_0x44;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x51;
                        iVar9 = xUnk + -0x23;
                        gmID = OpenSHC::DE::SHCDE::GM_FARMER_ANIMS;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_MILL:
                    iVar6 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = 0xbd;
                    if (iVar6 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, iVar6, xUnk + -0x26, yUnk + -0x72);
                    }
                    iVar6 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_WINDMILL;
                    if (iVar6 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_WINDMILL_ANIMS, iVar6, xUnk + -0x4e, yUnk + -0x103);
                    }
                    iVar6 = DAT_BuildingsState::instance.buildings[tileIndex].field21_0x3c;
                    if (iVar6 != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::IO::Graphics::GID_ANIM_WINDMILL, iVar6, xUnk + -0x4e, yUnk + -0x103, iVar11);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field22_0x40;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_WINDMILL_ANIMS, iVar11, xUnk + -0x4e, yUnk + -0xd0);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field23_0x44;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x124;
                        iVar9 = xUnk + -0x59;
                        gmID = OpenSHC::DE::SHCDE::GM_WINDMILL_ANIMS;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_STABLES:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = 0xbd;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, iVar11, xUnk + -0x12, yUnk + -99);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field23_0x44;
                    DAT_RenderedUnitOwner::instance = 0;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_STABLES;
                    if (iVar11 != 0) {
                        sVar1 = DAT_BuildingsState::instance.buildings[tileIndex].field66_0xbe;
                        if (iVar11 < 0x26) {
                            if (sVar1 == 0) {
                                iVar6 = yUnk + -0x6b;
                                iVar9 = xUnk + -0x50;
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_STABLE_ANIMS, iVar11, iVar9, iVar6);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_STABLES, iVar11,
                                    xUnk + -0x50, yUnk + -0x6b, (int)((int)(sVar1)));
                            }
                        } else {
                            if (sVar1 == 0) {
                                iVar6 = yUnk + -100;
                                iVar9 = xUnk + -0x67;
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_STABLE_ANIMS, iVar11, iVar9, iVar6);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_STABLES, iVar11,
                                    xUnk + -0x50, yUnk + -0x6b, (int)((int)(sVar1)));
                            }
                        }
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field22_0x40;
                    if (iVar11 != 0) {
                        sVar1 = DAT_BuildingsState::instance.buildings[tileIndex].field66_0xbe;
                        if (iVar11 < 0x26) {
                            if (sVar1 == 0) {
                                iVar6 = yUnk + -0x60;
                                iVar9 = xUnk + -0x3a;
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_STABLE_ANIMS, iVar11, iVar9, iVar6);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_STABLES, iVar11,
                                    xUnk + -0x3a, yUnk + -0x60, (int)((int)(sVar1)));
                            }
                        } else {
                            if (sVar1 == 0) {
                                iVar6 = yUnk + -0x53;
                                iVar9 = xUnk + -0x51;
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_STABLE_ANIMS, iVar11, iVar9, iVar6);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_STABLES, iVar11,
                                    xUnk + -0x3a, yUnk + -0x60, (int)((int)(sVar1)));
                            }
                        }
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field21_0x3c;
                    if (iVar11 != 0) {
                        sVar1 = DAT_BuildingsState::instance.buildings[tileIndex].field66_0xbe;
                        if (iVar11 < 0x26) {
                            if (sVar1 == 0) {
                                iVar6 = yUnk + -0x55;
                                iVar9 = xUnk + -0x24;
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_STABLE_ANIMS, iVar11, iVar9, iVar6);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_STABLES, iVar11,
                                    xUnk + -0x24, yUnk + -0x55, (int)((int)(sVar1)));
                            }
                        } else {
                            if (sVar1 == 0) {
                                iVar6 = yUnk + -0x4a;
                                iVar9 = xUnk + -0x37;
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_STABLE_ANIMS, iVar11, iVar9, iVar6);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_STABLES, iVar11,
                                    xUnk + -0x24, yUnk + -0x55, (int)((int)(sVar1)));
                            }
                        }
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                    if (iVar11 != 0) {
                        sVar1 = DAT_BuildingsState::instance.buildings[tileIndex].field66_0xbe;
                        if (iVar11 < 0x26) {
                            if (sVar1 == 0) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_STABLE_ANIMS, iVar11, xUnk + -0xe, yUnk + -0x4a);
                            } else {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_STABLES, iVar11,
                                    xUnk + -0xe, yUnk + -0x4a, (int)((int)(sVar1)));
                            }
                            sVar1 = DAT_BuildingsState::instance.buildings[tileIndex].field66_0xbe;
                            if (sVar1 == 0) {
                                iVar6 = yUnk + -0x49;
                                iVar9 = xUnk + -2;
                                iVar11 = 0x26;
                                gmID = OpenSHC::DE::SHCDE::GM_STABLE_ANIMS;
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                                break;
                            }
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_STABLES, 0x26,
                                xUnk + -0xd, yUnk + -0x49, (int)((int)(sVar1)));
                        } else {
                            if (sVar1 == 0) {
                                iVar6 = yUnk + -0x3f;
                                iVar9 = xUnk + -0x21;
                                gmID = OpenSHC::DE::SHCDE::GM_STABLE_ANIMS;
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                                break;
                            }
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_ANIM_STABLES, iVar11,
                                xUnk + -0xe, yUnk + -0x4a, (int)((int)(sVar1)));
                        }
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_CHAPEL:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x7c;
                        iVar9 = xUnk + -0x26;
                        DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                        gmID = OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_CHURCH:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x97;
                        iVar9 = xUnk + -9;
                        DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                        gmID = OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_CATHEDRAL:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field39_0x84;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0xca;
                        iVar9 = xUnk + -0xd;
                        DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_FLAG_SMALL;
                        gmID = OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_STONEKEEP:
                    if ((DAT_BuildingsState::instance.buildings[tileIndex].field62_0xb0 == 0)
                        && (iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38, iVar11 != 0)) {
                        iVar6 = yUnk + -0x8f;
                        iVar9 = xUnk + -0x60;
                        gmID = OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_STRONGHOLD:
                    if ((DAT_BuildingsState::instance.buildings[tileIndex].field62_0xb0 == 0)
                        && (iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38, iVar11 != 0)) {
                        iVar6 = yUnk + -0x12a;
                        iVar9 = xUnk + -0x9f;
                        gmID = OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + -7, yUnk + -0xc1);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field21_0x3c;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + -0x60, yUnk + -0xc1);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field22_0x40;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + 3, yUnk + -0x5b);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field23_0x44;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + -0x33, yUnk + -0x5b);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field29_0x5c;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_BODY_GATE, iVar11, xUnk + 0x11, yUnk + -0x5e);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].shouldRenderRoof;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x5e;
                        iVar9 = xUnk + -0x56;
                        gmID = OpenSHC::DE::SHCDE::GM_BODY_GATE;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + 5, yUnk + -0xb2);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field21_0x3c;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + -0x40, yUnk + -0xb1);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field22_0x40;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + -0xd, yUnk + -0x53);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field23_0x44;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + -0x23, yUnk + -0x53);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field29_0x5c;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_BODY_GATE, iVar11, xUnk, yUnk + -0x58);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].shouldRenderRoof;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x58;
                        iVar9 = xUnk + -0x46;
                        gmID = OpenSHC::DE::SHCDE::GM_BODY_GATE;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_WOODGATE1:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + 3, yUnk + -0x6e);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field21_0x3c;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + -0x20, yUnk + -0x6a);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field22_0x40;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + -0x20, yUnk + -0x46);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field23_0x44;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + 8, yUnk + -0x47);
                    }
                    if (DAT_BuildingsState::instance.buildings[tileIndex].field62_0xb0 == 0) {
                        iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field29_0x5c;
                        if (iVar11 != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + 0x11, yUnk + -0x37);
                        }
                        iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].shouldRenderRoof;
                        if (iVar11 != 0) {
                            iVar6 = yUnk + -0x37;
                            iVar9 = xUnk + -0x15;
                            gmID = OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS;
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                            break;
                        }
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_DRAWBRIDGE:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                    if (iVar11 != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + 7, yUnk + -0x7c);
                    }
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field23_0x44;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x7e;
                        iVar9 = xUnk + -0x33;
                        gmID = OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_TOWER1:
                    if (DAT_BuildingsState::instance.buildings[tileIndex].field62_0xb0 == 0) {
                        iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                        if (iVar11 != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + -0x21, yUnk + -0x140);
                        }
                        iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].shouldRenderRoof;
                        if (iVar11 != 0) {
                            iVar6 = yUnk + -0x17b;
                            iVar9 = xUnk + -0x22;
                            gmID = OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS;
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                            break;
                        }
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_TOWER2:
                    if (DAT_BuildingsState::instance.buildings[tileIndex].field62_0xb0 == 0) {
                        iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                        if (iVar11 != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + -0x30, yUnk + -0xc2);
                        }
                        iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field22_0x40;
                        if (iVar11 != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + -0x29, yUnk + -0x93);
                        }
                        iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field29_0x5c;
                        if (iVar11 != 0) {
                            iVar6 = yUnk + -0x8c;
                            iVar9 = xUnk + -2;
                            gmID = OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS;
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                            break;
                        }
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_TOWER3:
                    if (DAT_BuildingsState::instance.buildings[tileIndex].field62_0xb0 == 0) {
                        iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                        if (iVar11 != 0) {
                            /*
                              crenellations
                             */

                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + -0x3f, yUnk + -0xe1);
                        }
                        iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field22_0x40;
                        if (iVar11 != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + -0x29, yUnk + -0x96);
                        }
                        iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field29_0x5c;
                        if (iVar11 != 0) {
                            iVar6 = yUnk + -0x93;
                            iVar9 = xUnk + 0xd;
                            gmID = OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS;
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                            break;
                        }
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_TOWER4:
                    if (DAT_BuildingsState::instance.buildings[tileIndex].field62_0xb0 == 0) {
                        iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                        if (iVar11 != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + -0x4d, yUnk + -0xf6);
                        }
                        iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field22_0x40;
                        if (iVar11 != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + -0x39, yUnk + -0x9a);
                        }
                        iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field29_0x5c;
                        if (iVar11 != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + 0xf, yUnk + -0x96);
                        }
                        iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].shouldRenderRoof;
                        if (iVar11 != 0) {
                            /*
                              roof
                             */

                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + -0x4d, yUnk + -0x13b);
                        }
                        iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].shouldRenderSomeOverlay;
                        if (iVar11 != 0) {
                            iVar6 = yUnk + -0x114;
                            iVar9 = xUnk + -0x4d;
                            gmID = OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS;
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                            break;
                        }
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_TOWER5:
                    if (DAT_BuildingsState::instance.buildings[tileIndex].field62_0xb0 == 0) {
                        iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                        if (iVar11 != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + -0x4c, yUnk + -0x104);
                        }
                        iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field22_0x40;
                        if (iVar11 != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS, iVar11, xUnk + -0x32, yUnk + -0x9d);
                        }
                        iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field29_0x5c;
                        if (iVar11 != 0) {
                            iVar6 = yUnk + -0x97;
                            iVar9 = xUnk + 0x10;
                            gmID = OpenSHC::DE::SHCDE::GM_CASTLE_ANIMS;
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                            break;
                        }
                    }
                    break;
                case OpenSHC::Map::Buildings::BT_CHOPPINGBLOCK:
                    iVar11 = DAT_BuildingsState::instance.buildings[tileIndex].field20_0x38;
                    DAT_CurrentlyRenderedSpriteID::instance = OpenSHC::IO::Graphics::GID_ANIM_CHOPPING_BLOCK;
                    DAT_RenderedUnitOwner::instance = 0;
                    if (iVar11 != 0) {
                        iVar6 = yUnk + -0x4c;
                        iVar9 = xUnk + -0x23;
                        gmID = OpenSHC::DE::SHCDE::GM_ANIM_CHOPPING_BLOCK;
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar9, iVar6);
                        break;
                    }
                }
            }
        }
        iVar11 = DAT_BuildingDefinedData::instance
                     .BuildingHeights[(short)DAT_BuildingsState::instance.buildings[tileIndex].buildingType];
        xUnk = 0;
        yUnk = 0;
        if (iVar11 == 0) {
            uVar8 = DAT_BuildingsState::instance.buildings[tileIndex].widthOrHeight;
            xUnk = uVar8 << 5;
            yUnk = uVar8 << 4;
        }
        if (((((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU)
                  && (tileIndex == DAT_BuildingsState::instance.menuSelectedBuildingID))
                 || ((tileIndex == DAT_BuildingsState::instance.field28_0x18e05c
                     && (DAT_BuildingsState::instance.field29_0x18e060
                         == DAT_BuildingsState::instance.buildings[tileIndex].uid))))
                && (((((sVar1 = DAT_BuildingsState::instance.buildings[tileIndex].maxHealth,
                           sVar1 != 0
                               && (DAT_BuildingsState::instance.buildings[tileIndex].buildingType
                                   != OpenSHC::Map::Buildings::BT_MANORHOUSE))
                          && (DAT_BuildingsState::instance.buildings[tileIndex].buildingType
                              != OpenSHC::Map::Buildings::BT_STONEKEEP))
                         && ((DAT_BuildingsState::instance.buildings[tileIndex].buildingType
                                 != OpenSHC::Map::Buildings::BT_STRONGHOLD
                             && (DAT_BuildingsState::instance.buildings[tileIndex].buildingType
                                 != OpenSHC::Map::Buildings::BT_KEEPFOUR))))
                    && (DAT_BuildingsState::instance.buildings[tileIndex].buildingType
                        != OpenSHC::Map::Buildings::BT_KEEPFIVE))))
            && (DAT_BuildingsState::instance.buildings[tileIndex].buildingType
                != OpenSHC::Map::Buildings::BT_CAMPGROUND)) {
            iVar6 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::computeHealthPercentage,
                DAT_DirectionAlgorithmState::ptr)(
                (int)DAT_BuildingsState::instance.buildings[tileIndex].currentHealth, (int)((int)(sVar1)));
            switch (DAT_BuildingsState::instance.buildings[tileIndex].buildingType) {
            case OpenSHC::Map::Buildings::BT_GATEHOUSELARGE:
                yUnk = yUnk + 0x14;
                break;
            case OpenSHC::Map::Buildings::BT_GATEHOUSESMALL:
                yUnk = yUnk + 0x1e;
                break;
            case OpenSHC::Map::Buildings::BT_SIEGETOWER_PLACED:
                yUnk = yUnk + -0x1e;
                break;
            case OpenSHC::Map::Buildings::BT_TOWER2:
                yUnk = yUnk + 0x50;
                break;
            case OpenSHC::Map::Buildings::BT_TOWER3:
            case OpenSHC::Map::Buildings::BT_TOWER4:
                yUnk = yUnk + 0x5a;
                break;
            case OpenSHC::Map::Buildings::BT_TOWER5:
                yUnk = yUnk + 100;
            }
            if ((uint)(iVar6 / 10) < 0xb) {
                BVar2 = DAT_BuildingsState::instance.buildings[tileIndex].buildingType;
                if ((BVar2 == OpenSHC::Map::Buildings::BT_GRANARY) || (BVar2 == OpenSHC::Map::Buildings::BT_ARMORY)) {
                    iVar9 = 0;
                    piVar7 = &DAT_BuildingsState::instance.buildings[tileIndex].tileRef2;
                    do {
                        if (piVar7[-1] == param_4)
                            break;
                        if (*piVar7 == param_4) {
                            iVar9 = iVar9 + 1;
                            break;
                        }
                        if (piVar7[1] == param_4) {
                            iVar9 = iVar9 + 2;
                            break;
                        }
                        if (piVar7[2] == param_4) {
                            iVar9 = iVar9 + 3;
                            break;
                        }
                        iVar9 = iVar9 + 4;
                        piVar7 = piVar7 + 4;
                    } while (iVar9 < 0x10);
                    if (((DAT_TileMapState::instance.mapOrientation == 0) && (iVar9 == 0xf))
                        || ((DAT_TileMapState::instance.mapOrientation == 2) && (iVar9 == 0xc))
                        || ((DAT_TileMapState::instance.mapOrientation == 4) && (iVar9 == 0))
                        || ((DAT_TileMapState::instance.mapOrientation == 6) && (iVar9 == 3))) {
                        iVar11 = (iVar5 - iVar11) - yUnk;
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_FLOATS, iVar6 / 10 + 0x11, iVar4 + 4, iVar11 + -0xc);
                    }
                } else {
                    iVar11 = (iVar5 - iVar11) - yUnk;
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_FLOATS, iVar6 / 10 + 0x11, iVar4 + 4, iVar11 + -0xc);
                }
            }
        }
        if ((DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_BUILDERUnk)
            || (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 != OpenSHC::Map::MT_SIEGE)) {
            if (DAT_BuildingsState::instance.buildings[tileIndex].sleeping != false) {
                uVar8 = DAT_TileMapState::instance.field161_0x5549c0 - 1U & 0x80000007;
                if ((int)uVar8 < 0) {
                    uVar8 = (uVar8 - 1 | 0xfffffff8) + 1;
                }
                iVar11 = uVar8 + 0xd3;
                maskGmID = OpenSHC::IO::Graphics::GID_FLOAT_POP_CIRC;
                iVar9 = (iVar5
                            - DAT_BuildingDefinedData::instance
                                .BuildingHeights[(short)DAT_BuildingsState::instance.buildings[tileIndex].buildingType])
                    - yUnk;
                iVar6 = uVar8 + 0xcb;
                GVar12 = OpenSHC::IO::Graphics::GID_FLOAT_POP_CIRC;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(GVar12, iVar6, iVar4 + -0x23, iVar9 + -0x2a, maskGmID, iVar11, 0);
            } else if ((DAT_BuildingsState::instance.buildings[tileIndex].currentlyNeededEmployeeCount != 0)
                && (DAT_GameCore::instance.field63_0x108 != 0)) {
                iVar11 = DAT_TileMapState::instance.field161_0x5549c0 + 0x128;
                maskGmID = OpenSHC::IO::Graphics::GID_FLOATS_NEW;
                iVar9 = (iVar5
                            - DAT_BuildingDefinedData::instance
                                .BuildingHeights[(short)DAT_BuildingsState::instance.buildings[tileIndex].buildingType])
                    - yUnk;
                iVar6 = DAT_TileMapState::instance.field161_0x5549c0 + 0x118;
                GVar12 = OpenSHC::IO::Graphics::GID_FLOATS_NEW;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(GVar12, iVar6, iVar4 + -0x23, iVar9 + -0x2a, maskGmID, iVar11, 0);
            }
        }
        sVar1 = DAT_BuildingsState::instance.buildings[tileIndex].field68_0xc2;
        if (sVar1 == 1) {
            iVar11 = DAT_TileMapState::instance.field161_0x5549c0 + 0x10;
            iVar6 = DAT_TileMapState::instance.field161_0x5549c0;
        } else {
            if (sVar1 != 2) {
                return;
            }
            iVar11 = DAT_TileMapState::instance.field161_0x5549c0 + 0x84;
            iVar6 = DAT_TileMapState::instance.field161_0x5549c0 + 0x74;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW, iVar6, iVar4 + -0x23,
            ((iVar5
                 - DAT_BuildingDefinedData::instance
                     .BuildingHeights[(short)DAT_BuildingsState::instance.buildings[tileIndex].buildingType])
                - xUnk)
                + -0x2a,
            OpenSHC::IO::Graphics::GID_FLOATS_NEW, iVar11, 0);
        DAT_BuildingsState::instance.buildings[tileIndex].field68_0xc2 = 0;
        return;
    }

}
}
