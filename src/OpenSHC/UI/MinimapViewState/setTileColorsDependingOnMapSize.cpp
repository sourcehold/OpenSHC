#include "OpenSHC/UI/MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B6680
    void MinimapViewState::setTileColorsDependingOnMapSize(int param_1, uint param_2)
    {
        if (200 < DAT_TileMapState::instance.mapSize) {
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapTileColors, this)(
                4, 2, 1, param_1, param_2);
            return;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapTileColors, this)(4, 4, 2, param_1, param_2);
    }

}
}
