#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x005017A0
    void TileMapState::forceFullTileMapRedraw()
    {
        this->forceUpdateLogicalAndMiscDisplayLayers = TRUE;
        this->forceUpdateTextureTilemap = TRUE;
        this->forceUpdateGFXLayers = TRUE;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::setChangedLayerToThreeAndMapping0x40x40, this)();
    }

}
}
