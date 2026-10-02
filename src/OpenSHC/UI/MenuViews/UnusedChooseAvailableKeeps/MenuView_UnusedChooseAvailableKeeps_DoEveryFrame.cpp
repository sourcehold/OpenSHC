#include "../UnusedChooseAvailableKeeps.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;
        using OpenSHC::Rendering::Colors::BGR24;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042FAC0
        void UnusedChooseAvailableKeeps::MenuView_UnusedChooseAvailableKeeps_DoEveryFrame()
        {
            int iVar1;
            char* textAddress;
            int iVar2;
            int iVar3;
            int iVar4;
            TextAlignment alignment;
            BGR24 color;
            int iVar5;
            BOOLEnum keepOffsetX;
            int iVar6;
            int local_20;
            int local_1c;
            char local_18[20];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_20;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(0,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                    / 2);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderBanner, DAT_PencilRenderCore::ptr)(
                DAT_MenuHandlerState::instance.x + 100, DAT_MenuHandlerState::instance.y + 0x1e, 600, 0x32);
            iVar6 = 0;
            keepOffsetX = FALSE;
            iVar5 = 0x10;
            color = 0xc2f0eb;
            alignment = OpenSHC::Text::TTA_CENTER;
            iVar1 = DAT_MenuHandlerState::instance.y + 0x3b;
            iVar3 = DAT_MenuHandlerState::instance.x + 400;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0x15), iVar3, iVar1, alignment, color, iVar5, keepOffsetX, iVar6);
            iVar3 = DAT_MenuHandlerState::instance.y;
            iVar1 = DAT_MenuHandlerState::instance.x;
            local_1c = DAT_MenuHandlerState::instance.y + 0x122;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            iVar5 = DAT_TileMapState::instance.mapSize;
            if (DAT_TileMapState::instance.mapSize == 0) {
                iVar5 = 400;
            }
            DAT_MinimapViewState::instance.field0_0x0 = 1;
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_18, "%dx%d", iVar5, iVar5);
            switch (iVar5) {
            case 100:
                iVar3 = iVar3 + 0xf0;
                iVar6 = iVar1 + 0x226;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    iVar6, iVar3, iVar5, iVar5);
                local_20 = 100;
                break;
            default:
                iVar4 = 200;
                goto LAB_0042fc47;
            case 0xa0:
                iVar3 = iVar3 + 0xd2;
                iVar6 = iVar1 + 0x208;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    iVar6, iVar3, iVar5, iVar5);
                local_20 = 0xa0;
                break;
            case 200:
                iVar4 = iVar5;
            LAB_0042fc47:
                iVar3 = iVar3 + 0xbe;
                iVar6 = iVar1 + 500;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    iVar6, iVar3, iVar4, iVar4);
                local_20 = 200;
                break;
            case 300:
                iVar3 = iVar3 + 0xd7;
                iVar6 = iVar1 + 0x20d;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    iVar6, iVar3, 0x96, 0x96);
                local_20 = 0x96;
            }
            iVar4 = local_1c;
            if (iVar5 == 0xa0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                    DAT_PencilRenderCore::ptr)(iVar1 + 0x20a, local_1c + -0x4f, iVar1 + 0x2a6, local_1c + 0x4d,
                    (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar5 = iVar4 + 0x4e;
                iVar2 = iVar1 + 0x2a7;
                iVar4 = iVar4 + -0x50;
                iVar1 = iVar1 + 0x209;
            } else if (iVar5 == 200) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                    DAT_PencilRenderCore::ptr)(iVar1 + 0x1f6, local_1c + -99, iVar1 + 699, local_1c + 99,
                    (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar5 = iVar4 + 100;
                iVar2 = iVar1 + 700;
                iVar4 = iVar4 + -100;
                iVar1 = iVar1 + 0x1f5;
            } else if (iVar5 == 300) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                    DAT_PencilRenderCore::ptr)(iVar1 + 0x20d, local_1c + -0x4b, iVar1 + 0x2a1, local_1c + 0x4a,
                    (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar5 = iVar4 + 0x4b;
                iVar2 = iVar1 + 0x2a2;
                iVar4 = iVar4 + -0x4c;
                iVar1 = iVar1 + 0x20c;
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                    DAT_PencilRenderCore::ptr)(iVar1 + 500, local_1c + -100, iVar1 + 699, local_1c + 100,
                    (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar5 = iVar4 + 0x65;
                iVar2 = iVar1 + 700;
                iVar4 = iVar4 + -0x65;
                iVar1 = iVar1 + 499;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                iVar1, iVar4, iVar2, iVar5, (ushort)((int)(COL_BLACK::instance.shortValue)));
            iVar6 = iVar6 + local_20;
            iVar1 = iVar3 + -0xf;
            iVar5 = iVar6;
            iVar4 = iVar3;
            iVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                local_18, 0x13);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                (iVar6 - iVar2) + -0xf, iVar1, iVar5, iVar4);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                local_18, iVar6 + -5, iVar3 + -0xb, OpenSHC::Text::TTA_RIGHT, 0xc2f0eb, 0, 0x13, FALSE, 0);
            ;
            return;
        }

    }
}
}
