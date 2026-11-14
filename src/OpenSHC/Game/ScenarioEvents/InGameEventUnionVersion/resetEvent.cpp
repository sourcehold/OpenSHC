#include "OpenSHC/Game/ScenarioEvents/InGameEventUnionVersion.func.hpp"

namespace OpenSHC {
namespace Game {
    namespace ScenarioEvents {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B7730
        BOOLEnum InGameEventUnionVersion::resetEvent()
        {
            this->header.month = 0;
            this->header.year = 1181;
            this->data.invasion.repeatMonths = 0;
            this->header.tl_type = 1;
            this->data.invasion.crusaderArabian = 0;
            this->data.invasion.totalUnitCount = 0;
            for (int i = 0; i < 24; ++i) {
                this->data.invasion.unitCountsPerUnitType[i] = 0;
            }
            this->data.invasion.invasionPoint = 0;
            return FALSE;
        }

    }
}
}
