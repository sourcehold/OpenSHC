#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeInt.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Map::Buildings::BuildingTypeInt;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CDB20
    int AICState ::chooseRandomBuildingIDFromPlayersArrayOfBuildings(int playerID)

    {

        int _chosenBuilding;

        int _selectionIndex;

        int _chosenBuildingTypeIndex;

        short* _ptr_buildingIDArray;

        int _buildingID;

        BuildingTypeInt _buildingType;

        bool bVar1;

        _selectionIndex = DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildingsTracker;

        _chosenBuilding = 0;

        _chosenBuildingTypeIndex = 46;

        if (0 < _selectionIndex) {

            _ptr_buildingIDArray = DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildings;

            playerID = _selectionIndex;

            do {

                _buildingID = (int)*_ptr_buildingIDArray;

                if ((_buildingID != 0) && (_selectionIndex = 0, 0 < _chosenBuildingTypeIndex)) {

                    _buildingType
                        = (BuildingTypeInt)(short)DAT_BuildingsState::instance.buildings[_buildingID].buildingType;

                    do {

                        if (((byte)SEC_RNG::instance.currentNumber2 & 7) < 2) {

                            bVar1 = _buildingType
                                == DAT_SkirmishDefinedData::instance.buildingTargetPrioritySet3[_selectionIndex];

                        }

                        else if (((byte)SEC_RNG::instance.currentNumber2 & 7) < 4) {

                            bVar1 = _buildingType
                                == DAT_SkirmishDefinedData::instance.buildingTargetPrioritySet2[_selectionIndex];

                        }

                        else {

                            bVar1 = _buildingType
                                == DAT_SkirmishDefinedData::instance.buildingTargetPrioritySet1[_selectionIndex];
                        }

                        if (bVar1) {

                            /*
                                          very unique way to break from a loop ;) */

                            _chosenBuilding = _buildingID;

                            _chosenBuildingTypeIndex = _selectionIndex;
                        }

                        _selectionIndex = _selectionIndex + 1;

                    } while (_selectionIndex < _chosenBuildingTypeIndex);
                }

                _ptr_buildingIDArray = _ptr_buildingIDArray + 1;

                playerID = playerID + -1;

            } while (playerID != 0);
        }

        return _chosenBuilding;
    }

}
}
