#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051C2D0
        void TroopValueState::updateArcherBrazierProximityFlags()
        {
            for (int unitID = 1; unitID < DAT_UnitsState::instance.maxUnitCount; ++unitID) {
                Unit* const unit = &DAT_UnitsState::instance.units[unitID];
                if (unit->logicalState == Map::Units::ULS_INVISIBLE) {
                    continue;
                }
                BOOLEnum const isAIPlayerWithKeep
                    = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getPlayerNot1AndHasKeep, this)(unit->owner);
                if (!isAIPlayerWithKeep) {
                    continue;
                }
                if ((unit->unitType == Map::Units::UT_E_ARCHER || unit->unitType == Map::Units::UT_A_ARCHER)
                    && !unit->dying) {
                    BOOLEnum const isBrazierNearby = MACRO_CALL_MEMBER(Map::Entities::EntityState_Func::isBrazierNearby,
                        DAT_EntityState::ptr)(unit->x, unit->y, unit->buildingHeight + unit->terrainOrClimbHeight);
                    unit->field_0x40d = isBrazierNearby != 0;
                }
            }
        }

    }
}
}
