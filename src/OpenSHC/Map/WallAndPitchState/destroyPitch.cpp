#include "../WallAndPitchState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::Resources::ResourceType;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00500EE0
    void WallAndPitchState::destroyPitch(int playerID, int count, int amount, int param_4)
    {
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain, DAT_BuildingsState::ptr)(
            playerID, OpenSHC::Game::Resources::RT_PITCH, amount / 4);
        for (int i = 0; i < count; i++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::destroyPitchDitch, DAT_TileMapState::ptr)(
                this->receivedWallPlacementInfoArray[i].tile_OR_pitchID);
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::triggerMinimapRedraw, DAT_MinimapViewState::ptr)(1);
    }

}
}
