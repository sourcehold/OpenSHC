#include "../UnitsState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

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
            for (int i = 0; i < 9; i++) {
                this->unitCountOfSelection[i] = 0;
            }
            for (int unitID = 0; unitID < 2500; ++unitID) {
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(Unit), 0, &this->units[unitID]);
            }
            this->maxUnitCount = 2500;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_TileMapState::instance.UnitLayer), 0, DAT_TileMapState::instance.UnitLayer);
        }

    }
}
}
