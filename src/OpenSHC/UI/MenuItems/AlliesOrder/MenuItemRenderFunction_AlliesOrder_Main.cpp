#include "../AlliesOrder.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_00df51f8.hpp"
#include "OpenSHC/Globals/DAT_00df51fc.hpp"
#include "OpenSHC/Globals/DAT_00df5200.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_EnemyArrayIndex.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RequestedGoodsByWhoArray.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004AD480
        void AlliesOrder::MenuItemRenderFunction_AlliesOrder_Main(int param_1, ...)
        {
            char* textAddress;
            int iVar1;
            int iVar2;
            int xParam;
            int yParam;
            TextAlignment alignment;
            uint foregroundColor;
            uint backgroundColor;
            int fontSize;
            BOOLEnum keepOffsetX;
            int blendStrength;
            if (param_1 == -2) {
                MACRO_CALL(
                    OpenSHC::UI::Rendering_Func::RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk)();
            }
            if (9 < param_1) {
                if (param_1 == 10) {
                    DAT_00df5200::instance = ((eTextSections)0);
                }
                MACRO_CALL(
                    OpenSHC::UI::Rendering_Func::RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk)();
                if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                    if (param_1 == 10) {
                        DAT_00df5200::instance = 0xe0;
                        DAT_00df51fc::instance = 8;
                    }
                    if (param_1 == 0xb) {
                        DAT_00df5200::instance = 0xe0;
                        DAT_00df51fc::instance = 9;
                    }
                }
            }
            iVar1 = param_1;
            if (param_1 < 7) {
                if (param_1 == -1)
                    goto LAB_004ad69c;
                iVar1 = param_1 + -1;
                if (DAT_EnemyArrayIndex::instance <= iVar1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                        DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)),
                        (int)((int)(DAT_ButtonX::instance + 0x47)), (int)((int)(DAT_ButtonY::instance + 0x47)),
                        (ushort)((int)(COL_BLACK::instance.shortValue)));
                    goto LAB_004ad693;
                }
                iVar1 = DAT_RequestedGoodsByWhoArray::instance[param_1];
                iVar2 = 0;
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar1] == -1) {
                    iVar2 = DAT_GameSynchronyState::instance.currentAIArray[iVar1];
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar1 + 0x222,
                    (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)));
                if (iVar2 == 0) {
                    if (DAT_GameCore::instance.lordIcons[iVar1] == 0) {
                        iVar2 = 0x21b;
                        goto LAB_004ad609;
                    }
                    if (DAT_GameCore::instance.lordIcons[iVar1] == 1) {
                        iVar2 = 0x21c;
                        goto LAB_004ad609;
                    }
                    if (0 < DAT_TextureRenderCoreObject::instance.field69_0x98[iVar1 + 0x13]) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x21d,
                            (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)));
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawBitmapFace,
                            DAT_TextureRenderCoreObject::ptr)(iVar1 + 0x13, (int)((int)(DAT_ButtonX::instance + 4)),
                            (int)((int)(DAT_ButtonY::instance + 4)));
                    }
                } else {
                    iVar2 = iVar2 + 0x20a;
                LAB_004ad609:
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar2,
                        (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)));
                }
                if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x202,
                        (int)((int)(DAT_ButtonX::instance + -6)), (int)((int)(DAT_ButtonY::instance + -6)),
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x201, 0);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x23e,
                        (int)((int)(DAT_ButtonX::instance + -10)), (int)((int)(DAT_ButtonY::instance + -8)),
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 0x23f, 0);
                    DAT_00df5200::instance = OpenSHC::DE::SHCDE::TEXT_ALLIES;
                    DAT_00df51fc::instance = 10;
                    DAT_00df51f8::instance = iVar1;
                }
            }
        LAB_004ad693:
            if (iVar1 != -1) {}
        LAB_004ad69c:
            iVar2 = DAT_ButtonY::instance;
            iVar1 = DAT_ButtonX::instance;
            if (DAT_00df5200::instance != ((eTextSections)0)) {
                blendStrength = 0;
                keepOffsetX = FALSE;
                fontSize = 0x11;
                backgroundColor = 0;
                foregroundColor = 0xb8eefb;
                alignment = OpenSHC::Text::TTA_LEFT;
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                xParam = DAT_ButtonX::instance;
                yParam = DAT_ButtonY::instance;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        (OpenSHC::DE::SHCDE::eTextSections)DAT_00df5200::instance, DAT_00df51fc::instance),
                    xParam, yParam, alignment, foregroundColor, backgroundColor, fontSize, keepOffsetX, blendStrength);
                if (DAT_00df51fc::instance == 10) {
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[DAT_00df51f8::instance] != -1) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                            DAT_GameSynchronyState::instance.DAT_PlayerNames[DAT_00df51f8::instance], iVar1 + 5, iVar2,
                            OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 0x11, TRUE, 0);
                        DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                        (int)((int)(DAT_GameSynchronyState::instance.aiVariationArray[DAT_00df51f8::instance] + 0x67
                            + DAT_GameSynchronyState::instance.currentAIArray[DAT_00df51f8::instance] * 8)),
                        iVar1 + 5, iVar2, OpenSHC::Text::TTA_LEFT, 0xb8eefb, 0, 0x11, TRUE);
                }
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            }
        }

    }
}
}
