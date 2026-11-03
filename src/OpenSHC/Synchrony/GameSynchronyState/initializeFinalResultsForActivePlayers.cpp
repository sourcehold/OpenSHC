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
        byte* pbVar1;
        int* piVar4;
        int iVar6;
        int (*paiVar7)[9];
        strcpy(this->DAT_PlayerNames[1],
            MACRO_CALL_MEMBER(Text::UserTextHandler_Func::getTextArrayPointer, DAT_UserTextHandlerState::ptr)(0));
        /*
          piVar4 stays a walker. Naming the fields it reaches - finalGold, finalBuildingsBurned and the rest,
          all at [iVar6] - is measured at 88.5% -> 38.3%, and the last three alone at 88.5% -> 70.4%, so do
          not retry it.
         */
        for (iVar6 = 1, piVar4 = this->currentPlayerFullIDArray + 1; iVar6 < 9;
            iVar6 = iVar6 + 1, piVar4 = piVar4 + 1) {
            if ((*piVar4 == -1) && (piVar4[0x1b] == 0)) {
                this->finalResults.active[iVar6] = 0;
            } else {
                this->finalResults.active[iVar6] = 1;
                strcpy(this->finalResults.names[iVar6], this->DAT_PlayerNames[iVar6]);
                piVar4[0x42494] = 0;
                this->finalResults.finalMaxPopulation[iVar6] = 0;
                this->finalResults.finalMaxGoodThings[iVar6] = 0;
                this->finalResults.finalMaxBadThings[iVar6] = 0;
                piVar4[0x424fe] = 0;
                piVar4[0x42542] = 0;
                piVar4[0x42507] = 0;
                piVar4[0x42539] = 0;
                piVar4[0x42510] = 0;
                piVar4[0x42519] = 0;
                piVar4[0x42522] = 0;
                piVar4[0x4252b] = 0;
                this->finalResults.finalKilledLords[iVar6] = 0;
                piVar4[0x4254b] = 0;
                piVar4[0x42554] = 0;
                piVar4[0x424a4] = 0;
                piVar4[0x4255d] = 0;
                piVar4[0x42566] = 0;
                piVar4[0x4256f] = 0;
                this->finalResults.unknownShortArray1[iVar6] = 0;
                this->finalResults.unknownShortArray2[iVar6] = 0;
                piVar4[0x42581] = 0;
                piVar4[0x4258a] = 0;
                piVar4[0x42593] = 0;
                piVar4[0x4259c] = 0;
            }
        }
        paiVar7 = this->finalResults.finalKillMatrix;
        for (iVar6 = 0x51; iVar6 != 0; iVar6 = iVar6 + -1) {
            (*paiVar7)[0] = 0;
            paiVar7 = (int (*)[9])(*paiVar7 + 1);
        }
    }

}
}
