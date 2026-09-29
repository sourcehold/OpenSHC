
#include "OpenSHC/Map/Entities.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_PLAIN2_AND_PITCH;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005114C0
    void TileMapState::updatePitchDitches()
    {
        if (DAT_GameState::instance.gameTicksLoadBalancer % 10 == 3) {
            this->maxPitchDitchCount = 0;
            for (int id = 1; id < 4000; id++) {
                if (this->pitchDitches[id].owner != 0) {
                    this->maxPitchDitchCount = id + 1;
                }
            }
        }

        for (int id = 1; id < this->maxPitchDitchCount; id++) {
            if (this->pitchDitches[id].owner == 0) {
                continue;
            }
            int tile = this->pitchDitches[id].tile;
            if ((this->LogicLayer[tile] & L_PLAIN2_AND_PITCH) == 0 || this->pitchDitches[id].state == -1) {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::destroyPitchDitch, this)(id);
            } else if (this->pitchDitches[id].state == 0) {
                /* the original increments the state rather than storing the literal */
                this->pitchDitches[id].state = this->pitchDitches[id].state + 1;
                this->pitchDitches[id].field7_0x12 = 0;
            } else if (this->pitchDitches[id].state == 2) {
                this->pitchDitches[id].field7_0x12 = this->pitchDitches[id].field7_0x12 + 1;
                if (this->pitchDitches[id].field7_0x12 == 0x14) {
                    this->pitchDitches[id].state = this->pitchDitches[id].state + 1;
                    this->pitchDitches[id].field7_0x12 = 0;
                    uint height = this->HeightLayer[tile];
                    /* the fire spreads to the four adjacent ditches that are still unlit */
                    for (int i = 0; i < 4; i++) {
                        int neighbour = DAT_ViewportRenderState::instance
                                            .translationMatrix[this->pitchDitches[id].y
                                                + DAT_TerrainDefinedData::instance.field2477_0x376c[i].y]
                                            .addXgetTile
                            + this->pitchDitches[id].x + DAT_TerrainDefinedData::instance.field2477_0x376c[i].x;
                        if ((this->LogicLayer[neighbour] & L_PLAIN2_AND_PITCH) == 0) {
                            continue;
                        }
                        int other = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getPitchDitchIDForTile, this)(neighbour);
                        if (other == 0 || this->pitchDitches[other].state != 1) {
                            continue;
                        }
                        if (abs((int)(height - this->HeightLayer[neighbour])) < 0x19) {
                            MACRO_CALL(OpenSHC::Map::Entities_Func::SetPlaceOnFire)(this->pitchDitches[other].owner,
                                this->pitchDitches[other].x * 8, this->pitchDitches[other].y * 8,
                                this->HeightLayer[this->pitchDitches[other].tile], 3);
                            this->pitchDitches[other].state = 2;
                        }
                    }
                }
            } else if (this->pitchDitches[id].state == 3) {
                this->pitchDitches[id].field7_0x12 = this->pitchDitches[id].field7_0x12 + 1;
                if (this->pitchDitches[id].field7_0x12 == 200) {
                    this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
                    this->pitchDitches[id].state = -1;
                }
            }
        }
    }

}
}
