#include "../CrusadeMap.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/Text/GameLanguage.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/BOOLEnum_00ed313c.hpp"
#include "OpenSHC/Globals/DAT_CurrentlyRenderedSpriteID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_RenderedUnitOwner.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DWORD_00ed27a8.hpp"
#include "OpenSHC/Globals/DWORD_00ed311c.hpp"
#include "OpenSHC/Globals/DWORD_00ed3138.hpp"
#include "OpenSHC/Globals/INT_00eb9b48.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Game::TrailType;
        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Rendering::ScreenResolutionEnum;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::GameLanguage;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004DE300
        void CrusadeMap::MenuView_CrusadeMap_DoEveryFrame()
        {
            int (*paiVar1)[2];
            int (*paiVar2)[2];
            DWORD DVar3;
            DWORD DVar4;
            char* pcVar5;
            int drawX;
            int iVar6;
            int iVar7;
            int* piVar8;
            dword dVar9;
            uint uVar10;
            int iVar11;
            int iVar12;
            int iVar13;
            int iVar14;
            bool bVar15;
            TextAlignment TVar16;
            BGR24 BVar17;
            eGM eVar18;
            BOOLEnum BVar19;
            uint local_8;
            int* local_4;
            if ((BOOLEnum_00ed313c::instance & TRUE) == FALSE) {
                BOOLEnum_00ed313c::instance = BOOLEnum_00ed313c::instance | TRUE;
                DWORD_00ed3138::instance = timeGetTime();
            }
            DVar3 = timeGetTime();
            if ((DWORD_00ed311c::instance != 0) && (DVar4 = timeGetTime(), 1000 < DVar4 - DWORD_00ed311c::instance)) {
                DWORD_00ed311c::instance = 0;
                /*
                  "Afraid?"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                    "ri_kick_player_01.wav");
            }
            local_8 = (DVar3 - DWORD_00ed3138::instance) / 0x32;
            if (0xf < local_8) {
                local_8 = 0;
                DWORD_00ed3138::instance = timeGetTime();
            }
            piVar8 = local_4;
            if (INT_00eb9b48::instance == 0) {
                uVar10 = (DVar3 - DWORD_00ed27a8::instance) / 100;
                if (21 < uVar10) {
                    uVar10 = 0;
                    DWORD_00ed27a8::instance = timeGetTime();
                }
                piVar8 = (int*)DAT_MissionDefinedData::instance.field37_0x1314[uVar10];
            }
            if (0 < INT_00eb9b48::instance) {
                piVar8 = (int*)((DVar3 - DWORD_00ed27a8::instance) / 0x28);
                if ((int)piVar8 < 0x2d) {
                    if ((int)piVar8 < 0x25)
                        goto LAB_004de3ed;
                } else {
                    INT_00eb9b48::instance = 0;
                    DWORD_00ed27a8::instance = timeGetTime();
                }
                piVar8 = (int*)0x24;
            }
        LAB_004de3ed:
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderGfxHelperUnk)(0, 0, 0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            iVar11 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[0xcc].originX;
            iVar13 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight
                - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[0xcc].originY;
            iVar12 = iVar11 + -0xb;
            iVar14 = iVar13 + 0x12;
            local_4 = (int*)0x0;
            if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_FIRST_EDITION) {
                dVar9 = 0;
                if (0 < DAT_GameCore::instance.furthestSkirmishTrailMission) {
                    do {
                        if (0x30 < (int)dVar9)
                            break;
                        if (dVar9 == DAT_GameCore::instance.skirmishTrailProgress) {
                            if ((dVar9 == 0x22)
                                && (DAT_WindowAndDirectDraw::instance.currentGameResolution
                                    == OpenSHC::Rendering::SRE_800x600)) {
                                iVar11 = DAT_MissionDefinedData::instance.field32_0xbbc[0x22][0] + -0x14;
                                iVar6 = DAT_MissionDefinedData::instance.field32_0xbbc[0x22][1];
                            } else {
                                iVar6 = DAT_MissionDefinedData::instance.field32_0xbbc[dVar9][1];
                                iVar11 = DAT_MissionDefinedData::instance.field32_0xbbc[dVar9][0] + 10;
                            }
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_SKIRMISH_TRAIL_ICONS,
                                (int)((int)(piVar8 + 0x5e)), iVar11 + iVar12, iVar6 + -0x1a + iVar14, 0x10);
                        }
                        if (DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken[dVar9] != -0x4b0) {
                            if ((dVar9 == 0x12) || (dVar9 == 0x22)) {
                                local_4 = (int*)((int)local_4 + 4);
                            }
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_SKIRMISH_TRAIL_ICONS,
                                (int)((int)(DAT_MissionDefinedData::instance.field35_0xf2c[dVar9] + 0x2d + local_4)),
                                DAT_MissionDefinedData::instance.field32_0xbbc[dVar9][0] + iVar12,
                                DAT_MissionDefinedData::instance.field32_0xbbc[dVar9][1] + iVar14, 0x10);
                        }
                        if (dVar9 == DAT_GameCore::instance.skirmishTrailProgress) {
                            if ((dVar9 == 0x22)
                                && (DAT_WindowAndDirectDraw::instance.currentGameResolution
                                    == OpenSHC::Rendering::SRE_800x600)) {
                                iVar11 = DAT_MissionDefinedData::instance.field32_0xbbc[0x22][0] + -0x14;
                                iVar6 = DAT_MissionDefinedData::instance.field32_0xbbc[0x22][1];
                            } else {
                                iVar6 = DAT_MissionDefinedData::instance.field32_0xbbc[dVar9][1];
                                iVar11 = DAT_MissionDefinedData::instance.field32_0xbbc[dVar9][0] + 10;
                            }
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                (OpenSHC::DE::SHCDE::eGM)(OpenSHC::DE::SHCDE::GM_TREE_CACTII
                                    | OpenSHC::DE::SHCDE::GM_SEA_CHEVRONS),
                                (int)((int)(piVar8 + 0x39)), iVar11 + iVar12, iVar6 + -0x1a + iVar14);
                        }
                        if (DAT_GameCore::instance.skirmishTrailMonthsTakenOrChicken[dVar9] == -0x4b0) {
                            iVar6 = DAT_MissionDefinedData::instance.field36_0xff4[dVar9][3]
                                + DAT_MissionDefinedData::instance.field32_0xbbc[dVar9][1];
                            DAT_CurrentlyRenderedSpriteID::instance
                                = DAT_MissionDefinedData::instance.field36_0xff4[dVar9][0];
                            iVar7 = DAT_MissionDefinedData::instance.field36_0xff4[dVar9][2]
                                + DAT_MissionDefinedData::instance.field32_0xbbc[dVar9][0];
                            iVar11 = DAT_MissionDefinedData::instance.field36_0xff4[dVar9][1];
                            DAT_RenderedUnitOwner::instance = (OpenSHC::DE::SHCDE::eGM)(0);
                            eVar18 = (OpenSHC::DE::SHCDE::eGM)(DAT_CurrentlyRenderedSpriteID::instance);
                        } else {
                            iVar6 = DAT_MissionDefinedData::instance.field32_0xbbc[dVar9][1];
                            iVar7 = DAT_MissionDefinedData::instance.field32_0xbbc[dVar9][0];
                            iVar11 = (OpenSHC::DE::SHCDE::eGM)(DAT_MissionDefinedData::instance.field35_0xf2c[dVar9]
                                + 0x21 + (int)local_4);
                            eVar18 = (OpenSHC::DE::SHCDE::eGM)(OpenSHC::DE::SHCDE::GM_TREE_CACTII
                                | OpenSHC::DE::SHCDE::GM_SEA_CHEVRONS);
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(eVar18, iVar11, iVar7 + iVar12, iVar6 + iVar14);
                        dVar9 = dVar9 + 1;
                    } while ((int)dVar9 < DAT_GameCore::instance.furthestSkirmishTrailMission);
                }
                if ((DAT_GameCore::instance.skirmishTrailProgress
                        == DAT_GameCore::instance.furthestSkirmishTrailMission)
                    || (DAT_GameCore::instance.skirmishTrailProgress == 0x31)) {
                    paiVar2
                        = DAT_MissionDefinedData::instance.field32_0xbbc + DAT_GameCore::instance.skirmishTrailProgress;
                    paiVar1
                        = DAT_MissionDefinedData::instance.field32_0xbbc + DAT_GameCore::instance.skirmishTrailProgress;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_SKIRMISH_TRAIL_ICONS,
                        (int)((int)(piVar8 + 0x5e)), (*paiVar1)[0] + 10 + iVar12,
                        (int)((int)(iVar13 + -8
                            + DAT_MissionDefinedData::instance
                                .field32_0xbbc[DAT_GameCore::instance.skirmishTrailProgress][1])),
                        0x10);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)(OpenSHC::DE::SHCDE::GM_TREE_CACTII
                                                              | OpenSHC::DE::SHCDE::GM_SEA_CHEVRONS),
                        (int)((int)(piVar8 + 0x39)), (*paiVar1)[0] + 10 + iVar12,
                        (int)((int)(iVar13 + -8 + (*paiVar2)[1])));
                }
                dVar9 = DAT_GameCore::instance.furthestSkirmishTrailMission;
                if (0x31 < DAT_GameCore::instance.furthestSkirmishTrailMission) {
                    dVar9 = 0x31;
                }
                iVar12 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                    - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[0xcc].originX;
                iVar11 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight
                    - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[0xcc].originY;
                if (dVar9 != DAT_GameCore::instance.skirmishTrailProgress) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_SKIRMISH_TRAIL_ICONS,
                        (int)((int)(local_8 + 0x11)), DAT_MissionDefinedData::instance.field32_0xbbc[dVar9][0] + iVar12,
                        DAT_MissionDefinedData::instance.field32_0xbbc[dVar9][1] + iVar11, 0x10);
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    (OpenSHC::DE::SHCDE::eGM)(OpenSHC::DE::SHCDE::GM_TREE_CACTII | OpenSHC::DE::SHCDE::GM_SEA_CHEVRONS),
                    (int)((int)((OpenSHC::DE::SHCDE::eGM)((
                        OpenSHC::DE::SHCDE::eGM)((OpenSHC::DE::SHCDE::eGM)((OpenSHC::DE::SHCDE::eGM)(local_8 + 1)))))),
                    DAT_MissionDefinedData::instance.field32_0xbbc[dVar9][0] + iVar12,
                    DAT_MissionDefinedData::instance.field32_0xbbc[dVar9][1] + iVar11);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameCore::instance.skirmishTrailProgress + 1,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 10,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x10, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x10, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(".",
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xb,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x10, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x10, TRUE, 0);
                iVar14 = 0;
                BVar19 = TRUE;
                iVar13 = 0x10;
                BVar17 = 0xccfaff;
                TVar16 = OpenSHC::Text::TTA_LEFT;
                iVar11 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x10;
                iVar12 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x10;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TRAIL_NAMES_CRU,
                        (int)((int)(DAT_GameCore::instance.skirmishTrailProgress + 1))),
                    iVar12, iVar11, TVar16, BVar17, iVar13, BVar19, iVar14);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameCore::instance.skirmishTrailStartDateInMonths[DAT_GameCore::instance.skirmishTrailProgress]
                        / 0xc,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x10,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x30, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x12, FALSE, 0);
                if (DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_GERMAN) {
                    pcVar5 = " n. Chr.";
                } else {
                    pcVar5 = " A.D.";
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    pcVar5, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x11,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x30, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x12, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    (int)DAT_GameCore::instance.skirmishTrailYearReached / 0xc,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x2b7,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x10, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x11, FALSE, 0);
                iVar14 = 0;
                BVar19 = FALSE;
                iVar13 = 0x11;
                BVar17 = 0xccfaff;
                TVar16 = OpenSHC::Text::TTA_RIGHT;
                iVar11 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x10;
                iVar12 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x2b2;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MONTHS,
                        (int)((int)(DAT_GameCore::instance.skirmishTrailYearReached % 0xc))),
                    iVar12, iVar11, TVar16, BVar17, iVar13, BVar19, iVar14);
                if (DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_GERMAN) {
                    pcVar5 = " n. Chr.";
                } else {
                    pcVar5 = " A.D.";
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    pcVar5, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 700,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x15, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x12, TRUE, 0);
                bVar15 = DAT_GameCore::instance.furthestSkirmishTrailMission == 0x32;
            } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                dVar9 = 0;
                if (0 < DAT_GameCore::instance.furthestWarchestTrailMission) {
                    local_4 = DAT_MissionDefinedData::instance.field36_0xff4[0] + 2;
                    do {
                        if (0x1c < (int)dVar9)
                            break;
                        if (dVar9 == DAT_GameCore::instance.warchestTrailProgress) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_SKIRMISH_TRAIL_ICONS,
                                (int)((int)(piVar8 + 0x5e)),
                                DAT_MissionDefinedData::instance.field33_0xd4c[dVar9][0] + 10 + iVar12,
                                DAT_MissionDefinedData::instance.field33_0xd4c[dVar9][1] + -0x1a + iVar14, 0x10);
                        }
                        if (DAT_GameCore::instance.warchestTrailMonthsTakenOrChicken[dVar9] != -0x4b0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_SKIRMISH_TRAIL_ICONS,
                                (int)((int)(DAT_MissionDefinedData::instance.field35_0xf2c[dVar9] + 0x2d)),
                                DAT_MissionDefinedData::instance.field33_0xd4c[dVar9][0] + iVar12,
                                DAT_MissionDefinedData::instance.field33_0xd4c[dVar9][1] + iVar14, 0x10);
                        }
                        if (dVar9 == DAT_GameCore::instance.warchestTrailProgress) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                (OpenSHC::DE::SHCDE::eGM)(OpenSHC::DE::SHCDE::GM_TREE_CACTII
                                    | OpenSHC::DE::SHCDE::GM_SEA_CHEVRONS),
                                (OpenSHC::DE::SHCDE::eGM)((int)piVar8 + 0x39),
                                DAT_MissionDefinedData::instance.field33_0xd4c[dVar9][0] + 10 + iVar12,
                                DAT_MissionDefinedData::instance.field33_0xd4c[dVar9][1] + -0x1a + iVar14);
                        }
                        iVar11 = DAT_MissionDefinedData::instance.field33_0xd4c[dVar9][1];
                        if (DAT_GameCore::instance.warchestTrailMonthsTakenOrChicken[dVar9] == -0x4b0) {
                            iVar11 = iVar11 + local_4[1];
                            DAT_CurrentlyRenderedSpriteID::instance = (*(int (*)[4])(local_4 + -2))[0];
                            iVar13 = DAT_MissionDefinedData::instance.field33_0xd4c[dVar9][0] + *local_4;
                            iVar6 = local_4[-1];
                            DAT_RenderedUnitOwner::instance = 0;
                            eVar18 = (OpenSHC::DE::SHCDE::eGM)(DAT_CurrentlyRenderedSpriteID::instance);
                        } else {
                            iVar13 = DAT_MissionDefinedData::instance.field33_0xd4c[dVar9][0];
                            iVar6 = DAT_MissionDefinedData::instance.field35_0xf2c[dVar9] + 0x21;
                            eVar18 = (OpenSHC::DE::SHCDE::eGM)(OpenSHC::DE::SHCDE::GM_TREE_CACTII
                                | OpenSHC::DE::SHCDE::GM_SEA_CHEVRONS);
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(eVar18, iVar6, iVar13 + iVar12, iVar11 + iVar14);
                        local_4 = local_4 + 4;
                        dVar9 = dVar9 + 1;
                    } while ((int)dVar9 < DAT_GameCore::instance.furthestWarchestTrailMission);
                }
                if ((DAT_GameCore::instance.warchestTrailProgress
                        == DAT_GameCore::instance.furthestWarchestTrailMission)
                    || (DAT_GameCore::instance.warchestTrailProgress == 0x1d)) {
                    paiVar2
                        = DAT_MissionDefinedData::instance.field33_0xd4c + DAT_GameCore::instance.warchestTrailProgress;
                    paiVar1
                        = DAT_MissionDefinedData::instance.field33_0xd4c + DAT_GameCore::instance.warchestTrailProgress;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_SKIRMISH_TRAIL_ICONS,
                        (int)((int)(piVar8 + 0x5e)), (*paiVar1)[0] + 10 + iVar12,
                        DAT_MissionDefinedData::instance.field33_0xd4c[DAT_GameCore::instance.warchestTrailProgress][1]
                            + -0x1a + iVar14,
                        0x10);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)(OpenSHC::DE::SHCDE::GM_TREE_CACTII
                                                              | OpenSHC::DE::SHCDE::GM_SEA_CHEVRONS),
                        (int)((int)(piVar8 + 0x39)), (*paiVar1)[0] + 10 + iVar12, (*paiVar2)[1] + -0x1a + iVar14);
                }
                dVar9 = DAT_GameCore::instance.furthestWarchestTrailMission;
                if (0x1d < DAT_GameCore::instance.furthestWarchestTrailMission) {
                    dVar9 = 0x1d;
                }
                iVar12 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                    - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[0xcc].originX;
                iVar11 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight
                    - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[0xcc].originY;
                if (dVar9 != DAT_GameCore::instance.warchestTrailProgress) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_SKIRMISH_TRAIL_ICONS,
                        (int)((int)(local_8 + 0x11)), DAT_MissionDefinedData::instance.field33_0xd4c[dVar9][0] + iVar12,
                        DAT_MissionDefinedData::instance.field33_0xd4c[dVar9][1] + iVar11, 0x10);
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    (OpenSHC::DE::SHCDE::eGM)(OpenSHC::DE::SHCDE::GM_TREE_CACTII | OpenSHC::DE::SHCDE::GM_SEA_CHEVRONS),
                    (int)((int)((OpenSHC::DE::SHCDE::eGM)((
                        OpenSHC::DE::SHCDE::eGM)((OpenSHC::DE::SHCDE::eGM)((OpenSHC::DE::SHCDE::eGM)(local_8 + 1)))))),
                    DAT_MissionDefinedData::instance.field33_0xd4c[dVar9][0] + iVar12,
                    DAT_MissionDefinedData::instance.field33_0xd4c[dVar9][1] + iVar11);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameCore::instance.warchestTrailProgress + 0x33,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 10,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x10, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x10, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(".",
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xb,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x10, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x10, TRUE, 0);
                iVar14 = 0;
                BVar19 = TRUE;
                iVar13 = 0x10;
                BVar17 = 0xccfaff;
                TVar16 = OpenSHC::Text::TTA_LEFT;
                iVar11 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x10;
                iVar12 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x10;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TRAIL_NAMES_CRU,
                        (int)((int)(DAT_GameCore::instance.warchestTrailProgress + 0x33))),
                    iVar12, iVar11, TVar16, BVar17, iVar13, BVar19, iVar14);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameCore::instance.warchestTrailStartDatesInMonths[DAT_GameCore::instance.warchestTrailProgress]
                        / 0xc,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x10,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x30, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x12, FALSE, 0);
                if (DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_GERMAN) {
                    pcVar5 = " n. Chr.";
                } else {
                    pcVar5 = " A.D.";
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    pcVar5, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x11,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x30, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x12, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    (int)DAT_GameCore::instance.warchestTrailYearReached / 0xc,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x2b7,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x10, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x11, FALSE, 0);
                iVar14 = 0;
                BVar19 = FALSE;
                iVar13 = 0x11;
                BVar17 = 0xccfaff;
                TVar16 = OpenSHC::Text::TTA_RIGHT;
                iVar11 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x10;
                iVar12 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x2b2;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MONTHS,
                        (int)((int)(DAT_GameCore::instance.warchestTrailYearReached % 0xc))),
                    iVar12, iVar11, TVar16, BVar17, iVar13, BVar19, iVar14);
                if (DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_GERMAN) {
                    pcVar5 = " n. Chr.";
                } else {
                    pcVar5 = " A.D.";
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    pcVar5, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 700,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x15, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x12, TRUE, 0);
                bVar15 = DAT_GameCore::instance.furthestWarchestTrailMission == 0x1e;
            } else {
                if (DAT_GameCore::instance.currentTrailType != OpenSHC::Game::TT_EXTREME) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                }
                iVar13 = 0;
                if (0 < DAT_GameCore::instance.furthestExtremeTrailMission) {
                    local_4 = DAT_MissionDefinedData::instance.field36_0xff4[0] + 2;
                    do {
                        if (0x12 < iVar13)
                            break;
                        if (iVar13 == DAT_GameCore::instance.extremeTrailProgress) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_SKIRMISH_TRAIL_ICONS,
                                (int)((int)(piVar8 + 0x5e)),
                                DAT_MissionDefinedData::instance.field34_0xe3c[iVar13][0] + 10 + iVar12,
                                DAT_MissionDefinedData::instance.field34_0xe3c[iVar13][1] + -0x1a + iVar14, 0x10);
                        }
                        if (DAT_GameCore::instance.extremeTrailMonthsTakenOrChicken[iVar13] != -0x4b0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_SKIRMISH_TRAIL_ICONS,
                                (int)((int)(DAT_MissionDefinedData::instance.field35_0xf2c[iVar13] + 0x2d)),
                                DAT_MissionDefinedData::instance.field34_0xe3c[iVar13][0] + iVar12,
                                DAT_MissionDefinedData::instance.field34_0xe3c[iVar13][1] + iVar14, 0x10);
                        }
                        if (iVar13 == DAT_GameCore::instance.extremeTrailProgress) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                (OpenSHC::DE::SHCDE::eGM)(OpenSHC::DE::SHCDE::GM_TREE_CACTII
                                    | OpenSHC::DE::SHCDE::GM_SEA_CHEVRONS),
                                (OpenSHC::DE::SHCDE::eGM)((int)piVar8 + 0x39),
                                DAT_MissionDefinedData::instance.field34_0xe3c[iVar13][0] + 10 + iVar12,
                                DAT_MissionDefinedData::instance.field34_0xe3c[iVar13][1] + -0x1a + iVar14);
                        }
                        iVar6 = DAT_MissionDefinedData::instance.field34_0xe3c[iVar13][1];
                        if (DAT_GameCore::instance.extremeTrailMonthsTakenOrChicken[iVar13] == -0x4b0) {
                            iVar6 = iVar6 + local_4[1];
                            DAT_CurrentlyRenderedSpriteID::instance = (*(int (*)[4])(local_4 + -2))[0];
                            drawX = DAT_MissionDefinedData::instance.field34_0xe3c[iVar13][0] + iVar12 + *local_4;
                            iVar7 = local_4[-1];
                            DAT_RenderedUnitOwner::instance = 0;
                            eVar18 = (OpenSHC::DE::SHCDE::eGM)(DAT_CurrentlyRenderedSpriteID::instance);
                        } else {
                            drawX = DAT_MissionDefinedData::instance.field34_0xe3c[iVar13][0] + iVar12;
                            iVar7 = DAT_MissionDefinedData::instance.field35_0xf2c[iVar13] + 0x21;
                            eVar18 = (OpenSHC::DE::SHCDE::eGM)(OpenSHC::DE::SHCDE::GM_TREE_CACTII
                                | OpenSHC::DE::SHCDE::GM_SEA_CHEVRONS);
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(eVar18, iVar7, drawX, iVar6 + iVar14);
                        local_4 = local_4 + 4;
                        iVar13 = iVar13 + 1;
                    } while (iVar13 < DAT_GameCore::instance.furthestExtremeTrailMission);
                }
                if ((DAT_GameCore::instance.extremeTrailProgress == DAT_GameCore::instance.furthestExtremeTrailMission)
                    || (DAT_GameCore::instance.extremeTrailProgress == 0x13)) {
                    paiVar2
                        = DAT_MissionDefinedData::instance.field34_0xe3c + DAT_GameCore::instance.extremeTrailProgress;
                    paiVar1
                        = DAT_MissionDefinedData::instance.field34_0xe3c + DAT_GameCore::instance.extremeTrailProgress;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_SKIRMISH_TRAIL_ICONS,
                        (int)((int)(piVar8 + 0x5e)), (int)((int)(iVar11 + -1 + (*paiVar1)[0])),
                        DAT_MissionDefinedData::instance.field34_0xe3c[DAT_GameCore::instance.extremeTrailProgress][1]
                            + -0x1a + iVar14,
                        0x10);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)(OpenSHC::DE::SHCDE::GM_TREE_CACTII
                                                              | OpenSHC::DE::SHCDE::GM_SEA_CHEVRONS),
                        (int)((int)(piVar8 + 0x39)), (int)((int)(iVar11 + -1 + (*paiVar1)[0])),
                        (*paiVar2)[1] + -0x1a + iVar14);
                }
                iVar11 = DAT_GameCore::instance.furthestExtremeTrailMission;
                if (0x13 < DAT_GameCore::instance.furthestExtremeTrailMission) {
                    iVar11 = 0x13;
                }
                iVar13 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                    - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[0xcc].originX;
                iVar12 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight
                    - DAT_TextureRenderCoreObject::instance.gmFileHeaderColorpaletteArray[0xcc].originY;
                if (iVar11 != DAT_GameCore::instance.extremeTrailProgress) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_SKIRMISH_TRAIL_ICONS,
                        (int)((int)(local_8 + 0x11)),
                        DAT_MissionDefinedData::instance.field34_0xe3c[iVar11][0] + iVar13,
                        DAT_MissionDefinedData::instance.field34_0xe3c[iVar11][1] + iVar12, 0x10);
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    (OpenSHC::DE::SHCDE::eGM)(OpenSHC::DE::SHCDE::GM_TREE_CACTII | OpenSHC::DE::SHCDE::GM_SEA_CHEVRONS),
                    (int)((int)((OpenSHC::DE::SHCDE::eGM)((
                        OpenSHC::DE::SHCDE::eGM)((OpenSHC::DE::SHCDE::eGM)((OpenSHC::DE::SHCDE::eGM)(local_8 + 1)))))),
                    DAT_MissionDefinedData::instance.field34_0xe3c[iVar11][0] + iVar13,
                    DAT_MissionDefinedData::instance.field34_0xe3c[iVar11][1] + iVar12);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameCore::instance.extremeTrailProgress + 1,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 10,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x10, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x10, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(".",
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xb,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x10, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x10, TRUE, 0);
                iVar14 = 0;
                BVar19 = TRUE;
                iVar13 = 0x10;
                BVar17 = 0xccfaff;
                TVar16 = OpenSHC::Text::TTA_LEFT;
                iVar11 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x10;
                iVar12 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x10;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_TRAIL_NAMES_CRU, DAT_GameCore::instance.extremeTrailProgress + 0x51),
                    iVar12, iVar11, TVar16, BVar17, iVar13, BVar19, iVar14);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameCore::instance.extremeTrailStartDatesInMonths[DAT_GameCore::instance.extremeTrailProgress]
                        / 0xc,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x10,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x30, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x12, FALSE, 0);
                if (DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_GERMAN) {
                    pcVar5 = " n. Chr.";
                } else {
                    pcVar5 = " A.D.";
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    pcVar5, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x11,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x30, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x12, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    (int)DAT_GameCore::instance.extremeTrailYearReached / 0xc,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x2b7,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x10, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x11, FALSE, 0);
                iVar14 = 0;
                BVar19 = FALSE;
                iVar13 = 0x11;
                BVar17 = 0xccfaff;
                TVar16 = OpenSHC::Text::TTA_RIGHT;
                iVar11 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x10;
                iVar12 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x2b2;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MONTHS,
                        (int)((int)(DAT_GameCore::instance.extremeTrailYearReached % 0xc))),
                    iVar12, iVar11, TVar16, BVar17, iVar13, BVar19, iVar14);
                if (DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_GERMAN) {
                    pcVar5 = " n. Chr.";
                } else {
                    pcVar5 = " A.D.";
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    pcVar5, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 700,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x15, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x12, TRUE, 0);
                bVar15 = DAT_GameCore::instance.furthestExtremeTrailMission == 0x1e;
            }
            if (bVar15) {
                iVar14 = 0;
                BVar19 = FALSE;
                iVar13 = 0x12;
                BVar17 = 0xccfaff;
                TVar16 = OpenSHC::Text::TTA_CENTER;
                iVar11 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x23e;
                iVar12 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xdc;
                /*
                  added by script: "Crusader Trail Completed!"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 6),
                    iVar12, iVar11, TVar16, BVar17, iVar13, BVar19, iVar14);
            }
        }

    }
}
}
