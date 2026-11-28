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

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B310
        int TroopValueState::placeSiegeTentAtAttackAngle(int tribeID, MappersEnum commandBuildingType)
        {
            int const targetUnitID = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
            int const attackLocationIndex
                = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::algFindAttackAngle,
                    DAT_PathFindingState::ptr)(200, DAT_UnitsState::instance.units[targetUnitID].x,
                    DAT_UnitsState::instance.units[targetUnitID].y, tribeID);
            if (attackLocationIndex) {
                short const previousSiegeIndex = DAT_TribesState::instance.tribes[tribeID].siegeIndexValue1;
                int const tribeUID = DAT_TribesState::instance.tribes[tribeID].uid;
                DAT_TribesState::instance.tribes[tribeID].siegeIndexValue2 = previousSiegeIndex;
                DAT_TroopValueState::instance.attackInfo.tentPointsValues[previousSiegeIndex].tribeID = 0;
                DAT_TroopValueState::instance.attackInfo.tentPointsValues[previousSiegeIndex].tribeUID = 0;
                DAT_TroopValueState::instance.attackInfo.tentPointsValues[attackLocationIndex].tribeUID = tribeUID;
                int const y = DAT_TroopValueState::instance.attackInfo.tentPointsValues[attackLocationIndex].y;
                int const x = DAT_TroopValueState::instance.attackInfo.tentPointsValues[attackLocationIndex].x;
                DAT_TroopValueState::instance.attackInfo.tentPointsValues[attackLocationIndex].tribeID = tribeID;
                DAT_TroopValueState::instance.attackInfo.tentPointsValues[attackLocationIndex].three = 3;
                int const playerID = DAT_TribesState::instance.tribes[tribeID].owner;
                DAT_TribesState::instance.tribes[tribeID].siegeIndexValue1 = attackLocationIndex;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                    playerID, x - 1, y - 1, commandBuildingType, 3, 15);
                int const buildingID = DAT_TileMapState::instance.placedBuildingID;
                DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.placedBuildingID].attackWave
                    = DAT_TribesState::instance.tribes[tribeID].attackWave;
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(tribeID,
                    Map::Units::UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED, buildingID,
                    DAT_BuildingsState::instance.buildings[buildingID].uid, 0);
                return attackLocationIndex;
            }
            return 0;
        }

    }
}
}
