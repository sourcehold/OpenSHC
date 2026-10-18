#include "OpenSHC/Map.func.hpp"

#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "../TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitLogicState;
        using Map::Units::UnitType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051C2D0
        void TroopValueState::updateArcherBrazierProximityFlags()
        {
            BOOLEnum isAIPlayerWithKeep;
            int _isBrazierNearby;
            Unit* _pUnit;
            int _unitID;
            _unitID = 1;
            if (1 < DAT_UnitsState::instance.maxUnitCount) {
                _pUnit = &DAT_UnitsState::instance.units[1];
                do {
                    if (_pUnit->logicalState != Map::Units::ULS_INVISIBLE
                        && (isAIPlayerWithKeep = MACRO_CALL_MEMBER(
                                Map::Units::TroopValueState_Func::getPlayerNot1AndHasKeep, this)((int)_pUnit->owner),
                            isAIPlayerWithKeep)
                        && (_pUnit->unitType == Map::Units::UT_E_ARCHER
                            || (_pUnit->unitType == Map::Units::UT_A_ARCHER))
                        && !_pUnit->dying) {
                        _isBrazierNearby = MACRO_CALL_MEMBER(
                            Map::Entities::EntityState_Func::isBrazierNearby, DAT_EntityState::ptr)((int)_pUnit->x,
                            (int)(_pUnit->y), (int)(_pUnit->buildingHeight + _pUnit->terrainOrClimbHeight));
                        _pUnit->field297_0x40d = _isBrazierNearby != 0;
                    }
                    _unitID = _unitID + 1;
                    _pUnit = _pUnit + 1;
                } while (_unitID < DAT_UnitsState::instance.maxUnitCount);
            }
        }

    }
}
}
