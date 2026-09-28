#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"

#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    /*
      WARNING: Restarted to delay deadcode elimination for space: ram
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004FF870
    byte TileMapState::setBitFlagBasedOnWallTowerGatehouseOrKeep(int x, int y)
    {
        this->DAT_SomeY = y;
        this->DAT_SomeTile = MACRO_CALL_MEMBER(
            OpenSHC::Rendering::ViewportRenderState_Func::translateXYToTile, DAT_ViewportRenderState::ptr)(x, y);
        this->bitFlag = 0;
        if ((((uint*)this->ptr_LogicLayer)[this->DAT_SomeTile + 1] & (L_WALL_OR_GATEHOUSE | L_KEEP_NON_MANOR_HOUSE))
            != 0) {
            this->bitFlag = 0x20;
        }
        if ((((uint*)this->ptr_LogicLayer)[this->DAT_SomeTile - 1] & (L_WALL_OR_GATEHOUSE | L_KEEP_NON_MANOR_HOUSE))
            != 0) {
            this->bitFlag = this->bitFlag | 2;
        }

        uint* northRow = (uint*)this->ptr_LogicLayer + this->DAT_SomeTile
            + ((int*)this->ptr_MovementDirectionTranslationMatrix)[this->DAT_SomeY * 8];
        if ((northRow[-1] & (L_WALL_OR_GATEHOUSE | L_KEEP_NON_MANOR_HOUSE)) != 0) {
            this->bitFlag = this->bitFlag | 1;
        }
        if ((northRow[1] & (L_WALL_OR_GATEHOUSE | L_KEEP_NON_MANOR_HOUSE)) != 0) {
            this->bitFlag = this->bitFlag | 0x40;
        }
        if ((*northRow & (L_WALL_OR_GATEHOUSE | L_KEEP_NON_MANOR_HOUSE)) != 0) {
            this->bitFlag = this->bitFlag | 0x80;
        }

        uint* southRow = (uint*)this->ptr_LogicLayer + this->DAT_SomeTile
            + ((int*)this->ptr_MovementDirectionTranslationMatrix)[this->DAT_SomeY * 8 + 4];
        if ((southRow[-1] & (L_WALL_OR_GATEHOUSE | L_KEEP_NON_MANOR_HOUSE)) != 0) {
            this->bitFlag = this->bitFlag | 4;
        }
        if ((southRow[1] & (L_WALL_OR_GATEHOUSE | L_KEEP_NON_MANOR_HOUSE)) != 0) {
            this->bitFlag = this->bitFlag | 0x10;
        }
        if ((*southRow & (L_WALL_OR_GATEHOUSE | L_KEEP_NON_MANOR_HOUSE)) != 0) {
            this->bitFlag = this->bitFlag | 8;
        }
        return this->bitFlag;
    }

}
}
