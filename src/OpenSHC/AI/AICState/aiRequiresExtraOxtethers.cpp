#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Map::Buildings::BuildingType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB3A0
    undefined4 AICState ::aiRequiresExtraOxtethers(int playerID)

    {
        int _playerID = playerID;

        int _buildingID
            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_QUARRY);

        // _stoneWaiting declared first so it gets lower stack slot
        int _stoneWaiting = 0;
        int _quarryID = 0;

        int _oxTetherCount = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::countBuildingsForPlayer,
            DAT_BuildingsState::ptr)(_playerID, OpenSHC::Map::Buildings::BT_OXTETHER, 1);

        if (_oxTetherCount >= 0xa) {
            return (undefined4)(0);
        }

        int* piVar1 = &DAT_GameState::instance.playerDataArray[_playerID].highestLoadedQuarryUnk;

        *piVar1 = 0;

        if (_buildingID != 0) {

            do {
                int _localStone
                    = DAT_BuildingsState::instance
                          .buildings[(short)DAT_BuildingsState::instance.buildings[_buildingID].quarryStockpileID]
                          .resourceStone;

                int _linkedTetherCount = 0;

                short* _linkedTetherIDs = DAT_BuildingsState::instance.buildings[_buildingID].quarryLinkedOxTethers;

                int _oxTetherLoopIndex = 3;

                do {
                    int _linkedTetherID = (int)*_linkedTetherIDs;

                    if (_linkedTetherID != 0) {
                        if ((DAT_BuildingsState::instance.buildings[_linkedTetherID].buildingType
                                == OpenSHC::Map::Buildings::BT_OXTETHER)
                            && (DAT_BuildingsState::instance.buildings[_linkedTetherID].oxtetherLinkedQuarryID
                                == _buildingID)) {
                            _linkedTetherCount = _linkedTetherCount + 1;
                        } else {
                            *_linkedTetherIDs = 0;
                        }
                    }

                    _linkedTetherIDs = _linkedTetherIDs + 1;
                    _oxTetherLoopIndex = _oxTetherLoopIndex + -1;

                } while (_oxTetherLoopIndex != 0);

                if (_linkedTetherCount <= 0) {
                    *piVar1 = _buildingID;
                    return (undefined4)(1);
                }

                if (_stoneWaiting < _localStone / _linkedTetherCount) {
                    _quarryID = _buildingID;
                    _stoneWaiting = _localStone / _linkedTetherCount;
                }

                _buildingID
                    = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findNextBuildingForPlayerAndType,
                        DAT_BuildingsState::ptr)(_playerID, OpenSHC::Map::Buildings::BT_QUARRY, _buildingID);

            } while (_buildingID != 0);

            if (0x14 < _stoneWaiting) {
                *piVar1 = _quarryID;
                return (undefined4)(1);
            }
        }

        return (undefined4)(0);
    }

}
}
