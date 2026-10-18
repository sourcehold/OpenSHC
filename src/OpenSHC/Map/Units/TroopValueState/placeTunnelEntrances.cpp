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

        using Map::Units::UnitInstructionType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B570
        int TroopValueState::placeTunnelEntrances(int tribeID)
        {
            int const _unitID = (int)DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
            /*
              finds a route from target to siege engine location?
             */
            int _tentPointIndex = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::algFindAttackAngle,
                DAT_PathFindingState::ptr)(200, (uint)(DAT_UnitsState::instance.units[_unitID].x),
                (uint)(DAT_UnitsState::instance.units[_unitID].y), tribeID);
            if (_tentPointIndex) {
                short const _previousSiegeIndex = DAT_TribesState::instance.tribes[tribeID].siegeIndexValue1;
                int _tribeUID = DAT_TribesState::instance.tribes[tribeID].uid;
                DAT_TribesState::instance.tribes[tribeID].siegeIndexValue2 = _previousSiegeIndex;
                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_previousSiegeIndex].tribeID = 0;
                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_previousSiegeIndex].tribeUID = 0;
                int const _tentPointY = DAT_TroopValueState::instance.attackInfo.tentPointsValues[_tentPointIndex].y;
                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_tentPointIndex].tribeUID = _tribeUID;
                int const playerID = DAT_TribesState::instance.tribes[tribeID].owner;
                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_tentPointIndex].tribeID = tribeID;
                DAT_TroopValueState::instance.attackInfo.tentPointsValues[_tentPointIndex].three = 3;
                _tribeUID = DAT_TroopValueState::instance.attackInfo.tentPointsValues[_tentPointIndex].x;
                DAT_TribesState::instance.tribes[tribeID].siegeIndexValue1 = (short)_tentPointIndex;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                    playerID, _tribeUID + -1, _tentPointY + -1, (MappersEnum)((int)(66)), 3, 0xf);
                _tribeUID = DAT_TileMapState::instance.placedBuildingID;
                if (0 < _tribeUID) {
                    DAT_BuildingsState::instance.buildings[_tribeUID].attackWave
                        = (int)DAT_TribesState::instance.tribes[tribeID].attackWave;
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                        tribeID, ((UnitInstructionType)0x15), _tribeUID,
                        DAT_BuildingsState::instance.buildings[_tribeUID].uid, 0);
                    return _tentPointIndex;
                }
            }
            return 0;
        }

    }
}
}
