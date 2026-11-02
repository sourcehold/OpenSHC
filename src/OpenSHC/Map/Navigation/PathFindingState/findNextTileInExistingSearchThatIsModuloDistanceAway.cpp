#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00496F90
        void PathFindingState::findNextTileInExistingSearchThatIsModuloDistanceAway(int modulo, int ySpace, int y)
        {
            int result = 0;
            int generation = DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]];
            int index = DAT_TribesState::instance.ALG_ResultTileIndex;
            int* pTile = this->searchQueue.tilesQueue + index;
            int tileUnk;
            do {
                tileUnk = *pTile;
                int distance = DAT_TileMapState::instance.CertainPathLayer[tileUnk];
                int tileY = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tileUnk];
                if (distance > 0
                    && (abs(tileUnk - DAT_ViewportRenderState::instance.translationMatrix[tileY].addXgetTile - ySpace)
                           + abs(tileY - y))
                            % modulo
                        == 0
                    && distance < 4000) {
                    result = index;
                    break;
                }
                index = index + 1;
                pTile = pTile + 1;
                if (index > 4000)
                    break;
            } while (DAT_TileMapState::instance.WalkLayer[tileUnk] == generation);
            tileUnk = this->searchQueue.tilesQueue[result];
            DAT_TribesState::instance.ALG_ResultY = (int)this->searchQueue.yQueue[result];
            DAT_TribesState::instance.ALG_ResultX
                = tileUnk
                - DAT_ViewportRenderState::instance.translationMatrix[DAT_TribesState::instance.ALG_ResultY]
                      .addXgetTile;
            DAT_TribesState::instance.ALG_ResultTileIndex = result;
            return;
        }

    }
}
}
