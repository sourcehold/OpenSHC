#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Entities/Entity.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00408250
    void Version::UpgradeFirst25Entities()
    {
        for (DAT_CurrentEntityID::instance = 1; (int)DAT_CurrentEntityID::instance < 25;
            ++DAT_CurrentEntityID::instance) {
            int entityID = DAT_CurrentEntityID::instance;
            if (DAT_EntityState::instance.entityArray[entityID].logicalState == 2) {
                MACRO_CALL_MEMBER(Entities::EntityState_Func::removeEntityFromTileLinkedList, DAT_EntityState::ptr)(
                    entityID);
                MACRO_CALL_MEMBER(Entities::EntityState_Func::processEntityHitBuildingOrUnit, DAT_EntityState::ptr)(
                    entityID);
            }
        }
    }

}
}
