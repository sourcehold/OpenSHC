#include "../TileMapState.func.hpp"

#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_PLAIN2_AND_PITCH;

    // FUNCTION: STRONGHOLDCRUSADER 0x005116E0
    int TileMapState::placePitchDitch(undefined4 playerID, uint x, uint y)
    {
        if (x > 399 || y > 399) {
            return 0;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
            return 0;
        }

        int const existingPitchDitchID = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getPitchDitchIDForTile,
            this)(DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x);
        if (existingPitchDitchID != 0) {
            return existingPitchDitchID;
        }

        for (int pitchDitchID = 1; pitchDitchID < 4000; pitchDitchID++) {
            if (this->pitchDitches[pitchDitchID].owner != 0) {
                continue;
            }

            if (pitchDitchID >= this->maxPitchDitchCount) {
                this->maxPitchDitchCount = pitchDitchID + 1;
            }
            this->pitchDitches[pitchDitchID].owner = playerID;
            this->pitchDitches[pitchDitchID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
            DAT_GameCore::instance.uniqueGameObjectTracker++;
            this->pitchDitches[pitchDitchID].y = y;
            this->pitchDitches[pitchDitchID].x = x;
            this->pitchDitches[pitchDitchID].field_0x12 = 0;
            this->pitchDitches[pitchDitchID].tile
                = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            this->pitchDitches[pitchDitchID].state = 0;
            this->pitchDitches[pitchDitchID].rng = SEC_RNG::instance.currentNumber2;
            if (this->HeightLayer[this->pitchDitches[pitchDitchID].tile] > 4) {
                this->HeightLayer[this->pitchDitches[pitchDitchID].tile] -= 4;
            } else {
                this->HeightLayer[this->pitchDitches[pitchDitchID].tile] = 0;
            }
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            this->LogicLayer[this->pitchDitches[pitchDitchID].tile] |= L_PLAIN2_AND_PITCH;
            this->MiscDisplayLayer[this->pitchDitches[pitchDitchID].tile] &= 0xbfff;
            this->MiscDisplayLayer[this->pitchDitches[pitchDitchID].tile] &= 0xdfff;
            this->ChangedLayer[this->pitchDitches[pitchDitchID].tile] = 2;
            return pitchDitchID;
        }
        return 0;
    }

}
}
