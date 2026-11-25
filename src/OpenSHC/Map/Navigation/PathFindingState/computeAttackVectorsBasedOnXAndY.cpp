#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/MapConstants.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x004A69F0
        void PathFindingState::computeAttackVectorsBasedOnXAndY(int playerID)
        {
            this->calculations += 1;
            int attackVectorIndex = 0;
            this->searchQueue.readIndex = 0;
            while (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                uint y = (uint)this->searchQueue.yQueue[this->searchQueue.readIndex];
                int tile = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                uint x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                if (DAT_TileMapState::instance.CertainPathLayer[tile] != 100) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::budgetFloodFillOnCertainPathLayer, this)(
                        x, y, 100, 100);
                    DAT_GameState::instance.mapAndTime.attackVectors[playerID][attackVectorIndex].x = x;
                    DAT_GameState::instance.mapAndTime.attackVectors[playerID][attackVectorIndex].y = y;
                    DAT_GameState::instance.mapAndTime.attackVectors[playerID][attackVectorIndex].tribeUIDUnk = 0;
                    DAT_GameState::instance.mapAndTime.attackVectors[playerID][attackVectorIndex].tribeID = 0;
                    attackVectorIndex += 1;
                }
                if (attackVectorIndex >= 50) {
                    return;
                }
                this->searchQueue.readIndex += 1;
                if ((int)this->searchQueue.readIndex >= Map::MC_MAP_TILES_COUNT) {
                    this->searchQueue.readIndex = 0;
                }
            }
        }

    }
}
}
