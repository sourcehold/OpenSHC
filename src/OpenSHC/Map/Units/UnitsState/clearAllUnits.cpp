#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0052E7B0
        void UnitsState::clearAllUnits()
        {
            this->unitCount = 0;
            this->unknownInitially0_01 = 0;
            this->totalUnitsInSelection = 0;
            this->unitCountOfSelection[0] = 0;
            this->unitCountOfSelection[1] = 0;
            this->unitCountOfSelection[2] = 0;
            this->unitCountOfSelection[3] = 0;
            this->unitCountOfSelection[4] = 0;
            this->unitCountOfSelection[5] = 0;
            this->unitCountOfSelection[6] = 0;
            this->unitCountOfSelection[7] = 0;
            this->unitCountOfSelection[8] = 0;
            for (int unitID = 0; unitID < 2500; ++unitID) {
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    1168, '\0', &this->units[unitID]);
            }
            this->maxUnitCount = 2500;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                160800, '\0', DAT_TileMapState::instance.UnitLayer);
        }

    }
}
}
