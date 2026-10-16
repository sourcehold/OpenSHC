#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051C360
        int TroopValueState::getValueOfTroopType(UnitType unitType)
        {
            switch (unitType) {
            case Map::Units::UT_TUNNELER:
                return DAT_RenderingDefinedData::instance.TUNNELER;
            case Map::Units::UT_E_MONK:
                return DAT_RenderingDefinedData::instance.MONK;
            case Map::Units::UT_S_CATAPULT:
                return DAT_RenderingDefinedData::instance.CATAPULT;
            case Map::Units::UT_A_ARCHER:
                return DAT_RenderingDefinedData::instance.A_ARCHER;
            case Map::Units::UT_A_SLAVE:
                return DAT_RenderingDefinedData::instance.SLAVE;
            case Map::Units::UT_A_SLINGER:
                return DAT_RenderingDefinedData::instance.SLINGER;
            case Map::Units::UT_A_ASSASSIN:
                return DAT_RenderingDefinedData::instance.ASSASSIN;
            case Map::Units::UT_A_HARCHER:
                return DAT_RenderingDefinedData::instance.HARCHER;
            case Map::Units::UT_A_SWORDSMAN:
                return DAT_RenderingDefinedData::instance.A_SWORDSMAN;
            case Map::Units::UT_A_FIRETHROWER:
                return DAT_RenderingDefinedData::instance.FIRETHROWER;
            case Map::Units::UT_S_FBALLISTA:
                return DAT_RenderingDefinedData::instance.S_FBALLISTA;
            }
            if ((0x15 < (int)unitType) && ((int)unitType < 0x1f)) {
                return DAT_RenderingDefinedData::instance.NoRushTicks[unitType + Map::Units::UT_TUNNELER];
            }
            return 0;
        }

    }
}
}
