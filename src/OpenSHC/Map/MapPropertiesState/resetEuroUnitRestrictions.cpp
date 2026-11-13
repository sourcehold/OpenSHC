#include "OpenSHC/Map/MapPropertiesState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004BB900
    void MapPropertiesState::resetEuroUnitRestrictions()
    {
        for (int i = 0; i < this->eventsCount; ++i) {
            switch (this->scenarioEvents[i].header.tl_type) {
            case 1:
                if (this->scenarioEvents[i].data.invasion.repeatMonths != 0) {
                    this->scenarioEvents[i].data.invasion.repeatMonths *= 12;
                }
                break;
            }
        }
        this->SEC_XbowProducible_save = 1;
        this->SEC_BowProducible_save = 1;
        this->SEC_PikeProducible_save = 1;
        this->SEC_SpearProducible_save = 1;
        this->SEC_SwordProducible_save = 1;
        this->SEC_MaceProducible_save = 1;
        for (int i = 0; i < 7; ++i) {
            this->barracksRecruitability.array.barracksRecruitability[i] = 1;
            this->SEC_MercRecruitable[i] = 1;
        }
    }

}
}
