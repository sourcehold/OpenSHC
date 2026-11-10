#include "../BuildingMenus.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00b96120.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Audio::SFX::SpeechEffectID;
    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::IO::Graphics::GmID;
    using OpenSHC::Rendering::Colors::BGR24;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043B3B0
    void BuildingMenus::RenderBuildingMenu_Granary()
    {
        int playerID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        int iconOffsetY = 0;
        int iconOffsetX = 0;
        INT_00b96120::instance = 4;
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .timeTaxesOrRationsChange
            != 0) {
            DWORD now = timeGetTime();
            if (2000 < now - DAT_GameState::instance.playerDataArray[playerID].timeTaxesOrRationsChange) {
                int rations = DAT_GameState::instance.playerDataArray[playerID].rationsSetting3;
                if (rations == 4) {
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTaxesSetting_unknown)(2);
                } else if (rations == 0) {
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTaxesSetting_unknown)(3);
                } else {
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::SetTaxesSetting_unknown)(1);
                }
            }
            now = timeGetTime();
            if (2500 < now - DAT_GameState::instance.playerDataArray[playerID].timeTaxesOrRationsChange) {
                int rations = DAT_GameState::instance.playerDataArray[playerID].rationsSetting3;
                DAT_GameState::instance.playerDataArray[playerID].timeTaxesOrRationsChange = 0;
                SpeechEffectID speech;
                switch (rations) {
                case 0:
                    speech = OpenSHC::Audio::SFX::SEID_FOOD_NONE;
                    break;
                case 1:
                    speech = OpenSHC::Audio::SFX::SEID_FOOD_HALF;
                    break;
                case 2:
                    speech = OpenSHC::Audio::SFX::SEID_FOOD_NORMAL;
                    break;
                case 3:
                    speech = OpenSHC::Audio::SFX::SEID_FOOD_EXTRA;
                    break;
                case 4:
                    speech = OpenSHC::Audio::SFX::SEID_FOOD_DOUBLE;
                }
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(speech);
            }
        }
        // "Granary"
        int titleY = DAT_MenuHandlerState::instance.y + 467;
        int titleX = DAT_MenuHandlerState::instance.x + 25;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, 0),
            titleX, titleY, OpenSHC::Text::TTA_LEFT, 0, 16, FALSE, 0);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        int rationIcon;
        switch (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .rationsSetting3) {
        case 0:
            iconOffsetX = -1;
            rationIcon = 287;
            iconOffsetY = -5;
            break;
        case 1:
            iconOffsetX = -1;
            rationIcon = 288;
            iconOffsetY = 1;
            break;
        case 2:
            iconOffsetX = 10;
            rationIcon = 284;
            iconOffsetY = -10;
            break;
        case 4:
            iconOffsetX = 9;
            rationIcon = 286;
            iconOffsetY = -5;
            break;
        case 3:
            iconOffsetX = 0;
            rationIcon = 285;
            iconOffsetY = 0;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, rationIcon, DAT_MenuHandlerState::instance.x + 345 + iconOffsetX,
            DAT_MenuHandlerState::instance.y + 527 + iconOffsetY);
        int barY = DAT_MenuHandlerState::instance.y + 494;
        int barX = DAT_MenuHandlerState::instance.x + 23;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            OpenSHC::DE::SHCDE::GM_INTERFACE_SLIDER, 6, barX + 8, barY + 4);
        MACRO_CALL_MEMBER(
            OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRect, DAT_TextureRenderCoreObject::ptr)(0, 0,
            (DAT_GameState::instance.playerDataArray[playerID].foodClock * 162) / 15000 + 16 + barX,
            DAT_WindowAndDirectDraw::instance.resolutionY);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawTgxGmOnFlaggedSurface,
            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 8, barX + 8, barY + 4);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setRenderingRectToGameResolution,
            DAT_TextureRenderCoreObject::ptr)();
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 5, barX, barY - 1,
            OpenSHC::IO::Graphics::GID_INTERFACE_SLIDER_BAR, 7, 0);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[playerID].totalFood, DAT_MenuHandlerState::instance.x + 24,
            DAT_MenuHandlerState::instance.y + 528, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        int foodY = DAT_MenuHandlerState::instance.y + 528;
        int foodX = DAT_MenuHandlerState::instance.x + 28;
        if (DAT_GameState::instance.playerDataArray[playerID].totalFood != 1) {
            // "units of food."
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, 1),
                foodX, foodY, OpenSHC::Text::TTA_LEFT, 0, 18, TRUE, 0);
        } else {
            // "unit of food."
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, 2),
                foodX, foodY, OpenSHC::Text::TTA_LEFT, 0, 18, TRUE, 0);
        }
        int rationText = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                             .rationsSetting3;
        if (rationText == 3) {
            rationText = 12;
        } else if (rationText == 4) {
            rationText = 6;
        } else {
            rationText += 3;
        }
        int rationY = DAT_MenuHandlerState::instance.y + 465;
        int rationX = DAT_MenuHandlerState::instance.x + 540;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, rationText),
            rationX, rationY, OpenSHC::Text::TTA_RIGHT, 0, 18, FALSE, 0);
        // Popularity from the rations
        int popularity;
        if (DAT_GameState::instance.playerDataArray[playerID].currentPopulation == 0) {
            popularity = 0;
        } else if (DAT_GameState::instance.playerDataArray[playerID].foodTypesInStock == 0) {
            popularity = -200;
        } else {
            int rations = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .rationsSetting3;
            if (rations == 4) {
                popularity = 200;
            } else if (rations == 3) {
                popularity = 100;
            } else if (rations == 2) {
                popularity = 0;
            } else if (rations == 1) {
                popularity = -100;
            } else if (rations == 0) {
                popularity = -200;
            }
        }
        MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
            DAT_MenuHandlerState::instance.x + 520, DAT_MenuHandlerState::instance.y + 483, popularity, FALSE);
        int months = DAT_GameState::instance.playerDataArray[playerID].foodStorageLevel;
        if (months != -1) {
            if (months == 0) {
                int monthsY = DAT_MenuHandlerState::instance.y + 548;
                int monthsX = DAT_MenuHandlerState::instance.x + 14;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, 11),
                    monthsX, monthsY, OpenSHC::Text::TTA_LEFT, 0, 18, TRUE, 0);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    months, DAT_MenuHandlerState::instance.x + 24, DAT_MenuHandlerState::instance.y + 548,
                    OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
                int monthsY = DAT_MenuHandlerState::instance.y + 548;
                int monthsX = DAT_MenuHandlerState::instance.x + 28;
                if (DAT_GameState::instance.playerDataArray[playerID].foodStorageLevel != 1) {
                    // "months supply."
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, 9),
                        monthsX, monthsY, OpenSHC::Text::TTA_LEFT, 0, 18, TRUE, 0);
                } else {
                    // "month supply."
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, 10),
                        monthsX, monthsY, OpenSHC::Text::TTA_LEFT, 0, 18, TRUE, 0);
                }
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
            DAT_GameState::instance.playerDataArray[playerID].foodTypesCurrentlyEaten,
            DAT_MenuHandlerState::instance.x + 24, DAT_MenuHandlerState::instance.y + 568, OpenSHC::Text::TTA_LEFT, 0,
            18, FALSE, 0);
        int eatenWidth;
        if (DAT_GameState::instance.playerDataArray[playerID].foodTypesCurrentlyEaten != 1) {
            // "food types eaten."
            int eatenY = DAT_MenuHandlerState::instance.y + 568;
            int eatenX = DAT_MenuHandlerState::instance.x + 28;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, 7),
                eatenX, eatenY, OpenSHC::Text::TTA_LEFT, 0, 18, TRUE, 0);
            eatenWidth
                = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, 7),
                    18);
        } else {
            // "food type eaten."
            int eatenY = DAT_MenuHandlerState::instance.y + 568;
            int eatenX = DAT_MenuHandlerState::instance.x + 28;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, 8),
                eatenX, eatenY, OpenSHC::Text::TTA_LEFT, 0, 18, TRUE, 0);
            eatenWidth
                = MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_IN_GRANARY, 8),
                    18);
        }
        // Popularity from the food variety; more than four types keeps the rations value
        int varieties = DAT_GameState::instance.playerDataArray[playerID].foodTypesCurrentlyEaten;
        if (varieties == 0) {
            popularity = 0;
        } else if (varieties == 1) {
            popularity = 0;
        } else if (varieties == 2) {
            popularity = 25;
        } else if (varieties == 3) {
            popularity = 50;
        } else if (varieties == 4) {
            popularity = 75;
        }
        MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
            DAT_MenuHandlerState::instance.x + 60 + eatenWidth, DAT_MenuHandlerState::instance.y + 568, popularity,
            FALSE);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
