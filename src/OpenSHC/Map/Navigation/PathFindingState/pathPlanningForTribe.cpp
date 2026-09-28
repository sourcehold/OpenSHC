#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Location::Point8ShortXY;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Type propagation algorithm not settling
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A79A0
        void PathFindingState::pathPlanningForTribe(
            uint tribeID, undefined4 targetUnitID, uint x, uint y, int unitCount, dword area, int playerID)
        {
            int iVar5;
            BOOLEnum BVar6;
            uint uVar7;
            uint uVar8;
            int (*paiVar9)[8];
            int* _pDest2;
            short* psVar10;
            uint uVar11;
            int* _pDest3;
            int iVar12;
            int _destIndex;
            int* _pDest1;
            _destIndex = 0;
            BOOL _assasinsTribe = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TribesState_Func::isTribeAllAssassins, DAT_TribesState::ptr)(tribeID);
            if (399 < x) {
                return;
            }
            if (399 < y) {
                return;
            }
            if (*(char*)(y * 400 + 0x21aec98 + x) == '\0') {
                return;
            }
            this->searchGeneration = this->searchGeneration + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            unitCount = unitCount * 2;
            if (unitCount < 500) {
                if (unitCount < 50) {
                    unitCount = 50;
                }
            } else {
                unitCount = 500;
            }
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.yQueue[0] = (short)y;
            this->searchQueue.xQueue[0] = (short)x;
            int iVar4 = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
            this->searchQueue.tilesQueue[0] = iVar4;
            DAT_TileMapState::instance.CertainPathLayer[iVar4] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                while (uVar11 = this->searchQueue.tilesQueue[this->searchQueue.readIndex], uVar11 < 0x13a10) {
                    int sVar1 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    int sVar2 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[uVar11];
                    if ((0x13a10 < this->searchQueue.currentDistance) || (10 < this->searchQueue.currentDistance))
                        break;
                    for (int _direction = 0; _direction < 8; _direction = _direction + 1) {
                        iVar12 = DAT_TileMapState::instance.directionTranslationMatrix[sVar2][_direction] + uVar11;
                        if (DAT_TileMapState::instance.WalkLayer[iVar12] != this->searchGeneration
                            && ((area == (int)(short)DAT_TileMapState::instance.PathConnectionLayer[iVar12]
                                    || (iVar5 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                                      calculateCanPlayerUnitsNavigateToAreaFromArea,
                                            this)(playerID, (dword)((int)(area)),
                                            (dword)((int)((
                                                int)(short)DAT_TileMapState::instance.PathConnectionLayer[iVar12])),
                                            0),
                                        iVar5 != 0))
                                || ((_assasinsTribe != 0
                                    && (BVar6 = MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::
                                                                      calculateCanReachUsingCachedAreaLogic,
                                            this)(iVar4, iVar12),
                                        BVar6 != FALSE))))) {
                            short sVar3 = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.xOffset;
                            DAT_TileMapState::instance.CertainPathLayer[iVar12]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar12] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex] = sVar3 + sVar1;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex] = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction].short_.yOffset + sVar2;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar12;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                    }

                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (0x13a0f < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    if (this->searchQueue.readIndex == this->searchQueue.writeIndex)
                        break;
                }
            }
            this->searchQueue.readIndex = 0;
            if (0 < this->searchQueue.writeIndex) {
                _pDest1 = &this->searchQueue.destinationsArray[0].tile2OrAHelper;
                do {
                    /*
                      warning
                     */
                    tribeID = (uint)DAT_TileMapState::instance.HeightLayer[iVar4];
                    if ((DAT_TileMapState::instance.LogicLayer[iVar4] & 0x10000000U) != 0) {
                        iVar12 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                            DAT_BuildingsState::ptr)((int)DAT_TileMapState::instance.BuildingLayer[iVar4]);
                        tribeID = tribeID + iVar12;
                    }
                    iVar12 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    uVar11 = (uint)DAT_TileMapState::instance.HeightLayer[iVar12];
                    if ((DAT_TileMapState::instance.LogicLayer[iVar12] & 0x10000000U) != 0) {
                        iVar12 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                            DAT_BuildingsState::ptr)((int)DAT_TileMapState::instance.BuildingLayer[iVar12]);
                        uVar11 = uVar11 + iVar12;
                    }
                    uVar7 = y - (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    uVar8 = (int)uVar7 >> 0x1f;
                    iVar5 = (uVar7 ^ uVar8) - uVar8;
                    uVar7 = x - (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    uVar8 = (int)uVar7 >> 0x1f;
                    iVar12 = (uVar7 ^ uVar8) - uVar8;
                    if (iVar12 <= iVar5) {
                        iVar12 = iVar5;
                    }
                    if (iVar12 == 2
                        && (uVar7 = (int)(tribeID - uVar11) >> 0x1f,
                            (int)((tribeID - uVar11 ^ uVar7) - uVar7) < 0x20)) {
                        _pDest1[-1] = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                        _destIndex = _destIndex + 1;
                        *_pDest1 = 1;
                        _pDest1 = _pDest1 + 3;
                        if (unitCount <= _destIndex) {
                            return;
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                } while (this->searchQueue.readIndex < this->searchQueue.writeIndex);
                if (4 < _destIndex)
                    goto LAB_004a7e8c;
            }
            this->searchQueue.readIndex = 0;
            if (0 < this->searchQueue.writeIndex) {
                _pDest2
                    = &((PathFindingStatePartB*)(this->climbData + 200))->destinationsArray[_destIndex].tile2OrAHelper;
                do {
                    tribeID = (uint)DAT_TileMapState::instance.HeightLayer[iVar4];
                    if ((DAT_TileMapState::instance.LogicLayer[iVar4] & 0x10000000U) != 0) {
                        iVar12 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                            DAT_BuildingsState::ptr)((int)DAT_TileMapState::instance.BuildingLayer[iVar4]);
                        tribeID = tribeID + iVar12;
                    }
                    iVar12 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                    uVar11 = (uint)DAT_TileMapState::instance.HeightLayer[iVar12];
                    if ((DAT_TileMapState::instance.LogicLayer[iVar12] & 0x10000000U) != 0) {
                        iVar12 = MACRO_CALL_MEMBER(
                            OpenSHC::Map::Buildings::BuildingsState_Func::getBuildingHeightForBuildingID,
                            DAT_BuildingsState::ptr)((int)DAT_TileMapState::instance.BuildingLayer[iVar12]);
                        uVar11 = uVar11 + iVar12;
                    }
                    uVar7 = y - (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    uVar8 = (int)uVar7 >> 0x1f;
                    iVar5 = (uVar7 ^ uVar8) - uVar8;
                    uVar7 = x - (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    uVar8 = (int)uVar7 >> 0x1f;
                    iVar12 = (uVar7 ^ uVar8) - uVar8;
                    if (iVar12 <= iVar5) {
                        iVar12 = iVar5;
                    }
                    if (iVar12 == 1
                        && (uVar7 = (int)(tribeID - uVar11) >> 0x1f,
                            (int)((tribeID - uVar11 ^ uVar7) - uVar7) < 0x20)) {
                        ((PathHelper12*)(_pDest2 + -1))->tile1
                            = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                        _destIndex = _destIndex + 1;
                        *_pDest2 = 1;
                        _pDest2 = _pDest2 + 3;
                        if (unitCount <= _destIndex) {
                            return;
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                } while (this->searchQueue.readIndex < this->searchQueue.writeIndex);
            }
        LAB_004a7e8c:
            this->searchQueue.readIndex = 0;
            if (0 < this->searchQueue.writeIndex) {
                _pDest3
                    = &((PathFindingStatePartB*)(this->climbData + 200))->destinationsArray[_destIndex].tile2OrAHelper;
                do {
                    uint _yDiff3 = y - (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    iVar12 = (_yDiff3 ^ (int)_yDiff3 >> 0x1f) - ((int)_yDiff3 >> 0x1f);
                    uint _xDiff3 = x - (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    iVar4 = (_xDiff3 ^ (int)_xDiff3 >> 0x1f) - ((int)_xDiff3 >> 0x1f);
                    if (iVar4 <= iVar12) {
                        iVar4 = iVar12;
                    }
                    if (2 < iVar4) {
                        ((PathHelper12*)(_pDest3 + -1))->tile1
                            = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                        _destIndex = _destIndex + 1;
                        *_pDest3 = 0;
                        _pDest3 = _pDest3 + 3;
                        if (unitCount <= _destIndex) {
                            return;
                        }
                    }
                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                } while (this->searchQueue.readIndex < this->searchQueue.writeIndex);
            }
            this->searchQueue.destinationsArray[_destIndex].tile1 = 0;
            ((PathFindingStatePartB*)(this->climbData + 200))->destinationsArray[_destIndex].tile2OrAHelper = 0;
            return;
        }

    }
}
}
