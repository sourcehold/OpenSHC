#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::GameMode2;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Type propagation algorithm not settling
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0045AF30
    void GameStateStructures::computePopulationStatistics()
    {
        for (int playerID = 1; playerID < 9; playerID++) {
            this->playerDataArray[playerID].currentPopulation
                = ((this->playerDataArray[playerID].countEntities
                       - this->playerDataArray[playerID].nonInteractiveCitizenCountUnk)
                      - this->playerDataArray[playerID].field645_0x2174)
                - this->playerDataArray[playerID].armySize;
            if ((this->playerDataArray[playerID].lordID != 0)
                && (DAT_UnitsState::instance.units[this->playerDataArray[playerID].lordID].uid
                    == this->playerDataArray[playerID].lordUID)) {
                this->playerDataArray[playerID].currentPopulation
                    = this->playerDataArray[playerID].currentPopulation - 1;
            }
            if ((this->playerDataArray[playerID].ladyIDUnk != 0)
                && (DAT_UnitsState::instance.units[this->playerDataArray[playerID].ladyIDUnk].uid
                    == this->playerDataArray[playerID].someUnitIDSelfRef)) {
                this->playerDataArray[playerID].currentPopulation
                    = this->playerDataArray[playerID].currentPopulation - 1;
            }
            if ((this->playerDataArray[playerID].jesterIDUnk != 0)
                && (DAT_UnitsState::instance.units[this->playerDataArray[playerID].jesterIDUnk].uid
                    == this->playerDataArray[playerID].someUnitIDSelfRef_2)) {
                this->playerDataArray[playerID].currentPopulation
                    = this->playerDataArray[playerID].currentPopulation - 1;
            }
            this->playerDataArray[playerID].populationRelatedCrowdingCountUnk
                = this->playerDataArray[playerID].currentPopulation_2
                - this->playerDataArray[playerID].availablePeasantsOrHousedPeasants;
            if (this->playerDataArray[playerID].blessedPeopleCountUnk < 1) {
                this->playerDataArray[playerID].blessedPeoplePercentage = 0;
            } else if (this->playerDataArray[playerID].unblessedPeopleCountUnk
                    + this->playerDataArray[playerID].blessedPeopleCountUnk
                == 0) {
                this->playerDataArray[playerID].blessedPeoplePercentage = 100;
            } else {
                this->playerDataArray[playerID].blessedPeoplePercentage
                    = (this->playerDataArray[playerID].blessedPeopleCountUnk * 100)
                    / (this->playerDataArray[playerID].unblessedPeopleCountUnk
                        + this->playerDataArray[playerID].blessedPeopleCountUnk);
            }
            if (this->mapAndTime.startOfDay != FALSE) {
                this->playerDataArray[playerID]
                    .populationGrowth[this->playerDataArray[playerID].populationGrowthStatisticCounter]
                    = this->playerDataArray[playerID].availablePeasantsOrHousedPeasants;
                this->playerDataArray[playerID].populationGrowthStatisticCounter
                    = this->playerDataArray[playerID].populationGrowthStatisticCounter + 1;
                if (this->playerDataArray[playerID].populationGrowthStatisticCounter >= 8) {
                    this->playerDataArray[playerID].populationGrowthStatisticCounter = 0;
                }
                this->playerDataArray[playerID].averagePopulationGrowthUnk
                    = (this->playerDataArray[playerID].populationGrowth[0]
                          + this->playerDataArray[playerID].populationGrowth[1]
                          + this->playerDataArray[playerID].populationGrowth[2]
                          + this->playerDataArray[playerID].populationGrowth[3]
                          + this->playerDataArray[playerID].populationGrowth[4]
                          + this->playerDataArray[playerID].populationGrowth[5]
                          + this->playerDataArray[playerID].populationGrowth[7]
                          + this->playerDataArray[playerID].populationGrowth[6])
                    / 8;
            }
            if (this->mapAndTime.monthChanged != 0) {
                if (this->mapAndTime.populationIndex < 300) {
                    this->mapAndTime.playerPopulationStatistics[playerID][this->mapAndTime.populationIndex]
                        = (short)this->playerDataArray[playerID].currentPopulation;
                } else {
                    /*
                      Running average move values
                     */
                    for (int sample = 0; sample < 299; sample++) {
                        this->mapAndTime.playerPopulationStatistics[playerID][sample]
                            = this->mapAndTime.playerPopulationStatistics[playerID][sample + 1];
                    }
                    this->mapAndTime.playerPopulationStatistics[playerID][299]
                        = (short)this->playerDataArray[playerID].currentPopulation;
                }
            }
            if ((int)DAT_GameSynchronyState::instance.finalResults.finalMaxPopulation[playerID]
                < this->playerDataArray[playerID].currentPopulation) {
                DAT_GameSynchronyState::instance.finalResults.finalMaxPopulation[playerID]
                    = (short)this->playerDataArray[playerID].currentPopulation;
            }
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR) {
                if (this->playerDataArray[playerID].tacticalPowersBarLevel < 7000) {
                    this->playerDataArray[playerID].tacticalPowersBarLevel
                        = this->playerDataArray[playerID].tacticalPowersBarLevel + 1;
                }
                if (this->playerDataArray[playerID].goldDonation > 0) {
                    int goldIncrement = this->playerDataArray[playerID].goldDonation;
                    if (goldIncrement > 10) {
                        goldIncrement = 10;
                    }
                    this->playerDataArray[playerID].currentResources[15]
                        = this->playerDataArray[playerID].currentResources[15] + goldIncrement;
                    this->playerDataArray[playerID].goldDonation
                        = this->playerDataArray[playerID].goldDonation - goldIncrement;
                    if (playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                        DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 1;
                    }
                }
            }
        }
        if (this->mapAndTime.monthChanged != 0) {
            this->mapAndTime.populationIndex = this->mapAndTime.populationIndex + 1;
        }
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::updateFoodTypesInStockForAllPlayers, this)();
    }
}
}
