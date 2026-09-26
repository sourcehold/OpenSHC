#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0041A760
        BuildingsState* BuildingsState::Constructor_BuildingsState()
        {
            this->field37_0x18e080 = timeGetTime();
            this->field14_0x18e024 = 1;
            this->pathLinkageKeepWasUpdatedUnk = 0;
            this->counter = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::clearBuildings, this)();
            this->maxBuildingsCount = 2000;
            return this;
        }

    }
}
}
