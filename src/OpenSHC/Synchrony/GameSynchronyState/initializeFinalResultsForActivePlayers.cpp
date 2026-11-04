// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

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
        for (int player = 1; player < 9; ++player) {
            int* const perPlayer = this->currentPlayerFullIDArray + player;
            // perPlayer[27] is currentAIArray[player].
            if (*perPlayer == -1 && perPlayer[27] == 0) {
                this->finalResults.active[player] = 0;
            } else {
                this->finalResults.active[player] = 1;
                strcpy(this->finalResults.names[player], this->DAT_PlayerNames[player]);
                this->finalResults.finalGold[player] = 0;
                this->finalResults.finalMaxPopulation[player] = 0;
                this->finalResults.finalMaxGoodThings[player] = 0;
                this->finalResults.finalMaxBadThings[player] = 0;
                this->finalResults.finalBuildingsBurned[player] = 0;
                this->finalResults.finalBuidingsDestroyed[player] = 0;
                this->finalResults.finalFoodProduced[player] = 0;
                this->finalResults.finalWeaponsProduced[player] = 0;
                this->finalResults.finalIronProduced[player] = 0;
                this->finalResults.finalStoneProduced[player] = 0;
                this->finalResults.finalWoodProduced[player] = 0;
                this->finalResults.finalPitchProduced[player] = 0;
                this->finalResults.finalKilledLords[player] = 0;
                this->finalResults.finalTroopsKilledWeighted[player] = 0;
                this->finalResults.finalBuildingsDestroyedWeighted[player] = 0;
                this->finalResults.finalTimeAlive[player] = 0;
                this->finalResults.finalTroopsProduced[player] = 0;
                this->finalResults.finalGoodsRecieved[player] = 0;
                this->finalResults.finalGoodsSent[player] = 0;
                this->finalResults.unknownShortArray1[player] = 0;
                this->finalResults.unknownShortArray2[player] = 0;
                // The first is finalDateOfDeathInMonths[player]; naming it swaps two registers in the strcpy above.
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
