
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_MOAT_DUG_OR_PLANNED;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005005F0
    void TileMapState::clearMoat(int tile)
    {
        if ((this->LogicLayer[tile] & L_MOAT_DUG_OR_PLANNED) == 0) {
            return;
        }

        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearMoatDataAtTile, this)(tile
                - DAT_ViewportRenderState::instance
                    .translationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]]
                    .addXgetTile,
            DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]);
        this->LogicLayer[tile] = this->LogicLayer[tile] & ~L_MOAT_DUG_OR_PLANNED;
    }

}
}
