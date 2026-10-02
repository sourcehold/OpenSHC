#include "../RankingGames.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/GameLanguage.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00eb9b60.hpp"
#include "OpenSHC/Globals/DAT_00ed27a0.hpp"
#include "OpenSHC/Globals/DAT_00ed3120.hpp"
#include "OpenSHC/Globals/DAT_00ed3124.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2DataArray.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00eb96d8.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::GameLanguage;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004DFB90
        void RankingGames::MenuView_RankingGames_DoEveryFrame()
        {
            char* text;
            char* _text;
            char* pcVar1;
            int iVar2;
            int* piVar3;
            int iVar4;
            SkMasterDataEntry* pSVar5;
            bool bVar6;
            TextAlignment TVar7;
            int iVar8;
            eGM gmID;
            int iVar9;
            BGR24 BVar10;
            int fontSize;
            int iVar11;
            uint uVar12;
            BOOLEnum BVar13;
            int blendStrength;
            int iVar14;
            int local_b4;
            int local_b0;
            int local_ac;
            int local_a8;
            int local_a4;
            int local_a0;
            int local_9c;
            int local_98;
            int local_94;
            int local_90;
            int local_8c;
            int local_88;
            int local_84;
            uint local_80;
            uint local_7c;
            int local_78;
            int local_74;
            int local_70;
            int local_6c;
            int local_68;
            char local_64[32];
            char local_44[64];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_b4;
            local_78 = DAT_MouseState::instance.screenSpaceX;
            local_74 = DAT_MouseState::instance.screenSpaceY;
            local_80 = 0xffffffff;
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderGfxHelperUnk)(0, 0, 0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
                DAT_PencilRenderCore::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x10,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0xc, 0x300, 0x240);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(0xf0, 0, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x10,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0xc, 0x300, 0x240);
            iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x8a;
            local_a0 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x92;
            local_ac = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x96;
            local_a4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0xa2;
            local_a8 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x8e;
            local_88 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x85;
            local_94 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0xb3;
            local_98 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x84;
            local_7c = 0;
            do {
                uVar12 = local_7c;
                iVar2 = local_88;
                iVar9 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                if ((((local_78 < DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x18)
                         || (DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x2f2 <= local_78))
                        || (local_74 < local_98))
                    || ((local_94 <= local_74
                        || (DAT_00eb9b60::instance <= (int)(DAT_00ed3120::instance + local_7c))))) {
                    if (local_7c == (local_7c & 0xfffffffe)) {
                        iVar8 = 0x2d8;
                    } else {
                        iVar8 = 0x2d9;
                    }
                } else {
                    local_80 = local_7c;
                    if (local_7c == (local_7c & 0xfffffffe)) {
                        iVar8 = 0x2ed;
                    } else {
                        iVar8 = 0x2ee;
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, iVar8,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x18, local_88, 0xe);
                if ((int)(DAT_00ed3120::instance + uVar12) < DAT_00eb9b60::instance) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(DAT_00ed3120::instance + uVar12 + 1, iVar9 + 0x2d, local_a0,
                        OpenSHC::Text::TTA_CENTER, 0xccfaff, 0x11, FALSE, 0);
                    iVar2 = INT_ARRAY_00eb96d8::instance[DAT_00ed3120::instance + uVar12];
                    iVar8 = DAT_SkMasters2DataArray::instance[iVar2].score;
                    iVar14 = iVar9 + 0x4e;
                    if (iVar8 == 0) {
                        pcVar1 = DAT_SkMasters2DataArray::instance[iVar2].mapName;
                        text = MACRO_CALL(OpenSHC::Global_Func::GetStringBasedOnHardcodedMaps)(pcVar1, &local_68);
                        iVar8 = MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(text, 0x12);
                        if (iVar8 < 0xa1) {
                            _text = MACRO_CALL(OpenSHC::Global_Func::GetStringBasedOnHardcodedMaps)(pcVar1, &local_6c);
                            DAT_TextManagerObject::instance.field12_0x30 = 1;
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk,
                                DAT_TextManagerObject::ptr)(_text, iVar14, local_a8, 0xa0, 0xccfaff, 0x12, 0);
                        } else {
                            pcVar1 = MACRO_CALL(OpenSHC::Global_Func::GetStringBasedOnHardcodedMaps)(pcVar1, &local_70);
                            iVar8 = local_a8;
                            DAT_TextManagerObject::instance.field12_0x30 = 1;
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk,
                                DAT_TextManagerObject::ptr)(pcVar1, iVar14, local_a8, 0x91, 0xccfaff, 0x12, 0);
                            MACRO_CALL_MEMBER(
                                OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                                "...", iVar9 + 0xdf, iVar8, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, FALSE, 0);
                        }
                        iVar8 = DAT_SkMasters2DataArray::instance[iVar2].score;
                        if (iVar8 != 0)
                            goto LAB_004dfe50;
                    } else {
                    LAB_004dfe50:
                        iVar11 = local_a8;
                        pcVar1 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TRAIL_NAMES_CRU, iVar8);
                        MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_44, "\"%s\"", pcVar1);
                        iVar8 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth,
                            DAT_TextManagerObject::ptr)(local_44, 0x12);
                        DAT_TextManagerObject::instance.field12_0x30 = 1;
                        if (iVar8 < 0xa1) {
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk,
                                DAT_TextManagerObject::ptr)(local_44, iVar14, iVar11, 0x9b, 0xccfaff, 0x12, 0);
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk,
                                DAT_TextManagerObject::ptr)(local_44, iVar14, iVar11, 0x91, 0xccfaff, 0x12, 0);
                            MACRO_CALL_MEMBER(
                                OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                                "...", iVar9 + 0xdf, iVar11, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, FALSE, 0);
                        }
                    }
                    iVar11 = local_a4;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(DAT_SkMasters2DataArray::instance[iVar2].localTimeDay, iVar14,
                        local_a4, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x13, FALSE, 0);
                    blendStrength = 0;
                    BVar13 = TRUE;
                    fontSize = 0x13;
                    BVar10 = 0xccfaff;
                    TVar7 = OpenSHC::Text::TTA_LEFT;
                    iVar8 = iVar9 + 0x52;
                    iVar14 = iVar11;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MONTHS, (int)((int)(DAT_SkMasters2DataArray::instance[iVar2].localTimeMonth - 1))), iVar8, iVar14, TVar7, BVar10, fontSize, BVar13, blendStrength);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(DAT_SkMasters2DataArray::instance[iVar2].localTimeYear,
                        iVar9 + 0x56, iVar11, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x13, TRUE, 0);
                    iVar8 = DAT_SkMasters2DataArray::instance[iVar2].gameDurationInMinutes % 0x3c;
                    if (iVar8 < 10) {
                        pcVar1 = "%d:0%d";
                    } else {
                        pcVar1 = "%d:%d";
                    }
                    MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_64, (char const*)((int)(pcVar1)),
                        DAT_SkMasters2DataArray::instance[iVar2].gameDurationInMinutes / 0x3c, iVar8);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        local_64, iVar9 + 0xc6, iVar11, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x13, FALSE, 0);
                    iVar14 = iVar9 + 0xf9;
                    iVar8 = 0x25;
                    local_90 = 0x25;
                    local_9c = 0x11;
                    if ((DAT_SkMasters2DataArray::instance[iVar2].activePlayerCount == 8)
                        && (DAT_SkMasters2DataArray::instance[iVar2].array1[8]
                                + DAT_SkMasters2DataArray::instance[iVar2].array1[7]
                                + DAT_SkMasters2DataArray::instance[iVar2].array1[6]
                                + DAT_SkMasters2DataArray::instance[iVar2].array1[5]
                                + DAT_SkMasters2DataArray::instance[iVar2].array1[4]
                                + DAT_SkMasters2DataArray::instance[iVar2].array1[3]
                                + DAT_SkMasters2DataArray::instance[iVar2].array1[2]
                                + DAT_SkMasters2DataArray::instance[iVar2].array1[1]
                            == 0)) {
                        iVar8 = 0x24;
                        local_90 = 0x24;
                        local_9c = 0x10;
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x2cf, iVar14, iVar4);
                    if (DAT_SkMasters2DataArray::instance[iVar2].lordType == 0) {
                        iVar11 = 0x2cd;
                    } else {
                        iVar11 = 0x2ce;
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar11, iVar14, iVar4);
                    if (DAT_SkMasters2DataArray::instance[iVar2].results.finalDateOfDeathInMonths[1] != 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x299, iVar9 + 0x10f, iVar4);
                    }
                    iVar14 = iVar14 + iVar8;
                    local_84 = DAT_SkMasters2DataArray::instance[iVar2].array1[1];
                    local_b0 = 1;
                    if (local_84 == 0) {
                        local_84 = -1;
                    }
                    iVar9 = DAT_SkMasters2DataArray::instance[iVar2].activePlayerCount;
                    iVar8 = 2;
                    if (iVar9 < 2) {
                    LAB_004e017f:
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x2d7, iVar14, local_ac);
                        iVar14 = iVar14 + local_9c;
                    } else {
                        piVar3 = DAT_SkMasters2DataArray::instance[iVar2].array1 + 2;
                        do {
                            if (*piVar3 == local_84)
                                break;
                            iVar8 = iVar8 + 1;
                            piVar3 = piVar3 + 1;
                        } while (iVar8 <= iVar9);
                        if (iVar9 < iVar8)
                            goto LAB_004e017f;
                        local_b4 = 2;
                        if (1 < iVar9) {
                            piVar3 = DAT_SkMasters2DataArray::instance[iVar2].aiArray + 2;
                            do {
                                if (piVar3[-9] == local_84) {
                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                        DAT_TextureRenderCoreObject::ptr)(
                                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, local_b4 + 0x2ce, iVar14, iVar4);
                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                                        (int)((int)(*piVar3 + 700)), iVar14, iVar4);
                                    if (piVar3[0x1d2] != 0) {
                                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                            DAT_TextureRenderCoreObject::ptr)(
                                            OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x299, iVar14 + 0x16, iVar4);
                                    }
                                    iVar14 = iVar14 + local_90;
                                    local_b0 = local_b0 + 1;
                                }
                                local_b4 = local_b4 + 1;
                                piVar3 = piVar3 + 1;
                            } while (local_b4 <= DAT_SkMasters2DataArray::instance[iVar2].activePlayerCount);
                        }
                        if (local_b0 < DAT_SkMasters2DataArray::instance[iVar2].activePlayerCount)
                            goto LAB_004e017f;
                    }
                    local_8c = 1;
                    do {
                        if (local_8c != local_84) {
                            iVar9 = DAT_SkMasters2DataArray::instance[iVar2].activePlayerCount;
                            iVar8 = 2;
                            if (1 < iVar9) {
                                piVar3 = DAT_SkMasters2DataArray::instance[iVar2].array1 + 2;
                                do {
                                    if (*piVar3 == local_8c)
                                        break;
                                    iVar8 = iVar8 + 1;
                                    piVar3 = piVar3 + 1;
                                } while (iVar8 <= iVar9);
                                if (iVar8 <= iVar9) {
                                    local_b4 = 2;
                                    if (1 < iVar9) {
                                        piVar3 = DAT_SkMasters2DataArray::instance[iVar2].aiArray + 2;
                                        do {
                                            if (piVar3[-9] == local_8c) {
                                                MACRO_CALL_MEMBER(
                                                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                    DAT_TextureRenderCoreObject::ptr)(
                                                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, local_b4 + 0x2ce, iVar14,
                                                    iVar4);
                                                MACRO_CALL_MEMBER(
                                                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                    DAT_TextureRenderCoreObject::ptr)(
                                                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                                                    (int)((int)(*piVar3 + 700)), iVar14, iVar4);
                                                if (piVar3[0x1d2] != 0) {
                                                    MACRO_CALL_MEMBER(
                                                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                        DAT_TextureRenderCoreObject::ptr)(
                                                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x299, iVar14 + 0x16,
                                                        iVar4);
                                                }
                                                iVar14 = iVar14 + local_90;
                                                local_b0 = local_b0 + 1;
                                            }
                                            local_b4 = local_b4 + 1;
                                            piVar3 = piVar3 + 1;
                                        } while (
                                            local_b4 <= DAT_SkMasters2DataArray::instance[iVar2].activePlayerCount);
                                    }
                                    if (DAT_SkMasters2DataArray::instance[iVar2].activePlayerCount <= local_b0)
                                        break;
                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                        DAT_TextureRenderCoreObject::ptr)(
                                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x2d7, iVar14, local_ac);
                                    iVar14 = iVar14 + local_9c;
                                }
                            }
                        }
                        local_8c = local_8c + 1;
                    } while (local_8c < 5);
                    if ((local_b0 < DAT_SkMasters2DataArray::instance[iVar2].activePlayerCount)
                        && (local_b4 = 2, 1 < DAT_SkMasters2DataArray::instance[iVar2].activePlayerCount)) {
                        piVar3 = DAT_SkMasters2DataArray::instance[iVar2].aiArray + 2;
                        do {
                            if (piVar3[-9] == 0) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, local_b4 + 0x2ce, iVar14, iVar4);
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                                    (int)((int)(*piVar3 + 700)), iVar14, iVar4);
                                if (piVar3[0x1d2] != 0) {
                                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                        DAT_TextureRenderCoreObject::ptr)(
                                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x299, iVar14 + 0x16, iVar4);
                                }
                                iVar14 = iVar14 + local_90;
                                local_b0 = local_b0 + 1;
                                if (DAT_SkMasters2DataArray::instance[iVar2].activePlayerCount <= local_b0)
                                    break;
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x2d7, iVar14, local_ac);
                                iVar14 = iVar14 + local_9c;
                            }
                            local_b4 = local_b4 + 1;
                            piVar3 = piVar3 + 1;
                        } while (local_b4 <= DAT_SkMasters2DataArray::instance[iVar2].activePlayerCount);
                    }
                    iVar9 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                    if (DAT_SkMasters2DataArray::instance[iVar2].aliveArray[1] == 0) {
                        iVar8 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x293;
                        iVar11 = 0x299;
                        gmID = OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2;
                        iVar14 = local_a0;
                    } else {
                        iVar8 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x291;
                        iVar11 = 0x8b;
                        gmID = OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3;
                        iVar14 = local_ac;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(gmID, iVar11, iVar8, iVar14);
                    iVar8 = local_a0;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(DAT_SkMasters2DataArray::instance[iVar2].skMasterScore,
                        iVar9 + 0x2a7, local_a0, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x11, FALSE, 0);
                    uVar12 = local_7c;
                    iVar2 = local_88;
                    local_a0 = iVar8;
                }
                local_94 = local_94 + 0x2f;
                local_98 = local_98 + 0x2f;
                local_a0 = local_a0 + 0x2f;
                local_a4 = local_a4 + 0x2f;
                local_a8 = local_a8 + 0x2f;
                local_ac = local_ac + 0x2f;
                local_88 = iVar2 + 0x2f;
                iVar4 = iVar4 + 0x2f;
                local_7c = uVar12 + 1;
            } while ((int)local_7c < 8);
            if (local_80 != 0xffffffff) {
                iVar14 = 0;
                iVar8 = 0x12;
                uVar12 = 0xccfaff;
                iVar9 = 300;
                iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x20a;
                iVar2 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0x1c2;
                /*
                  added by script: "Left Click a game for more information or Right Click to   Delete"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_MASTERS, 5), iVar2, iVar4, iVar9, uVar12, iVar8, iVar14);
                pSVar5 = DAT_SkMasters2DataArray::instance
                    + INT_ARRAY_00eb96d8::instance[DAT_00ed3120::instance + local_80];
                iVar4 = pSVar5->score;
                if (iVar4 != 0) {
                    if (iVar4 < 0x51) {
                        if (iVar4 < 0x33) {
                            MACRO_CALL_MEMBER(
                                OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)("1 / ",
                                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xaf,
                                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x20a, OpenSHC::Text::TTA_LEFT,
                                0xccfaff, 0x12, FALSE, 0);
                            iVar4 = pSVar5->score;
                            iVar2 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x20a;
                            iVar9 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xaf;
                        } else {
                            MACRO_CALL_MEMBER(
                                OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)("2 / ",
                                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xaf,
                                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x20a, OpenSHC::Text::TTA_LEFT,
                                0xccfaff, 0x12, FALSE, 0);
                            iVar2 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x20a;
                            iVar9 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xaf;
                            iVar4 = pSVar5->score + -0x32;
                        }
                    } else {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)("3 / ",
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xaf,
                            DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x20a, OpenSHC::Text::TTA_LEFT,
                            0xccfaff, 0x12, FALSE, 0);
                        iVar2 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x20a;
                        iVar9 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xaf;
                        iVar4 = pSVar5->score + -0x50;
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        iVar4, iVar9, iVar2, OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, TRUE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        ".", DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xb0,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x20a, OpenSHC::Text::TTA_LEFT,
                        0xccfaff, 0x12, TRUE, 0);
                    pcVar1 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TRAIL_NAMES_CRU, pSVar5->score);
                    MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_44, "\"%s\"", pcVar1);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        local_44, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xe1,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x20a, OpenSHC::Text::TTA_LEFT,
                        0xccfaff, 0x12, FALSE, 0);
                }
            }
            if (0 < DAT_00eb9b60::instance) {
                iVar8 = 0;
                BVar13 = FALSE;
                iVar9 = 0x11;
                BVar10 = 0xccfaff;
                TVar7 = OpenSHC::Text::TTA_LEFT;
                iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x226;
                iVar2 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xaf;
                /*
                  added by script: "Games"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKMASTERS, 0xb), iVar2, iVar4, TVar7, BVar10, iVar9, BVar13, iVar8);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(":",
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xb0,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x226, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x11, TRUE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_00eb9b60::instance, DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xb6,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x226, OpenSHC::Text::TTA_LEFT, 0xccfaff,
                    0x11, TRUE, 0);
            }
            if (DAT_00eb9b60::instance == 0) {
                iVar8 = 0;
                BVar13 = FALSE;
                iVar9 = 0x11;
                BVar10 = 0xccfaff;
                TVar7 = OpenSHC::Text::TTA_LEFT;
                iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 0x226;
                iVar2 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xaf;
                /*
                  added by script: "No Games Found"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKMASTERS, 10), iVar2, iVar4, TVar7, BVar10, iVar9, BVar13, iVar8);
            }
            if (DAT_00ed27a0::instance != 0) {
                if (DAT_00ed27a0::instance == 0x1e) {
                    iVar8 = 0;
                    BVar13 = FALSE;
                    iVar9 = 0x11;
                    BVar10 = 0xccfaff;
                    iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100;
                    TVar7 = OpenSHC::Text::TTA_LEFT;
                    iVar2 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xfa;
                    bVar6 = DAT_00ed3124::instance == 1;
                    if (bVar6) {
                        /*
                          added by script: "Turn off"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKMASTERS, 0xc), iVar2, iVar4, TVar7, BVar10, iVar9, BVar13, iVar8);
                        iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100;
                        iVar2 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xfe;
                    }
                    iVar8 = 0;
                    BVar13 = (BOOLEnum)bVar6;
                    iVar9 = 0x11;
                    BVar10 = 0xccfaff;
                    TVar7 = OpenSHC::Text::TTA_LEFT;
                    /*
                      added by script: "Crusader Trail Only"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKMASTERS, 8), iVar2, iVar4, TVar7, BVar10, iVar9, BVar13, iVar8);
                }
                if (DAT_00ed27a0::instance == 0x1f) {
                    iVar4 = 0;
                    BVar13 = FALSE;
                    if (DAT_00ed3124::instance == 2) {
                        iVar9 = 0x11;
                        BVar10 = 0xccfaff;
                        iVar2 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100;
                        TVar7 = OpenSHC::Text::TTA_LEFT;
                        if (DAT_TextManagerObject::instance.gameLanguage == OpenSHC::Text::GL_FRENCH) {
                            iVar8 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 200;
                            /*
                              added by script: "Turn off"
                             */
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKMASTERS, 0xc), iVar8, iVar2, TVar7, BVar10, iVar9, BVar13, iVar4);
                            iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xcc;
                        } else {
                            iVar8 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xfa;
                            /*
                              added by script: "Turn off"
                             */
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKMASTERS, 0xc), iVar8, iVar2, TVar7, BVar10, iVar9, BVar13, iVar4);
                            iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xfe;
                        }
                        BVar13 = TRUE;
                    } else {
                        iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xfa;
                    }
                    iVar8 = 0;
                    iVar9 = 0x11;
                    BVar10 = 0xccfaff;
                    TVar7 = OpenSHC::Text::TTA_LEFT;
                    iVar2 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100;
                    /*
                      added by script: "Custom Games Only"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKMASTERS, 9), iVar4, iVar2, TVar7, BVar10, iVar9, BVar13, iVar8);
                }
                if (DAT_00ed27a0::instance < 0x1e) {
                    iVar8 = 0;
                    BVar13 = FALSE;
                    iVar9 = 0x11;
                    BVar10 = 0xccfaff;
                    TVar7 = OpenSHC::Text::TTA_LEFT;
                    iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100;
                    iVar2 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xfa;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKMASTERS, 1), iVar2, iVar4, TVar7, BVar10, iVar9, BVar13, iVar8);
                    iVar4 = 2;
                    if (DAT_00ed27a0::instance == 0x15) {
                        iVar4 = 3;
                    } else if (DAT_00ed27a0::instance == 0x16) {
                        iVar4 = 5;
                    } else if (DAT_00ed27a0::instance == 0x17) {
                        iVar4 = 4;
                    }
                    iVar14 = 0;
                    BVar13 = TRUE;
                    iVar8 = 0x11;
                    BVar10 = 0xccfaff;
                    TVar7 = OpenSHC::Text::TTA_LEFT;
                    iVar2 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100;
                    iVar9 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xff;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKMASTERS, iVar4), iVar9, iVar2, TVar7, BVar10, iVar8, BVar13, iVar14);
                }
                if (DAT_00ed27a0::instance != 0)
                    goto LAB_004e0a24;
            }
            iVar8 = 0;
            BVar13 = FALSE;
            iVar9 = 0x11;
            BVar10 = 0xccfaff;
            TVar7 = OpenSHC::Text::TTA_LEFT;
            iVar4 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100;
            iVar2 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xfa;
            /*
              added by script: "Sorted by"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKMASTERS, 0), iVar2, iVar4, TVar7, BVar10, iVar9, BVar13, iVar8);
            iVar4 = 2;
            if (DAT_MissionDefinedData::instance.sortColumn == 2) {
                iVar4 = 3;
            } else if (DAT_MissionDefinedData::instance.sortColumn == 3) {
                iVar4 = 5;
            } else if (DAT_MissionDefinedData::instance.sortColumn == 4) {
                iVar4 = 4;
            }
            iVar14 = 0;
            BVar13 = TRUE;
            iVar8 = 0x11;
            BVar10 = 0xccfaff;
            TVar7 = OpenSHC::Text::TTA_LEFT;
            iVar2 = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100;
            iVar9 = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 0xff;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKMASTERS, iVar4), iVar9, iVar2, TVar7, BVar10, iVar8, BVar13, iVar14);
        LAB_004e0a24:
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            ;
        }

    }
}
}
