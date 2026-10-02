#include "../General.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_00b95960.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/INT_00b95950.hpp"
#include "OpenSHC/Globals/INT_00b95f6c.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Rendering::Enums::RenderTarget;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00428150
        void General::MenuItemRenderFunction_General_MenuMiniMap(int param_1, ...)
        {
            int drawY;
            char cVar1;
            int iVar2;
            int iVar3;
            int iVar4;
            BOOLEnum BVar5;
            int iVar6;
            int iVar7;
            BVar5 = MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)();
            iVar4 = DAT_ButtonY::instance;
            iVar3 = DAT_ButtonX::instance;
            if (BVar5 == FALSE) {
                iVar7 = 0;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithCustomBlendedBackground,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance + -0x6c,
                    (int)((int)(DAT_ButtonY::instance + -0x6c)), 0xd8, 0xd8,
                    (int)((int)(DAT_ButtonBackgroundBlendStrength::instance)));
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                if ((DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber != 0)
                    && (DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected != -1)) {
                    if (DAT_ButtonBackgroundBlendStrength::instance == 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapPreview,
                            DAT_MinimapViewState::ptr)(iVar3 + -100, iVar4 + -100);
                        do {
                            iVar2 = DAT_GameCore::instance.keepPositions[iVar7].x;
                            if (-1 < iVar2) {
                                cVar1 = DAT_GameSynchronyState::instance.playerPositionsArray[iVar7];
                                if (cVar1 != DAT_00b95960::instance) {
                                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                                    if (cVar1 == -10) {
                                        if (INT_00b95950::instance == iVar7) {
                                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                DAT_TextureRenderCoreObject::ptr)(
                                                OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 0xd3, iVar2 + -0x67 + iVar3,
                                                DAT_GameCore::instance.keepPositions[iVar7].y + -0x6b + iVar4);
                                        } else {
                                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                DAT_TextureRenderCoreObject::ptr)(
                                                OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 0xdc, iVar2 + -0x67 + iVar3,
                                                DAT_GameCore::instance.keepPositions[iVar7].y + -0x6b + iVar4);
                                        }
                                    } else {
                                        if ('\0'
                                            < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[cVar1 + 1]) {
                                            MACRO_CALL_MEMBER(
                                                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                                DAT_TextureRenderCoreObject::ptr)(
                                                OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2,
                                                (int)((int)((char)DAT_GameSynchronyState::instance
                                                                .DAT_PlayerGroupArray[cVar1 + 1]
                                                        * 2
                                                    + 0x1ec)),
                                                iVar2 + -0x60 + iVar3,
                                                DAT_GameCore::instance.keepPositions[iVar7].y + -100 + iVar4, 0xc);
                                        }
                                        if (INT_00b95f6c::instance == 0) {
                                            if (INT_00b95950::instance == iVar7) {
                                                MACRO_CALL_MEMBER(
                                                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                    DAT_TextureRenderCoreObject::ptr)(
                                                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3,
                                                    (int)((int)(DAT_GameSynchronyState::instance
                                                                    .playerPositionsArray[iVar7]
                                                        + 0xd4)),
                                                    DAT_GameCore::instance.keepPositions[iVar7].x + -0x67 + iVar3,
                                                    DAT_GameCore::instance.keepPositions[iVar7].y + -0x6b + iVar4);
                                            } else {
                                                MACRO_CALL_MEMBER(
                                                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                    DAT_TextureRenderCoreObject::ptr)(
                                                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                                                    (int)((int)(DAT_GameSynchronyState::instance
                                                                    .playerPositionsArray[iVar7]
                                                        + 0x1d6)),
                                                    DAT_GameCore::instance.keepPositions[iVar7].x + -0x67 + iVar3,
                                                    DAT_GameCore::instance.keepPositions[iVar7].y + -0x6b + iVar4);
                                            }
                                        } else {
                                            iVar2 = DAT_GameCore::instance.keepPositions[iVar7].x + -0x71 + iVar3;
                                            iVar6 = (int)DAT_GameSynchronyState::instance.playerPositionsArray[iVar7];
                                            drawY = DAT_GameCore::instance.keepPositions[iVar7].y + -0x74 + iVar4;
                                            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar6 + 1]
                                                == -1) {
                                                if (DAT_GameSynchronyState::instance.currentAIArray[iVar6 + 1] != 0) {
                                                    /*
                                                      Render AI portrait
                                                     */
                                                    MACRO_CALL_MEMBER(
                                                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                        DAT_TextureRenderCoreObject::ptr)(
                                                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar6 + 0x2cf, iVar2,
                                                        drawY);
                                                    MACRO_CALL_MEMBER(
                                                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                        DAT_TextureRenderCoreObject::ptr)(
                                                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                                                        (int)((int)(DAT_GameSynchronyState::instance
                                                                        .currentAIArray[DAT_GameSynchronyState::instance
                                                                                            .playerPositionsArray[iVar7]
                                                                            + 1]
                                                            + 700)),
                                                        iVar2, drawY);
                                                }
                                            } else {
                                                /*
                                                  Render Player portrait
                                                 */
                                                MACRO_CALL_MEMBER(
                                                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                                    DAT_TextureRenderCoreObject::ptr)(
                                                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar6 + 0x2cf, iVar2,
                                                    drawY);
                                                MACRO_CALL_MEMBER(
                                                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderFacesSmallUnk,
                                                    DAT_TextureRenderCoreObject::ptr)(
                                                    DAT_GameSynchronyState::instance.playerPositionsArray[iVar7] + 20,
                                                    iVar2 + 2, drawY + 2);
                                                MACRO_CALL_MEMBER(
                                                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                                                    DAT_PencilRenderCore::ptr)(iVar2, drawY, iVar2 + 0x23, drawY + 0x23,
                                                    (ushort)((int)(COL_BLACK::instance.shortValue)));
                                            }
                                        }
                                    }
                                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                                }
                            }
                            iVar7 = iVar7 + 1;
                        } while (iVar7 < 8);
                        if (-1 < DAT_00b95960::instance) {
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                                DAT_00b95960::instance + 0x1d6, DAT_MouseState::instance.screenSpaceX + -5,
                                DAT_MouseState::instance.screenSpaceY + -7);
                            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                                = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                            if ((DAT_MouseState::instance.leftClickState == FALSE)
                                && (DAT_MouseState::instance.draggingStopped == FALSE)) {
                                DAT_00b95960::instance = -1;
                            }
                        }
                    }
                    INT_00b95950::instance = -1;
                }
            }
        }

    }
}
}
