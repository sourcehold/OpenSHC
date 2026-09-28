#include "../PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00499DC0
        void PathFindingState::updatePathLinkageLayerAtTileForSomeLogicalReason(int tile, int y)
        {
            byte bVar1;
            int iVar2;
            int* _ptrY;
            int iVar3;
            uint uVar4;
            uint uVar5;
            iVar2 = tile;
            uVar5 = 4;
            bVar1 = DAT_TileMapState::instance.PathLinkageLayer[tile];
            _ptrY = DAT_TileMapState::instance.directionTranslationMatrix[y] + 1;
            tile = 2;
            do {
                iVar3 = (*(int (*)[8])(_ptrY + -1))[0] + iVar2;
                if (((DAT_TileMapState::instance.LogicLayer[iVar3] & 0x30U) == 0)
                    && ((DAT_TileMapState::instance.LogicLayer[iVar3] & 0x4a5014b1U) == 0)) {
                    if ((bVar1 & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[uVar5 - 4]) == 0) {
                        uVar4 = uVar5 & 0x80000007;
                        if ((int)uVar4 < 0) {
                            uVar4 = (uVar4 - 1 | 0xfffffff8) + 1;
                        }
                        DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                            = DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                            & ~DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[uVar4];
                    } else {
                        uVar4 = uVar5 & 0x80000007;
                        if ((int)uVar4 < 0) {
                            uVar4 = (uVar4 - 1 | 0xfffffff8) + 1;
                        }
                        DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                            = DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                            | DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[uVar4];
                    }
                }
                iVar3 = *_ptrY + iVar2;
                if (((DAT_TileMapState::instance.LogicLayer[iVar3] & 0x30U) == 0)
                    && ((DAT_TileMapState::instance.LogicLayer[iVar3] & 0x4a5014b1U) == 0)) {
                    if ((bVar1 & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[uVar5 - 3]) == 0) {
                        uVar4 = uVar5 + 1 & 0x80000007;
                        if ((int)uVar4 < 0) {
                            uVar4 = (uVar4 - 1 | 0xfffffff8) + 1;
                        }
                        DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                            = DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                            & ~DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[uVar4];
                    } else {
                        uVar4 = uVar5 + 1 & 0x80000007;
                        if ((int)uVar4 < 0) {
                            uVar4 = (uVar4 - 1 | 0xfffffff8) + 1;
                        }
                        DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                            = DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                            | DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[uVar4];
                    }
                }
                iVar3 = _ptrY[1] + iVar2;
                if (((DAT_TileMapState::instance.LogicLayer[iVar3] & 0x30U) == 0)
                    && ((DAT_TileMapState::instance.LogicLayer[iVar3] & 0x4a5014b1U) == 0)) {
                    if ((bVar1 & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[uVar5 - 2]) == 0) {
                        uVar4 = uVar5 + 2 & 0x80000007;
                        if ((int)uVar4 < 0) {
                            uVar4 = (uVar4 - 1 | 0xfffffff8) + 1;
                        }
                        DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                            = DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                            & ~DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[uVar4];
                    } else {
                        uVar4 = uVar5 + 2 & 0x80000007;
                        if ((int)uVar4 < 0) {
                            uVar4 = (uVar4 - 1 | 0xfffffff8) + 1;
                        }
                        DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                            = DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                            | DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[uVar4];
                    }
                }
                iVar3 = _ptrY[2] + iVar2;
                if (((DAT_TileMapState::instance.LogicLayer[iVar3] & 0x30U) == 0)
                    && ((DAT_TileMapState::instance.LogicLayer[iVar3] & 0x4a5014b1U) == 0)) {
                    if ((bVar1 & DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[uVar5 - 1]) == 0) {
                        uVar4 = uVar5 + 3 & 0x80000007;
                        if ((int)uVar4 < 0) {
                            uVar4 = (uVar4 - 1 | 0xfffffff8) + 1;
                        }
                        DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                            = DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                            & ~DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[uVar4];
                    } else {
                        uVar4 = uVar5 + 3 & 0x80000007;
                        if ((int)uVar4 < 0) {
                            uVar4 = (uVar4 - 1 | 0xfffffff8) + 1;
                        }
                        DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                            = DAT_TileMapState::instance.PathLinkageLayer[iVar3]
                            | DAT_ClimbLogicDefinedData::instance.BitFlagHelperForPathLinkage[uVar4];
                    }
                }
                _ptrY = _ptrY + 4;
                uVar5 = uVar5 + 4;
                tile = tile + -1;
            } while (tile != 0);
            return;
        }

    }
}
}
