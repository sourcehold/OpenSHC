#include "../UnusedCreateSiege.func.hpp"

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

namespace OpenSHC {
namespace UI {
    namespace MenuViews {
        namespace UnusedCreateSiege {

            // FUNCTION: STRONGHOLDCRUSADER 0x004306D0
            void MenuView_UnusedCreateSiege_DoEveryFrame()
            {
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
                    DAT_MenuHandlerState::instance.x + 48, DAT_MenuHandlerState::instance.y + 6, 704, 50);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                if (!DAT_BottomLeftTextDisplayState::instance.currentlyDisplayedTextIsDisplayedUnk) {
                    // "Use the pre-built map and fixed amounts of stone and gold to build the strongest castle ..."
                    DAT_TextManagerObject::instance.field_0x24 = 1;
                    // its position named, y first (inline: quick_diff 0.8802 -> 0.5928)
                    int const textY = DAT_MenuHandlerState::instance.y + 118;
                    int const textX = DAT_MenuHandlerState::instance.x + 18;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 37),
                        textX, textY, 456, 0xccfaff, OpenSHC::Rendering::Colors::COL_000000, 17, 0);
                }
                // "'Siege That' Builder - " and the map's name
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 34),
                    DAT_MenuHandlerState::instance.x + 140, DAT_MenuHandlerState::instance.y + 35,
                    OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 17, FALSE, 0);
                // " - "
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    s___005a2304, DAT_MenuHandlerState::instance.x + 140, DAT_MenuHandlerState::instance.y + 35,
                    OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 17, TRUE, 0);
                if (INT_00b960e4::instance == 0) {
                    // "Untitled"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MAPEDIT, 24),
                        DAT_MenuHandlerState::instance.x + 140, DAT_MenuHandlerState::instance.y + 35,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 17, TRUE, 0);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(2),
                        DAT_MenuHandlerState::instance.x + 140, DAT_MenuHandlerState::instance.y + 35,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 17, TRUE, 0);
                }

                if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE) {
                    // the minimap preview, centred on (x, y)
                    int x = DAT_MenuHandlerState::instance.x + 600;
                    int y = DAT_MenuHandlerState::instance.y + 240;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    int mapSize = DAT_TileMapState::instance.mapSize;
                    if (mapSize == 0) {
                        mapSize = OpenSHC::Map::MC_MAP_SIZE_400;
                    }
                    int const centerX = x;
                    int const centerY = y;
                    DAT_MinimapViewState::instance.needsRedraw = TRUE;
                    char sizeText[20];
                    // "%dx%d"
                    MACRO_CALL(OpenSHC::OS_Func::_sprintf)(sizeText, s__dx_d_005a22fc, mapSize, mapSize);
                    // x and y move to the preview's top left corner
                    int previewSize;
                    switch (mapSize) {
                    case 100:
                        x -= 50;
                        y -= 50;
                        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor,
                            DAT_MinimapViewState::ptr)(x, y, mapSize, mapSize);
                        previewSize = 100;
                        break;
                    case OpenSHC::Map::MC_MAP_SIZE_160:
                        x -= 80;
                        y -= 80;
                        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor,
                            DAT_MinimapViewState::ptr)(x, y, mapSize, mapSize);
                        previewSize = 160;
                        break;
                    case OpenSHC::Map::MC_MAP_SIZE_200:
                        x -= 100;
                        y -= 100;
                        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor,
                            DAT_MinimapViewState::ptr)(x, y, mapSize, mapSize);
                        previewSize = 200;
                        break;
                    case OpenSHC::Map::MC_MAP_SIZE_300:
                        // drawn at half size
                        x -= 75;
                        y -= 75;
                        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor,
                            DAT_MinimapViewState::ptr)(x, y, 150, 150);
                        previewSize = 150;
                        break;
                    default:
                        // 400 is drawn at half size
                        x -= 100;
                        y -= 100;
                        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapEditor,
                            DAT_MinimapViewState::ptr)(x, y, 200, 200);
                        previewSize = 200;
                        break;
                    }

                    // a two-pixel black frame around the preview
                    // default first, as the original lays the arms out; a 100 map gets the default 200 frame
                    switch (mapSize) {
                    default:
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                            centerX - 100, centerY - 100, centerX + 99, centerY + 100, COL_BLACK::instance.shortValue);
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                            centerX - 101, centerY - 101, centerX + 100, centerY + 101, COL_BLACK::instance.shortValue);
                        break;
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
                    }

                    // the size label at the top right (x += previewSize: quick_diff 0.9760 -> 0.8617)
                    int const labelX = x + previewSize;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                        labelX
                            - MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth,
                                DAT_TextManagerObject::ptr)(sizeText, 19)
                            - 15,
                        y - 15, labelX, y);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)(sizeText, labelX - 5, y - 11, OpenSHC::Text::TTA_RIGHT,
                        OpenSHC::Rendering::Colors::COL_C2F0EB, OpenSHC::Rendering::Colors::COL_000000, 19, FALSE, 0);
                }
                if (DAT_MenuTextInputState::instance.field_0xa4 != 0) {
                    INT_00b95f68::instance = 0;
                    DAT_MenuTextInputState::instance.field_0xa4 = 0;
                }
                INT_00b960ec::instance
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .buildingEntryInfos[0]
                          .id
                    != 0;
            }

        }
    }
}
}
