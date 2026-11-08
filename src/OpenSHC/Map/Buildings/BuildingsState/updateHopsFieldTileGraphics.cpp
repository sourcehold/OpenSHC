#include "../BuildingsState.func.hpp"

#include "OpenSHC/DE/SHCDE/eGM.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040EDF0
        void BuildingsState::updateHopsFieldTileGraphics(int buildingID)
        {
            // Unless all tiles are refreshed (field_0x18e024), only one tile is updated per call and the position to
            // continue from is stored in padding_0x2fc
            // Matching note: i is set in both arms rather than in the for. In the loop preheader it lets the
            // buildingID * 0xcb temporary take ebx ahead of start, unlike the original
            int start = 0;
            int unchangedLeft = 3;
            int i;
            if (DAT_BuildingsState::instance.field_0x18e024 == 0) {
                start = *(short*)DAT_BuildingsState::instance.buildings[buildingID].padding_0x2fc;
                i = 0;
            } else {
                i = 0;
            }
            for (; i < 24; ++i) {
                int const tile = this->buildings[buildingID].tileRefs[(i + start) % 24];
                char const stage = DAT_TileMapState::instance.DamageLayer[tile];
                // Matching note: the separate stage == 0 test is in the original; folding it into stage < 2 costs 2%
                int frame;
                if (stage == 0) {
                    frame = 0;
                } else if (stage < 2) {
                    frame = 0;
                } else if (stage < 4) {
                    frame = 1;
                } else if (stage < 6) {
                    frame = 2;
                } else if (stage < 8) {
                    frame = 3;
                } else if (stage < 10) {
                    frame = 4;
                } else if (stage < 12) {
                    frame = 5;
                } else if (stage < 14) {
                    frame = 6;
                } else if (stage < 28) {
                    frame = 7;
                } else if (stage < 32) {
                    frame = 8;
                } else {
                    frame = 0;
                }

                int const gfx = GMFirstPictureIndex::instance[OpenSHC::DE::SHCDE::GM_FARMLAND]
                    + (DAT_TileMapState::instance.RandomLayer[tile] & 1) * 9 + 37 + frame;
                if (gfx == DAT_TileMapState::instance.GfxLayer[tile]) {
                    if (--unchangedLeft == 0) {
                        continue;
                    }
                } else {
                    DAT_TileMapState::instance.GfxLayer[tile] = gfx;
                }
                if (DAT_BuildingsState::instance.field_0x18e024 == 0) {
                    // Note: wraps at 36 instead of 24 like the tile index above
                    *(short*)DAT_BuildingsState::instance.buildings[buildingID].padding_0x2fc = (i + 1 + start) % 36;
                    return;
                }
            }
        }

    }
}
}
