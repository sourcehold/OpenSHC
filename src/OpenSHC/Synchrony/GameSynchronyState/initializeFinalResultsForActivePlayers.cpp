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
        for (int player = 1; player < countof(this->currentAIArray); ++player) {
            if (this->currentAIArray[player] == 0 && this->currentPlayerFullIDArray[player] == -1) {
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
                this->finalResults.finalDateOfDeathInMonths[player] = 0;
                this->finalResults.tail.tail2.field_0x0[player] = 0;
                this->finalResults.tail.tail2.field_0x24[player] = 0;
                this->finalResults.tail.tail2.field_0x48[player] = 0;
            }
        }
        for (int row = 0; row < countof(this->finalResults.finalKillMatrix); ++row) {
            for (int column = 0; column < countof(this->finalResults.finalKillMatrix[0]); ++column) {
                this->finalResults.finalKillMatrix[row][column] = 0;
            }
        }
    }

}
}
