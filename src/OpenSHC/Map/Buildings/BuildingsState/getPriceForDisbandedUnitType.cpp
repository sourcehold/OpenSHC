#include "../BuildingsState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040C800
        void BuildingsState::getPriceForDisbandedUnitType(UnitType unitType, int* outPrice)
        {
            switch (unitType) {
            case Units::UT_E_ARCHER:
                *outPrice = 12;
                return;
            case Units::UT_E_SPEAR:
                *outPrice = 8;
                return;
            case Units::UT_E_PIKE:
                *outPrice = 20;
                return;
            case Units::UT_E_MACE:
                *outPrice = 20;
                return;
            case Units::UT_TUNNELER:
            case Units::UT_E_XBOW:
                *outPrice = 20;
                return;
            case Units::UT_E_SWORD:
                *outPrice = 40;
                return;
            case Units::UT_E_KNIGHT:
                *outPrice = 40;
                return;
            case Units::UT_E_LADDER:
                *outPrice = 1;
                return;
            case Units::UT_E_ENGINEER:
                *outPrice = 30;
                return;
            case Units::UT_E_MONK:
                *outPrice = 10;
                return;
            case Units::UT_S_CATAPULT:
                *outPrice = this->buildingCosts[BT_CATAPULT].requiredGold;
                return;
            case Units::UT_S_TREBUCHET:
                *outPrice = this->buildingCosts[BT_TREBUCHET].requiredGold;
                return;
            case Units::UT_S_MANGONEL:
                *outPrice = this->buildingCosts[BT_MANGONEL].requiredGold;
                return;
            case Units::UT_S_BALLISTA:
                *outPrice = this->buildingCosts[BT_BALLISTA].requiredGold;
                return;
            case Units::UT_S_FBALLISTA:
                *outPrice = this->buildingCosts[BT_FIREBALLISTA].requiredGold;
                return;
            case Units::UT_S_SHIELD:
                *outPrice = this->buildingCosts[BT_SHIELD].requiredGold;
                return;
            // the original pairs the tower with the battering ram's cost and vice versa
            case Units::UT_S_TOWER:
                *outPrice = this->buildingCosts[BT_BATTERINGRAM].requiredGold;
                return;
            case Units::UT_S_BATTERINGRAM:
                *outPrice = this->buildingCosts[BT_SIEGETOWER].requiredGold;
                return;
            }
        }

    }
}
}
