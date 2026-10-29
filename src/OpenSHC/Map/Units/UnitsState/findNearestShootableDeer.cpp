#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00537880
        int UnitsState::findNearestShootableDeer(int unitID)
        {
            int _bestUnitID = 0;
            int _shooterX = this->units[unitID].x;
            int _shooterY = this->units[unitID].y;
            int _bestDistance = 100000;
            int _minimumDistance = 20;
            while (true) {
                for (int _deerUnitID = 1; _deerUnitID < (int)this->maxUnitCount; ++_deerUnitID) {
                    if (this->units[_deerUnitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                        continue;
                    }
                    if (this->units[_deerUnitID].dying != 0) {
                        continue;
                    }
                    if (this->units[_deerUnitID].owner != 0) {
                        continue;
                    }
                    if (this->units[_deerUnitID].unitType != OpenSHC::Map::Units::UT_ANTELOPESHDEER) {
                        continue;
                    }
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(
                        _shooterX, _shooterY, this->units[_deerUnitID].x, this->units[_deerUnitID].y);
                    if (DAT_DirectionAlgorithmState::instance.distanceHigh <= _minimumDistance) {
                        continue;
                    }
                    if (DAT_DirectionAlgorithmState::instance.distanceHigh < 0x36) {
                        int _shotResult = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Entities::EntityState_Func::arrowShootingRelated, DAT_EntityState::ptr)(
                            this->units[unitID].microXPosition, this->units[unitID].microYPosition,
                            this->units[unitID].buildingHeight + 0x1e + this->units[unitID].terrainOrClimbHeight,
                            this->units[_deerUnitID].microXPosition, this->units[_deerUnitID].microYPosition,
                            this->units[_deerUnitID].terrainOrClimbHeight + 0x1a
                                + this->units[_deerUnitID].buildingHeight);
                        if ((uint)(_shotResult + -1) > 0x1af) {
                            continue;
                        }
                    }
                    if (DAT_DirectionAlgorithmState::instance.distanceHigh < _bestDistance) {
                        _bestDistance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                        _bestUnitID = _deerUnitID;
                    }
                }
                if (_bestUnitID != 0 || _minimumDistance != 20) {
                    return _bestUnitID;
                }
                _minimumDistance = 5;
            }
        }
    }
}
}
