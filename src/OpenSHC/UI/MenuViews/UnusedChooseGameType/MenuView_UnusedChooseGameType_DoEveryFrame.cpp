#include "../UnusedChooseGameType.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
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

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00430150
        void UnusedChooseGameType::MenuView_UnusedChooseGameType_DoEveryFrame()
        {
            int iVar1;
            char* textAddress;
            int iVar2;
            int iVar3;
            int _mapSize;
            TextAlignment alignment;
            BGR24 color;
            int iVar4;
            BOOLEnum keepOffsetX;
            int iVar5;
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
            iVar4 = 0x10;
            color = 0xc2f0eb;
            alignment = OpenSHC::Text::TTA_CENTER;
            iVar1 = DAT_MenuHandlerState::instance.y + 0x3b;
            iVar3 = DAT_MenuHandlerState::instance.x + 400;
            /*
              added by script: "Select Game Type"
             */
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0x1b),
                iVar3, iVar1, alignment, color, iVar4, keepOffsetX, iVar6);
            iVar3 = DAT_MenuHandlerState::instance.y;
            iVar1 = DAT_MenuHandlerState::instance.x;
            local_1c = DAT_MenuHandlerState::instance.y + 0x122;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            _mapSize = DAT_TileMapState::instance.mapSize;
            if (DAT_TileMapState::instance.mapSize == 0) {
                _mapSize = 400;
            }
            DAT_MinimapViewState::instance.field0_0x0 = 1;
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_18, "%dx%d", _mapSize, _mapSize);
            switch (_mapSize) {
            case 100:
                iVar3 = iVar3 + 0xf0;
                iVar4 = iVar1 + 0x226;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    iVar4, iVar3, _mapSize, _mapSize);
                local_20 = 100;
                break;
            default:
                iVar6 = 200;
                goto LAB_004302d7;
            case 0xa0:
                iVar3 = iVar3 + 0xd2;
                iVar4 = iVar1 + 0x208;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    iVar4, iVar3, _mapSize, _mapSize);
                local_20 = 0xa0;
                break;
            case 200:
                iVar6 = _mapSize;
            LAB_004302d7:
                iVar3 = iVar3 + 0xbe;
                iVar4 = iVar1 + 500;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    iVar4, iVar3, iVar6, iVar6);
                local_20 = 200;
                break;
            case 300:
                iVar3 = iVar3 + 0xd7;
                iVar4 = iVar1 + 0x20d;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    iVar4, iVar3, 0x96, 0x96);
                local_20 = 0x96;
            }
            iVar6 = local_1c;
            if (_mapSize == 160) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                    DAT_PencilRenderCore::ptr)(iVar1 + 0x20a, local_1c + -0x4f, iVar1 + 0x2a6, local_1c + 0x4d,
                    (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar5 = iVar6 + 0x4e;
                iVar2 = iVar1 + 0x2a7;
                iVar6 = iVar6 + -0x50;
                iVar1 = iVar1 + 0x209;
            } else if (_mapSize == 200) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                    DAT_PencilRenderCore::ptr)(iVar1 + 0x1f6, local_1c + -99, iVar1 + 699, local_1c + 99,
                    (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar5 = iVar6 + 100;
                iVar2 = iVar1 + 700;
                iVar6 = iVar6 + -100;
                iVar1 = iVar1 + 0x1f5;
            } else if (_mapSize == 300) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                    DAT_PencilRenderCore::ptr)(iVar1 + 0x20d, local_1c + -0x4b, iVar1 + 0x2a1, local_1c + 0x4a,
                    (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar5 = iVar6 + 0x4b;
                iVar2 = iVar1 + 0x2a2;
                iVar6 = iVar6 + -0x4c;
                iVar1 = iVar1 + 0x20c;
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                    DAT_PencilRenderCore::ptr)(iVar1 + 500, local_1c + -100, iVar1 + 699, local_1c + 100,
                    (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar5 = iVar6 + 0x65;
                iVar2 = iVar1 + 700;
                iVar6 = iVar6 + -0x65;
                iVar1 = iVar1 + 499;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                iVar1, iVar6, iVar2, iVar5, (ushort)((int)(COL_BLACK::instance.shortValue)));
            iVar4 = iVar4 + local_20;
            iVar1 = iVar3 + -0xf;
            iVar6 = iVar4;
            iVar5 = iVar3;
            iVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                local_18, 0x13);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                (iVar4 - iVar2) + -0xf, iVar1, iVar6, iVar5);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                local_18, iVar4 + -5, iVar3 + -0xb, OpenSHC::Text::TTA_RIGHT, 0xc2f0eb, 0, 0x13, FALSE, 0);
            ;
            return;
        }

    }
}
}
