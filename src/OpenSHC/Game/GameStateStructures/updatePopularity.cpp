#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Audio/SFX/SpeechEffectID.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Audio::SFX::SpeechEffectID;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::Map::MapType2;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0045B830
    void GameStateStructures::updatePopularity()
    {
        /*
          the change of the category currently being applied, reused for every category
         */
        int popularityChange = 0;
        if (this->mapAndTime.weekChanged == 0) {
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::recomputeReligionBonuses, this)();
        for (int playerID = 1; playerID < 9; playerID++) {
            if ((this->playerDataArray[playerID].keep.id <= 0)
                || (this->playerDataArray[playerID].campground.id <= 0)) {
                continue;
            }
            if ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk)
                && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE)) {
                this->playerDataArray[playerID].popularity
                    = DAT_GameSynchronyState::instance.currentPlayerSlotID != 2 ? 10000 : 0;
                continue;
            }
            if ((this->playerDataArray[playerID].currentPopulation <= 3)
                && (this->playerDataArray[playerID].popularity < 5000)) {
                /*
                  75(00)
                 */
                this->playerDataArray[playerID].popularity = 7500;
                continue;
            }
            int currentGold = this->playerDataArray[playerID].currentResources[0xf];
            this->playerDataArray[playerID].storedPopularityPercent = this->playerDataArray[playerID].popularity;
            int worstChange = 0;
            int worstChangeReason = 0;
            if (this->playerDataArray[playerID].foodTypesInStock <= 0) {
                this->playerDataArray[playerID].weeksWithoutFood = this->playerDataArray[playerID].weeksWithoutFood + 1;
            } else {
                this->playerDataArray[playerID].weeksWithoutFood = 0;
            }
            if (this->playerDataArray[playerID].currentPopulation <= 0) {
                popularityChange = 200;
            } else if (this->playerDataArray[playerID].foodTypesInStock <= 0) {
                popularityChange = -200;
            } else if (this->playerDataArray[playerID].rationsSetting == 0) {
                popularityChange = -200;
            } else if (this->playerDataArray[playerID].rationsSetting == 1) {
                popularityChange = -100;
            } else if (this->playerDataArray[playerID].rationsSetting == 2) {
                popularityChange = 0;
            } else if (this->playerDataArray[playerID].rationsSetting == 4) {
                popularityChange = 200;
            } else if (this->playerDataArray[playerID].rationsSetting == 3) {
                popularityChange = 100;
            }
            if (this->playerDataArray[playerID].foodTypesCurrentlyEaten == 2) {
                popularityChange = popularityChange + 25;
            } else if (this->playerDataArray[playerID].foodTypesCurrentlyEaten == 3) {
                popularityChange = popularityChange + 50;
            } else if (this->playerDataArray[playerID].foodTypesCurrentlyEaten == 4) {
                popularityChange = popularityChange + 75;
            }
            /*
              sets popularity
             */
            this->playerDataArray[playerID].popularity = this->playerDataArray[playerID].popularity + popularityChange;
            this->playerDataArray[playerID].popularityChangeBasedOnFood = popularityChange;
            if (popularityChange < 0) {
                worstChange = popularityChange;
                worstChangeReason = 1;
            }
            if (this->playerDataArray[playerID].crowding <= 100) {
                popularityChange = 0;
            } else if (this->playerDataArray[playerID].crowding <= 120) {
                popularityChange = -50;
            } else if (this->playerDataArray[playerID].crowding <= 140) {
                popularityChange = -100;
            } else if (this->playerDataArray[playerID].crowding <= 160) {
                popularityChange = -150;
            } else {
                popularityChange = this->playerDataArray[playerID].crowding <= 180 ? -200 : -250;
            }
            this->playerDataArray[playerID].popularity = this->playerDataArray[playerID].popularity + popularityChange;
            this->playerDataArray[playerID].popularityChangeBasedOnCrowding = popularityChange;
            if (popularityChange < worstChange) {
                worstChange = popularityChange;
                worstChangeReason = 2;
            }
            if ((this->playerDataArray[playerID].taxesSetting < 3) && (currentGold <= 0)) {
                popularityChange = 25;
            } else if (this->playerDataArray[playerID].taxesSetting == 0) {
                popularityChange = 175;
            } else if (this->playerDataArray[playerID].taxesSetting == 1) {
                popularityChange = 125;
            } else if (this->playerDataArray[playerID].taxesSetting == 2) {
                popularityChange = 75;
            } else if (this->playerDataArray[playerID].taxesSetting == 3) {
                popularityChange = 25;
            } else if (this->playerDataArray[playerID].taxesSetting == 4) {
                popularityChange = -50;
            } else if (this->playerDataArray[playerID].taxesSetting == 5) {
                popularityChange = -100;
            } else if (this->playerDataArray[playerID].taxesSetting == 6) {
                popularityChange = -150;
            } else if (this->playerDataArray[playerID].taxesSetting == 7) {
                popularityChange = -200;
            } else if (this->playerDataArray[playerID].taxesSetting == 8) {
                popularityChange = -300;
            } else if (this->playerDataArray[playerID].taxesSetting == 9) {
                popularityChange = -400;
            } else {
                popularityChange = this->playerDataArray[playerID].taxesSetting == 10 ? -500 : -600;
            }
            this->playerDataArray[playerID].popularity = this->playerDataArray[playerID].popularity + popularityChange;
            int popularityAfterTax = this->playerDataArray[playerID].popularity;
            this->playerDataArray[playerID].popularityChangeBasedOnTax = popularityChange;
            if (popularityChange < worstChange) {
                worstChange = popularityChange;
                worstChangeReason = 4;
            }
            this->playerDataArray[playerID].field642_0x2168 = 0;
            if (worstChange > 0) {
                worstChange = 0;
                worstChangeReason = 3;
            }
            popularityChange = this->playerDataArray[playerID].areCarnivalUnitsPresent != FALSE ? 400 : 0;
            this->playerDataArray[playerID].popularity = popularityAfterTax + popularityChange;
            this->playerDataArray[playerID].popularityChangeBasedOnFair = popularityChange;
            if (popularityChange < worstChange) {
                worstChange = popularityChange;
                worstChangeReason = 5;
            }
            if (this->playerDataArray[playerID].blessedPeoplePercentage <= 24) {
                popularityChange = 0;
            } else if (this->playerDataArray[playerID].blessedPeoplePercentage <= 49) {
                popularityChange = 50;
            } else if (this->playerDataArray[playerID].blessedPeoplePercentage <= 74) {
                popularityChange = 100;
            } else {
                /*
                  < 95? => 150   >= 95? 200
                 */
                popularityChange = this->playerDataArray[playerID].blessedPeoplePercentage <= 94 ? 150 : 200;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].ownsChurchUnk != 0) {
                popularityChange = popularityChange + 25;
            }
            if (DAT_GameState::instance.playerDataArray[playerID].ownsCathedralUnk != 0) {
                popularityChange = popularityChange + 50;
            }
            if (popularityChange < 0) {
                popularityChange = 0;
            }
            this->playerDataArray[playerID].popularity = this->playerDataArray[playerID].popularity + popularityChange;
            this->playerDataArray[playerID].popularityReligionBasedDiv25
                = this->playerDataArray[playerID].popularityReligionBasedDiv25 + popularityChange / 25;
            this->playerDataArray[playerID].popularityChangeBasedOnReligion = popularityChange;
            if (popularityChange < worstChange) {
                worstChange = popularityChange;
                worstChangeReason = 6;
            }
            this->playerDataArray[playerID].beerPercentage
                = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeAleCoverage, this)(playerID);
            if ((int)this->playerDataArray[playerID].beerPercentage < 25) {
                popularityChange = 0;
            } else if ((int)this->playerDataArray[playerID].beerPercentage < 50) {
                popularityChange = 50;
            } else if ((int)this->playerDataArray[playerID].beerPercentage < 75) {
                popularityChange = 100;
            } else {
                /*
                  if aleCoverage > 99: 200; else: 150
                 */
                popularityChange = (int)this->playerDataArray[playerID].beerPercentage < 100 ? 150 : 200;
            }
            this->playerDataArray[playerID].popularity = this->playerDataArray[playerID].popularity + popularityChange;
            this->playerDataArray[playerID].popularityChangeAleBased = popularityChange;
            if (popularityChange < worstChange) {
                worstChange = popularityChange;
                worstChangeReason = 7;
            }
            if ((int)this->playerDataArray[playerID].fearFactorLevel >= 1) {
                popularityChange = this->playerDataArray[playerID].fearFactorLevel * 25;
            } else if ((int)this->playerDataArray[playerID].fearFactorLevel <= -1) {
                popularityChange = this->playerDataArray[playerID].fearFactorLevel * 25;
            } else {
                popularityChange = 0;
            }
            this->playerDataArray[playerID].popularity = this->playerDataArray[playerID].popularity + popularityChange;
            int popularityAfterFear = this->playerDataArray[playerID].popularity;
            this->playerDataArray[playerID].popularityChangeFearFactorBased = popularityChange;
            if (popularityChange < worstChange) {
                worstChangeReason = 8;
            }
            if (this->playerDataArray[playerID].someCount48 == 0) {
                this->playerDataArray[playerID].someCount54 = 0;
                this->playerDataArray[playerID].someCount60 = 0;
            } else {
                this->playerDataArray[playerID].someCount48 = this->playerDataArray[playerID].someCount48 - 1;
                if (this->playerDataArray[playerID].someCount60 != 0) {
                    this->playerDataArray[playerID].someCount60 = this->playerDataArray[playerID].someCount60 + 1;
                }
                if (this->playerDataArray[playerID].someCount60 <= 0) {
                    this->playerDataArray[playerID].popularity = popularityAfterFear - 150;
                    this->playerDataArray[playerID].someCount54 = -150;
                } else if (this->playerDataArray[playerID].someCount60 <= 5) {
                    this->playerDataArray[playerID].popularity = popularityAfterFear - 125;
                    this->playerDataArray[playerID].someCount54 = -125;
                } else if (this->playerDataArray[playerID].someCount60 <= 10) {
                    this->playerDataArray[playerID].popularity = popularityAfterFear - 100;
                    this->playerDataArray[playerID].someCount54 = -100;
                } else if (this->playerDataArray[playerID].someCount60 <= 15) {
                    this->playerDataArray[playerID].popularity = popularityAfterFear - 75;
                    this->playerDataArray[playerID].someCount54 = -75;
                } else if (this->playerDataArray[playerID].someCount60 <= 20) {
                    this->playerDataArray[playerID].popularity = popularityAfterFear - 50;
                    this->playerDataArray[playerID].someCount54 = -50;
                } else {
                    int lateSiegePenalty = this->playerDataArray[playerID].someCount60 <= 25 ? -25 : 0;
                    this->playerDataArray[playerID].popularity = popularityAfterFear + lateSiegePenalty;
                    this->playerDataArray[playerID].someCount54 = (short)lateSiegePenalty;
                }
            }
            if (this->playerDataArray[playerID].someCount49 == 0) {
                this->playerDataArray[playerID].someCount55 = 0;
            } else {
                this->playerDataArray[playerID].someCount49 = this->playerDataArray[playerID].someCount49 - 1;
                this->playerDataArray[playerID].popularity = this->playerDataArray[playerID].popularity - 75;
                this->playerDataArray[playerID].someCount55 = -75;
            }
            if (this->playerDataArray[playerID].someCount50 == 0) {
                this->playerDataArray[playerID].someCount56 = 0;
            } else {
                this->playerDataArray[playerID].someCount50 = this->playerDataArray[playerID].someCount50 - 1;
                this->playerDataArray[playerID].popularity = this->playerDataArray[playerID].popularity - 125;
                this->playerDataArray[playerID].someCount56 = -125;
            }
            if (this->playerDataArray[playerID].someCount51 == 0) {
                this->playerDataArray[playerID].someCount57 = 0;
            } else {
                this->playerDataArray[playerID].someCount51 = this->playerDataArray[playerID].someCount51 - 1;
                this->playerDataArray[playerID].popularity = this->playerDataArray[playerID].popularity - 50;
                this->playerDataArray[playerID].someCount57 = -50;
            }
            if (this->playerDataArray[playerID].someCount52 == 0) {
                this->playerDataArray[playerID].someCount58 = 0;
            } else {
                this->playerDataArray[playerID].someCount52 = this->playerDataArray[playerID].someCount52 - 1;
                this->playerDataArray[playerID].popularity = this->playerDataArray[playerID].popularity + 200;
                this->playerDataArray[playerID].someCount58 = 200;
            }
            if (this->playerDataArray[playerID].someCount53 == 0) {
                this->playerDataArray[playerID].someCount59 = 0;
            } else {
                this->playerDataArray[playerID].someCount53 = this->playerDataArray[playerID].someCount53 - 1;
                this->playerDataArray[playerID].popularity = this->playerDataArray[playerID].popularity + 50;
                this->playerDataArray[playerID].someCount59 = 50;
            }
            this->playerDataArray[playerID].someCount40 = worstChangeReason;
            if (this->playerDataArray[playerID].popularity < 0) {
                this->playerDataArray[playerID].popularity = 0;
            }
            if (this->playerDataArray[playerID].popularity > 10000) {
                this->playerDataArray[playerID].popularity = 10000;
            }
            if (this->playerDataArray[playerID].storedPopularityPercent > this->playerDataArray[playerID].popularity) {
                if (((int)this->playerDataArray[playerID].someCount44
                        > this->playerDataArray[playerID].popularity + 500)
                    && (this->playerDataArray[playerID].currentPopulation >= 4)
                    && (this->playerDataArray[playerID].field25_0x40 == 0)) {
                    this->playerDataArray[playerID].field25_0x40 = 1;
                    this->playerDataArray[playerID].someCount44 = (short)this->playerDataArray[playerID].popularity;
                    if ((playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID)
                        && (MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::shouldSoundXNotBePlaying,
                                DAT_SoundSystemState::ptr)()
                            == 0)) {
                        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                            OpenSHC::Audio::SFX::SEID_POP_FALLING);
                    }
                }
            } else if ((this->playerDataArray[playerID].storedPopularityPercent
                           < this->playerDataArray[playerID].popularity)
                && ((int)this->playerDataArray[playerID].someCount44 < this->playerDataArray[playerID].popularity - 500)
                && (this->playerDataArray[playerID].currentPopulation >= 4)
                && (this->playerDataArray[playerID].field25_0x40 == 1)) {
                this->playerDataArray[playerID].field25_0x40 = 0;
                this->playerDataArray[playerID].someCount44 = (short)this->playerDataArray[playerID].popularity;
                if ((playerID == DAT_GameSynchronyState::instance.currentPlayerSlotID)
                    && (MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::shouldSoundXNotBePlaying,
                            DAT_SoundSystemState::ptr)()
                        == 0)) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSpeechSFX, DAT_SFXState::ptr)(
                        OpenSHC::Audio::SFX::SEID_POP_RISING);
                }
            }
        }
    }
}
}
