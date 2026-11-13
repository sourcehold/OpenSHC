#include "../TileMapState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_PLAIN2_AND_PITCH;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x00500890
    void TileMapState::destroyPitchDitch(int pitchDitchID)
    {
        this->LogicLayer[this->pitchDitches[pitchDitchID].tile] &= ~L_PLAIN2_AND_PITCH;
        this->MiscDisplayLayer[this->pitchDitches[pitchDitchID].tile] &= ~0x2000;
        this->MiscDisplayLayer[this->pitchDitches[pitchDitchID].tile] &= ~0x4000;
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
