#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049A2E0
        void PathFindingState::updatePathLinkageTileMapRelatedToSiegeTower(int param_1)
        {
            byte* pbVar1;
            int iVar2;
            int iVar3;
            int iVar4;
            iVar4 = (int)(short)DAT_BuildingsState::instance.buildings[param_1].x;
            iVar2 = (int)(short)DAT_BuildingsState::instance.buildings[param_1].y;
            DAT_TileMapState::instance
                .PathLinkageLayer[DAT_ViewportRenderState::instance.translationMatrix[iVar2 + -1].addXgetTile + iVar4
                    + 1]
                = DAT_TileMapState::instance
                      .PathLinkageLayer[DAT_ViewportRenderState::instance.translationMatrix[iVar2 + -1].addXgetTile
                          + iVar4 + 1]
                | 0x10;
            DAT_TileMapState::instance
                .PathLinkageLayer[DAT_ViewportRenderState::instance.translationMatrix[iVar2].addXgetTile + iVar4 + 1]
                = DAT_TileMapState::instance
                      .PathLinkageLayer[DAT_ViewportRenderState::instance.translationMatrix[iVar2].addXgetTile + iVar4
                          + 1]
                | 0x11;
            DAT_TileMapState::instance
                .PathLinkageLayer[DAT_ViewportRenderState::instance.translationMatrix[iVar2 + 2].addXgetTile + iVar4
                    + 1]
                = DAT_TileMapState::instance
                      .PathLinkageLayer[DAT_ViewportRenderState::instance.translationMatrix[iVar2 + 2].addXgetTile
                          + iVar4 + 1]
                | 0x11;
            iVar3 = DAT_ViewportRenderState::instance.translationMatrix[iVar2 + 1].addXgetTile + iVar4;
            DAT_TileMapState::instance
                .PathLinkageLayer[DAT_ViewportRenderState::instance.translationMatrix[iVar2 + 3].addXgetTile + iVar4
                    + 1]
                = DAT_TileMapState::instance
                      .PathLinkageLayer[DAT_ViewportRenderState::instance.translationMatrix[iVar2 + 3].addXgetTile
                          + iVar4 + 1]
                | 1;
            pbVar1 = (byte*)((int)DAT_TileMapState::instance.PathConnectionLayer + iVar3 + 0x2741f);
            *pbVar1 = *pbVar1 | 4;
            DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                = DAT_TileMapState::instance.PathLinkageLayer[iVar3] | 0x44;
            DAT_TileMapState::instance.PathLinkageLayer[iVar3 + 2]
                = DAT_TileMapState::instance.PathLinkageLayer[iVar3 + 2] | 0x44;
            DAT_TileMapState::instance.PathLinkageLayer[iVar3 + 3]
                = DAT_TileMapState::instance.PathLinkageLayer[iVar3 + 3] | 0x40;
            return;
        }

    }
}
}
