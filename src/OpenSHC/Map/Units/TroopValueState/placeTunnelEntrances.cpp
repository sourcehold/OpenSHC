#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B570
        int TroopValueState::placeTunnelEntrances(int tribeID)
        {
            int const unitID = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
            int const tentPointIndex = MACRO_CALL_MEMBER(
                Map::Navigation::PathFindingState_Func::algFindAttackAngle, DAT_PathFindingState::ptr)(
                200, DAT_UnitsState::instance.units[unitID].x, DAT_UnitsState::instance.units[unitID].y, tribeID);
            if (tentPointIndex) {
                short const previousSiegeIndex = DAT_TribesState::instance.tribes[tribeID].siegeIndexValue1;
                int const tribeUID = DAT_TribesState::instance.tribes[tribeID].uid;
                DAT_TribesState::instance.tribes[tribeID].siegeIndexValue2 = previousSiegeIndex;
                DAT_TroopValueState::instance.attackInfo.tentPointsValues[previousSiegeIndex].tribeID = 0;
                DAT_TroopValueState::instance.attackInfo.tentPointsValues[previousSiegeIndex].tribeUID = 0;
                int const tentPointY = DAT_TroopValueState::instance.attackInfo.tentPointsValues[tentPointIndex].y;
                DAT_TroopValueState::instance.attackInfo.tentPointsValues[tentPointIndex].tribeUID = tribeUID;
                int const playerID = DAT_TribesState::instance.tribes[tribeID].owner;
                DAT_TroopValueState::instance.attackInfo.tentPointsValues[tentPointIndex].tribeID = tribeID;
                DAT_TroopValueState::instance.attackInfo.tentPointsValues[tentPointIndex].three = 3;
                int const tentPointX = DAT_TroopValueState::instance.attackInfo.tentPointsValues[tentPointIndex].x;
                DAT_TribesState::instance.tribes[tribeID].siegeIndexValue1 = tentPointIndex;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                    playerID, tentPointX - 1, tentPointY - 1, Commands::M_MAPPER_TUNNEL_CONSTRUCTION, 3, 15);
                int const buildingID = DAT_TileMapState::instance.placedBuildingID;
                if (buildingID <= 0) {
                    return 0;
                }
                DAT_BuildingsState::instance.buildings[buildingID].attackWave
                    = DAT_TribesState::instance.tribes[tribeID].attackWave;
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                    tribeID, UIT_DIG_TUNNEL, buildingID, DAT_BuildingsState::instance.buildings[buildingID].uid, 0);
                return tentPointIndex;
            }
            return 0;
        }

    }
}
}
