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
        void PathFindingState::findNextTileInExistingSearchThatIsModuloDistanceAway(int modulo, int x, int y)
        {
            int iVar2;
            uint uVar3;
            uint uVar4;
            int* _pLastTile;
            uint uVar5;
            uint uVar6;
            int local_10;
            local_10 = 0;
            _pLastTile = this->searchQueue.tilesQueue + DAT_TribesState::instance.ALG_ResultTileIndex;
            while (true) {
                int iVar1 = *_pLastTile;
                if (0 < DAT_TileMapState::instance.CertainPathLayer[iVar1]
                    && (uVar3 = (iVar1
                                    - DAT_ViewportRenderState::instance
                                        .translationMatrix[DAT_ViewportRenderState::instance
                                                .tileTranslationMatrix_YComponent[iVar1]]
                                        .addXgetTile)
                            - x,
                        uVar5 = (int)uVar3 >> 0x1f,
                        uVar4 = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[iVar1] - y,
                        uVar6 = (int)uVar4 >> 0x1f,
                        (int)(((uVar4 ^ uVar6) - uVar6) + ((uVar3 ^ uVar5) - uVar5)) % modulo == 0)
                    && (iVar2 = DAT_TribesState::instance.ALG_ResultTileIndex,
                        DAT_TileMapState::instance.CertainPathLayer[iVar1] < 4000))
                    break;
                DAT_TribesState::instance.ALG_ResultTileIndex = DAT_TribesState::instance.ALG_ResultTileIndex + 1;
                _pLastTile = _pLastTile + 1;
                iVar2 = local_10;
                if ((4000 < DAT_TribesState::instance.ALG_ResultTileIndex)
                    || (DAT_TileMapState::instance.WalkLayer[iVar1]
                        != DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]]))
                    break;
            }
            local_10 = iVar2;
            DAT_TribesState::instance.ALG_ResultY = (int)this->searchQueue.yQueue[local_10];
            DAT_TribesState::instance.ALG_ResultX = this->searchQueue.tilesQueue[local_10]
                - DAT_ViewportRenderState::instance.translationMatrix[DAT_TribesState::instance.ALG_ResultY]
                      .addXgetTile;
            DAT_TribesState::instance.ALG_ResultTileIndex = local_10;
            return;
        }

    }
}
}
