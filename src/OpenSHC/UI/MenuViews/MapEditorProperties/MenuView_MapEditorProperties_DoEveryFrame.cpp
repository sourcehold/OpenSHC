#include "../MapEditorProperties.func.hpp"

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
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapEditorProperties_ClickedButton.hpp"
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
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0042E0D0
        void MapEditorProperties::MenuView_MapEditorProperties_DoEveryFrame()
        {
            int iVar1;
            char* pcVar2;
            int iVar3;
            int iVar4;
            int iVar5;
            TextAlignment TVar6;
            uint uVar7;
            BGR24 BVar8;
            uint uVar9;
            int iVar10;
            BOOLEnum BVar11;
            int iVar12;
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
                DAT_MenuHandlerState::instance.x + 0x30, DAT_MenuHandlerState::instance.y + 6, 0x2c0, 0x32);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            if (DAT_GameCore::instance.field115_0x1d98 != 0) {
                iVar12 = 0;
                BVar11 = FALSE;
                iVar10 = 0x11;
                BVar8 = 0xc2f0eb;
                iVar1 = DAT_MenuHandlerState::instance.y + 0x23;
                TVar6 = OpenSHC::Text::TTA_LEFT;
                iVar4 = DAT_MenuHandlerState::instance.x + 0x8c;
                if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 0) {
                    /*
                      added by script: "Single-Player"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0xc),
                        iVar4, iVar1, TVar6, BVar8, iVar10, BVar11, iVar12);
                    switch (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1) {
                    case OpenSHC::Map::MT_SIEGE:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(" - ", DAT_MenuHandlerState::instance.x + 0x8c,
                            DAT_MenuHandlerState::instance.y + 0x23, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x11, TRUE, 0);
                        /*
                          added by script: "Siege"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0x1c, DAT_MenuHandlerState::instance.x + 0x8c,
                            DAT_MenuHandlerState::instance.y + 0x23, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x11, TRUE);
                        break;
                    case OpenSHC::Map::MT_INVASION:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(" - ", DAT_MenuHandlerState::instance.x + 0x8c,
                            DAT_MenuHandlerState::instance.y + 0x23, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x11, TRUE, 0);
                        if (DAT_GameCore::instance.mapU3EndInt == 0) {
                            /*
                              added by script: "Invasion"
                             */
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0x1d, DAT_MenuHandlerState::instance.x + 0x8c,
                                DAT_MenuHandlerState::instance.y + 0x23, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x11, TRUE);
                        } else {
                            /*
                              added by script: "Economic"
                             */
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0x1e, DAT_MenuHandlerState::instance.x + 0x8c,
                                DAT_MenuHandlerState::instance.y + 0x23, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x11, TRUE);
                        }
                        break;
                    case OpenSHC::Map::MT_ECONOMIC:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(" - ", DAT_MenuHandlerState::instance.x + 0x8c,
                            DAT_MenuHandlerState::instance.y + 0x23, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x11, TRUE, 0);
                        /*
                          added by script: "Economic"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0x1e, DAT_MenuHandlerState::instance.x + 0x8c,
                            DAT_MenuHandlerState::instance.y + 0x23, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x11, TRUE);
                        break;
                    case OpenSHC::Map::MT_JUST_BUILD:
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(" - ", DAT_MenuHandlerState::instance.x + 0x8c,
                            DAT_MenuHandlerState::instance.y + 0x23, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x11, TRUE, 0);
                        /*
                          added by script: "Landscape"
                         */
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0x21, DAT_MenuHandlerState::instance.x + 0x8c,
                            DAT_MenuHandlerState::instance.y + 0x23, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x11, TRUE);
                    }
                } else {
                    /*
                      added by script: "Multi-Player"
                     */
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0xd),
                        iVar4, iVar1, TVar6, BVar8, iVar10, BVar11, iVar12);
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    " - ", DAT_MenuHandlerState::instance.x + 0x8c, DAT_MenuHandlerState::instance.y + 0x23,
                    OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x11, TRUE, 0);
                if (INT_00b960e4::instance == 0) {
                    iVar12 = 0;
                    BVar11 = TRUE;
                    iVar10 = 0x11;
                    BVar8 = 0xc2f0eb;
                    TVar6 = OpenSHC::Text::TTA_LEFT;
                    iVar1 = DAT_MenuHandlerState::instance.y + 0x23;
                    iVar4 = DAT_MenuHandlerState::instance.x + 0x8c;
                    /*
                      added by script: "Untitled"
                     */
                    pcVar2 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0x18);
                } else {
                    iVar1 = DAT_MenuHandlerState::instance.y + 0x23;
                    iVar4 = DAT_MenuHandlerState::instance.x + 0x8c;
                    pcVar2 = MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(2);
                    iVar12 = 0;
                    BVar11 = TRUE;
                    iVar10 = 0x11;
                    BVar8 = 0xc2f0eb;
                    TVar6 = OpenSHC::Text::TTA_LEFT;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    pcVar2, iVar4, iVar1, TVar6, BVar8, iVar10, BVar11, iVar12);
            }
            iVar1 = DAT_MenuHandlerState::instance.y;
            if (DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE)
                goto LAB_0042e7ab;
            if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 0) {
                iVar4 = DAT_MenuHandlerState::instance.x + 400;
            } else {
                iVar4 = DAT_MenuHandlerState::instance.x + 600;
            }
            local_1c = DAT_MenuHandlerState::instance.y + 0xf0;
            iVar10 = DAT_TileMapState::instance.mapSize;
            if (DAT_TileMapState::instance.mapSize == 0) {
                iVar10 = 400;
            }
            DAT_MinimapViewState::instance.field0_0x0 = 1;
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_18, "%dx%d", iVar10, iVar10);
            switch (iVar10) {
            case 100:
                iVar1 = iVar1 + 0xbe;
                iVar12 = iVar4 + -0x32;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    iVar12, iVar1, iVar10, iVar10);
                local_20 = 100;
                break;
            default:
                iVar5 = 200;
                goto LAB_0042e507;
            case 0xa0:
                iVar1 = iVar1 + 0xa0;
                iVar12 = iVar4 + -0x50;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    iVar12, iVar1, iVar10, iVar10);
                local_20 = 0xa0;
                break;
            case 200:
                iVar5 = iVar10;
            LAB_0042e507:
                iVar1 = iVar1 + 0x8c;
                iVar12 = iVar4 + -100;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    iVar12, iVar1, iVar5, iVar5);
                local_20 = 200;
                break;
            case 300:
                iVar1 = iVar1 + 0xa5;
                iVar12 = iVar4 + -0x4b;
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor, DAT_MinimapViewState::ptr)(
                    iVar12, iVar1, 0x96, 0x96);
                local_20 = 0x96;
            }
            iVar5 = local_1c;
            if (iVar10 == 0xa0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                    DAT_PencilRenderCore::ptr)(iVar4 + -0x4e, local_1c + -0x4f, iVar4 + 0x4e, local_1c + 0x4d,
                    (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar10 = iVar5 + 0x4e;
                iVar3 = iVar4 + 0x4f;
                iVar5 = iVar5 + -0x50;
                iVar4 = iVar4 + -0x4f;
            } else if (iVar10 == 200) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                    DAT_PencilRenderCore::ptr)(iVar4 + -0x62, local_1c + -99, iVar4 + 99, local_1c + 99,
                    (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar10 = iVar5 + 100;
                iVar3 = iVar4 + 100;
                iVar5 = iVar5 + -100;
                iVar4 = iVar4 + -99;
            } else if (iVar10 == 300) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                    DAT_PencilRenderCore::ptr)(iVar4 + -0x4b, local_1c + -0x4b, iVar4 + 0x49, local_1c + 0x4a,
                    (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar10 = iVar5 + 0x4b;
                iVar3 = iVar4 + 0x4a;
                iVar5 = iVar5 + -0x4c;
                iVar4 = iVar4 + -0x4c;
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                    DAT_PencilRenderCore::ptr)(iVar4 + -100, local_1c + -100, iVar4 + 99, local_1c + 100,
                    (ushort)((int)(COL_BLACK::instance.shortValue)));
                iVar10 = iVar5 + 0x65;
                iVar3 = iVar4 + 100;
                iVar5 = iVar5 + -0x65;
                iVar4 = iVar4 + -0x65;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                iVar4, iVar5, iVar3, iVar10, (ushort)((int)(COL_BLACK::instance.shortValue)));
            iVar12 = local_20 + iVar12;
            iVar4 = iVar1 + -0xf;
            iVar10 = iVar12;
            iVar5 = iVar1;
            iVar3 = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                local_18, 0x13);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                (iVar12 - iVar3) + -0xf, iVar4, iVar10, iVar5);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                local_18, iVar12 + -5, iVar1 + -0xb, OpenSHC::Text::TTA_RIGHT, 0xc2f0eb, 0, 0x13, FALSE, 0);
            if (DAT_MapEditorProperties_ClickedButton::instance == -3) {
                iVar12 = 0;
                BVar11 = FALSE;
                iVar10 = 0x11;
                uVar9 = 0;
                uVar7 = 0xc2f0eb;
                TVar6 = OpenSHC::Text::TTA_CENTER;
                iVar1 = DAT_MenuHandlerState::instance.y + 0x230;
                iVar4 = DAT_MenuHandlerState::instance.x + 300;
                /*
                  added by script: "Flag this map as Balanced"
                 */
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0x2d),
                    iVar4, iVar1, TVar6, uVar7, uVar9, iVar10, BVar11, iVar12);
            }
            if (DAT_MapEditorProperties_ClickedButton::instance == -4) {
                iVar12 = 0;
                BVar11 = FALSE;
                iVar10 = 0x11;
                uVar9 = 0;
                uVar7 = 0xc2f0eb;
                TVar6 = OpenSHC::Text::TTA_CENTER;
                iVar1 = DAT_MenuHandlerState::instance.y + 0x230;
                iVar4 = DAT_MenuHandlerState::instance.x + 300;
                /*
                  added by script: "Flag this map as Un-Balanced"
                 */
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0x2e),
                    iVar4, iVar1, TVar6, uVar7, uVar9, iVar10, BVar11, iVar12);
            }
            if (DAT_MapEditorProperties_ClickedButton::instance == -5) {
                iVar12 = 0;
                BVar11 = FALSE;
                iVar10 = 0x11;
                uVar9 = 0;
                uVar7 = 0xc2f0eb;
                TVar6 = OpenSHC::Text::TTA_CENTER;
                iVar1 = DAT_MenuHandlerState::instance.y + 0x230;
                iVar4 = DAT_MenuHandlerState::instance.x + 300;
                /*
                  added by script: "Invasion"
                 */
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0x1d),
                    iVar4, iVar1, TVar6, uVar7, uVar9, iVar10, BVar11, iVar12);
            }
            if (DAT_MapEditorProperties_ClickedButton::instance == -6) {
                iVar12 = 0;
                BVar11 = FALSE;
                iVar10 = 0x11;
                uVar9 = 0;
                uVar7 = 0xc2f0eb;
                TVar6 = OpenSHC::Text::TTA_CENTER;
                iVar1 = DAT_MenuHandlerState::instance.y + 0x230;
                iVar4 = DAT_MenuHandlerState::instance.x + 300;
                /*
                  added by script: "Economic"
                 */
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 0x1e),
                    iVar4, iVar1, TVar6, uVar7, uVar9, iVar10, BVar11, iVar12);
            }
        LAB_0042e7ab:
            if (DAT_GameCore::instance.isTimeHalted2 != 0) {
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    "Game Paused", 0x31e, 0x240, OpenSHC::Text::TTA_RIGHT, 0xa2ff, 0x3e66, 0x11, FALSE, 0);
            }
            DAT_MapEditorProperties_ClickedButton::instance = 0;
            if (DAT_MenuTextInputState::instance.field44_0xa4 != 0) {
                INT_00b95f68::instance = 0;
                DAT_MenuTextInputState::instance.field44_0xa4 = 0;
            };
            return;
        }

    }
}
}
