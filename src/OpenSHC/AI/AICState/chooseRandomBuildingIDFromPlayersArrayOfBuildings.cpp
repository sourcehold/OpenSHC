#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeInt.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Map::Buildings::BuildingTypeInt;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CDB20
    int AICState ::chooseRandomBuildingIDFromPlayersArrayOfBuildings(int playerID)

    {

        int _count = DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildingsTracker;

        int _chosenBuilding = 0;

        int _chosenBuildingTypeIndex = 46;

        if (0 < _count) {

            int _rng = (int)(unsigned char)SEC_RNG::instance.currentNumber2 & 7;

            short* _ptr = DAT_GameState::instance.playerDataArray[playerID].top100TargetableBuildings;

            do {

                int _buildingID = (int)*_ptr;

                if (_buildingID != 0) {

                    int _selectionIndex = 0;

                    if (0 < _chosenBuildingTypeIndex) {

                        BuildingTypeInt _buildingType
                            = (BuildingTypeInt)(short)DAT_BuildingsState::instance.buildings[_buildingID].buildingType;

                        do {

                            BuildingTypeInt _cmpType;

                            if (_rng < 2) {
                                _cmpType
                                    = DAT_SkirmishDefinedData::instance.BuildingTargetPrioritySet3[_selectionIndex];
                            } else if (_rng < 4) {
                                _cmpType
                                    = DAT_SkirmishDefinedData::instance.BuildingTargetPrioritySet2[_selectionIndex];
                            } else {
                                _cmpType
                                    = DAT_SkirmishDefinedData::instance.BuildingTargetPrioritySet1[_selectionIndex];
                            }

                            if (_buildingType == _cmpType) {
                                _chosenBuilding = _buildingID;
                                _chosenBuildingTypeIndex = _selectionIndex;
                            }

                            _selectionIndex = _selectionIndex + 1;

                        } while (_selectionIndex < _chosenBuildingTypeIndex);
                    }
                }

                _ptr = _ptr + 1;

                _count = _count - 1;

            } while (_count != 0);
        }

        return _chosenBuilding;
    }

}
}
