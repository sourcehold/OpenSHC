#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Entities/Entity.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004038B0
    void Version::SetFlagEntityColor()
    {
        for (DAT_CurrentEntityID::instance = 1; (int)DAT_CurrentEntityID::instance < 3000;
            ++DAT_CurrentEntityID::instance) {
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState == 2
                && (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].entityType
                        == Entities::ET_FLAG_1
                    || DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].entityType
                        == Entities::ET_FLAG_4
                    || DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].entityType
                        == Entities::ET_FLAG_2
                    || DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].entityType
                        == Entities::ET_FLAG_3)) {
                DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].colorUnk
                    = DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].owner;
            }
        }
    }

}
}
