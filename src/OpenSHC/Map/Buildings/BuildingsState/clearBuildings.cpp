#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040A020
        void BuildingsState::clearBuildings()
        {
            this->structCount = 0;
            for (int i = 0; i < 2000; ++i) {
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(Building), 0, &this->buildings[i]);
            }
            this->maxBuildingsCount = 2000;
        }

    }
}
}
