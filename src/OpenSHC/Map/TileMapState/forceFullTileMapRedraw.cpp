#include "../TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */

    // FUNCTION: STRONGHOLDCRUSADER 0x005017A0
    void TileMapState::forceFullTileMapRedraw()

    {
        this->forceUpdateLogicalAndMiscDisplayLayers = 1;
        this->forceUpdateTextureTilemap = 1;
        this->forceUpdateGFXLayers = 1;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setChangedLayerToThreeAndMapping0x40x40, this)();
        return;
    }

}
}
