#include "../Rendering.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/GreatestLord.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/DAT_00eb9af8.hpp"
#include "OpenSHC/Globals/DAT_00ec082c.hpp"
#include "OpenSHC/Globals/DAT_00ed3118.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_FinalResultsOrderByColumn.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00eb0e44.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::IO::Graphics::GmID;
    using OpenSHC::Rendering::ScreenResolutionEnum;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // The tables behind the Greatest Lord screen, one entry per player slot (index 0 unused). The original keeps them
    // in one block of the stack frame, and its statistic orders are filled by one strided loop, so they are one
    // struct here rather than separate arrays.
    struct GreatestLordTablesUnk {
        int points[9];
        int stars[9];
        int overallOrder[9];
        int kills[9];
        int losses[9];
        // Player order per statistic, best first: 0 kills, 1 buildings burned, 2 food, 3 gold, 4 max population,
        // 5 wood, 6 stone, 7 iron, 8 pitch, 9 unused, 10 losses, 11 weapons, 12 buildings lost, 13 troops,
        // 14 goods received, 15 goods sent.
        int statOrder[16][9];
    };

    // FUNCTION: STRONGHOLDCRUSADER 0x004D5810
    void Rendering::RenderGreatestLordScreen()
    {
        int y;
        int columnOffset;
        int index;
        int x;
        GreatestLordTablesUnk tables;
        char saveText[100];
        char scoreText[100];
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
            x = DAT_MenuHandlerState::instance.x + 10;
            columnOffset = 58;
        } else {
            x = DAT_MenuHandlerState::instance.x - 102;
            columnOffset = 522;
        }
        y = DAT_MenuHandlerState::instance.y;

        for (int player = 1; player < 9; ++player) {
            tables.points[player] = 0;
        }
        for (int player = 1; player < 9; ++player) {
            int kills = 0;
            for (int victim = 1; victim < 9; ++victim) {
                if (victim != player) {
                    kills = kills + DAT_GameSynchronyState::instance.finalResults.finalKillMatrix[player][victim];
                }
            }
            tables.kills[player] = kills;
            int losses = 0;
            for (int killer = 0; killer < 9; ++killer) {
                if (killer != player) {
                    losses = losses + DAT_GameSynchronyState::instance.finalResults.finalKillMatrix[killer][player];
                }
            }
            tables.losses[player] = losses;
        }
        for (int player = 1; player < 9; ++player) {
            tables.stars[player] = 0;
        }
        for (int player = 1; player < 9; ++player) {
            tables.overallOrder[player] = player;
            for (int stat = 0; stat < 16; ++stat) {
                tables.statOrder[stat][player] = player;
            }
        }

        // bubble sort every order at once; index is the pass here and the rank further down
        for (index = 8; index > 0; --index) {
            for (int i = 1; i < index; ++i) {
                int const first = tables.overallOrder[i];
                int const firstScore = MACRO_CALL(OpenSHC::UI::GreatestLord_Func::ComputeSkMasterScore)(first);
                int const second = tables.overallOrder[i + 1];
                int const secondScore = MACRO_CALL(OpenSHC::UI::GreatestLord_Func::ComputeSkMasterScore)(second);
                if (firstScore < secondScore
                    || firstScore == secondScore
                        && (DAT_GameSynchronyState::instance.finalResults.finalTimeAlive[first]
                                < DAT_GameSynchronyState::instance.finalResults.finalTimeAlive[second]
                            || DAT_GameSynchronyState::instance.finalResults.finalTimeAlive[first]
                                    == DAT_GameSynchronyState::instance.finalResults.finalTimeAlive[second]
                                && DAT_GameState::instance.mapAndTime.playerIsAlive[first]
                                    < DAT_GameState::instance.mapAndTime.playerIsAlive[second])) {
                    tables.overallOrder[i] = second;
                    tables.overallOrder[i + 1] = first;
                }

                int current = tables.statOrder[0][i];
                if (tables.kills[current] < tables.kills[tables.statOrder[0][i + 1]]) {
                    tables.statOrder[0][i] = tables.statOrder[0][i + 1];
                    tables.statOrder[0][i + 1] = current;
                }
                current = tables.statOrder[10][i];
                if (tables.losses[tables.statOrder[10][i + 1]] < tables.losses[current]) {
                    tables.statOrder[10][i] = tables.statOrder[10][i + 1];
                    tables.statOrder[10][i + 1] = current;
                }
                current = tables.statOrder[1][i];
                if (DAT_GameSynchronyState::instance.finalResults.finalBuildingsBurned[current]
                    < DAT_GameSynchronyState::instance.finalResults.finalBuildingsBurned[tables.statOrder[1][i + 1]]) {
                    tables.statOrder[1][i] = tables.statOrder[1][i + 1];
                    tables.statOrder[1][i + 1] = current;
                }
                current = tables.statOrder[2][i];
                if (DAT_GameSynchronyState::instance.finalResults.finalFoodProduced[current]
                    < DAT_GameSynchronyState::instance.finalResults.finalFoodProduced[tables.statOrder[2][i + 1]]) {
                    tables.statOrder[2][i] = tables.statOrder[2][i + 1];
                    tables.statOrder[2][i + 1] = current;
                }
                current = tables.statOrder[3][i];
                if (DAT_GameSynchronyState::instance.finalResults.finalGold[current]
                    < DAT_GameSynchronyState::instance.finalResults.finalGold[tables.statOrder[3][i + 1]]) {
                    tables.statOrder[3][i] = tables.statOrder[3][i + 1];
                    tables.statOrder[3][i + 1] = current;
                }
                current = tables.statOrder[4][i];
                if (DAT_GameSynchronyState::instance.finalResults.finalMaxPopulation[current]
                    < DAT_GameSynchronyState::instance.finalResults.finalMaxPopulation[tables.statOrder[4][i + 1]]) {
                    tables.statOrder[4][i] = tables.statOrder[4][i + 1];
                    tables.statOrder[4][i + 1] = current;
                }
                current = tables.statOrder[5][i];
                if (DAT_GameSynchronyState::instance.finalResults.finalWoodProduced[current]
                    < DAT_GameSynchronyState::instance.finalResults.finalWoodProduced[tables.statOrder[5][i + 1]]) {
                    tables.statOrder[5][i] = tables.statOrder[5][i + 1];
                    tables.statOrder[5][i + 1] = current;
                }
                current = tables.statOrder[6][i];
                if (DAT_GameSynchronyState::instance.finalResults.finalStoneProduced[current]
                    < DAT_GameSynchronyState::instance.finalResults.finalStoneProduced[tables.statOrder[6][i + 1]]) {
                    tables.statOrder[6][i] = tables.statOrder[6][i + 1];
                    tables.statOrder[6][i + 1] = current;
                }
                current = tables.statOrder[7][i];
                if (DAT_GameSynchronyState::instance.finalResults.finalIronProduced[current]
                    < DAT_GameSynchronyState::instance.finalResults.finalIronProduced[tables.statOrder[7][i + 1]]) {
                    tables.statOrder[7][i] = tables.statOrder[7][i + 1];
                    tables.statOrder[7][i + 1] = current;
                }
                current = tables.statOrder[8][i];
                if (DAT_GameSynchronyState::instance.finalResults.finalPitchProduced[current]
                    < DAT_GameSynchronyState::instance.finalResults.finalPitchProduced[tables.statOrder[8][i + 1]]) {
                    tables.statOrder[8][i] = tables.statOrder[8][i + 1];
                    tables.statOrder[8][i + 1] = current;
                }
                current = tables.statOrder[11][i];
                if (DAT_GameSynchronyState::instance.finalResults.finalWeaponsProduced[current]
                    < DAT_GameSynchronyState::instance.finalResults.finalWeaponsProduced[tables.statOrder[11][i + 1]]) {
                    tables.statOrder[11][i] = tables.statOrder[11][i + 1];
                    tables.statOrder[11][i + 1] = current;
                }
                current = tables.statOrder[12][i];
                if (DAT_GameSynchronyState::instance.finalResults.finalBuidingsDestroyed[tables.statOrder[12][i + 1]]
                    < DAT_GameSynchronyState::instance.finalResults.finalBuidingsDestroyed[current]) {
                    tables.statOrder[12][i] = tables.statOrder[12][i + 1];
                    tables.statOrder[12][i + 1] = current;
                }
                current = tables.statOrder[13][i];
                if (DAT_GameSynchronyState::instance.finalResults.finalTroopsProduced[current]
                    < DAT_GameSynchronyState::instance.finalResults.finalTroopsProduced[tables.statOrder[13][i + 1]]) {
                    tables.statOrder[13][i] = tables.statOrder[13][i + 1];
                    tables.statOrder[13][i + 1] = current;
                }
                current = tables.statOrder[14][i];
                if (DAT_GameSynchronyState::instance.finalResults.finalGoodsRecieved[current]
                    < DAT_GameSynchronyState::instance.finalResults.finalGoodsRecieved[tables.statOrder[14][i + 1]]) {
                    tables.statOrder[14][i] = tables.statOrder[14][i + 1];
                    tables.statOrder[14][i + 1] = current;
                }
                current = tables.statOrder[15][i];
                if (DAT_GameSynchronyState::instance.finalResults.finalGoodsSent[current]
                    < DAT_GameSynchronyState::instance.finalResults.finalGoodsSent[tables.statOrder[15][i + 1]]) {
                    tables.statOrder[15][i] = tables.statOrder[15][i + 1];
                    tables.statOrder[15][i + 1] = current;
                }
            }
        }

        // bonus points for the winner and for a clear lead in a statistic
        tables.points[tables.overallOrder[1]] = tables.points[tables.overallOrder[1]] + 3;
        if (tables.kills[tables.statOrder[0][1]] > 10
            && tables.kills[tables.statOrder[0][1]] > tables.kills[tables.statOrder[0][2]] * 2) {
            tables.points[tables.statOrder[0][1]] = tables.points[tables.statOrder[0][1]] + 3;
        }
        int value = DAT_GameSynchronyState::instance.finalResults.finalBuildingsBurned[tables.statOrder[1][1]];
        if (value > 2
            && value > DAT_GameSynchronyState::instance.finalResults.finalBuildingsBurned[tables.statOrder[1][2]] * 2) {
            tables.points[tables.statOrder[1][1]] = tables.points[tables.statOrder[1][1]] + 2;
        }
        value = DAT_GameSynchronyState::instance.finalResults.finalFoodProduced[tables.statOrder[2][1]];
        if (value > 50
            && value > DAT_GameSynchronyState::instance.finalResults.finalFoodProduced[tables.statOrder[2][2]] * 2) {
            tables.points[tables.statOrder[2][1]] = tables.points[tables.statOrder[2][1]] + 2;
        }
        value = DAT_GameSynchronyState::instance.finalResults.finalGold[tables.statOrder[3][1]];
        if (value > 100
            && value > DAT_GameSynchronyState::instance.finalResults.finalGold[tables.statOrder[3][2]] * 2) {
            tables.points[tables.statOrder[3][1]] = tables.points[tables.statOrder[3][1]] + 3;
        }
        short const maxPopulation
            = DAT_GameSynchronyState::instance.finalResults.finalMaxPopulation[tables.statOrder[4][1]];
        if (maxPopulation > 24
            && maxPopulation
                > DAT_GameSynchronyState::instance.finalResults.finalMaxPopulation[tables.statOrder[4][2]] * 2) {
            // fixme: the original gives the population point to the player with the most kills
            tables.points[tables.statOrder[0][1]] = tables.points[tables.statOrder[0][1]] + 1;
        }
        value = DAT_GameSynchronyState::instance.finalResults.finalWoodProduced[tables.statOrder[5][1]];
        if (value > 100
            && value > DAT_GameSynchronyState::instance.finalResults.finalWoodProduced[tables.statOrder[5][2]] * 2) {
            tables.points[tables.statOrder[5][1]] = tables.points[tables.statOrder[5][1]] + 1;
        }
        value = DAT_GameSynchronyState::instance.finalResults.finalStoneProduced[tables.statOrder[6][1]];
        if (value > 50
            && value > DAT_GameSynchronyState::instance.finalResults.finalStoneProduced[tables.statOrder[6][2]] * 2) {
            tables.points[tables.statOrder[6][1]] = tables.points[tables.statOrder[6][1]] + 1;
        }
        value = DAT_GameSynchronyState::instance.finalResults.finalIronProduced[tables.statOrder[7][1]];
        if (value > 10
            && value > DAT_GameSynchronyState::instance.finalResults.finalIronProduced[tables.statOrder[7][2]] * 2) {
            tables.points[tables.statOrder[7][1]] = tables.points[tables.statOrder[7][1]] + 1;
        }
        value = DAT_GameSynchronyState::instance.finalResults.finalPitchProduced[tables.statOrder[8][1]];
        if (value > 20
            && value > DAT_GameSynchronyState::instance.finalResults.finalPitchProduced[tables.statOrder[8][2]] * 2) {
            tables.points[tables.statOrder[8][1]] = tables.points[tables.statOrder[8][1]] + 1;
        }
        value = DAT_GameSynchronyState::instance.finalResults.finalWeaponsProduced[tables.statOrder[11][1]];
        if (value > 20
            && value
                > DAT_GameSynchronyState::instance.finalResults.finalWeaponsProduced[tables.statOrder[11][2]] * 2) {
            tables.points[tables.statOrder[11][1]] = tables.points[tables.statOrder[11][1]] + 1;
        }

        // three points per star, at most five, and at most four unless player slot 1 took part
        int starLimitUnk = 0;
        if (DAT_GameSynchronyState::instance.finalResults.active[1]) {
            starLimitUnk = 8;
        }
        for (int player = 1; player < 9; ++player) {
            tables.stars[player] = tables.points[player] / 3;
            if (tables.points[player] / 3 > 5) {
                tables.stars[player] = 5;
            }
            if (starLimitUnk < 4 && tables.stars[player] == 5) {
                tables.stars[player] = 4;
            }
        }

        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                DAT_PencilRenderCore::ptr)(DAT_MenuHandlerState::instance.x, DAT_MenuHandlerState::instance.y,
                DAT_MenuHandlerState::instance.x + 800, DAT_MenuHandlerState::instance.y + 600, 16);
            // "Greatest Lord"
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(225, 1, DAT_MenuHandlerState::instance.x + 40, y, 720, 720);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                DAT_PencilRenderCore::ptr)(DAT_MenuHandlerState::instance.x - 112,
                DAT_MenuHandlerState::instance.y - 84, DAT_MenuHandlerState::instance.x + 912,
                DAT_MenuHandlerState::instance.y + 684, 16);
            // "Greatest Lord"
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(225, 1, DAT_MenuHandlerState::instance.x - 104, y - 30, 1008, 0);
            y = y + 20;
        }
        y = y + 190;
        int iconY = y - 18;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        int player;
        for (index = 0; index < 8; ++index) {
            switch (DAT_FinalResultsOrderByColumn::instance) {
            case 0:
                player = tables.overallOrder[index + 1];
                break;
            case 1:
                player = tables.statOrder[0][index + 1];
                break;
            case 2:
                player = tables.statOrder[1][index + 1];
                break;
            case 3:
                player = tables.statOrder[10][index + 1];
                break;
            case 4:
                player = tables.statOrder[3][index + 1];
                break;
            case 5:
                player = tables.statOrder[2][index + 1];
                break;
            case 6:
                player = tables.statOrder[5][index + 1];
                break;
            case 7:
                player = tables.statOrder[6][index + 1];
                break;
            case 8:
                player = tables.statOrder[7][index + 1];
                break;
            case 9:
                player = tables.statOrder[8][index + 1];
                break;
            case 10:
                player = tables.statOrder[4][index + 1];
                break;
            case 11:
                player = tables.statOrder[11][index + 1];
                break;
            case 12:
                player = tables.statOrder[12][index + 1];
                break;
            case 13:
                player = tables.statOrder[13][index + 1];
                break;
            case 14:
                player = tables.statOrder[14][index + 1];
                break;
            case 15:
                player = tables.statOrder[15][index + 1];
                break;
            }
            if (!DAT_GameSynchronyState::instance.finalResults.active[player]) {
                continue;
            }
            char* const name = DAT_GameSynchronyState::instance.finalResults.names[player];
            DAT_TextManagerObject::instance.field12_0x30 = 1;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
                name, x, y, 260,
                DAT_RenderingDefinedData::instance
                    .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[player]],
                0, 18, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(name, 18);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            int iconX = x;
            if (DAT_GameState::instance.mapAndTime.playerIsAlive[player] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 139, x, iconY - 2);
                iconX = x + 22;
            }
            for (int star = 0; star < tables.stars[player]; ++star) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 139, iconX, iconY - 2);
                iconX = iconX + 22;
            }
            for (int lord = 0; lord < DAT_GameSynchronyState::instance.finalResults.finalKilledLords[player]; ++lord) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 138, iconX, iconY - 5);
                iconX = iconX + 22;
            }
            if (DAT_GameSynchronyState::instance.finalResults.finalDateOfDeathInMonths[player] != 0) {
                // "("
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    s_brace_close_005a2778, iconX + 8, iconY, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 19, FALSE, 0);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 665, iconX + 14, iconY - 5);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MONTHS,
                        DAT_GameSynchronyState::instance.finalResults.finalDateOfDeathInMonths[player] % 12),
                    iconX + 28, iconY, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 19, FALSE, 0);
                iconX = iconX + 32;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.finalResults.finalDateOfDeathInMonths[player] / 12, iconX, iconY,
                    OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 19, TRUE, 0);
                // ")"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    s_brace_open_005a2774, iconX, iconY, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 19, TRUE, 0);
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            if (DAT_00ec082c::instance == 0 || DAT_00ec082c::instance == 2) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    tables.kills[player], x + 279, y, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    tables.losses[player], x + 337, y, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.finalResults.finalGold[player], x + 395, y,
                    OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.finalResults.finalFoodProduced[player], x + 453, y,
                    OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.finalResults.finalWoodProduced[player], x + 511, y,
                    OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.finalResults.finalStoneProduced[player], x + 569, y,
                    OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.finalResults.finalIronProduced[player], x + 627, y,
                    OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.finalResults.finalPitchProduced[player], x + 685, y,
                    OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.finalResults.finalWeaponsProduced[player], x + 743, y,
                    OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 18, FALSE, 0);
            }
            if (DAT_00ec082c::instance == 1 || DAT_00ec082c::instance == 2) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.finalResults.finalMaxPopulation[player], columnOffset + 279 + x, y,
                    OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 18, FALSE, 0);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                    DAT_GameSynchronyState::instance.finalResults.finalMaxGoodThings[player] * 6
                        - DAT_GameSynchronyState::instance.finalResults.finalMaxBadThings[player] + 140,
                    columnOffset + 330 + x, y, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 176, 0);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.finalResults.finalBuildingsBurned[player], columnOffset + 395 + x,
                    y, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.finalResults.finalBuidingsDestroyed[player],
                    columnOffset + 453 + x, y, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 18, FALSE, 0);
                if (DAT_00ec082c::instance == 1) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.finalResults.finalTroopsProduced[player],
                        columnOffset + 511 + x, y, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 18, FALSE, 0);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.finalResults.finalGoodsRecieved[player],
                        columnOffset + 569 + x, y, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 18, FALSE, 0);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.finalResults.finalGoodsSent[player], columnOffset + 627 + x, y,
                        OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 18, FALSE, 0);
                }
            }
            if (DAT_00ec082c::instance == 3) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.finalResults.finalTroopsProduced[player], x + 511, y,
                    OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.finalResults.finalGoodsRecieved[player], x + 569, y,
                    OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 18, FALSE, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.finalResults.finalGoodsSent[player], x + 627, y,
                    OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 18, FALSE, 0);
            }
            y = y + 45;
            iconY = iconY + 45;
        }

        if ((char)INT_00eb0e44::instance == '\0') {
            if (DAT_00eb9af8::instance == 0 && DAT_GameSynchronyState::instance.finalResults.yearStart != 0) {
                // fixme: the original writes the date into the (no longer needed) statistic orders
                char* const dateText = (char*)tables.statOrder[0];
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(dateText, s__s__d____s__d_005aaf3c,
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MONTHS, DAT_GameSynchronyState::instance.finalResults.monthStart),
                    DAT_GameSynchronyState::instance.finalResults.yearStart,
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MONTHS, DAT_GameSynchronyState::instance.finalResults.monthEnd),
                    DAT_GameSynchronyState::instance.finalResults.yearEnd);
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((eTextSections)DAT_MissionDefinedData::instance
                                                            .GreatestLordTextEntries[DAT_00eb9af8::instance][0],
                            DAT_MissionDefinedData::instance.GreatestLordTextEntries[DAT_00eb9af8::instance][1]),
                        DAT_MenuHandlerState::instance.x + 457, DAT_MenuHandlerState::instance.y + 545,
                        OpenSHC::Text::TTA_CENTER, 0xccfaff, 17, FALSE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        dateText, DAT_MenuHandlerState::instance.x + 457, DAT_MenuHandlerState::instance.y + 575,
                        OpenSHC::Text::TTA_CENTER, 0xccfaff, 18, FALSE, 0);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)((eTextSections)DAT_MissionDefinedData::instance
                                                            .GreatestLordTextEntries[DAT_00eb9af8::instance][0],
                            DAT_MissionDefinedData::instance.GreatestLordTextEntries[DAT_00eb9af8::instance][1]),
                        DAT_MenuHandlerState::instance.x + 412, DAT_MenuHandlerState::instance.y + 602,
                        OpenSHC::Text::TTA_CENTER, 0xccfaff, 17, FALSE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        dateText, DAT_MenuHandlerState::instance.x + 412, DAT_MenuHandlerState::instance.y + 632,
                        OpenSHC::Text::TTA_CENTER, 0xccfaff, 18, FALSE, 0);
                }
            } else if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((eTextSections)DAT_MissionDefinedData::instance
                                                        .GreatestLordTextEntries[DAT_00eb9af8::instance][0],
                        DAT_MissionDefinedData::instance.GreatestLordTextEntries[DAT_00eb9af8::instance][1]),
                    DAT_MenuHandlerState::instance.x + 457, DAT_MenuHandlerState::instance.y + 560,
                    OpenSHC::Text::TTA_CENTER, 0xccfaff, 17, FALSE, 0);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)((eTextSections)DAT_MissionDefinedData::instance
                                                        .GreatestLordTextEntries[DAT_00eb9af8::instance][0],
                        DAT_MissionDefinedData::instance.GreatestLordTextEntries[DAT_00eb9af8::instance][1]),
                    DAT_MenuHandlerState::instance.x + 412, DAT_MenuHandlerState::instance.y + 617,
                    OpenSHC::Text::TTA_CENTER, 0xccfaff, 17, FALSE, 0);
            }
        }
        DAT_00eb9af8::instance = DAT_FinalResultsOrderByColumn::instance;
        if ((char)INT_00eb0e44::instance == '\0') {
            return;
        }

        // Extreme: show the score and the save file to submit it with
        MACRO_CALL(OpenSHC::OS_Func::_sprintf)(scoreText, s____d_005aaf2c,
            MACRO_CALL(OpenSHC::UI::GreatestLord_Func::ComputeSkMasterScore)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID));
        MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
            saveText, s____M_d_d_sav_005aaf18, DAT_GameCore::instance.extremeTrailProgress + 1, DAT_00ed3118::instance);
        int boxRight;
        int boxLeft;
        int boxTop;
        int boxBottom;
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
            // "Extreme Score"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 27),
                DAT_MenuHandlerState::instance.x + 50, DAT_MenuHandlerState::instance.y + 553, OpenSHC::Text::TTA_LEFT,
                0xccfaff, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                scoreText, DAT_MenuHandlerState::instance.x + 50, DAT_MenuHandlerState::instance.y + 553,
                OpenSHC::Text::TTA_LEFT, 0xccfaff, 18, TRUE, 0);
            // "Save File"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 28),
                DAT_MenuHandlerState::instance.x + 50, DAT_MenuHandlerState::instance.y + 553, OpenSHC::Text::TTA_LEFT,
                0xccfaff, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(saveText,
                DAT_MenuHandlerState::instance.x + 50, DAT_MenuHandlerState::instance.y + 553, OpenSHC::Text::TTA_LEFT,
                0xccfaff, 18, TRUE, 0);
            boxRight = DAT_TextManagerObject::instance.currentXOffset_0x0 + 50 + DAT_MenuHandlerState::instance.x;
            // "To submit this score, visit"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 29),
                DAT_MenuHandlerState::instance.x + 50, DAT_MenuHandlerState::instance.y + 575, OpenSHC::Text::TTA_LEFT,
                0xccfaff, 18, FALSE, 0);
            // "www.fireflyworlds.com"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 30),
                DAT_MenuHandlerState::instance.x + 56, DAT_MenuHandlerState::instance.y + 575, OpenSHC::Text::TTA_LEFT,
                0xffffff, 18, TRUE, 0);
            if (boxRight < DAT_TextManagerObject::instance.currentXOffset_0x0 + 56 + DAT_MenuHandlerState::instance.x) {
                boxRight = DAT_TextManagerObject::instance.currentXOffset_0x0 + 56 + DAT_MenuHandlerState::instance.x;
            }
            boxLeft = DAT_MenuHandlerState::instance.x + 30;
            boxTop = DAT_MenuHandlerState::instance.y + 546;
            boxBottom = DAT_MenuHandlerState::instance.y + 595;
        } else {
            // "Extreme Score"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 27),
                DAT_MenuHandlerState::instance.x - 42, DAT_MenuHandlerState::instance.y + 610, OpenSHC::Text::TTA_LEFT,
                0xccfaff, 18, FALSE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                scoreText, DAT_MenuHandlerState::instance.x - 42, DAT_MenuHandlerState::instance.y + 610,
                OpenSHC::Text::TTA_LEFT, 0xccfaff, 18, TRUE, 0);
            // "Save File"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 28),
                DAT_MenuHandlerState::instance.x - 42, DAT_MenuHandlerState::instance.y + 610, OpenSHC::Text::TTA_LEFT,
                0xccfaff, 18, TRUE, 0);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(saveText,
                DAT_MenuHandlerState::instance.x - 42, DAT_MenuHandlerState::instance.y + 610, OpenSHC::Text::TTA_LEFT,
                0xccfaff, 18, TRUE, 0);
            boxRight = DAT_TextManagerObject::instance.currentXOffset_0x0 - 42 + DAT_MenuHandlerState::instance.x;
            // "To submit this score, visit"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 29),
                DAT_MenuHandlerState::instance.x - 42, DAT_MenuHandlerState::instance.y + 632, OpenSHC::Text::TTA_LEFT,
                0xccfaff, 18, FALSE, 0);
            // "www.fireflyworlds.com"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 30),
                DAT_MenuHandlerState::instance.x - 36, DAT_MenuHandlerState::instance.y + 632, OpenSHC::Text::TTA_LEFT,
                0xffffff, 18, TRUE, 0);
            if (boxRight < DAT_TextManagerObject::instance.currentXOffset_0x0 - 36 + DAT_MenuHandlerState::instance.x) {
                boxRight = DAT_TextManagerObject::instance.currentXOffset_0x0 - 36 + DAT_MenuHandlerState::instance.x;
            }
            boxLeft = DAT_MenuHandlerState::instance.x - 62;
            boxTop = DAT_MenuHandlerState::instance.y + 603;
            boxBottom = DAT_MenuHandlerState::instance.y + 652;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
            boxLeft, boxTop, boxRight + 20, boxBottom, COL_WHITE::instance.shortValue);
    }

}
}
