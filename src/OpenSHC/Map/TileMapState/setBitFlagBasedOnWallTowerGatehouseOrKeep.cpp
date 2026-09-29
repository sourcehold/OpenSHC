#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Map/TileMapState/NeighbourFlagsAsm.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

#define NEIGHBOUR_FLAGS_MASK_WALL_OR_KEEP 0x10000100 // L_WALL_OR_GATEHOUSE | L_KEEP_NON_MANOR_HOUSE

namespace OpenSHC {
namespace Map {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FF870
    byte TileMapState::setBitFlagBasedOnWallTowerGatehouseOrKeep(int x, int y)
    {
        /*
          The body is the handwritten neighbour-flag macro; see NeighbourFlagsAsm.hpp. Written as C++
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
            OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile, DAT_ViewportRenderState::ptr)(x, y);

        MACRO_NEIGHBOUR_FLAGS_LOGIC_8(1, NEIGHBOUR_FLAGS_MASK_WALL_OR_KEEP)

        return this->bitFlag;
    }

}
}
