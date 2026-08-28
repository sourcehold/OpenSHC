#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/Player/PlayerData.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeInt.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Game::Player::PlayerData;
    using OpenSHC::Map::Buildings::BuildingTypeInt;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CDBC0
    int AICState ::getTargetableBuildingForPlayerID(int playerID, int param_2)

    {

        int* piVar1;

        PlayerData* pPVar2;

        int iVar3;

        int _candidateBuilding;

        BuildingTypeInt* _pTargets;

        int _index;

        int _aiType;

        int _outerPatrolGroupsCount;

        int _tracker;

        iVar3 = playerID;

        _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;

        if ((_aiType != 0)
            && (_outerPatrolGroupsCount = *(int*)((int)this + (_aiType + -1) * 0x2a4 + 0x174),
                0 < _outerPatrolGroupsCount)) {

            _tracker = DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildingsTracker;

            if (0 < _tracker) {

                piVar1 = &DAT_GameState::instance.playerDataArray[playerID].someCounter2;

                *piVar1 = *piVar1 + 1;

                if (_tracker <= DAT_GameState::instance.playerDataArray[playerID].someCounter2) {

                    DAT_GameState::instance.playerDataArray[playerID].someCounter2 = 0;
                }

                pPVar2 = DAT_GameState::instance.playerDataArray + playerID;

                playerID = 0;

                _index = ((_tracker / _outerPatrolGroupsCount) * param_2 + pPVar2->someCounter2) % _tracker;

                if (0 < _tracker) {

                    do {

                        _candidateBuilding
                            = (int)DAT_GameState::instance.playerDataArray[iVar3].top100TargetableBuildings[_index];

                        _index = _index + 1;

                        if (_tracker <= _index) {

                            _index = 0;
                        }

                        if (_candidateBuilding != 0) {

                            _pTargets = DAT_SkirmishDefinedData::instance.BuildingTargetPrioritySet1;

                            do {

                                if ((int)(short)DAT_BuildingsState::instance.buildings[_candidateBuilding].buildingType
                                    == *_pTargets) {

                                    return _candidateBuilding;
                                }

                                _pTargets = _pTargets + 1;

                                /*
                                                Iterates only over resource buildings, so if resource building, return
                                 */

                            } while ((int)_pTargets < 0xb427c8);
                        }

                        playerID = playerID + 1;

                    } while (playerID < _tracker);
                }
            }

            return 0;
        }

        return 0;
    }

}
}
