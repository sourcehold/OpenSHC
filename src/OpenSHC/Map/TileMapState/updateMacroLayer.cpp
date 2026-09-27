
#include "OpenSHC/Map/TileMapState.func.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L2_BEACH;
    using OpenSHC::Map::LogicHelpers::L2_EARTH_AND_STONES;
    using OpenSHC::Map::LogicHelpers::L2_OASIS_GRASS;
    using OpenSHC::Map::LogicHelpers::L2_PLATEAU_HIGH;
    using OpenSHC::Map::LogicHelpers::L2_PLATEAU_MEDIUM;
    using OpenSHC::Map::LogicHelpers::L2_SCRUB;
    using OpenSHC::Map::LogicHelpers::L_DEFAULT_EARTH_OR_TEXTURE;
    using OpenSHC::Map::LogicHelpers::L_MARSH;
    using OpenSHC::Map::LogicHelpers::L_NONE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00511020
    void TileMapState::updateMacroLayer()
    {
        if ((int)this->forceUpdateMacroLayerFlag <= 0) {
            return;
        }

        this->forceUpdateMacroLayerFlag = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateMacroLayerRelated, this)(
            L_DEFAULT_EARTH_OR_TEXTURE, L2_SCRUB, 0);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateMacroLayerRelated, this)(L_MARSH, L_NONE, 0);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateMacroLayerRelated, this)(
            L_NONE, L2_EARTH_AND_STONES, 0);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateMacroLayerRelated, this)(L_NONE, L2_OASIS_GRASS, 0);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateMacroLayerRelated, this)(L_NONE, L2_BEACH, 0);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateMacroLayerRelated, this)(L_NONE, L2_PLATEAU_MEDIUM, 0);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateMacroLayerRelated, this)(L_NONE, L2_PLATEAU_HIGH, 0);
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateMacroLayerRelated2, this)();
        this->forceUpdateTextureTilemap = 1;
    }

}
}
