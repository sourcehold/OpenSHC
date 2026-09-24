#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x00410920
        undefined4 BuildingsState::getBuildingFlammabilityFactor(int buildingID)
        {
            switch (this->buildings[buildingID].buildingType) {
            case BT_HOVEL:
            case BT_WOODCUTTERSHUT:
            case BT_OXTETHER:
            case BT_IRONMINE:
            case BT_HUNTERSHUT:
            case BT_MERCENARYPOST:
            case BT_BARRACKS:
            case BT_ARMORY:
            case BT_FLETCHER:
            case BT_POLETURNER:
            case BT_ARMOURER:
            case BT_TANNER:
            case BT_BREWERY:
            case BT_GRANARY:
            case BT_QUARRY:
            case BT_APOTHECARY:
            case BT_ENGINEERSGUILD:
            case BT_TUNNELERSGUILD:
            case BT_MARKETPLACE:
            case BT_WHEATFARM:
            case BT_HOPFARM:
            case BT_APPLEFARM:
            case BT_DAIRYFARM:
            case BT_MILL:
            case BT_STABLES:
            case BT_CHAPEL:
            case BT_CHURCH:
            case BT_CATHEDRAL:
            case BT_GALLOWS:
            case BT_STOCKS:
            case BT_MAYPOLE:
            case BT_BURNINGSTAKE:
            case BT_GIBBET:
            case BT_STRETCHINGRACK:
            case BT_CHOPPINGBLOCK:
            case BT_DANCINGBEAR:
            case BT_OUTPOST_EUROPEAN:
            case BT_OUTPOST_ARABIAN:
                return 1;
            case BT_BLACKSMITH:
            case BT_BAKERY:
            case BT_INN:
            case BT_OILSMELTER:
                return 5;
            case BT_PARADEGROUND:
            case BT_CAMPGROUND:
            case BT_PARADEGROUND2:
            case BT_PARADEGROUND3:
            case BT_PARADEGROUND4:
            case BT_PARADEGROUND5:
                return 4;
            default:
                return 0;
            }
        }

    }
}
}
