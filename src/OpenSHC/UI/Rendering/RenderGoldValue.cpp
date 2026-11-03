#include "../Rendering.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"

#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

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
            = DAT_GMImageHeaders::instance.imh[GMTotalPicturesProcessed::instance[DE::SHCDE::GM_INTERFACE_ICONS2] + 123]
                  .width;

        int goldDigitSet = 0;
        if (gold > 999) {
            goldDigitSet = 2;
        }
        int goldColor;
        if (gold > 0) {
            goldColor = 0x7d3e;
        } else {
            gold = 0;
            goldColor = 0xff;
        }
        goldDigitSet = goldDigitSet + 1;
        int goldWidth = MACRO_CALL_MEMBER(Text::TextManager_Func::calcRenderedNumberWidth, DAT_TextManagerObject::ptr)(
            gold, goldDigitSet);
        if (gold >= 100000) {
            goldWidth = goldWidth - 2;
        }
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(gold,
            DAT_MenuHandlerState::instance.x - goldWidth + 743, DAT_MenuHandlerState::instance.y + 537, 5, goldColor,
            goldDigitSet, FALSE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(gold,
            DAT_MenuHandlerState::instance.x - goldWidth + 743, DAT_MenuHandlerState::instance.y + 537, 4, goldColor,
            goldDigitSet, TRUE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(gold,
            DAT_MenuHandlerState::instance.x - goldWidth + 743, DAT_MenuHandlerState::instance.y + 537, 3, goldColor,
            goldDigitSet, TRUE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(gold,
            DAT_MenuHandlerState::instance.x - goldWidth + 743, DAT_MenuHandlerState::instance.y + 537, 2, goldColor,
            goldDigitSet, TRUE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(gold,
            DAT_MenuHandlerState::instance.x - goldWidth + 743, DAT_MenuHandlerState::instance.y + 537, 1, goldColor,
            goldDigitSet, TRUE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(gold,
            DAT_MenuHandlerState::instance.x - goldWidth + 743, DAT_MenuHandlerState::instance.y + 537, 0, goldColor,
            goldDigitSet, TRUE);

        int populationDigitSetUnk = 0;
        int populationColor = DAT_GameState::instance.playerDataArray[playerID].crowding <= 100 ? 0x7d3e : 0xff;
        if (populationCap == 0) {
            populationColor = 0x7d3e;
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
        int const populationWidth = MACRO_CALL_MEMBER(Text::TextManager_Func::calcRenderedNumberWidth,
            DAT_TextManagerObject::ptr)(population, populationDigitSet);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(population,
            DAT_MenuHandlerState::instance.x - populationWidth + 729, DAT_MenuHandlerState::instance.y + 552, 2,
            populationColor, populationDigitSet, FALSE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(population,
            DAT_MenuHandlerState::instance.x - populationWidth + 729, DAT_MenuHandlerState::instance.y + 552, 1,
            populationColor, populationDigitSet, TRUE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(population,
            DAT_MenuHandlerState::instance.x - populationWidth + 729, DAT_MenuHandlerState::instance.y + 552, 0,
            populationColor, populationDigitSet, TRUE);
        // the "/" between the population and the cap
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(population,
            DAT_MenuHandlerState::instance.x + 729, DAT_MenuHandlerState::instance.y + 552, -1, populationColor,
            populationDigitSet, FALSE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(populationCap,
            DAT_MenuHandlerState::instance.x + 727 + populationDigitSetUnk, DAT_MenuHandlerState::instance.y + 552, 2,
            populationColor, populationDigitSet, TRUE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(populationCap,
            DAT_MenuHandlerState::instance.x + 727 + populationDigitSetUnk, DAT_MenuHandlerState::instance.y + 552, 1,
            populationColor, populationDigitSet, TRUE);
        MACRO_CALL_MEMBER(Text::TextManager_Func::renderPartOfNumberUnk, DAT_TextManagerObject::ptr)(populationCap,
            DAT_MenuHandlerState::instance.x + 727 + populationDigitSetUnk, DAT_MenuHandlerState::instance.y + 552, 0,
            populationColor, populationDigitSet, TRUE);

        int const popularityColor = popularity < 50 ? 0xff : 0x7d3e;
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
