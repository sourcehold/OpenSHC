#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        // FUNCTION: STRONGHOLDCRUSADER 0x0040EFD0
        ushort* BuildingsState::updateBuildingAreaTileGraphics(int param_1)
        {
            for (int i = 0; i < 23; ++i) {
                int tile = (&this->buildings[param_1].tileRef5)[i];
                int gfx = GMTotalPicturesProcessed::instance[14] + 55
                    + MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getRubbleGraphicStageForDamageLevel,
                        DAT_TileMapState::ptr)((char)DAT_TileMapState::instance.DamageLayer[tile]);
                if (gfx != DAT_TileMapState::instance.GfxLayer[tile]) {
                    DAT_TileMapState::instance.GfxLayer[tile] = gfx;
                    DAT_TileMapState::instance.MiscDisplayLayer[tile] &= 0xfff3;
                }
            }
            // The original has no meaningful return value
            return 0;
        }

    }
}
}
