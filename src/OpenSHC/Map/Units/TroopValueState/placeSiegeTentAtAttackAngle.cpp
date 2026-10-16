#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitInstructionType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B310
        int TroopValueState::placeSiegeTentAtAttackAngle(int tribeID, MappersEnum commandBuildingType)
        {
            int _attackLocationIndex;
            int _offset;
            int _tribeUID;
            int _buildingID;
            short _unitID;
            PlayerID _playerID;
            short _siegeIndex;
            int _x;
            int _y;
            _unitID = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
            _attackLocationIndex
                = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::algFindAttackAngle,
                    DAT_PathFindingState::ptr)(200, (uint)((int)((int)DAT_UnitsState::instance.units[_unitID].x)),
                    (uint)((int)((int)DAT_UnitsState::instance.units[_unitID].y)), tribeID);
            if (_attackLocationIndex) {
                _siegeIndex = DAT_TribesState::instance.tribes[tribeID].siegeIndexValue1;
                _tribeUID = DAT_TribesState::instance.tribes[tribeID].uid;
                DAT_TribesState::instance.tribes[tribeID].siegeIndexValue2 = _siegeIndex;
                /*
                  fixme
                 */
                this->attackInfo.tentPointsValues[_siegeIndex].tribeID = 0;
                this->attackInfo.tentPointsValues[_siegeIndex].tribeUID = 0;
                this->attackInfo.tentPointsValues[_attackLocationIndex].tribeUID = _tribeUID;
                _y = this->attackInfo.tentPointsValues[_attackLocationIndex].y;
                _x = this->attackInfo.tentPointsValues[_attackLocationIndex].x;
                this->attackInfo.tentPointsValues[_attackLocationIndex].tribeID = tribeID;
                this->attackInfo.tentPointsValues[_attackLocationIndex].three = 3;
                _playerID = DAT_TribesState::instance.tribes[tribeID].owner;
                DAT_TribesState::instance.tribes[tribeID].siegeIndexValue1 = (short)_attackLocationIndex;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                    _playerID, _x + -1, _y + -1, commandBuildingType, 3, 0xf);
                _buildingID = DAT_TileMapState::instance.placedBuildingID;
                DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.placedBuildingID].attackWave
                    = (int)DAT_TribesState::instance.tribes[tribeID].attackWave;
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(
                    tribeID, Map::Units::UIT_CONSTRUCT_SIEGE_EQUIPMENTOIL_DUTYENGINEERRELATED, _buildingID,
                    DAT_BuildingsState::instance.buildings[_buildingID].uid, 0);
                return _attackLocationIndex;
            }
            return 0;
        }

    }
}
}
