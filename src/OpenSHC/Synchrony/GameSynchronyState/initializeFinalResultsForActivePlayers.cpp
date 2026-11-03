#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

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
        /*
          perPlayer stays a walker. Naming the fields it reaches - finalGold, finalBuildingsBurned and the rest,
          all at [player] - is measured at 88.5% -> 38.3%, and the last three alone at 88.5% -> 70.4%, so do
          not retry it.
         */
        int* perPlayer = this->currentPlayerFullIDArray + 1;
        for (int player = 1; player < 9; player++, perPlayer++) {
            // perPlayer[0x1b] is currentAIArray[player].
            if ((*perPlayer == -1) && (perPlayer[0x1b] == 0)) {
                this->finalResults.active[player] = 0;
            } else {
                this->finalResults.active[player] = 1;
                strcpy(this->finalResults.names[player], this->DAT_PlayerNames[player]);
                perPlayer[0x42494] = 0;
                this->finalResults.finalMaxPopulation[player] = 0;
                this->finalResults.finalMaxGoodThings[player] = 0;
                this->finalResults.finalMaxBadThings[player] = 0;
                perPlayer[0x424fe] = 0;
                perPlayer[0x42542] = 0;
                perPlayer[0x42507] = 0;
                perPlayer[0x42539] = 0;
                perPlayer[0x42510] = 0;
                perPlayer[0x42519] = 0;
                perPlayer[0x42522] = 0;
                perPlayer[0x4252b] = 0;
                this->finalResults.finalKilledLords[player] = 0;
                perPlayer[0x4254b] = 0;
                perPlayer[0x42554] = 0;
                perPlayer[0x424a4] = 0;
                perPlayer[0x4255d] = 0;
                perPlayer[0x42566] = 0;
                perPlayer[0x4256f] = 0;
                this->finalResults.unknownShortArray1[player] = 0;
                this->finalResults.unknownShortArray2[player] = 0;
                perPlayer[0x42581] = 0;
                perPlayer[0x4258a] = 0;
                perPlayer[0x42593] = 0;
                perPlayer[0x4259c] = 0;
            }
        }
        for (int row = 0; row < 9; row++) {
            for (int column = 0; column < 9; column++) {
                this->finalResults.finalKillMatrix[row][column] = 0;
            }
        }
    }

}
}
