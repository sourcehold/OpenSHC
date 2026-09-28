
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_PLAIN2_AND_PITCH;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005116E0
    int TileMapState::placePitchDitch(undefined4 playerID, uint x, uint y)
    {
        if (x > 399 || y > 399) {
            return 0;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
            return 0;
        }

        int existingPitchDitchID = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getPitchDitchIDForTile, this)(
            DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x);
        if (existingPitchDitchID != 0) {
            return existingPitchDitchID;
        }

        for (int pitchDitchID = 1; pitchDitchID < 4000; pitchDitchID++) {
            if (this->pitchDitches[pitchDitchID].owner != 0) {
                continue;
            }

            if (this->maxPitchDitchCount <= pitchDitchID) {
                this->maxPitchDitchCount = pitchDitchID + 1;
            }
            this->pitchDitches[pitchDitchID].owner = (short)playerID;
            this->pitchDitches[pitchDitchID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
            DAT_GameCore::instance.uniqueGameObjectTracker = DAT_GameCore::instance.uniqueGameObjectTracker + 1;
            this->pitchDitches[pitchDitchID].y = (short)y;
            this->pitchDitches[pitchDitchID].x = (short)x;
            this->pitchDitches[pitchDitchID].state = 0;
            this->pitchDitches[pitchDitchID].field7_0x12 = 0;
            this->pitchDitches[pitchDitchID].tile
                = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            this->pitchDitches[pitchDitchID].rng = SEC_RNG::instance.currentNumber2;
            if (this->HeightLayer[this->pitchDitches[pitchDitchID].tile] < 5) {
                this->HeightLayer[this->pitchDitches[pitchDitchID].tile] = 0;
            } else {
                this->HeightLayer[this->pitchDitches[pitchDitchID].tile]
                    = this->HeightLayer[this->pitchDitches[pitchDitchID].tile] - 4;
            }
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            this->LogicLayer[this->pitchDitches[pitchDitchID].tile]
                = this->LogicLayer[this->pitchDitches[pitchDitchID].tile] | L_PLAIN2_AND_PITCH;
            this->MiscDisplayLayer[this->pitchDitches[pitchDitchID].tile]
                = this->MiscDisplayLayer[this->pitchDitches[pitchDitchID].tile] & 0xbfff;
            this->MiscDisplayLayer[this->pitchDitches[pitchDitchID].tile]
                = this->MiscDisplayLayer[this->pitchDitches[pitchDitchID].tile] & 0xdfff;
            this->ChangedLayer[this->pitchDitches[pitchDitchID].tile] = 2;
            return pitchDitchID;
        }
        return 0;
    }

}
}
