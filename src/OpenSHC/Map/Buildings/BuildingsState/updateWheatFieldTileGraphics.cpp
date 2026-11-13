#include "../BuildingsState.func.hpp"

#include "OpenSHC/DE/SHCDE/eGM.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040CF20
        void BuildingsState::updateWheatFieldTileGraphics(int buildingID)
        {
            // Unless all tiles are refreshed (field_0x18e024), only one tile is updated per call and the position to
            // continue from is stored in wheatFieldIndexToGrow
            int start = 0;
            int frame = 0;
            int unchangedLeft = 3;
            if (DAT_BuildingsState::instance.field_0x18e024 == 0) {
                start = DAT_BuildingsState::instance.buildings[buildingID].wheatFieldIndexToGrow;
            }
            for (int i = 0; i < 36; ++i) {
                int const tile
                    = this->buildings[buildingID]
                          .tileRefs[DAT_BuildingDefinedData::instance.WheatFieldTile_Unknown[(i + start) % 36] - 1];
                char const stage = DAT_TileMapState::instance.DamageLayer[tile];
                // Stages above 121 keep the frame of the previous tile
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
                    gfx = (DAT_TileMapState::instance.RandomLayer[tile] & 3)
                        + GMFirstPictureIndex::instance[OpenSHC::DE::SHCDE::GM_FARMLAND] + frame;
                } else {
                    gfx = GMFirstPictureIndex::instance[OpenSHC::DE::SHCDE::GM_FARMLAND] + frame;
                }
                if (gfx == DAT_TileMapState::instance.GfxLayer[tile]) {
                    if (--unchangedLeft != 0 && DAT_BuildingsState::instance.field_0x18e024 == 0) {
                        DAT_BuildingsState::instance.buildings[buildingID].wheatFieldIndexToGrow = (i + 1 + start) % 36;
                        return;
                    }
                } else {
                    DAT_TileMapState::instance.GfxLayer[tile] = gfx;
                    if (DAT_BuildingsState::instance.field_0x18e024 == 0) {
                        DAT_BuildingsState::instance.buildings[buildingID].wheatFieldIndexToGrow = (i + 1 + start) % 36;
                        return;
                    }
                }
            }
        }

    }
}
}
