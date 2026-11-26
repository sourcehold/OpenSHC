#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401690
        void EntityState::flagUnitsWithActiveEntity()
        {
            for (int i = 1; i < this->maxEntityCount; ++i) {
                if (this->entityArray[i].logicalState == 2 && this->entityArray[i].unitID > 0) {
                    DAT_UnitsState::instance.units[this->entityArray[i].unitID].field_0x39a = 1;
                }
            }
        }

    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
