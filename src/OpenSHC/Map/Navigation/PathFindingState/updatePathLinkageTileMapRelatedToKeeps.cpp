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
        // FUNCTION: STRONGHOLDCRUSADER 0x0049A1C0
        void PathFindingState::updatePathLinkageTileMapRelatedToKeeps(int buildingID)
        {
            byte* pbVar1;
            uint uVar2;
            int iVar3;
            int iVar4;
            short _orientation;
            _orientation = DAT_BuildingsState::instance.buildings[buildingID].orientation;
            if (_orientation == 4) {
                iVar4 = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y;
                iVar3 = (int)DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight / 2
                    + (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x;
                pbVar1 = (byte*)(DAT_ViewportRenderState::instance.translationMatrix[iVar4 + -1].addXgetTile + 0x1e1e4f8
                    + iVar3);
                *pbVar1 = *pbVar1 | 0x10;
                DAT_TileMapState::instance
                    .PathLinkageLayer[DAT_ViewportRenderState::instance.translationMatrix[iVar4].addXgetTile + iVar3]
                    = DAT_TileMapState::instance
                          .PathLinkageLayer[DAT_ViewportRenderState::instance.translationMatrix[iVar4].addXgetTile
                              + iVar3]
                    | 1;
                return;
            }
            if (_orientation == 6) {
                iVar3 = (short)DAT_BuildingsState::instance.buildings[buildingID].x + -1;
                iVar4 = (int)DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight / 2
                    + (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y;
            } else {
                uVar2 = DAT_BuildingsState::instance.buildings[buildingID].widthOrHeight;
                if (_orientation != 2) {
                    iVar4 = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y;
                    iVar3 = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].x + (int)uVar2 / 2;
                    pbVar1 = (byte*)(DAT_ViewportRenderState::instance.translationMatrix[uVar2 + iVar4 + -1].addXgetTile
                        + 0x1e1e4f8 + iVar3);
                    *pbVar1 = *pbVar1 | 0x10;
                    pbVar1 = (byte*)(DAT_ViewportRenderState::instance.translationMatrix[uVar2 + iVar4].addXgetTile
                        + 0x1e1e4f8 + iVar3);
                    *pbVar1 = *pbVar1 | 1;
                    return;
                }
                iVar3 = (short)DAT_BuildingsState::instance.buildings[buildingID].x + -1 + uVar2;
                iVar4 = (int)(short)DAT_BuildingsState::instance.buildings[buildingID].y + (int)uVar2 / 2;
            }
            iVar3 = DAT_ViewportRenderState::instance.translationMatrix[iVar4].addXgetTile + iVar3;
            DAT_TileMapState::instance.PathLinkageLayer[iVar3] = DAT_TileMapState::instance.PathLinkageLayer[iVar3] | 4;
            DAT_TileMapState::instance.PathLinkageLayer[iVar3 + 1]
                = DAT_TileMapState::instance.PathLinkageLayer[iVar3 + 1] | 0x40;
            return;
        }

    }
}
}
