#include "../EntityState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x00403980
        EntityState* EntityState::Constructor_EntityState()
        {
            this->classConstructionTime = timeGetTime();
            MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::clearEntityArrayAndSeagullArray, this)();
            this->fireCount = 0;
            return this;
        }

    }
}
}
