#include "../MapEditorProperties.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/string-literals.hpp"

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

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042E0D0
        void MapEditorProperties::MenuView_MapEditorProperties_DoEveryFrame()
        {
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
                DAT_MenuHandlerState::instance.x + 48, DAT_MenuHandlerState::instance.y + 6, 704, 50);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            if (DAT_GameCore::instance.mapLoadedForEditor) {
                // the position in locals, y first, as the original reads it
                int const textY = DAT_MenuHandlerState::instance.y + 35;
                int const textX = DAT_MenuHandlerState::instance.x + 140;
                if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 0) {
                    // "Single-Player"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 12),
                        textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 17, FALSE, 0);
                    // the separators and map types read the position again, as the original does
                    switch (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1) {
                    case OpenSHC::Map::MT_SIEGE:
                        // " - "
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s___005a2304, DAT_MenuHandlerState::instance.x + 140,
                            DAT_MenuHandlerState::instance.y + 35, OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_C2F0EB, 17, TRUE, 0);
                        // "Siege"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 28, DAT_MenuHandlerState::instance.x + 140,
                            DAT_MenuHandlerState::instance.y + 35, OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_C2F0EB, 17, TRUE);
                        break;
                    case OpenSHC::Map::MT_INVASION:
                        // " - "
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s___005a2304, DAT_MenuHandlerState::instance.x + 140,
                            DAT_MenuHandlerState::instance.y + 35, OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_C2F0EB, 17, TRUE, 0);
                        if (DAT_GameCore::instance.mapU3EndInt == 0) {
                            // "Invasion"
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 29, DAT_MenuHandlerState::instance.x + 140,
                                DAT_MenuHandlerState::instance.y + 35, OpenSHC::Text::TTA_LEFT,
                                OpenSHC::Rendering::Colors::COL_C2F0EB, 17, TRUE);
                        } else {
                            // "Economic"
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                                OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 30, DAT_MenuHandlerState::instance.x + 140,
                                DAT_MenuHandlerState::instance.y + 35, OpenSHC::Text::TTA_LEFT,
                                OpenSHC::Rendering::Colors::COL_C2F0EB, 17, TRUE);
                        }
                        break;
                    case OpenSHC::Map::MT_ECONOMIC:
                        // " - "
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s___005a2304, DAT_MenuHandlerState::instance.x + 140,
                            DAT_MenuHandlerState::instance.y + 35, OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_C2F0EB, 17, TRUE, 0);
                        // "Economic"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 30, DAT_MenuHandlerState::instance.x + 140,
                            DAT_MenuHandlerState::instance.y + 35, OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_C2F0EB, 17, TRUE);
                        break;
                    case OpenSHC::Map::MT_JUST_BUILD:
                        // " - "
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen,
                            DAT_TextManagerObject::ptr)(s___005a2304, DAT_MenuHandlerState::instance.x + 140,
                            DAT_MenuHandlerState::instance.y + 35, OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_C2F0EB, 17, TRUE, 0);
                        // "Landscape"
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 33, DAT_MenuHandlerState::instance.x + 140,
                            DAT_MenuHandlerState::instance.y + 35, OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_C2F0EB, 17, TRUE);
                        break;
                    }
                } else {
                    // "Multi-Player"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 13),
                        textX, textY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 17, FALSE, 0);
                }
                // " - "
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    s___005a2304, DAT_MenuHandlerState::instance.x + 140, DAT_MenuHandlerState::instance.y + 35,
                    OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 17, TRUE, 0);
                if (INT_00b960e4::instance == 0) {
                    // y and x into locals before the call, as the original reads them
                    int const nameY = DAT_MenuHandlerState::instance.y + 35;
                    int const nameX = DAT_MenuHandlerState::instance.x + 140;
                    // "Untitled"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 24),
                        nameX, nameY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 17, TRUE, 0);
                } else {
                    // the position before the name lookup, as the original reads it
                    int const nameY = DAT_MenuHandlerState::instance.y + 35;
                    int const nameX = DAT_MenuHandlerState::instance.x + 140;
                    char* const name = MACRO_CALL_MEMBER(
                        OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(2);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        name, nameX, nameY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 17, TRUE,
                        0);
                }
            }
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE) {
                int left = DAT_MenuHandlerState::instance.x;
                if (DAT_GameCore::instance.U2_mapType_singleOrMulti == 0) {
                    left += 400;
                } else {
                    left += 600;
                }
                int top = DAT_MenuHandlerState::instance.y + 240;
                int mapSize = DAT_TileMapState::instance.mapSize;
                if (mapSize == 0) {
                    mapSize = OpenSHC::Map::MC_MAP_SIZE_400;
                }
                // the centre is copied once the size is settled, as the original does
                int const centerX = left;
                int const centerY = top;
                DAT_MinimapViewState::instance.needsRedraw = TRUE;
                char sizeText[20];
                // "%dx%d"
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(sizeText, s__dx_d_005a22fc, mapSize, mapSize);
                int width;
                switch (mapSize) {
                case OpenSHC::Map::MC_MAP_SIZE_100:
                    left -= 50;
                    top -= 50;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor,
                        DAT_MinimapViewState::ptr)(left, top, mapSize, mapSize);
                    width = 100;
                    break;
                case OpenSHC::Map::MC_MAP_SIZE_160:
                    left -= 80;
                    top -= 80;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor,
                        DAT_MinimapViewState::ptr)(left, top, mapSize, mapSize);
                    width = 160;
                    break;
                case OpenSHC::Map::MC_MAP_SIZE_200:
                    left -= 100;
                    top -= 100;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor,
                        DAT_MinimapViewState::ptr)(left, top, mapSize, mapSize);
                    width = 200;
                    break;
                case OpenSHC::Map::MC_MAP_SIZE_300:
                    left -= 75;
                    top -= 75;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor,
                        DAT_MinimapViewState::ptr)(left, top, 150, 150);
                    width = 150;
                    break;
                default: // 400 (no map size yet) and any other size
                    left -= 100;
                    top -= 100;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor,
                        DAT_MinimapViewState::ptr)(left, top, 200, 200);
                    width = 200;
                    break;
                }
                switch (mapSize) {
                case OpenSHC::Map::MC_MAP_SIZE_300:
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                        centerX - 75, centerY - 75, centerX + 73, centerY + 74, COL_BLACK::instance.shortValue);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                        centerX - 76, centerY - 76, centerX + 74, centerY + 75, COL_BLACK::instance.shortValue);
                    break;
                case OpenSHC::Map::MC_MAP_SIZE_200:
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                        centerX - 98, centerY - 99, centerX + 99, centerY + 99, COL_BLACK::instance.shortValue);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                        centerX - 99, centerY - 100, centerX + 100, centerY + 100, COL_BLACK::instance.shortValue);
                    break;
                case OpenSHC::Map::MC_MAP_SIZE_160:
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                        centerX - 78, centerY - 79, centerX + 78, centerY + 77, COL_BLACK::instance.shortValue);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                        centerX - 79, centerY - 80, centerX + 79, centerY + 78, COL_BLACK::instance.shortValue);
                    break;
                default:
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                        centerX - 100, centerY - 100, centerX + 99, centerY + 100, COL_BLACK::instance.shortValue);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                        centerX - 101, centerY - 101, centerX + 100, centerY + 101, COL_BLACK::instance.shortValue);
                    break;
                }
                int const right = width + left;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                    right
                        - MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(sizeText, 19)
                        - 15,
                    top - 15, right, top);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(sizeText, right - 5, top - 11, OpenSHC::Text::TTA_RIGHT,
                    OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 19, FALSE, 0);
                // each text's position in locals, y first, as the original reads it
                if (DAT_MapEditorProperties_ClickedButton::instance == -3) {
                    int const textY = DAT_MenuHandlerState::instance.y + 560;
                    int const textX = DAT_MenuHandlerState::instance.x + 300;
                    // "Flag this map as Balanced"
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 45),
                        textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 17, FALSE,
                        0);
                }
                if (DAT_MapEditorProperties_ClickedButton::instance == -4) {
                    int const textY = DAT_MenuHandlerState::instance.y + 560;
                    int const textX = DAT_MenuHandlerState::instance.x + 300;
                    // "Flag this map as Un-Balanced"
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 46),
                        textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 17, FALSE,
                        0);
                }
                if (DAT_MapEditorProperties_ClickedButton::instance == -5) {
                    int const textY = DAT_MenuHandlerState::instance.y + 560;
                    int const textX = DAT_MenuHandlerState::instance.x + 300;
                    // "Invasion"
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 29),
                        textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 17, FALSE,
                        0);
                }
                if (DAT_MapEditorProperties_ClickedButton::instance == -6) {
                    int const textY = DAT_MenuHandlerState::instance.y + 560;
                    int const textX = DAT_MenuHandlerState::instance.x + 300;
                    // "Economic"
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 30),
                        textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 17, FALSE,
                        0);
                }
            }
            if (DAT_GameCore::instance.isTimeHalted2 != 0) {
                // "Game Paused"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(s_Game_Paused_005a22f0, 798, 576, OpenSHC::Text::TTA_RIGHT,
                    OpenSHC::Rendering::Colors::COL_00A2FF, OpenSHC::Rendering::Colors::COL_003E66, 17, FALSE, 0);
            }
            DAT_MapEditorProperties_ClickedButton::instance = 0;
            if (DAT_MenuTextInputState::instance.field_0xa4 != 0) {
                INT_00b95f68::instance = 0;
                DAT_MenuTextInputState::instance.field_0xa4 = 0;
            }
        }

    }
}
}
