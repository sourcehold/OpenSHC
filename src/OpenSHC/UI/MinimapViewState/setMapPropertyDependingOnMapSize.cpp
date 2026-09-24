#include "OpenSHC/UI/MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B6640
    void MinimapViewState::setMapPropertyDependingOnMapSize(uint x, int y)
    {
        if (DAT_TileMapState::instance.mapSize > 200) {
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapTileStripWithLuminescence, this)(
                4, 2, 1, x, y);
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapTileStripWithLuminescence, this)(
            4, 4, 2, x, y);
    }

}
}
