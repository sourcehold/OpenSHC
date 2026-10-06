#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00537700
        BOOLEnum UnitsState::findTunnelTarget(int originBuildingID, int targetPlayer)
        {
            if ((int)DAT_BuildingsState::instance.buildings[originBuildingID].tunnelerCounter < 0) {
                return FALSE;
            }
            int _distance;
            if ((int)DAT_BuildingsState::instance.buildings[originBuildingID].tunnelerCounter <= 0) {
                _distance = 20;
            } else if ((int)DAT_BuildingsState::instance.buildings[originBuildingID].tunnelerCounter <= 1) {
                _distance = 20;
            } else if ((int)DAT_BuildingsState::instance.buildings[originBuildingID].tunnelerCounter <= 2) {
                _distance = 40;
            } else if ((int)DAT_BuildingsState::instance.buildings[originBuildingID].tunnelerCounter <= 3) {
                _distance = 40;
            } else if ((int)DAT_BuildingsState::instance.buildings[originBuildingID].tunnelerCounter <= 4) {
                _distance = 80;
            } else if ((int)DAT_BuildingsState::instance.buildings[originBuildingID].tunnelerCounter <= 5) {
                _distance = 80;
            } else {
                DAT_BuildingsState::instance.buildings[originBuildingID].tunnelerCounter = -1;
                return FALSE;
            }
            ushort _buildingX = DAT_BuildingsState::instance.buildings[originBuildingID].x;
            ushort _tunnelStartY;
            if ((DAT_BuildingsState::instance.buildings[originBuildingID].tunnelerCounter & 1) != 0) {
                DAT_BuildingsState::instance.buildings[originBuildingID].someX = _buildingX - 1;
                _tunnelStartY = DAT_BuildingsState::instance.buildings[originBuildingID].y;
            } else {
                DAT_BuildingsState::instance.buildings[originBuildingID].someX = _buildingX;
                _tunnelStartY = DAT_BuildingsState::instance.buildings[originBuildingID].y - 1;
            }
            DAT_BuildingsState::instance.buildings[originBuildingID].tunnelerCounter
                = DAT_BuildingsState::instance.buildings[originBuildingID].tunnelerCounter + 1;
            DAT_BuildingsState::instance.buildings[originBuildingID].someY = _tunnelStartY;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::algTunnelerFindTarget,
                DAT_PathFindingState::ptr)(DAT_BuildingsState::instance.buildings[originBuildingID].owner, targetPlayer,
                _distance, DAT_BuildingsState::instance.buildings[originBuildingID].someX, (short)_tunnelStartY);
            if (DAT_PathFindingState::instance.ALG_TargetTile == 0) {
                return FALSE;
            }
            DAT_BuildingsState::instance.buildings[originBuildingID].tunnelerCounter = -1;
            return TRUE;
        }

    }
}
}
