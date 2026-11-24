#include "../CrusadeMissionIntro.func.hpp"

#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/CHAR_ARRAY_00eb0ab0.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00eb9ae8.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x004DD7B0
        void CrusadeMissionIntro::MenuView_CrusadeMissionIntro_DoEveryFrame()
        {
            if (!DAT_MissionDefinedData::instance.field_0xaf8) {
                return;
            }
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderGfxHelperUnk)(0, 0, 0);
            // the four are read before the tests, as the original does; the campaign data is loaded with them
            int const trailType = DAT_GameCore::instance.currentTrailType;
            int const extremeProgress = DAT_GameCore::instance.extremeTrailProgress;
            int const warchestProgress = DAT_GameCore::instance.warchestTrailProgress;
            int const firstEditionProgress = DAT_GameCore::instance.skirmishTrailProgress;
            // a finished trail shows only its message: three copies, positions in locals (one copy or inline merges)
            if (trailType == OpenSHC::Game::TT_EXTREME) {
                if (extremeProgress >= 20) {
                    int const messageY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 50;
                    int const messageX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                    // "Crusader Trail Completed!"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 6),
                        messageX, messageY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 16,
                        FALSE, 0);
                    return;
                }
            } else if (trailType == OpenSHC::Game::TT_WARCHEST) {
                if (warchestProgress >= 30) {
                    int const messageY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 50;
                    int const messageX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                    // "Crusader Trail Completed!"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 6),
                        messageX, messageY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 16,
                        FALSE, 0);
                    return;
                }
            } else if (trailType == OpenSHC::Game::TT_FIRST_EDITION && firstEditionProgress >= 50) {
                int const messageY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 50;
                int const messageX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 400;
                // "Crusader Trail Completed!"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 6),
                    messageX, messageY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 16, FALSE,
                    0);
                return;
            }
            // avatarX is copied from listX after rowY: copied straight after listX, the border height is read once
            int const listX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 32;
            int rowY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 342;
            int avatarX = listX;
            int const avatarY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 254;
            int teams[10];
            int noLord[10];
            int sorted[10];
            struct Entry {
                int id, unknown4, unknown8;
            } entries[10];
            for (int k = 0; k < countof(sorted); ++k) {
                sorted[k] = 0;
            }
            for (int k = 0; k < countof(noLord); ++k) {
                noLord[k] = 0;
            }
            for (int k = 0; k < countof(teams); ++k) {
                teams[k] = 0;
            }
            if (!DAT_GameCore::instance.gameSuspended) {
                if (trailType == OpenSHC::Game::TT_EXTREME) {
                    MACRO_CALL(OpenSHC::Synchrony_Func::LoadSkirmishCampaignData)(extremeProgress);
                } else if (trailType == OpenSHC::Game::TT_WARCHEST) {
                    MACRO_CALL(OpenSHC::Synchrony_Func::LoadSkirmishCampaignData)(warchestProgress);
                } else {
                    MACRO_CALL(OpenSHC::Synchrony_Func::LoadSkirmishCampaignData)(firstEditionProgress);
                }
            }
            // the map's preview with the keeps
            int const previewX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 568;
            int const previewY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 10;
            if (!INT_00eb9ae8::instance) {
                MACRO_CALL(OpenSHC::UI::Helpers_Func::ReadMapHeaderFromFile)(CHAR_ARRAY_00eb0ab0::instance);
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
                DAT_PencilRenderCore::ptr)(previewX, previewY, 216, 216);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapPreview, DAT_MinimapViewState::ptr)(
                previewX + 8, previewY + 8);
            for (int i = 0; i < countof(DAT_GameCore::instance.keepPositions); ++i) {
                if (DAT_GameCore::instance.keepPositions[i].x >= 0) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    if (DAT_GameSynchronyState::instance.playerPositionsArray[i] != -10) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                            DAT_GameSynchronyState::instance.playerPositionsArray[i] + 470,
                            DAT_GameCore::instance.keepPositions[i].x + previewX + 5,
                            DAT_GameCore::instance.keepPositions[i].y + previewY + 1);
                    }
                }
            }
            // the lords and the gold
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
                DAT_PencilRenderCore::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 16,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 10, 528, 216);
            // the position in locals, y first (inline, the scratch registers rotate from here on)
            int const humanY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100;
            int const humanX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 32;
            // "Human Lord"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 7),
                humanX, humanY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 17, FALSE, 0);
            int const computerY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 140;
            int const computerX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 32;
            // "Computer Lords"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE, 8),
                computerX, computerY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 17, FALSE, 0);
            // the trail type and progress are read again from here on, as the original does
            int multiplier = 1;
            if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                multiplier = 3;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_RenderingDefinedData::instance
                        .field_0x53bb4[(DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance
                                           + DAT_GameSynchronyState::instance.skirmishGameIntensityType * 5)
                                * 2
                            + 12]
                    * multiplier,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 280,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 100, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 17, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                DAT_RenderingDefinedData::instance
                        .field_0x53bb4[(DAT_GameSynchronyState::instance.skirmishCurrentAdvantageBalance
                                           + DAT_GameSynchronyState::instance.skirmishGameIntensityType * 5)
                                * 2
                            + 13]
                    * multiplier,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 280,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 140, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 17, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 730,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 350,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 92);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 730,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 350,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 132);
            if (DAT_GameSynchronyState::instance.skirmishGameIntensityType == 2) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 604,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 500,
                    DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 180);
            }
            // the opponents' box
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithBlendedBackground,
                DAT_PencilRenderCore::ptr)(DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 16,
                DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 238, 768, 288);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            // the mission's title: its number, ".", its name; a long name gets the smaller font
            // a copy per trail and font, as in the original (one copy with the font in a local loses the match)
            if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                // "Look Out" (81) to "Ultimate Victory" (100)
                // the name's index in a local (inline, the scratch registers rotate through the title)
                int const nameIndex = DAT_GameCore::instance.extremeTrailProgress + 81;
                if (MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TRAIL_NAMES_CRU, nameIndex),
                        15)
                    > 445) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                        DAT_GameCore::instance.extremeTrailProgress + 1,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 30,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 30, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 16, FALSE, 0);
                    // "."
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)(s___005ab5d4,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 31,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 30, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 16, TRUE, 0);
                    // the index and the position in locals (inline, the six arms do not share their tails)
                    int const titleY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 30;
                    int const titleX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 35;
                    int const titleIndex = DAT_GameCore::instance.extremeTrailProgress + 81;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TRAIL_NAMES_CRU, titleIndex),
                        titleX, titleY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 16, TRUE,
                        0);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                        DAT_GameCore::instance.extremeTrailProgress + 1,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 30,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 30, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 15, FALSE, 0);
                    // "."
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)(s___005ab5d4,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 31,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 30, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 15, TRUE, 0);
                    int const titleY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 30;
                    int const titleX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 35;
                    int const titleIndex = DAT_GameCore::instance.extremeTrailProgress + 81;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TRAIL_NAMES_CRU, titleIndex),
                        titleX, titleY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 15, TRUE,
                        0);
                }
            } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                // "First Step" (51) to "The Big One!" (80)
                int const nameIndex = DAT_GameCore::instance.warchestTrailProgress + 51;
                if (MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TRAIL_NAMES_CRU, nameIndex),
                        15)
                    > 445) {
                    // the war chest's missions go on from the first edition's 50: they are numbered 51 to 80
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                        DAT_GameCore::instance.warchestTrailProgress + 51,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 30,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 30, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 16, FALSE, 0);
                    // "."
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)(s___005ab5d4,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 31,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 30, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 16, TRUE, 0);
                    int const titleY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 30;
                    int const titleX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 35;
                    int const titleIndex = DAT_GameCore::instance.warchestTrailProgress + 51;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TRAIL_NAMES_CRU, titleIndex),
                        titleX, titleY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 16, TRUE,
                        0);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                        DAT_GameCore::instance.warchestTrailProgress + 51,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 30,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 30, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 15, FALSE, 0);
                    // "."
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)(s___005ab5d4,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 31,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 30, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 15, TRUE, 0);
                    int const titleY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 30;
                    int const titleX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 35;
                    int const titleIndex = DAT_GameCore::instance.warchestTrailProgress + 51;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TRAIL_NAMES_CRU, titleIndex),
                        titleX, titleY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 15, TRUE,
                        0);
                }
            } else {
                // "Arrival" (1) to "Final Victory" (50)
                int const nameIndex = DAT_GameCore::instance.skirmishTrailProgress + 1;
                if (MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TRAIL_NAMES_CRU, nameIndex),
                        15)
                    > 445) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                        DAT_GameCore::instance.skirmishTrailProgress + 1,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 30,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 30, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 16, FALSE, 0);
                    // "."
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)(s___005ab5d4,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 31,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 30, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 16, TRUE, 0);
                    int const titleY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 30;
                    int const titleX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 35;
                    int const titleIndex = DAT_GameCore::instance.skirmishTrailProgress + 1;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TRAIL_NAMES_CRU, titleIndex),
                        titleX, titleY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 16, TRUE,
                        0);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                        DAT_GameCore::instance.skirmishTrailProgress + 1,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 30,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 30, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 15, FALSE, 0);
                    // "."
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                        DAT_TextManagerObject::ptr)(s___005ab5d4,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 31,
                        DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 30, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 15, TRUE, 0);
                    int const titleY = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight + 30;
                    int const titleX = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth + 35;
                    int const titleIndex = DAT_GameCore::instance.skirmishTrailProgress + 1;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TRAIL_NAMES_CRU, titleIndex),
                        titleX, titleY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 15, TRUE,
                        0);
                }
            }
            // the opponents: players 1 to 8 who take part, sorted by team
            for (int k = 0; k < countof(entries); ++k) {
                entries[k].id = 0;
            }
            int count = 0;
            for (int i = 1; i < countof(DAT_GameSynchronyState::instance.finalResults.active); ++i) {
                if (DAT_GameCore::instance.gameSuspended == 1) {
                    if (!DAT_GameSynchronyState::instance.finalResults.active[i]) {
                        continue;
                    }
                } else if (!DAT_GameCore::instance.gameSuspended
                    && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[i] == -1
                    && !DAT_GameSynchronyState::instance.currentAIArray[i]) {
                    continue;
                }
                entries[count].id = i;
                // the team in each arm, the no-lord arm counts on its own (a shared count: one pointer for the entries)
                if (DAT_GameCore::instance.gameSuspended == 1) {
                    teams[count] = DAT_GameState::instance.mapAndTime.playerTeams[i];
                    if (!MACRO_CALL_MEMBER(
                            OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(i)) {
                        entries[count].unknown4 = 0;
                        entries[count].unknown8 = 0;
                        ++count;
                        noLord[i] = 1;
                        continue;
                    }
                } else {
                    teams[count] = DAT_GameState::instance.mapAndTime.playerTeams[i];
                }
                ++count;
            }
            // no initial value: the first pick sets it (`= 0` puts a xor where the original loads the slot)
            int lowestTeam;
            for (int k = 0; k < count; ++k) {
                int found = -1;
                for (int j = 0; j < count; ++j) {
                    if (entries[j].id && (found == -1 || teams[j] < lowestTeam)) {
                        lowestTeam = teams[j];
                        found = j;
                    }
                }
                if (found < 0) {
                    break;
                }
                // the sorted ids start at index 1, as the original's do
                sorted[k + 1] = entries[found].id;
                entries[found].id = 0;
            }
            // the previous team in its own variable, set before the positions (the sort's variable: the slots move)
            int prev = 1;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            int iconY = rowY - 4;
            int markX = listX + 2;
            for (int n = 1; n < countof(DAT_GameSynchronyState::instance.finalResults.active); ++n) {
                if (n > 1) {
                    rowY += 22;
                    iconY += 22;
                    avatarX += 80;
                    markX += 80;
                }
                int const id = sorted[n];
                if (id < 1) {
                    break;
                }
                // a new team starts a new group
                // teams are stored by count, read by id - 1 as in the original (the same while players 1 to id play)
                if (teams[id - 1] > prev) {
                    prev = teams[id - 1];
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 576, avatarX, avatarY + 25);
                    avatarX += 36;
                    markX += 36;
                }
                if (noLord[id]
                    && (int)DAT_GameCore::instance.mapTimeInTicks > (int)(DAT_GameCore::instance.section1127 + 200)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 665, listX, iconY);
                }
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderPlayerAvatars)(id, avatarX, avatarY);
                // the same test again after the avatar, as the original makes it
                if (noLord[id]
                    && (int)DAT_GameCore::instance.mapTimeInTicks > (int)(DAT_GameCore::instance.section1127 + 200)) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                        markX, avatarY + 2, avatarX + 69, avatarY + 69);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 665, markX, avatarY + 2);
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameTextWithShadow,
                    DAT_TextManagerObject::ptr)(DAT_GameSynchronyState::instance.DAT_PlayerNames[id], listX + 44, rowY,
                    OpenSHC::Text::TTA_LEFT,
                    DAT_RenderingDefinedData::instance
                        .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[id]],
                    0, 18, FALSE, 0);
                // the blend strength the long way round, as the original computes it
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, id + 469,
                    listX + 20, iconY, (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
