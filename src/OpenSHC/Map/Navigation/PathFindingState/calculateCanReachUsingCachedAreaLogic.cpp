#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A5B00
        BOOLEnum PathFindingState::calculateCanReachUsingCachedAreaLogic(int tile1, int tile2)
        {
            int iVar1;
            AreaPairInt* pAVar2;
            BOOLEnum BVar3;
            int iVar4;
            int _area1;
            int _area2;
            _area2 = (int)(short)DAT_TileMapState::instance.PathConnectionLayer[tile2];
            _area1 = (int)(short)DAT_TileMapState::instance.PathConnectionLayer[tile1];
            if (_area1 == _area2) {
                return TRUE;
            }
            if ((_area1 == 0) || (_area2 == 0)) {
                return FALSE;
            }
            if (this->field48_0x90 == 0) {
                this->field48_0x90 = 1;
                this->searchQueue.acceptAreaPairArray1[0].area1 = -1;
                this->searchQueue.acceptAreaPairArray1[0].area2 = -1;
                this->searchQueue.rejectionAreaPairArray[0].area1 = -1;
                this->searchQueue.rejectionAreaPairArray[0].area2 = -1;
                this->searchQueue.acceptAreaPairArray1[1].area1 = -1;
                this->searchQueue.acceptAreaPairArray1[1].area2 = -1;
                this->searchQueue.rejectionAreaPairArray[1].area1 = -1;
                this->searchQueue.rejectionAreaPairArray[1].area2 = -1;
                this->searchQueue.acceptAreaPairArray1[2].area1 = -1;
                this->searchQueue.acceptAreaPairArray1[2].area2 = -1;
                this->searchQueue.rejectionAreaPairArray[2].area1 = -1;
                this->searchQueue.rejectionAreaPairArray[2].area2 = -1;
                this->searchQueue.acceptAreaPairArray1[3].area1 = -1;
                this->searchQueue.acceptAreaPairArray1[3].area2 = -1;
                this->searchQueue.rejectionAreaPairArray[3].area1 = -1;
                this->searchQueue.rejectionAreaPairArray[3].area2 = -1;
                this->searchQueue.acceptAreaPairArray1[4].area1 = -1;
                this->searchQueue.acceptAreaPairArray1[4].area2 = -1;
                this->searchQueue.rejectionAreaPairArray[4].area1 = -1;
                this->searchQueue.rejectionAreaPairArray[4].area2 = -1;
                this->searchQueue.acceptAreaPairArray1[5].area1 = -1;
                this->searchQueue.acceptAreaPairArray1[5].area2 = -1;
                this->searchQueue.rejectionAreaPairArray[5].area1 = -1;
                this->searchQueue.rejectionAreaPairArray[5].area2 = -1;
                this->searchQueue.acceptAreaPairArray1[6].area1 = -1;
                this->searchQueue.acceptAreaPairArray1[6].area2 = -1;
                this->searchQueue.rejectionAreaPairArray[6].area1 = -1;
                this->searchQueue.rejectionAreaPairArray[6].area2 = -1;
                this->searchQueue.acceptAreaPairArray1[7].area1 = -1;
                this->searchQueue.acceptAreaPairArray1[7].area2 = -1;
                this->searchQueue.rejectionAreaPairArray[7].area1 = -1;
                this->searchQueue.rejectionAreaPairArray[7].area2 = -1;
                this->searchQueue.acceptAreaPairArray1[8].area1 = -1;
                this->searchQueue.acceptAreaPairArray1[8].area2 = -1;
                this->searchQueue.rejectionAreaPairArray[8].area1 = -1;
                this->searchQueue.rejectionAreaPairArray[8].area2 = -1;
                this->searchQueue.acceptAreaPairArray1[9].area1 = -1;
                this->searchQueue.acceptAreaPairArray1[9].area2 = -1;
                this->searchQueue.rejectionAreaPairArray[9].area1 = -1;
                this->searchQueue.rejectionAreaPairArray[9].area2 = -1;
            } else {
                iVar4 = 0;
                pAVar2 = this->searchQueue.acceptAreaPairArray1;
                do {
                    iVar1 = pAVar2->area1;
                    if (iVar1 != -1) {
                        if ((iVar1 == _area1) && (pAVar2->area2 == _area2)) {
                            return TRUE;
                        }
                        if ((pAVar2->area2 == _area1) && (iVar1 == _area2)) {
                            return TRUE;
                        }
                    }
                    iVar4 = iVar4 + 1;
                    pAVar2 = pAVar2 + 1;
                } while (iVar4 < 10);
                iVar4 = 0;
                pAVar2 = this->searchQueue.rejectionAreaPairArray;
                do {
                    iVar1 = pAVar2->area1;
                    if (iVar1 != -1) {
                        if ((iVar1 == _area1) && (pAVar2->area2 == _area2)) {
                            return FALSE;
                        }
                        if ((pAVar2->area2 == _area1) && (iVar1 == _area2)) {
                            return FALSE;
                        }
                    }
                    iVar4 = iVar4 + 1;
                    pAVar2 = pAVar2 + 1;
                } while (iVar4 < 10);
            }
            BVar3 = MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::PathFindingState_Func::pathFindingWithBuildingsIncluded, this)(tile1
                    - DAT_ViewportRenderState::instance
                        .translationMatrix[(
                            short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile1]]
                        .addXgetTile,
                (uint)((short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile1]),
                (uint)(tile2
                    - DAT_ViewportRenderState::instance
                        .translationMatrix[(
                            short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile2]]
                        .addXgetTile),
                (uint)((short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile2]), 100000, 0);
            if (BVar3 != FALSE) {
                iVar4 = 0;
                pAVar2 = this->searchQueue.acceptAreaPairArray1;
                do {
                    if (pAVar2->area1 == -1) {
                        this->searchQueue.acceptAreaPairArray1[iVar4].area1 = _area1;
                        this->searchQueue.acceptAreaPairArray1[iVar4].area2 = _area2;
                        return TRUE;
                    }
                    iVar4 = iVar4 + 1;
                    pAVar2 = pAVar2 + 1;
                } while (iVar4 < 10);
                return TRUE;
            }
            iVar4 = 0;
            pAVar2 = this->searchQueue.rejectionAreaPairArray;
            do {
                if (pAVar2->area1 == -1) {
                    this->searchQueue.rejectionAreaPairArray[iVar4].area1 = _area1;
                    this->searchQueue.rejectionAreaPairArray[iVar4].area2 = _area2;
                    return FALSE;
                }
                iVar4 = iVar4 + 1;
                pAVar2 = pAVar2 + 1;
            } while (iVar4 < 10);
            return FALSE;
        }

    }
}
}
