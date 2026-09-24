#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040CF20
        void BuildingsState::updateWheatFieldTileGraphics(int buildingID)
        {
            // Unless all tiles are refreshed (field14_0x18e024), only one tile is updated per call and the position to
            // continue from is stored in padding_0x2fc
            int start = 0;
            int frame = 0;
            int unchangedLeft = 3;
            if (DAT_BuildingsState::instance.field14_0x18e024 == 0) {
                start = *(short*)DAT_BuildingsState::instance.buildings[buildingID].padding_0x2fc;
            }
            for (int i = 0; i < 36; ++i) {
                int tile = (&this->buildings[buildingID]
                        .tileRef1)[DAT_BuildingDefinedData::instance.WheatFieldTile_Unknown[(i + start) % 36] - 1];
                char stage = DAT_TileMapState::instance.DamageLayer[tile];
                if (stage == 0) {
                    frame = 0;
                } else if (stage < 1) {
                    frame = 0;
                } else if (stage < 2) {
                    frame = 4;
                } else if (stage < 5) {
                    frame = 8;
                } else if (stage < 8) {
                    frame = 12;
                } else if (stage < 11) {
                    frame = 16;
                } else if (stage < 101) {
                    frame = 20;
                } else if (stage < 102) {
                    frame = 28;
                } else if (stage < 103) {
                    frame = 32;
                } else if (stage < 120) {
                    frame = 32;
                } else if (stage == 120) {
                    frame = 24;
                } else if (stage == 121) {
                    frame = 36;
                }

                int gfx;
                if (frame < 36) {
                    gfx = (DAT_TileMapState::instance.RandomLayer[tile] & 3) + GMTotalPicturesProcessed::instance[14]
                        + frame;
                } else {
                    gfx = GMTotalPicturesProcessed::instance[14] + frame;
                }
                if (gfx == DAT_TileMapState::instance.GfxLayer[tile]) {
                    if (--unchangedLeft == 0) {
                        continue;
                    }
                } else {
                    DAT_TileMapState::instance.GfxLayer[tile] = gfx;
                }
                if (DAT_BuildingsState::instance.field14_0x18e024 == 0) {
                    *(short*)DAT_BuildingsState::instance.buildings[buildingID].padding_0x2fc = (i + 1 + start) % 36;
                    return;
                }
            }
        }

    }
}
}
