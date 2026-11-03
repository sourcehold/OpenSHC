#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040EFD0
        void BuildingsState::updateBuildingAreaTileGraphics(int param_1)
        {
            for (int i = 0; i < 23; ++i) {
                int tile = this->buildings[param_1].tileRefs[4 + i];
                int const damage = (char)DAT_TileMapState::instance.DamageLayer[tile];
                int const stage
                    = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getRubbleGraphicStageForDamageLevel,
                        DAT_TileMapState::ptr)(damage);
                int gfx = GMTotalPicturesProcessed::instance[14] + 55 + stage;
                if (gfx != DAT_TileMapState::instance.GfxLayer[tile]) {
                    DAT_TileMapState::instance.GfxLayer[tile] = gfx;
                    DAT_TileMapState::instance.MiscDisplayLayer[tile] &= 0xfff3;
                }
            }
        }

    }
}
}
