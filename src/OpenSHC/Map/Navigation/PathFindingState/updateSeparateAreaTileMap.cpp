#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Restarted to delay deadcode elimination for space: ram
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004995E0
        BOOLEnum PathFindingState::updateSeparateAreaTileMap(int forceUpdate)
        {
            int* piVar5;
            int iVar6;
            int iVar7;
            ushort _zoneCounter;
            int local_20;
            int* local_c;
            int local_8;
            _zoneCounter = 1;
            if (forceUpdate != 0) {
                this->toggleUpdateSeparateAreaTileMap = 1;
                DAT_GameState::instance.mapAndTime.counterForUpdatingSeparateAreaTileMaps = 0;
            }
            DAT_GameState::instance.mapAndTime.counterForUpdatingSeparateAreaTileMaps
                = DAT_GameState::instance.mapAndTime.counterForUpdatingSeparateAreaTileMaps + -1;
            if ((0 < DAT_GameState::instance.mapAndTime.counterForUpdatingSeparateAreaTileMaps)
                || (DAT_GameState::instance.mapAndTime.counterForUpdatingSeparateAreaTileMaps = 200,
                    this->toggleUpdateSeparateAreaTileMap == 0)) {
                return FALSE;
            }
            this->field41_0x74 = this->field41_0x74 + 1;
            this->toggleUpdateSeparateAreaTileMap = 0;
            this->totalZones = 0;
            this->sum = 0;
            ushort uVar4 = 1;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.PathConnectionLayer)));
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                4000, '\0', (void*)((int)(this->zoneSizesArray)));
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(1);
            short sVar3 = 0;
            local_20 = 0;
            local_c = &DAT_ViewportRenderState::instance.translationMatrix[1].firstTileOfRow;
            do {
                if (*local_c <= local_20) {
                    sVar3 = sVar3 + 1;
                    local_c = local_c + 3;
                }
                if ((char)DAT_TileMapState::instance.PathConnectionLayer[local_20] == '\0'
                    && (DAT_TileMapState::instance.LogicLayer[local_20] & 0x4a5014b1U) == 0) {
                    this->searchQueue.tilesQueue[0] = local_20;
                    forceUpdate = 1;
                    local_8 = 0;
                    this->searchQueue.yQueue[0] = sVar3;
                    DAT_TileMapState::instance.PathConnectionLayer[local_20] = _zoneCounter;
                    for (; local_8 != forceUpdate; local_8 = local_8 + 1) {
                        this->zoneSizesArray[uVar4] = this->zoneSizesArray[uVar4] + 1;
                        iVar7 = this->searchQueue.tilesQueue[local_8];
                        ushort uVar2 = this->searchQueue.yQueue[local_8];
                        int bVar1 = DAT_TileMapState::instance.PathLinkageLayer[iVar7];
                        if ((bVar1 & 0x40) != 0 && DAT_TileMapState::instance.MacroLayer[iVar7 + 0x13a0f] == 0) {
                            DAT_TileMapState::instance.MacroLayer[iVar7 + 0x13a0f] = uVar4;
                            this->searchQueue.tilesQueue[forceUpdate] = iVar7 + -1;
                            this->searchQueue.yQueue[forceUpdate] = uVar2;
                            forceUpdate = forceUpdate + 1;
                        }
                        if ((bVar1 & 4) != 0 && DAT_TileMapState::instance.PathConnectionLayer[iVar7 + 1] == 0) {
                            DAT_TileMapState::instance.PathConnectionLayer[iVar7 + 1] = uVar4;
                            this->searchQueue.tilesQueue[forceUpdate] = iVar7 + 1;
                            this->searchQueue.yQueue[forceUpdate] = uVar2;
                            forceUpdate = forceUpdate + 1;
                        }
                        iVar6 = iVar7 + DAT_TileMapState::instance.directionTranslationMatrix[uVar2][0];
                        if ((bVar1 & 0x80) != 0 && DAT_TileMapState::instance.MacroLayer[iVar6 + 0x13a0f] == 0) {
                            DAT_TileMapState::instance.MacroLayer[iVar6 + 0x13a0f] = uVar4;
                            this->searchQueue.tilesQueue[forceUpdate] = iVar6 + -1;
                            this->searchQueue.yQueue[forceUpdate] = uVar2 - 1;
                            forceUpdate = forceUpdate + 1;
                        }
                        if ((bVar1 & 1) != 0 && DAT_TileMapState::instance.PathConnectionLayer[iVar6] == 0) {
                            DAT_TileMapState::instance.PathConnectionLayer[iVar6] = uVar4;
                            this->searchQueue.tilesQueue[forceUpdate] = iVar6;
                            this->searchQueue.yQueue[forceUpdate] = uVar2 - 1;
                            forceUpdate = forceUpdate + 1;
                        }
                        if ((bVar1 & 2) != 0 && DAT_TileMapState::instance.PathConnectionLayer[iVar6 + 1] == 0) {
                            DAT_TileMapState::instance.PathConnectionLayer[iVar6 + 1] = uVar4;
                            this->searchQueue.tilesQueue[forceUpdate] = iVar6 + 1;
                            this->searchQueue.yQueue[forceUpdate] = uVar2 - 1;
                            forceUpdate = forceUpdate + 1;
                        }
                        iVar7 = iVar7 + DAT_TileMapState::instance.directionTranslationMatrix[uVar2][4];
                        if ((bVar1 & 0x20) != 0 && DAT_TileMapState::instance.MacroLayer[iVar7 + 0x13a0f] == 0) {
                            DAT_TileMapState::instance.MacroLayer[iVar7 + 0x13a0f] = uVar4;
                            this->searchQueue.tilesQueue[forceUpdate] = iVar7 + -1;
                            this->searchQueue.yQueue[forceUpdate] = uVar2 + 1;
                            forceUpdate = forceUpdate + 1;
                        }
                        if ((bVar1 & 0x10) != 0 && DAT_TileMapState::instance.PathConnectionLayer[iVar7] == 0) {
                            DAT_TileMapState::instance.PathConnectionLayer[iVar7] = uVar4;
                            this->searchQueue.tilesQueue[forceUpdate] = iVar7;
                            this->searchQueue.yQueue[forceUpdate] = uVar2 + 1;
                            forceUpdate = forceUpdate + 1;
                        }
                        if ((bVar1 & 8) != 0 && DAT_TileMapState::instance.PathConnectionLayer[iVar7 + 1] == 0) {
                            DAT_TileMapState::instance.PathConnectionLayer[iVar7 + 1] = uVar4;
                            this->searchQueue.tilesQueue[forceUpdate] = iVar7 + 1;
                            this->searchQueue.yQueue[forceUpdate] = uVar2 + 1;
                            forceUpdate = forceUpdate + 1;
                        }
                    }
                    _zoneCounter = uVar4 + 1;
                    uVar4 = _zoneCounter;
                    if (999 < (short)_zoneCounter)
                        break;
                }
                local_20 = local_20 + 1;
            } while (local_20 < 80400);
            this->totalZones = (int)(short)_zoneCounter;
            piVar5 = this->zoneSizesArray + 2;
            iVar7 = 333;
            do {
                this->sum = piVar5[1] + this->sum + piVar5[-1] + *piVar5;
                piVar5 = piVar5 + 3;
                iVar7 = iVar7 + -1;
            } while (iVar7 != 0);
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Buildings::BuildingsState_Func::updatePathLinkageTileMap, DAT_BuildingsState::ptr)(0);
            return TRUE;
        }

    }
}
}
