#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Map::Buildings::BuildingType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CB3A0
    undefined4 AICState ::aiRequiresExtraOxtethers(int playerID)

    {

        int* piVar1;

        int _buildingID;

        int _oxTetherCount;

        int _linkedTetherID;

        short* _linkedTetherIDs;

        int _linkedTetherCount;

        int _oxTetherLoopIndex;

        int _quarryID;

        int _stoneWaiting;

        int _playerID;

        _playerID = playerID;

        _buildingID
            = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findFirstBuildingIDForPlayerAndType,
                DAT_BuildingsState::ptr)(playerID, OpenSHC::Map::Buildings::BT_QUARRY);

        _quarryID = 0;

        /*
            reuse of playerID!! */

        playerID = 0;

        _oxTetherCount = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::countBuildingsForPlayer,
            DAT_BuildingsState::ptr)(_playerID, OpenSHC::Map::Buildings::BT_OXTETHER, 1);

        if (9 < _oxTetherCount) {

            return (undefined4)(0);
        }

        piVar1 = &DAT_GameState::instance.playerDataArray[_playerID].highestLoadedQuarryUnk;

        *piVar1 = 0;

        if (_buildingID != 0) {

            do {

                _stoneWaiting
                    = DAT_BuildingsState::instance
                          .buildings[(short)DAT_BuildingsState::instance.buildings[_buildingID].quarryStockpileID]
                          .resourceStone;

                _linkedTetherCount = 0;

                _linkedTetherIDs = DAT_BuildingsState::instance.buildings[_buildingID].quarryLinkedOxTethers;

                _oxTetherLoopIndex = 3;

                do {

                    _linkedTetherID = (int)*_linkedTetherIDs;

                    if (_linkedTetherID != 0) {

                        if ((DAT_BuildingsState::instance.buildings[_linkedTetherID].buildingType
                                == OpenSHC::Map::Buildings::BT_OXTETHER)
                            && (DAT_BuildingsState::instance.buildings[_linkedTetherID].oxtetherLinkedQuarryID
                                == _buildingID)) {

                            _linkedTetherCount = _linkedTetherCount + 1;

                        }

                        else {

                            *_linkedTetherIDs = 0;
                        }
                    }

                    _linkedTetherIDs = _linkedTetherIDs + 1;

                    _oxTetherLoopIndex = _oxTetherLoopIndex + -1;

                } while (_oxTetherLoopIndex != 0);

                if (_linkedTetherCount < 1) {

                    *piVar1 = _buildingID;

                    return (undefined4)(1);
                }

                /*
                        store the highest ratio of stone in quarry stockpile divided by linked ox
                   tethers */

                if (playerID < _stoneWaiting / _linkedTetherCount) {

                    playerID = _stoneWaiting / _linkedTetherCount;

                    _quarryID = _buildingID;
                }

                _buildingID
                    = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::findNextBuildingForPlayerAndType,
                        DAT_BuildingsState::ptr)(_playerID, OpenSHC::Map::Buildings::BT_QUARRY, _buildingID);

            } while (_buildingID != 0);

            /*
                  if the highest ratio is larger than 20, return true */

            if (20 < playerID) {

                *piVar1 = _quarryID;

                return (undefined4)(1);
            }
        }

        return (undefined4)(0);
    }

}
}
