#include "../UnusedCreateSiege.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_BottomLeftTextDisplayState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00b95f68.hpp"
#include "OpenSHC/Globals/INT_00b960e4.hpp"
#include "OpenSHC/Globals/INT_00b960ec.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Map::MapType2;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

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
        // FUNCTION: STRONGHOLDCRUSADER 0x004306D0
        void UnusedCreateSiege::MenuView_UnusedCreateSiege_DoEveryFrame()
        {
            int iVar1;
            char* pcVar2;
            int iVar3;
            int iVar4;
            int iVar5;
            TextAlignment TVar6;
            uint color1;
            BGR24 BVar7;
            uint color2;
            int iVar8;
            BOOLEnum BVar9;
            int iVar10;
            int local_20;
            int local_1c;
            char local_18[20];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_20;
            DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 = OpenSHC::Map::MT_SIEGE;
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
                DAT_MenuHandlerState::instance.x + 0x30, DAT_MenuHandlerState::instance.y + 6, 0x2c0, 0x32);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            if (DAT_BottomLeftTextDisplayState::instance.currentlyDisplayedTextIsDisplayedUnk == 0) {
                iVar10 = 0;
                iVar8 = 0x11;
                color2 = 0;
                color1 = 0xccfaff;
                iVar5 = 0x1c8;
                iVar1 = DAT_MenuHandlerState::instance.y + 0x76;
                iVar4 = DAT_MenuHandlerState::instance.x + 0x12;
                DAT_TextManagerObject::instance.field9_0x24 = 1;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0x25),
                    iVar4, iVar1, iVar5, color1, color2, iVar8, iVar10);
            }
            iVar8 = 0;
            BVar9 = FALSE;
            iVar5 = 0x11;
            BVar7 = 0xc2f0eb;
            TVar6 = OpenSHC::Text::TTA_LEFT;
            iVar1 = DAT_MenuHandlerState::instance.y + 0x23;
            iVar4 = DAT_MenuHandlerState::instance.x + 0x8c;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0x22),
                iVar4, iVar1, TVar6, BVar7, iVar5, BVar9, iVar8);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(" - ",
                DAT_MenuHandlerState::instance.x + 0x8c, DAT_MenuHandlerState::instance.y + 0x23,
                OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x11, TRUE, 0);
            if (INT_00b960e4::instance == 0) {
                iVar8 = 0;
                BVar9 = TRUE;
                iVar5 = 0x11;
                BVar7 = 0xc2f0eb;
                TVar6 = OpenSHC::Text::TTA_LEFT;
                iVar1 = DAT_MenuHandlerState::instance.y + 0x23;
                iVar4 = DAT_MenuHandlerState::instance.x + 0x8c;
                pcVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0x18);
            } else {
                iVar1 = DAT_MenuHandlerState::instance.y + 0x23;
                iVar4 = DAT_MenuHandlerState::instance.x + 0x8c;
                pcVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(2);
                iVar8 = 0;
                BVar9 = TRUE;
                iVar5 = 0x11;
                BVar7 = 0xc2f0eb;
                TVar6 = OpenSHC::Text::TTA_LEFT;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                pcVar2, iVar4, iVar1, TVar6, BVar7, iVar5, BVar9, iVar8);
            iVar4 = DAT_MenuHandlerState::instance.y;
            iVar1 = DAT_MenuHandlerState::instance.x;
            if (DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE)
                goto LAB_00430ac9;
            local_1c = DAT_MenuHandlerState::instance.y + 0xf0;
            iVar5 = DAT_TileMapState::instance.mapSize;
            if (DAT_TileMapState::instance.mapSize == 0) {
                iVar5 = 400;
            }
            DAT_MinimapViewState::instance.field0_0x0 = 1;
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_18, "%dx%d", iVar5, iVar5);
            switch (iVar5) {
            case 100:
                iVar4 = iVar4 + 0xbe;
                iVar8 = iVar1 + 0x226;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    iVar8, iVar4, iVar5, iVar5);
                local_20 = 100;
                break;
            default:
                iVar10 = 200;
                goto LAB_0043094b;
            case 0xa0:
                iVar4 = iVar4 + 0xa0;
                iVar8 = iVar1 + 0x208;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    iVar8, iVar4, iVar5, iVar5);
                local_20 = 0xa0;
                break;
            case 200:
                iVar10 = iVar5;
            LAB_0043094b:
                iVar4 = iVar4 + 0x8c;
                iVar8 = iVar1 + 500;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    iVar8, iVar4, iVar10, iVar10);
                local_20 = 200;
                break;
            case 300:
                iVar4 = iVar4 + 0xa5;
                iVar8 = iVar1 + 0x20d;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    iVar8, iVar4, 0x96, 0x96);
                local_20 = 0x96;
            }
            iVar10 = local_1c;
            if (iVar5 == 0xa0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                    DAT_PencilRenderCore::ptr)(iVar1 + 0x20a, local_1c + -0x4f, iVar1 + 0x2a6, local_1c + 0x4d,
                    (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar5 = iVar10 + 0x4e;
                iVar3 = iVar1 + 0x2a7;
                iVar10 = iVar10 + -0x50;
                iVar1 = iVar1 + 0x209;
            } else if (iVar5 == 200) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                    DAT_PencilRenderCore::ptr)(iVar1 + 0x1f6, local_1c + -99, iVar1 + 699, local_1c + 99,
                    (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar5 = iVar10 + 100;
                iVar3 = iVar1 + 700;
                iVar10 = iVar10 + -100;
                iVar1 = iVar1 + 0x1f5;
            } else if (iVar5 == 300) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                    DAT_PencilRenderCore::ptr)(iVar1 + 0x20d, local_1c + -0x4b, iVar1 + 0x2a1, local_1c + 0x4a,
                    (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar5 = iVar10 + 0x4b;
                iVar3 = iVar1 + 0x2a2;
                iVar10 = iVar10 + -0x4c;
                iVar1 = iVar1 + 0x20c;
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                    DAT_PencilRenderCore::ptr)(iVar1 + 500, local_1c + -100, iVar1 + 699, local_1c + 100,
                    (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar5 = iVar10 + 0x65;
                iVar3 = iVar1 + 700;
                iVar10 = iVar10 + -0x65;
                iVar1 = iVar1 + 499;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                iVar1, iVar10, iVar3, iVar5, (ushort)((int)(COL_BLACK::instance.shortValue)));
            iVar8 = iVar8 + local_20;
            iVar1 = iVar4 + -0xf;
            iVar5 = iVar8;
            iVar10 = iVar4;
            iVar3 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                local_18, 0x13);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                (iVar8 - iVar3) + -0xf, iVar1, iVar5, iVar10);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                local_18, iVar8 + -5, iVar4 + -0xb, OpenSHC::Text::TTA_RIGHT, 0xc2f0eb, 0, 0x13, FALSE, 0);
        LAB_00430ac9:
            if (DAT_MenuTextInputState::instance.field44_0xa4 != 0) {
                INT_00b95f68::instance = 0;
                DAT_MenuTextInputState::instance.field44_0xa4 = 0;
            }
            INT_00b960ec::instance
                = (int)(DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .keep.id
                    != 0);
            ;
            return;
        }

    }
}
}
