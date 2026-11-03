#include "../EntityState.func.hpp"

#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00401690
        void EntityState::flagUnitsWithActiveEntity()
        {
            for (int entityID = 1; entityID < (int)this->maxEntityCount; entityID++) {
                if (this->entityArray[entityID].logicalState == 2 && this->entityArray[entityID].unitID > 0) {
                    DAT_UnitsState::instance.units[this->entityArray[entityID].unitID].field233_0x39a = 1;
                }
            }
        }

    }
}
}
