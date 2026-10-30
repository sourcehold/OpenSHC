#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Entities/Entity.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_CurrentEntityID.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00404A70
    void Version::DeleteSeagull()
    {
        for (DAT_CurrentEntityID::instance = 1; (int)DAT_CurrentEntityID::instance < 3000;
            ++DAT_CurrentEntityID::instance) {
            if (DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].logicalState == 2
                && DAT_EntityState::instance.entityArray[DAT_CurrentEntityID::instance].entityType
                    == Entities::ET_SEAGULLUnk) {
                MACRO_CALL_MEMBER(Entities::EntityState_Func::deleteEntity, DAT_EntityState::ptr)(
                    DAT_CurrentEntityID::instance);
            }
        }
        for (int i = 0; i < 100; ++i) {
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                100, 0, &DAT_EntityState::instance.seagullArray[i]);
        }
    }

}
}
