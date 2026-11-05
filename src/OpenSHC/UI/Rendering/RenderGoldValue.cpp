#include "../Rendering.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x00433780
    void Rendering::RenderGoldValue()
    {
        int const playerID = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        int const popularity = DAT_GameState::instance.playerDataArray[playerID].popularity / 100;
        int const populationCap = DAT_GameState::instance.playerDataArray[playerID].populationCap;
        int population = DAT_GameState::instance.playerDataArray[playerID].currentPopulation;
        int gold = DAT_GameState::instance.playerDataArray[playerID].currentResources[Game::Resources::RT_GOLD];
        DAT_TextManagerObject::instance.currentXOffset_0x0
            = DAT_GMImageHeaders::instance.imh[GMFirstPictureIndex::instance[DE::SHCDE::GM_INTERFACE_ICONS2] + 123]
                  .width;

        int goldDigitSet = 0;
        if (gold > 999) {
            goldDigitSet = 2;
        }
        int goldColor;
        if (gold > 0) {
            goldColor = OpenSHC::Rendering::Colors::COL_007D3E;
        } else {
            gold = 0;
            goldColor = OpenSHC::Rendering::Colors::COL_0000FF;
        }
        ++goldDigitSet;
        // One width serves the gold and the population numbers: two variables swap two stack slots.
        int width = MACRO_CALL_MEMBER(Text::TextManager_Func::calcRenderedNumberWidth, DAT_TextManagerObject::ptr)(
            gold, goldDigitSet);
        if (gold >= 100000) {
            width -= 2;
        }
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(gold,
            DAT_MenuHandlerState::instance.x - width + 743, DAT_MenuHandlerState::instance.y + 537, 5, goldColor,
            goldDigitSet, FALSE);
        // Parts 4 to 0, one call each: a for loop over them compiles differently.
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(gold,
            DAT_MenuHandlerState::instance.x - width + 743, DAT_MenuHandlerState::instance.y + 537, 4, goldColor,
            goldDigitSet, TRUE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(gold,
            DAT_MenuHandlerState::instance.x - width + 743, DAT_MenuHandlerState::instance.y + 537, 3, goldColor,
            goldDigitSet, TRUE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(gold,
            DAT_MenuHandlerState::instance.x - width + 743, DAT_MenuHandlerState::instance.y + 537, 2, goldColor,
            goldDigitSet, TRUE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(gold,
            DAT_MenuHandlerState::instance.x - width + 743, DAT_MenuHandlerState::instance.y + 537, 1, goldColor,
            goldDigitSet, TRUE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(gold,
            DAT_MenuHandlerState::instance.x - width + 743, DAT_MenuHandlerState::instance.y + 537, 0, goldColor,
            goldDigitSet, TRUE);

        int populationDigitSetUnk = 0;
        int populationColor;
        if (DAT_GameState::instance.playerDataArray[playerID].crowding <= 100) {
            populationColor = OpenSHC::Rendering::Colors::COL_007D3E;
        } else {
            populationColor = OpenSHC::Rendering::Colors::COL_0000FF;
        }
        if (populationCap == 0) {
            populationColor = OpenSHC::Rendering::Colors::COL_007D3E;
            population = 0;
        } else {
            if (populationCap >= 100) {
                populationDigitSetUnk = 2;
            }
            if (population < 0) {
                population = 0;
            } else if (population >= 100) {
                populationDigitSetUnk = 2;
            }
        }
        int const populationDigitSet = populationDigitSetUnk + 1;
        width = MACRO_CALL_MEMBER(Text::TextManager_Func::calcRenderedNumberWidth, DAT_TextManagerObject::ptr)(
            population, populationDigitSet);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(population,
            DAT_MenuHandlerState::instance.x - width + 729, DAT_MenuHandlerState::instance.y + 552, 2, populationColor,
            populationDigitSet, FALSE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(population,
            DAT_MenuHandlerState::instance.x - width + 729, DAT_MenuHandlerState::instance.y + 552, 1, populationColor,
            populationDigitSet, TRUE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(population,
            DAT_MenuHandlerState::instance.x - width + 729, DAT_MenuHandlerState::instance.y + 552, 0, populationColor,
            populationDigitSet, TRUE);
        // the "/" between the population and the cap
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(population,
            DAT_MenuHandlerState::instance.x + 729, DAT_MenuHandlerState::instance.y + 552, -1, populationColor,
            populationDigitSet, FALSE);
        // The cap's parts 2 to 0, one call each: a for loop over them compiles differently.
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(populationCap,
            DAT_MenuHandlerState::instance.x + 727 + populationDigitSetUnk, DAT_MenuHandlerState::instance.y + 552, 2,
            populationColor, populationDigitSet, TRUE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(populationCap,
            DAT_MenuHandlerState::instance.x + 727 + populationDigitSetUnk, DAT_MenuHandlerState::instance.y + 552, 1,
            populationColor, populationDigitSet, TRUE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(populationCap,
            DAT_MenuHandlerState::instance.x + 727 + populationDigitSetUnk, DAT_MenuHandlerState::instance.y + 552, 0,
            populationColor, populationDigitSet, TRUE);

        int popularityColor;
        if (popularity < 50) {
            popularityColor = OpenSHC::Rendering::Colors::COL_0000FF;
        } else {
            popularityColor = OpenSHC::Rendering::Colors::COL_007D3E;
        }
        int const popularityHalfWidth = MACRO_CALL_MEMBER(Text::TextManager_Func::calcRenderedNumberWidth,
                                            DAT_TextManagerObject::ptr)(popularity, 0)
            / 2;
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(popularity,
            DAT_MenuHandlerState::instance.x - popularityHalfWidth + 747, DAT_MenuHandlerState::instance.y + 515, 2,
            popularityColor, 0, FALSE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(popularity,
            DAT_MenuHandlerState::instance.x - popularityHalfWidth + 747, DAT_MenuHandlerState::instance.y + 515, 1,
            popularityColor, 0, TRUE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(popularity,
            DAT_MenuHandlerState::instance.x - popularityHalfWidth + 747, DAT_MenuHandlerState::instance.y + 515, 0,
            popularityColor, 0, TRUE);
    }

}
}
