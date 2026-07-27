#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CBA50
    void AICState ::planToBuyWhenLowOnResourceAndSnoozeBuildings(int playerID)

    {

        int _buildingBurning;

        int _offset;

        int _currentWood;

        int _noWood;

        int _currentPopulation;

        int* _pResourceCounter;

        int _hasArmoyUnk;

        int* _pNoBeerCounter;

        int* _pNoHopsTracker;

        int* _pNoFlourTracker;

        int* _pNoIronTracker;

        bool _enoughFood;

        bool _enoughGold;

        bool _enoughPeopleUnk;

        int _nerves;

        int _noBeerCounterUnk;

        int _noFlourCounterUnk;

        int _noHopsCounterUnk;

        int _noIronCounterUnk;

        bool _noNerves;

        int* _pNoWoodTracker;

        int _resourceCounter;

        _offset = playerID * 0x39f4;

        if (DAT_GameState::instance.playerDataArray[playerID].aiType != OpenSHC::AI::AIT_NULL) {

            _enoughPeopleUnk = true;

            _enoughFood = true;

            _enoughGold = true;

            _buildingBurning = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::playerHasBurningBuilding,
                DAT_BuildingsState::ptr)(playerID);

            _currentWood = DAT_GameState::instance.playerDataArray[playerID].currentResources[2];

            if (_currentWood < 1) {

                _pNoWoodTracker = &DAT_GameState::instance.playerDataArray[playerID].noWoodTracker;

                *_pNoWoodTracker = *_pNoWoodTracker + 1;

            }

            else {

                DAT_GameState::instance.playerDataArray[playerID].noWoodTracker = 0;
            }

            if (DAT_GameState::instance.playerDataArray[playerID].currentResources[6] < 1) {

                _pNoIronTracker = &DAT_GameState::instance.playerDataArray[playerID].noIronTracker;

                *_pNoIronTracker = *_pNoIronTracker + 1;

            }

            else {

                DAT_GameState::instance.playerDataArray[playerID].noIronTracker = 0;
            }

            if (DAT_GameState::instance.playerDataArray[playerID].currentResources[0x10] < 1) {

                _pNoFlourTracker = &DAT_GameState::instance.playerDataArray[playerID].noFlourTracker;

                *_pNoFlourTracker = *_pNoFlourTracker + 1;

            }

            else {

                DAT_GameState::instance.playerDataArray[playerID].noFlourTracker = 0;
            }

            if (DAT_GameState::instance.playerDataArray[playerID].currentResources[3] < 1) {

                _pNoHopsTracker = &DAT_GameState::instance.playerDataArray[playerID].noHopsTracker;

                *_pNoHopsTracker = *_pNoHopsTracker + 1;

            }

            else {

                DAT_GameState::instance.playerDataArray[playerID].noHopsTracker = 0;
            }

            if (DAT_GameState::instance.playerDataArray[playerID].currentResources[0xe] < 1) {

                _pNoBeerCounter = &DAT_GameState::instance.playerDataArray[playerID].noBeerCounterUnk;

                *_pNoBeerCounter = *_pNoBeerCounter + 1;

            }

            else {

                DAT_GameState::instance.playerDataArray[playerID].noBeerCounterUnk = 0;
            }

            _pResourceCounter = &DAT_GameState::instance.playerDataArray[playerID].someResourceCounter;

            *_pResourceCounter = *_pResourceCounter + 1;

            if (DAT_GameState::instance.playerDataArray[playerID].countFletchersPoleturners < 1) {

                DAT_GameState::instance.playerDataArray[playerID].noWoodTracker = 0;
            }

            if (DAT_GameState::instance.playerDataArray[playerID].countArmorersAndBlacksmiths < 1) {

                DAT_GameState::instance.playerDataArray[playerID].noIronTracker = 0;
            }

            if (DAT_GameState::instance.playerDataArray[playerID].countBakers < 1) {

                DAT_GameState::instance.playerDataArray[playerID].noFlourTracker = 0;
            }

            if (DAT_GameState::instance.playerDataArray[playerID].countBrewers < 1) {

                DAT_GameState::instance.playerDataArray[playerID].noHopsTracker = 0;
            }

            _currentPopulation = DAT_GameState::instance.playerDataArray[playerID].currentPopulation;

            if ((_currentPopulation < 10)
                && ((DAT_GameState::instance.playerDataArray[playerID].farmsWithoutWorkers != 0
                    || (2 < DAT_GameState::instance.playerDataArray[playerID].countWoodcutters)))) {

                _enoughPeopleUnk = false;
            }

            if ((((20 < _currentWood) && (_currentPopulation < 10))
                    && (DAT_GameState::instance.playerDataArray[playerID].farmsWithoutWorkers != 0))
                && (DAT_GameState::instance.playerDataArray[playerID].totalFood < 8)) {

                _enoughFood = false;
            }

            if (((_buildingBurning == 0)
                    && (DAT_GameState::instance.playerDataArray[playerID].countFarms
                        <= DAT_GameState::instance.playerDataArray[playerID].farmsWithoutWorkers))
                && (DAT_GameState::instance.playerDataArray[playerID].currentResources[0xf] < 500)) {

                _enoughGold = false;
            }

            _hasArmoyUnk = DAT_GameState::instance.playerDataArray[playerID].armory.id;

            _noWood = DAT_GameState::instance.playerDataArray[playerID].noWoodTracker;

            _noIronCounterUnk = DAT_GameState::instance.playerDataArray[playerID].noIronTracker;

            _resourceCounter = DAT_GameState::instance.playerDataArray[playerID].someResourceCounter;

            _noFlourCounterUnk = DAT_GameState::instance.playerDataArray[playerID].noFlourTracker;

            _noHopsCounterUnk = DAT_GameState::instance.playerDataArray[playerID].noHopsTracker;

            _noBeerCounterUnk = DAT_GameState::instance.playerDataArray[playerID].noBeerCounterUnk;

            _nerves = DAT_GameState::instance.playerDataArray[playerID].aiNervousActionsTracker;

            _noNerves = _nerves < 1;

            if (!_noNerves) {

                _enoughPeopleUnk = false;

                _enoughFood = false;
            }

            if (_enoughGold) {

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[27] = false;

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[0x46] = false;

            }

            else {

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[0x1b] = true;

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[0x46] = true;
            }

            if (_enoughPeopleUnk) {

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[20] = false;

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[4] = false;

            }

            else {

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[0x14] = true;

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[4] = true;
            }

            *(bool*)(_offset + 0x115df8f) = !_enoughFood;

            *(bool*)(_offset + 0x115df91) = !_noNerves;

            *(bool*)(_offset + 0x115df92) = !_noNerves;

            *(bool*)(_offset + 0x115df98) = _nerves < 1 && (36 < _noWood || _hasArmoyUnk == 0);

            *(bool*)(_offset + 0x115df9a) = _nerves < 1 && (36 < _noWood || _hasArmoyUnk == 0);

            *(bool*)(_offset + 0x115df99) = _noNerves && (0x24 < _noIronCounterUnk || _hasArmoyUnk == 0);

            *(bool*)(_offset + 0x115df9b) = _noNerves && (0x24 < _noIronCounterUnk || _hasArmoyUnk == 0);

            *(bool*)(_offset + 0x115df9c) = _noNerves && (0x24 < _resourceCounter || _hasArmoyUnk == 0);

            *(bool*)(_offset + 0x115df9d) = !_noNerves || 0x24 < _noFlourCounterUnk;

            *(bool*)(_offset + 0x115df9e) = !_noNerves || 0x48 < _noHopsCounterUnk;

            *(bool*)(_offset + 0x115dfa2) = !_noNerves || 0x48 < _noBeerCounterUnk;

            if (_noNerves) {

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[0x1e] = false;

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[0x1f] = false;

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[0x20] = false;

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[0x21] = false;

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[7] = false;

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[34] = false;

            }

            else {

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[0x1e] = true;

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[0x1f] = true;

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[0x20] = true;

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[0x21] = true;

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[7] = true;

                DAT_GameState::instance.playerDataArray[playerID].snoozedBuildings[0x22] = true;
            }

            if (DAT_GameState::instance.playerDataArray[playerID].canStartSpending != 0) {

                if ((36 < DAT_GameState::instance.playerDataArray[playerID].noWoodTracker)
                    && (DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[2] == 0)) {

                    DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[2] = 5;
                }

                if ((36 < DAT_GameState::instance.playerDataArray[playerID].noIronTracker)
                    && (DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[6] == 0)) {

                    DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[6] = 2;
                }

                if ((36 < DAT_GameState::instance.playerDataArray[playerID].noFlourTracker)
                    && (DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[0x10] == 0)) {

                    DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[0x10] = 2;
                }

                if ((72 < DAT_GameState::instance.playerDataArray[playerID].noHopsTracker)
                    && (DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[3] == 0)) {

                    DAT_GameState::instance.playerDataArray[playerID].resourcesToAcquireArray[3] = 2;
                }
            }
        }

        return;
    }

}
}
