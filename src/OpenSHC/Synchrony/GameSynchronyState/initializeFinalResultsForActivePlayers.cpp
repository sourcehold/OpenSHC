// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"

#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

#include "string.h"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00486F20
    void GameSynchronyState::initializeFinalResultsForActivePlayers()
    {
        strcpy(this->DAT_PlayerNames[1],
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0));
        // perPlayer stays a walker. Naming the fields it reaches - finalGold, finalBuildingsBurned and the rest, all at
        // [player] - is measured at 88.5% -> 38.3%, and the last three alone at 88.5% -> 70.4%, so do not retry it.
        int* perPlayer = this->currentPlayerFullIDArray + 1;
        for (int player = 1; player < 9; ++player, ++perPlayer) {
            // perPlayer[27] is currentAIArray[player].
            if ((*perPlayer == -1) && (perPlayer[27] == 0)) {
                this->finalResults.active[player] = 0;
            } else {
                this->finalResults.active[player] = 1;
                strcpy(this->finalResults.names[player], this->DAT_PlayerNames[player]);
                perPlayer[271508] = 0;
                this->finalResults.finalMaxPopulation[player] = 0;
                this->finalResults.finalMaxGoodThings[player] = 0;
                this->finalResults.finalMaxBadThings[player] = 0;
                perPlayer[271614] = 0;
                perPlayer[271682] = 0;
                perPlayer[271623] = 0;
                perPlayer[271673] = 0;
                perPlayer[271632] = 0;
                perPlayer[271641] = 0;
                perPlayer[271650] = 0;
                perPlayer[271659] = 0;
                this->finalResults.finalKilledLords[player] = 0;
                perPlayer[271691] = 0;
                perPlayer[271700] = 0;
                perPlayer[271524] = 0;
                perPlayer[271709] = 0;
                perPlayer[271718] = 0;
                perPlayer[271727] = 0;
                this->finalResults.unknownShortArray1[player] = 0;
                this->finalResults.unknownShortArray2[player] = 0;
                perPlayer[271745] = 0;
                perPlayer[271754] = 0;
                perPlayer[271763] = 0;
                perPlayer[271772] = 0;
            }
        }
        for (int row = 0; row < 9; ++row) {
            for (int column = 0; column < 9; ++column) {
                this->finalResults.finalKillMatrix[row][column] = 0;
            }
        }
    }

}
}
