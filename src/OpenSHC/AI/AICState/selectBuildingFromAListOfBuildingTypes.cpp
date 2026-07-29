#include "OpenSHC/AI/AICState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"

namespace OpenSHC {
namespace AI {

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CDAB0
    int AICState ::selectBuildingFromAListOfBuildingTypes(int playerID)

    {

        int _selectedBuildingID;

        int _loopCounter;

        int _loopLimit;

        short* psVar1;

        int _arraySize;

        int _buildingID;

        _arraySize = DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildingsTracker;

        _selectedBuildingID = 0;

        _loopLimit = 0x2e;

        if (0 < _arraySize) {

            psVar1 = DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildings;

            do {

                _buildingID = (int)*psVar1;

                if ((_buildingID != 0) && (_loopCounter = 0, 0 < _loopLimit)) {

                    do {

                        if ((int)(short)DAT_BuildingsState::instance.buildings[_buildingID].buildingType
                            == DAT_SkirmishDefinedData::instance.BuildingTargetPrioritySet1[_loopCounter]) {

                            /*
                                          fancy break statement? */

                            _selectedBuildingID = _buildingID;

                            _loopLimit = _loopCounter;
                        }

                        _loopCounter = _loopCounter + 1;

                    } while (_loopCounter < _loopLimit);
                }

                psVar1 = psVar1 + 1;

                _arraySize = _arraySize + -1;

            } while (_arraySize != 0);
        }

        return _selectedBuildingID;
    }

}
}
