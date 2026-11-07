#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          @param size meaning width of climb area, e.g. gate small has 3, gate large has 4 (why not 5?),   ladder has 1
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A9510
        int PathFindingState::createClimbData(int size, int buildingID, int unitID, int direction, int param_5)
        {
            int _climbID;
            for (_climbID = 1; _climbID < 200; ++_climbID) {
                if (this->climbData[_climbID].canBeUsed == 0) {
                    break;
                }
            }
            if (_climbID == 200) {
                return 0;
            }
            this->climbData[_climbID].canBeUsed = 1;
            this->climbData[_climbID].type = size;
            this->climbData[_climbID].isRecognizedByPathfinding = 0;
            this->climbData[_climbID].climbDataRelated = DAT_GameCore::instance.uniqueGameObjectTracker;
            DAT_GameCore::instance.uniqueGameObjectTracker = DAT_GameCore::instance.uniqueGameObjectTracker + 1;
            this->climbData[_climbID].buildingID = buildingID;
            this->climbData[_climbID].unitID = unitID;
            if (buildingID != 0) {
                /*
                  buildingID != 0
                 */
                this->climbData[_climbID].sourceUID = DAT_BuildingsState::instance.buildings[buildingID].uid;
                this->climbData[_climbID].owner = (int)DAT_BuildingsState::instance.buildings[buildingID].owner;
                this->climbData[_climbID].bottomXPosition
                    = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x;
                this->climbData[_climbID].bottomYPosition
                    = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y;
                this->climbData[_climbID].bottomTilePosition
                    = DAT_BuildingsState::instance.buildings[buildingID].currentTilePositionAdjusted;
                if (size == 6) {
                    this->climbData[_climbID].ladderDirection = direction;
                } else if (size == 5) {
                    this->climbData[_climbID].ladderDirection = direction;
                } else if (size == 4) {
                    this->climbData[_climbID].ladderDirection = direction;
                } else if (size == 3) {
                    this->climbData[_climbID].ladderDirection = direction;
                }
                return _climbID;
            }
            if (unitID != 0) {
                this->climbData[_climbID].sourceUID = DAT_UnitsState::instance.units[unitID].uid;
                this->climbData[_climbID].owner = DAT_UnitsState::instance.units[unitID].owner;
                this->climbData[_climbID].bottomXPosition = DAT_UnitsState::instance.units[unitID].x;
                this->climbData[_climbID].bottomYPosition = DAT_UnitsState::instance.units[unitID].y;
                this->climbData[_climbID].bottomTilePosition = DAT_UnitsState::instance.units[unitID].tile;
                DAT_UnitsState::instance.units[unitID].wallDataID = (short)_climbID;
                return _climbID;
            }
            // neither a building nor a unit: nothing to climb
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::clearClimbData, this)(_climbID);
            return _climbID;
        }

    }
}
}
