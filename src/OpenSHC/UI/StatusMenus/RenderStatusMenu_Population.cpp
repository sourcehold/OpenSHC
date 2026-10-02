#include "../StatusMenus.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;
    using OpenSHC::Rendering::Colors::BGR24;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0043F6A0
    void StatusMenus::RenderStatusMenu_Population()
    {
        uint uVar1;
        int iVar2;
        int iVar3;
        short sVar4;
        int iVar5;
        char* pcVar6;
        short (*pasVar7)[300];
        int iVar8;
        int iVar9;
        TextAlignment TVar10;
        BGR24 BVar11;
        int iVar12;
        BOOLEnum BVar13;
        int iVar14;
        int blendStrength;
        int local_10;
        int local_c;
        iVar8 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        iVar3 = DAT_MenuHandlerState::instance.y;
        iVar2 = DAT_MenuHandlerState::instance.x;
        local_c = DAT_GameState::instance.mapAndTime.populationIndex;
        if (300 < DAT_GameState::instance.mapAndTime.populationIndex) {
            local_c = 300;
        }
        MACRO_CALL_MEMBER(
            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderLoadedGfx, DAT_TextureRenderCoreObject::ptr)(
            1, DAT_MenuHandlerState::instance.x + 0xe, DAT_MenuHandlerState::instance.y + 0x1e9);
        iVar14 = 0;
        BVar13 = FALSE;
        iVar12 = 0x11;
        BVar11 = 0;
        TVar10 = OpenSHC::Text::TTA_LEFT;
        iVar5 = DAT_MenuHandlerState::instance.y + 0x1d3;
        iVar9 = DAT_MenuHandlerState::instance.x + 0x19;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        /*
          added by script: "Population"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 3), iVar9, iVar5, TVar10, BVar11, iVar12, BVar13, iVar14);
        iVar5 = iVar3 + 0x23d;
        iVar9 = iVar2 + 0x1ed;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            iVar2 + 0xbc, iVar5, iVar9, iVar5, (ushort)((int)(COL_BLACK::instance.shortValue)));
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            iVar2 + 0xbc, iVar3 + 0x23e, iVar9, iVar3 + 0x23e, (ushort)((int)(COL_BLACK::instance.shortValue)));
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            iVar2 + 0xbc, iVar3 + 0x23f, iVar9, iVar3 + 0x23f, (ushort)((int)(COL_BLACK::instance.shortValue)));
        iVar12 = iVar3 + 0x1f1;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            iVar2 + 0xbe, iVar12, iVar2 + 0xbe, iVar5, (ushort)((int)(COL_BLACK::instance.shortValue)));
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            iVar2 + 0xbd, iVar12, iVar2 + 0xbd, iVar5, (ushort)((int)(COL_BLACK::instance.shortValue)));
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            iVar2 + 0xbc, iVar12, iVar2 + 0xbc, iVar5, (ushort)((int)(COL_BLACK::instance.shortValue)));
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            iVar2 + 0x1eb, iVar12, iVar2 + 0x1eb, iVar5, (ushort)((int)(COL_BLACK::instance.shortValue)));
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            iVar2 + 0x1ec, iVar12, iVar2 + 0x1ec, iVar5, (ushort)((int)(COL_BLACK::instance.shortValue)));
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
            iVar9, iVar12, iVar9, iVar5, (ushort)((int)(COL_BLACK::instance.shortValue)));
        blendStrength = 0;
        BVar13 = FALSE;
        iVar14 = 0x13;
        BVar11 = 0;
        TVar10 = OpenSHC::Text::TTA_CENTER;
        iVar9 = iVar3 + 0x24d;
        iVar12 = iVar2 + 0x154;
        /*
          added by script: "Years"
         */
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORT_BUTTONS, 0xd), iVar12, iVar9, TVar10, BVar11, iVar14, BVar13, blendStrength);
        sVar4 = 0;
        if (0 < local_c) {
            pasVar7 = DAT_GameState::instance.mapAndTime.playerPopulationStatistics + iVar8;
            iVar9 = local_c;
            do {
                if (sVar4 < (*pasVar7)[0]) {
                    sVar4 = (*pasVar7)[0];
                }
                pasVar7 = (short (*)[300])(*pasVar7 + 1);
                iVar9 = iVar9 + -1;
            } while (iVar9 != 0);
            if (0x32 < sVar4) {
                if (sVar4 < 0x65) {
                    local_10 = 2;
                } else if (sVar4 < 0xc9) {
                    local_10 = 4;
                } else if (sVar4 < 0x191) {
                    local_10 = 8;
                } else {
                    if (800 < sVar4) {
                        iVar9 = iVar2 + 0x9c;
                        local_10 = 0x20;
                        iVar12 = 0x640;
                        goto LAB_0043f8f7;
                    }
                    local_10 = 0x10;
                }
                iVar12 = local_10 * 0x32;
                iVar9 = iVar2 + 0xa4;
                goto LAB_0043f8f7;
            }
        }
        iVar9 = iVar2 + 0xac;
        local_10 = 1;
        iVar12 = 0x32;
    LAB_0043f8f7:
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            iVar12, iVar9, iVar3 + 0x1ec, OpenSHC::Text::TTA_LEFT, 0, 0x13, FALSE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            0, iVar2 + 0xb4, iVar3 + 0x237, OpenSHC::Text::TTA_LEFT, 0, 0x13, FALSE, 0);
        iVar12 = 0;
        iVar9 = 0;
        do {
            uVar1 = (DAT_GameState::instance.mapAndTime.populationIndex + -300) / 0xc;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                (((int)uVar1 < 0) - 1 & uVar1) + iVar12, iVar9 / 0x19 + 0xbe + iVar2, iVar3 + 0x241,
                OpenSHC::Text::TTA_LEFT, 0, 0x13, FALSE, 0);
            iVar9 = iVar9 + 0x5c3;
            iVar12 = iVar12 + 5;
        } while (iVar9 < 0x1cd0);
        if ((local_c < 0x12d) && (iVar9 = 0, 0 < local_c)) {
            pasVar7 = DAT_GameState::instance.mapAndTime.playerPopulationStatistics + iVar8;
            do {
                if ((0 < (*pasVar7)[0]) && (iVar8 = ((*pasVar7)[0] * 0x4b) / (local_10 * 0x32), 0 < iVar8)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRect,
                        DAT_TextureRenderCoreObject::ptr)(0, 0, DAT_WindowAndDirectDraw::instance.resolutionX, iVar5);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                        DAT_TextureRenderCoreObject::ptr)(0, iVar2 + 0xbf + iVar9, (iVar3 - iVar8) + 0x23d);
                }
                iVar9 = iVar9 + 1;
                pasVar7 = (short (*)[300])(*pasVar7 + 1);
            } while (iVar9 < local_c);
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRectToGameResolution,
            DAT_TextureRenderCoreObject::ptr)();
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
