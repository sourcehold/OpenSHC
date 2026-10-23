
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode2;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005110B0
    int TileMapState::createMoatData(undefined4 playerID, uint x, uint y, int filled)
    {
        if (x > 399 || y > 399) {
            return 0;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
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

        for (int moatID = 1; moatID < 16000; moatID++) {
            if (this->moats[moatID].owner != 0) {
                continue;
            }

            if (this->currentMoatCount <= moatID) {
                this->currentMoatCount = moatID + 1;
            }
            this->moats[moatID].owner = (char)playerID;
            this->moats[moatID].x = (short)x;
            this->moats[moatID].y = (short)y;
            this->moats[moatID].tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            this->moats[moatID].zeroOrTwo = 2;
            if (filled == 0) {
                this->moats[moatID].stage = 1;
                this->moats[moatID].fillProgress = 0;
                this->moatTileCount = this->moatTileCount + 1;
                return moatID;
            }
            this->moats[moatID].stage = 2;
            this->moats[moatID].fillProgress = 4;
            this->moatTileCount = this->moatTileCount + 1;
            return moatID;
        }
        return 0;
    }

}
}
