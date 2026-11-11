#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x005110B0
    int TileMapState::createMoatData(undefined4 playerID, uint x, uint y, int filled)
    {
        if (x > MC_MAP_XY_LIMIT_INCLUSIVE || y > MC_MAP_XY_LIMIT_INCLUSIVE) {
            return 0;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * MC_MAP_XY_LIMIT + x] == 0) {
            return 0;
        }

        int existingMoatID = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::returnOwnedMoatAtTile, this)(
            DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x);
        if (existingMoatID != 0) {
            return existingMoatID;
        }
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT
            && MACRO_CALL_MEMBER(
                   OpenSHC::Map::Buildings::BuildingsState_Func::hasEnoughGoldForMoat, DAT_BuildingsState::ptr)()
                == 0) {
            return 0;
        }

        for (int moatID = 1; moatID < countof(this->moats); moatID++) {
            if (this->moats[moatID].owner != 0) {
                continue;
            }

            if (moatID >= this->currentMoatCount) {
                this->currentMoatCount = moatID + 1;
            }
            this->moats[moatID].owner = playerID;
            this->moats[moatID].x = x;
            this->moats[moatID].y = y;
            this->moats[moatID].tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            this->moats[moatID].zeroOrTwo = 2;
            if (filled != 0) {
                this->moats[moatID].stage = 2;
                this->moats[moatID].fillProgress = 4;
            } else {
                this->moats[moatID].stage = 1;
                this->moats[moatID].fillProgress = 0;
            }
            this->moatTileCount += 1;
            return moatID;
        }
        return 0;
    }

}
}
