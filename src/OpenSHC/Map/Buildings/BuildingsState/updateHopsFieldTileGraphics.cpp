#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040EDF0
        void BuildingsState::updateHopsFieldTileGraphics(int buildingID)
        {
            // Unless all tiles are refreshed (field14_0x18e024), only one tile is updated per call and the position to
            // continue from is stored in padding_0x2fc
            int start = 0;
            int unchangedLeft = 3;
            if (DAT_BuildingsState::instance.field14_0x18e024 == 0) {
                start = *(short*)DAT_BuildingsState::instance.buildings[buildingID].padding_0x2fc;
            }
            for (int i = 0; i < 24; ++i) {
                int tile = (&this->buildings[buildingID].tileRef1)[(i + start) % 24];
                char stage = DAT_TileMapState::instance.DamageLayer[tile];
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

                int gfx = GMTotalPicturesProcessed::instance[14]
                    + (DAT_TileMapState::instance.RandomLayer[tile] & 1) * 9 + 37 + frame;
                if (gfx == DAT_TileMapState::instance.GfxLayer[tile]) {
                    if (--unchangedLeft == 0) {
                        continue;
                    }
                } else {
                    DAT_TileMapState::instance.GfxLayer[tile] = gfx;
                }
                if (DAT_BuildingsState::instance.field14_0x18e024 == 0) {
                    // Note: wraps at 36 instead of 24 like the tile index above
                    *(short*)DAT_BuildingsState::instance.buildings[buildingID].padding_0x2fc = (i + 1 + start) % 36;
                    return;
                }
            }
        }

    }
}
}
