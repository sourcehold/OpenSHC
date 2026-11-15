#include "../TileMapState.func.hpp"

#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Map/TileMapState/NeighbourFlagsGlobalAsm.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

#define NEIGHBOUR_FLAGS_MASK_WALL_OR_KEEP 0x10000100 // L_WALL_OR_GATEHOUSE | L_KEEP_NON_MANOR_HOUSE

/* the original was built without optimisation: this spilled to [ebp - 4] and reloaded for every access */
#pragma optimize("", off)

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004FF870
    uint TileMapState::setBitFlagBasedOnWallTowerGatehouseOrKeep(int x, int y)
    {
        /*
          The body is the handwritten neighbour-flag macro; see NeighbourFlagsGlobalAsm.hpp. Written as C++
          it would be:

          this->bitFlag = 0;
          if ((this->ptr_LogicLayer[this->DAT_SomeTile + 1] & (L_WALL_OR_GATEHOUSE | L_KEEP_NON_MANOR_HOUSE)) != 0) {
              this->bitFlag = 0x20;
          }
          ... and so on for the eight neighbours, where the north row is offset by
          ptr_MovementDirectionTranslationMatrix[DAT_SomeY * 8 + 0] and the south row by [+ 4].
        */
        this->DAT_SomeY = y;
        this->DAT_SomeTile = MACRO_CALL_MEMBER(
            OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile, &DAT_ViewportRenderState::instance)(x, y);

        MACRO_NEIGHBOUR_FLAGS_GLOBAL_LOGIC_8(1, NEIGHBOUR_FLAGS_MASK_WALL_OR_KEEP)

        return this->bitFlag;
    }

}
}

#pragma optimize("", on)
