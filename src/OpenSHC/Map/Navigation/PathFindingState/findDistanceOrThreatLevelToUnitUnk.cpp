#include "../PathFindingState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Map::Units::UnitLogicState;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A0B20
        int PathFindingState::findDistanceOrThreatLevelToUnitUnk(int param_1, int param_2, int param_3, int param_4)
        {
            int (*paiVar3)[8];
            int iVar4;
            int iVar5;
            short* psVar6;
            int local_c;
            int local_8;
            this->calculations = this->calculations + 1;
            this->searchGeneration = this->searchGeneration + 1;
            local_c = 0;
            local_8 = 0;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.yQueue[0] = (short)param_3;
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.tilesQueue[0]
                = DAT_ViewportRenderState::instance.translationMatrix[param_3].addXgetTile + param_2;
            DAT_TileMapState::instance.CertainPathLayer[this->searchQueue.tilesQueue[0]] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                return 0;
            }
            do {
                uint uVar2 = this->searchQueue.tilesQueue[this->searchQueue.readIndex];
                if (0x13a0f < uVar2) {
                    return local_c;
                }
                int sVar1 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[uVar2];
                if (0x13a10 < (int)this->searchQueue.currentDistance) {
                    return local_c;
                }
                if (this->searchQueue.currentDistance > param_4) {
                    return local_c;
                }
                for (int _direction = 0; _direction < 8; _direction = _direction + 1) {
                    iVar4 = DAT_TileMapState::instance.directionTranslationMatrix[sVar1][_direction] + uVar2;
                    if ((DAT_TileMapState::instance.LogicLayer[iVar4] & 0x4a5014b1U) == 0
                        && DAT_TileMapState::instance.WalkLayer[iVar4] != this->searchGeneration) {
                        iVar5 = (int)(short)DAT_TileMapState::instance.UnitLayer[iVar4];
                        DAT_TileMapState::instance.CertainPathLayer[iVar4]
                            = (short)this->searchQueue.currentDistance + 1;
                        DAT_TileMapState::instance.WalkLayer[iVar4] = (short)this->searchGeneration;
                        this->searchQueue.yQueue[this->searchQueue.writeIndex]
                            = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                  .short_.yOffset
                            + sVar1;
                        this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar4;
                        this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                        if (0x13a10 <= this->searchQueue.writeIndex) {
                            this->searchQueue.writeIndex = 0;
                        }
                        if (iVar5 != 0
                            && DAT_GameState::instance.mapAndTime.playerTeams[param_1]
                                != DAT_GameState::instance.mapAndTime
                                    .playerTeams[DAT_UnitsState::instance.units[iVar5].owner]
                            && DAT_UnitsState::instance.units[iVar5].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE
                            && DAT_UnitsState::instance.units[iVar5].dying == 0
                            && DAT_UnitsState::instance.units[iVar5].isSelectable_OR_matchTime != 0) {
                            switch (DAT_UnitsState::instance.units[iVar5].unitType) {
                            case OpenSHC::Map::Units::UT_E_ARCHER:
                            case OpenSHC::Map::Units::UT_E_XBOW:
                            case OpenSHC::Map::Units::UT_A_ARCHER:
                            case OpenSHC::Map::Units::UT_A_HARCHER:
                            case OpenSHC::Map::Units::UT_S_FBALLISTA:
                                param_3 = 0xc;
                                break;
                            case OpenSHC::Map::Units::UT_E_SPEAR:
                            case OpenSHC::Map::Units::UT_E_LADDER:
                            case OpenSHC::Map::Units::UT_S_TOWER:
                            case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                            case OpenSHC::Map::Units::UT_S_SHIELD:
                            case OpenSHC::Map::Units::UT_A_SLAVE:
                                param_3 = 4;
                                break;
                            case OpenSHC::Map::Units::UT_E_PIKE:
                            case OpenSHC::Map::Units::UT_E_SWORD:
                            case OpenSHC::Map::Units::UT_E_KNIGHT:
                            case OpenSHC::Map::Units::UT_A_ASSASSIN:
                            case OpenSHC::Map::Units::UT_A_SWORDSMAN:
                                param_3 = 0;
                                break;
                            case OpenSHC::Map::Units::UT_E_MACE:
                            case OpenSHC::Map::Units::UT_E_MONK:
                                param_3 = 2;
                                break;
                            case OpenSHC::Map::Units::UT_E_ENGINEER:
                            case OpenSHC::Map::Units::UT_S_CATAPULT:
                            case OpenSHC::Map::Units::UT_A_FIRETHROWER:
                                param_3 = 0x14;
                                break;
                            case OpenSHC::Map::Units::UT_S_TREBUCHET:
                                param_3 = 0x1e;
                                break;
                            case OpenSHC::Map::Units::UT_S_MANGONEL:
                            case OpenSHC::Map::Units::UT_S_BALLISTA:
                                param_3 = 0x28;
                                break;
                            case OpenSHC::Map::Units::UT_LORD:
                            case OpenSHC::Map::Units::UT_A_SLINGER:
                                param_3 = 8;
                            }
                            param_3 = param_3 + 1 + this->searchQueue.currentDistance;
                            if (local_8 < param_3) {
                                local_c = iVar5;
                                local_8 = param_3;
                            }
                        }
                    }
                }

                this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                if (0x13a10 <= this->searchQueue.readIndex) {
                    this->searchQueue.readIndex = 0;
                }
            } while (this->searchQueue.readIndex != this->searchQueue.writeIndex);
            return local_c;
        }

    }
}
}
