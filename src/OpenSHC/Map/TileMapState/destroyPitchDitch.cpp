#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_PLAIN2_AND_PITCH;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00500890
    void TileMapState::destroyPitchDitch(int pitchDitchID)
    {
        this->LogicLayer[this->pitchDitches[pitchDitchID].tile]
            = this->LogicLayer[this->pitchDitches[pitchDitchID].tile] & ~L_PLAIN2_AND_PITCH;
        this->MiscDisplayLayer[this->pitchDitches[pitchDitchID].tile]
            = this->MiscDisplayLayer[this->pitchDitches[pitchDitchID].tile] & 0xdfff;
        this->MiscDisplayLayer[this->pitchDitches[pitchDitchID].tile]
            = this->MiscDisplayLayer[this->pitchDitches[pitchDitchID].tile] & 0xbfff;
        if ((this->LogicLayer[this->pitchDitches[pitchDitchID].tile] & L_WALL_OR_GATEHOUSE) == 0
            && this->BuildingLayer[this->pitchDitches[pitchDitchID].tile] == 0) {
            this->HeightLayer[this->pitchDitches[pitchDitchID].tile]
                = this->DefaultHeightLayer[this->pitchDitches[pitchDitchID].tile];
        }
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(4, this->pitchDitches[pitchDitchID].x, this->pitchDitches[pitchDitchID].y);
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            sizeof(PitchDitch), 0, &this->pitchDitches[pitchDitchID]);
    }

}
}
