#include "../WallAndPitchState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::Resources::ResourceType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00500E20
    void WallAndPitchState::destroyWall(int playerID, int count, int amount, int param_4)
    {
        if (param_4 == 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_STONE, amount);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                DAT_BuildingsState::ptr)(playerID, OpenSHC::Game::Resources::RT_WOOD, amount);
        }
        for (int i = 0; i < count; i++) {
            int _tile = this->receivedWallPlacementInfoArray[i].tile_OR_pitchID;
            int _y = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile];
            DAT_TileMapState::instance.DamageLayer[_tile] = this->receivedWallPlacementInfoArray[i].damage;
            DAT_TileMapState::instance.HeightLayer[_tile] = this->receivedWallPlacementInfoArray[i].height;
            DAT_TileMapState::instance.LogicLayer[_tile] = DAT_TileMapState::instance.LogicLayer[_tile] & 0xffb8f4ff;
            DAT_TileMapState::instance.LogicLayer[_tile]
                = this->receivedWallPlacementInfoArray[i].logic | DAT_TileMapState::instance.LogicLayer[_tile];
            int _tileDelta = _tile - DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(_y, _tile);
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                DAT_PathFindingState::ptr)(9, (uint)_tileDelta, _y);
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::triggerMinimapRedraw, DAT_MinimapViewState::ptr)(1);
    }

}
}
