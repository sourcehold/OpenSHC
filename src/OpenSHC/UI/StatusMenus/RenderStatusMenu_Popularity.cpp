#include "../StatusMenus.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_PopularityMessageLayout.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0043E6C0
    void StatusMenus::RenderStatusMenu_Popularity()
    {
        // the rows of the active events, in counting order: carnival, marriage, jester, plague, lions, bandits, fire
        // (seven locals lose the match: the original keeps them side by side in its frame)
        int eventRows[7];
        // the active events: how many, and the row of the list each one is shown in
        int activeEvents = 0;
        int nextRow = 0;
        // the gold and the title's place are read before the draw-buffer store, as the original does (read where
        // they are used, they lose the match)
        int const gold = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                             .currentResources[OpenSHC::Game::Resources::RT_GOLD];
        int const titleY = DAT_MenuHandlerState::instance.y + 467;
        int const titleX = DAT_MenuHandlerState::instance.x + 25;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        // "Popularity"
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORTS, 1),
            titleX, titleY, OpenSHC::Text::TTA_LEFT, 0, 17, FALSE, 0);
        BOOLEnum const carnival
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .areCarnivalUnitsPresent;
        if (carnival) {
            ++activeEvents;
            eventRows[0] = nextRow++;
        }
        short const marriage
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .currentMarriageBoost;
        if (marriage != 0) {
            ++activeEvents;
            eventRows[1] = nextRow++;
        }
        short const jester
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .currentJesterBoost;
        if (jester != 0) {
            ++activeEvents;
            eventRows[2] = nextRow++;
        }
        short const plague
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .currentPlaguePenalty;
        if (plague != 0) {
            ++activeEvents;
            eventRows[3] = nextRow++;
        }
        short const lions
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .currentLionsPenalty;
        if (lions != 0) {
            ++activeEvents;
            eventRows[4] = nextRow++;
        }
        short const bandits
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .currentBanditsPenalty;
        if (bandits != 0) {
            ++activeEvents;
            eventRows[5] = nextRow++;
        }
        short const fire = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                               .currentFirePenalty;
        if (fire != 0) {
            ++activeEvents;
            eventRows[6] = nextRow++;
        }
        if (activeEvents > 2) {
            DAT_GameCore::instance.popularityMessagePageCount = 2;
        } else {
            DAT_GameCore::instance.popularityMessagePageCount = 1;
        }
        if (DAT_GameCore::instance.popularityMessagePage >= DAT_GameCore::instance.popularityMessagePageCount) {
            DAT_GameCore::instance.popularityMessagePage = 0;
        }
        int total = fire + bandits + lions + plague + jester + marriage;
        if (carnival) {
            total += 400;
        }
        if (DAT_GameCore::instance.popularityMessagePage == 0) {
            // "Food"
            // the text's y and x go through locals, y first, as the original reads them (inline loses the match)
            int const textY = DAT_MenuHandlerState::instance.y + 475;
            int const textX = DAT_MenuHandlerState::instance.x + 193;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORTS, 5),
                textX, textY, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        }
        // the food: none for an empty castle, -200 with nothing in stock, else by the rations, plus the variety
        int foodValue;
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .currentPopulation
            == 0) {
            foodValue = 0;
        } else if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                       .foodTypesInStock
            == 0) {
            foodValue = -200;
        } else {
            int const rations
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .rationsSetting;
            // one compare per value, as the original ((rations - 2) * 100 loses the match)
            if (rations == 4) {
                foodValue = 200;
            } else if (rations == 3) {
                foodValue = 100;
            } else if (rations == 2) {
                foodValue = 0;
            } else if (rations == 1) {
                foodValue = -100;
            } else if (rations == 0) {
                foodValue = -200;
            } else {
                // fixme: the original reads the fire row (indeterminate unless a fire is active) for a rations
                // value outside 0 to 4
                foodValue = eventRows[6];
            }
        }
        int const foodTypesEaten
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .foodTypesCurrentlyEaten;
        if (foodTypesEaten != 0 && foodTypesEaten != 1) {
            if (foodTypesEaten == 2) {
                foodValue += 25;
            } else if (foodTypesEaten == 3) {
                foodValue += 50;
            } else if (foodTypesEaten == 4) {
                foodValue += 75;
            }
        }
        if (DAT_GameCore::instance.popularityMessagePage == 0) {
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_MenuHandlerState::instance.x + 171, DAT_MenuHandlerState::instance.y + 474, foodValue, FALSE);
        }
        total += foodValue;
        if (DAT_GameCore::instance.popularityMessagePage == 0) {
            // "Tax"
            int const textY = DAT_MenuHandlerState::instance.y + 499;
            int const textX = DAT_MenuHandlerState::instance.x + 193;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORTS, 6),
                textX, textY, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        }
        // the taxes: a bribe the empty treasury cannot pay counts as no taxes (+25), else by the tax rate
        int taxValue;
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .currentPopulation
            == 0) {
            taxValue = 0;
        } else if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                       .taxesSliderUI
                < 3
            && gold <= 0) {
            taxValue = 25;
        } else {
            int const taxes
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .taxesSetting;
            // one compare per value, as the original (a switch loses the match)
            if (taxes == 0) {
                taxValue = 175;
            } else if (taxes == 1) {
                taxValue = 125;
            } else if (taxes == 2) {
                taxValue = 75;
            } else if (taxes == 3) {
                taxValue = 25;
            } else if (taxes == 4) {
                // the rates from 4 on cost popularity
                taxValue = -50;
            } else if (taxes == 5) {
                taxValue = -100;
            } else if (taxes == 6) {
                taxValue = -150;
            } else if (taxes == 7) {
                taxValue = -200;
            } else if (taxes == 8) {
                taxValue = -300;
            } else if (taxes == 9) {
                taxValue = -400;
            } else if (taxes == 10) {
                taxValue = -500;
            } else {
                taxValue = -600;
            }
        }
        if (DAT_GameCore::instance.popularityMessagePage == 0) {
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_MenuHandlerState::instance.x + 171, DAT_MenuHandlerState::instance.y + 498, taxValue, FALSE);
        }
        total += taxValue;
        if (DAT_GameCore::instance.popularityMessagePage == 0) {
            // "Crowding"
            int const textY = DAT_MenuHandlerState::instance.y + 523;
            int const textX = DAT_MenuHandlerState::instance.x + 193;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORTS, 7),
                textX, textY, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        }
        // crowding: from 101% of the housing on, down in steps of 50
        int crowdingValue;
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .currentPopulation
            == 0) {
            crowdingValue = 0;
        } else {
            int const crowding
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .crowding;
            if (crowding <= 100) {
                crowdingValue = 0;
            } else if (crowding <= 120) {
                crowdingValue = -50;
            } else if (crowding <= 140) {
                crowdingValue = -100;
            } else if (crowding <= 160) {
                crowdingValue = -150;
            } else if (crowding <= 180) {
                crowdingValue = -200;
            } else {
                crowdingValue = -250;
            }
        }
        if (DAT_GameCore::instance.popularityMessagePage == 0) {
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_MenuHandlerState::instance.x + 171, DAT_MenuHandlerState::instance.y + 522, crowdingValue, FALSE);
        }
        total += crowdingValue;
        if (DAT_GameCore::instance.popularityMessagePage == 0) {
            // "Fear Factor"
            int const textY = DAT_MenuHandlerState::instance.y + 547;
            int const textX = DAT_MenuHandlerState::instance.x + 193;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORTS, 12),
                textX, textY, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        }
        // the fear factor: 25 per level, either way; both signs compute the effect in their own branch, as the
        // original does
        int fearValue;
        int const fear = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                             .fearFactorLevel;
        if (fear >= 1) {
            fearValue = fear * 25;
        } else if (fear <= -1) {
            fearValue = fear * 25;
        } else {
            fearValue = 0;
        }
        if (DAT_GameCore::instance.popularityMessagePage == 0) {
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_MenuHandlerState::instance.x + 171, DAT_MenuHandlerState::instance.y + 546, fearValue, FALSE);
        }
        total += fearValue;
        if (DAT_GameCore::instance.popularityMessagePage == 0) {
            // "Religion"
            int const textY = DAT_MenuHandlerState::instance.y + 475;
            int const textX = DAT_MenuHandlerState::instance.x + 355;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORTS, 10),
                textX, textY, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        }
        // religion: by the share of blessed people, plus a church and a cathedral
        int religionValue;
        int const blessedPercentage
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                  .blessedPeoplePercentage;
        if (blessedPercentage <= 24) {
            religionValue = 0;
        } else if (blessedPercentage <= 49) {
            religionValue = 50;
        } else if (blessedPercentage <= 74) {
            religionValue = 100;
        } else if (blessedPercentage <= 94) {
            religionValue = 150;
        } else {
            religionValue = 200;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].ownsChurchUnk
            != 0) {
            religionValue += 25;
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .ownsCathedralUnk
            != 0) {
            religionValue += 50;
        }
        if (DAT_GameCore::instance.popularityMessagePage == 0) {
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_MenuHandlerState::instance.x + 333, DAT_MenuHandlerState::instance.y + 474, religionValue, FALSE);
        }
        total += religionValue;
        if (DAT_GameCore::instance.popularityMessagePage == 0) {
            // "Ale coverage"
            int const textY = DAT_MenuHandlerState::instance.y + 499;
            int const textX = DAT_MenuHandlerState::instance.x + 355;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORTS, 11),
                textX, textY, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        }
        // ale: by the share of the people the inns reach
        int aleValue;
        int const aleCoverage = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeAleCoverage,
            DAT_GameState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID);
        // one compare per value, as the original (`aleCoverage / 25 * 50` loses the match)
        if (aleCoverage < 25) {
            aleValue = 0;
        } else if (aleCoverage < 50) {
            aleValue = 50;
        } else if (aleCoverage < 75) {
            aleValue = 100;
        } else if (aleCoverage < 100) {
            aleValue = 150;
        } else {
            aleValue = 200;
        }
        if (DAT_GameCore::instance.popularityMessagePage == 0) {
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_MenuHandlerState::instance.x + 333, DAT_MenuHandlerState::instance.y + 498, aleValue, FALSE);
        }
        total += aleValue;
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .areCarnivalUnitsPresent
            && DAT_PopularityMessageLayout::instance[eventRows[0]][0] == DAT_GameCore::instance.popularityMessagePage) {
            // "Fair"
            // y and x through locals, as in the titles (inline loses the match)
            int const textY = DAT_PopularityMessageLayout::instance[eventRows[0]][2] + DAT_MenuHandlerState::instance.y;
            int const textX = DAT_PopularityMessageLayout::instance[eventRows[0]][1] + DAT_MenuHandlerState::instance.x;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORTS, 9),
                textX, textY, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_PopularityMessageLayout::instance[eventRows[0]][1] - 22 + DAT_MenuHandlerState::instance.x,
                DAT_PopularityMessageLayout::instance[eventRows[0]][2] - 1 + DAT_MenuHandlerState::instance.y, 400,
                FALSE);
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentMarriageBoost
                != 0
            && DAT_PopularityMessageLayout::instance[eventRows[1]][0] == DAT_GameCore::instance.popularityMessagePage) {
            // "Marriage"
            int const textY = DAT_PopularityMessageLayout::instance[eventRows[1]][2] + DAT_MenuHandlerState::instance.y;
            int const textX = DAT_PopularityMessageLayout::instance[eventRows[1]][1] + DAT_MenuHandlerState::instance.x;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 149),
                textX, textY, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_PopularityMessageLayout::instance[eventRows[1]][1] - 22 + DAT_MenuHandlerState::instance.x,
                DAT_PopularityMessageLayout::instance[eventRows[1]][2] - 1 + DAT_MenuHandlerState::instance.y,
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentMarriageBoost,
                FALSE);
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentJesterBoost
                != 0
            && DAT_PopularityMessageLayout::instance[eventRows[2]][0] == DAT_GameCore::instance.popularityMessagePage) {
            // "Jester"
            int const textY = DAT_PopularityMessageLayout::instance[eventRows[2]][2] + DAT_MenuHandlerState::instance.y;
            int const textX = DAT_PopularityMessageLayout::instance[eventRows[2]][1] + DAT_MenuHandlerState::instance.x;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 150),
                textX, textY, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_PopularityMessageLayout::instance[eventRows[2]][1] - 22 + DAT_MenuHandlerState::instance.x,
                DAT_PopularityMessageLayout::instance[eventRows[2]][2] - 1 + DAT_MenuHandlerState::instance.y,
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentJesterBoost,
                FALSE);
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentPlaguePenalty
                != 0
            && DAT_PopularityMessageLayout::instance[eventRows[3]][0] == DAT_GameCore::instance.popularityMessagePage) {
            // "Plague"
            int const textY = DAT_PopularityMessageLayout::instance[eventRows[3]][2] + DAT_MenuHandlerState::instance.y;
            int const textX = DAT_PopularityMessageLayout::instance[eventRows[3]][1] + DAT_MenuHandlerState::instance.x;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 139),
                textX, textY, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_PopularityMessageLayout::instance[eventRows[3]][1] - 22 + DAT_MenuHandlerState::instance.x,
                DAT_PopularityMessageLayout::instance[eventRows[3]][2] - 1 + DAT_MenuHandlerState::instance.y,
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentPlaguePenalty,
                FALSE);
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentLionsPenalty
                != 0
            && DAT_PopularityMessageLayout::instance[eventRows[4]][0] == DAT_GameCore::instance.popularityMessagePage) {
            // "Lion Attack"
            int const textY = DAT_PopularityMessageLayout::instance[eventRows[4]][2] + DAT_MenuHandlerState::instance.y;
            int const textX = DAT_PopularityMessageLayout::instance[eventRows[4]][1] + DAT_MenuHandlerState::instance.x;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 145),
                textX, textY, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_PopularityMessageLayout::instance[eventRows[4]][1] - 22 + DAT_MenuHandlerState::instance.x,
                DAT_PopularityMessageLayout::instance[eventRows[4]][2] - 1 + DAT_MenuHandlerState::instance.y,
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentLionsPenalty,
                FALSE);
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentBanditsPenalty
                != 0
            && DAT_PopularityMessageLayout::instance[eventRows[5]][0] == DAT_GameCore::instance.popularityMessagePage) {
            // "Bandits"
            int const textY = DAT_PopularityMessageLayout::instance[eventRows[5]][2] + DAT_MenuHandlerState::instance.y;
            int const textX = DAT_PopularityMessageLayout::instance[eventRows[5]][1] + DAT_MenuHandlerState::instance.x;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 146),
                textX, textY, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_PopularityMessageLayout::instance[eventRows[5]][1] - 22 + DAT_MenuHandlerState::instance.x,
                DAT_PopularityMessageLayout::instance[eventRows[5]][2] - 1 + DAT_MenuHandlerState::instance.y,
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentBanditsPenalty,
                FALSE);
        }
        if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentFirePenalty
                != 0
            && DAT_PopularityMessageLayout::instance[eventRows[6]][0] == DAT_GameCore::instance.popularityMessagePage) {
            // "Fire!"
            int const textY = DAT_PopularityMessageLayout::instance[eventRows[6]][2] + DAT_MenuHandlerState::instance.y;
            int const textX = DAT_PopularityMessageLayout::instance[eventRows[6]][1] + DAT_MenuHandlerState::instance.x;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 179),
                textX, textY, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
            MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
                DAT_PopularityMessageLayout::instance[eventRows[6]][1] - 22 + DAT_MenuHandlerState::instance.x,
                DAT_PopularityMessageLayout::instance[eventRows[6]][2] - 1 + DAT_MenuHandlerState::instance.y,
                DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .currentFirePenalty,
                FALSE);
        }
        // "In the coming month"
        int const monthY = DAT_MenuHandlerState::instance.y + 577;
        int const monthX = DAT_MenuHandlerState::instance.x + 220;
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_REPORTS, 4),
            monthX, monthY, OpenSHC::Text::TTA_LEFT, 0, 18, FALSE, 0);
        MACRO_CALL(OpenSHC::UI::Rendering_Func::TransformAndRenderPercentage)(
            DAT_TextManagerObject::instance.currentXOffset_0x0 + 250 + DAT_MenuHandlerState::instance.x,
            DAT_MenuHandlerState::instance.y + 577, total, TRUE);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
    }

}
}
