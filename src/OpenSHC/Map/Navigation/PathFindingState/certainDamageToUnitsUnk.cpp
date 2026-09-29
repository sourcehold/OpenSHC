#include "../PathFindingState.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"
#include "OpenSHC/Map/Location/Point8ShortXY.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::DE::SHCDE::eSFX;
        using OpenSHC::Map::Entities::EntityType;
        using OpenSHC::Map::Location::Point8ShortXY;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A3B20
        undefined4 PathFindingState::certainDamageToUnitsUnk(
            int param_1, int param_2, int param_3, int param_4, undefined4 param_5)
        {
            short sVar5;
            short sVar6;
            short* psVar8;
            int iVar9;
            int* piVar10;
            int iVar11;
            eSFX sfxOffsetInArray;
            EntityType local_8;
            int local_4;
            this->searchGeneration = this->searchGeneration + 1;
            this->calculations = this->calculations + 1;
            if (32000 < this->searchGeneration) {
                this->searchGeneration = 1;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    0x27420, '\0', (void*)((int)(DAT_TileMapState::instance.WalkLayer)));
            }
            this->searchQueue.yQueue[0]
                = (short)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[param_1];
            uint uVar7 = (uint)this->searchQueue.yQueue[0];
            iVar9 = param_1 - DAT_ViewportRenderState::instance.translationMatrix[uVar7].addXgetTile;
            local_4 = 1;
            uint uVar1 = iVar9 + 100;
            if (399 < uVar1 || 399 < uVar7
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[uVar7 * 400 + uVar1] == '\0') {
                local_4 = -1;
            }
            this->searchQueue.tilesQueue[0] = param_1;
            this->searchQueue.xQueue[0] = (short)iVar9;
            this->searchQueue.currentDistance = 1;
            this->searchQueue.readIndex = 0;
            this->searchQueue.writeIndex = 1;
            DAT_TileMapState::instance.CertainPathLayer[param_1] = 1;
            DAT_TileMapState::instance.WalkLayer[this->searchQueue.tilesQueue[0]] = (short)this->searchGeneration;
            local_8 = OpenSHC::Map::Entities::ET_ARROW_AND_DEFAULT;
            if ((char)param_5 == '\0') {
                local_8 = OpenSHC::Map::Entities::ET_CATAPULT;
            }
            if (this->searchQueue.readIndex != this->searchQueue.writeIndex) {
                while (uVar1 = this->searchQueue.tilesQueue[this->searchQueue.readIndex], uVar1 < 0x13a10) {
                    int sVar2 = (int)this->searchQueue.xQueue[this->searchQueue.readIndex];
                    int sVar3 = (int)this->searchQueue.yQueue[this->searchQueue.readIndex];
                    this->searchQueue.currentDistance = (int)DAT_TileMapState::instance.CertainPathLayer[uVar1];
                    if (0x13a10 < this->searchQueue.currentDistance) {
                        return (undefined4)(0);
                    }
                    if (this->searchQueue.currentDistance > param_2) {
                        return (undefined4)(0);
                    }
                    int uVar4 = (short)DAT_TileMapState::instance.UnitLayer[uVar1];
                    while (iVar9 = (int)(short)uVar4, iVar9 != 0) {
                        if (param_3 != 0
                            && DAT_GameState::instance.mapAndTime
                                    .playerTeams[DAT_UnitsState::instance.units[iVar9].owner]
                                != DAT_GameState::instance.mapAndTime.playerTeams[param_3]
                            && DAT_UnitsState::instance.units[iVar9].unitType != OpenSHC::Map::Units::UT_LORD) {
                            DAT_UnitsState::instance.units[iVar9].health
                                = DAT_UnitsState::instance.units[iVar9].health - param_4;
                            if ((DAT_UnitsState::instance.units[iVar9].health < 1)
                                && (DAT_UnitsState::instance.units[iVar9].dying == 0)) {
                                DAT_UnitsState::instance.units[iVar9].health = 0;
                                DAT_UnitsState::instance.units[iVar9].dying = 1;
                                DAT_UnitsState::instance.units[iVar9].animationCycleNumber = 0;
                                if ((char)param_5 == '\0') {
                                    sVar6 = DAT_UnitsState::instance.units[iVar9].y;
                                    sVar5 = DAT_UnitsState::instance.units[iVar9].x;
                                    sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_SPLAT;
                                    DAT_UnitsState::instance.units[iVar9].state.generic
                                        = OpenSHC::Map::Units::States::US_STONE_DEATH_01;
                                } else {
                                    sVar6 = DAT_UnitsState::instance.units[iVar9].y;
                                    sVar5 = DAT_UnitsState::instance.units[iVar9].x;
                                    sfxOffsetInArray = OpenSHC::DE::SHCDE::FX_DEATH_ARROW;
                                    DAT_UnitsState::instance.units[iVar9].state.generic
                                        = OpenSHC::Map::Units::States::US_DEATH_01;
                                }
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation,
                                    DAT_SFXState::ptr)((int)sVar5, (int)(sVar6), sfxOffsetInArray);
                                DAT_UnitsState::instance.units[iVar9].tunnelerFinishedDigging = 1;
                            }
                            iVar11 = DAT_UnitsState::instance.units[iVar9].maxHealth;
                            if (iVar11 == 0) {
                                sVar6 = 100;
                            } else {
                                sVar6 = (short)((DAT_UnitsState::instance.units[iVar9].health * 100) / iVar11);
                            }
                            DAT_UnitsState::instance.units[iVar9].healthPercentage = sVar6;
                            DAT_UnitsState::instance.units[iVar9].healthbar
                                = (sVar6 / 10 + (sVar6 >> 0xf)) - (short)((longlong)(int)sVar6 * 0x66666667 >> 0x3f);
                        }
                        uVar4 = DAT_UnitsState::instance.units[iVar9].nextUnitOnTheSameTile;
                    }
                    uVar7 = (uint)SEC_RNG::instance.currentNumber2;
                    MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                    if ((uVar7 & 1) == 0) {
                        iVar11 = (int)SEC_RNG::instance.currentNumber2;
                        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                        iVar9 = sVar3 * 8;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity, DAT_EntityState::ptr)(0,
                            (undefined4)((int)(param_3)), 0, (int)(((uVar7 >> 4) % 0x32 + 0x32) * local_4 + sVar2 * 8),
                            iVar9 + (iVar11 / 0x32) * -0x32 + -0x19 + iVar11,
                            (int)((uint)DAT_TileMapState::instance.HeightLayer[uVar1] + (uVar7 / 1000) * -1000 + 500
                                + uVar7),
                            (int)(sVar2 * 8 + 4), iVar9 + 4, (int)(DAT_TileMapState::instance.HeightLayer[uVar1]),
                            local_8, 0);
                    }
                    for (int _direction = 0; _direction < 8; _direction = _direction + 4) {
                        iVar9 = DAT_TileMapState::instance.directionTranslationMatrix[sVar3][_direction] + uVar1;
                        if (DAT_TileMapState::instance.WalkLayer[iVar9] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar9] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar9]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar9] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                      .short_.xOffset
                                + sVar2;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction]
                                      .short_.yOffset
                                + sVar3;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar9;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar9 = DAT_TileMapState::instance.directionTranslationMatrix[sVar3][_direction + 1] + uVar1;
                        if (DAT_TileMapState::instance.WalkLayer[iVar9] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar9] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar9]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar9] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 1]
                                      .short_.xOffset
                                + sVar2;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 1]
                                      .short_.yOffset
                                + sVar3;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar9;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar9 = DAT_TileMapState::instance.directionTranslationMatrix[sVar3][_direction + 2] + uVar1;
                        if (DAT_TileMapState::instance.WalkLayer[iVar9] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar9] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar9]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar9] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 2]
                                      .short_.xOffset
                                + sVar2;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 2]
                                      .short_.yOffset
                                + sVar3;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar9;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                        iVar9 = DAT_TileMapState::instance.directionTranslationMatrix[sVar3][_direction + 3] + uVar1;
                        if (DAT_TileMapState::instance.WalkLayer[iVar9] != this->searchGeneration
                            && (DAT_TileMapState::instance.LogicLayer[iVar9] & 0x30) == 0) {
                            DAT_TileMapState::instance.CertainPathLayer[iVar9]
                                = (short)this->searchQueue.currentDistance + 1;
                            DAT_TileMapState::instance.WalkLayer[iVar9] = (short)this->searchGeneration;
                            this->searchQueue.xQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 3]
                                      .short_.xOffset
                                + sVar2;
                            this->searchQueue.yQueue[this->searchQueue.writeIndex]
                                = DAT_TerrainDefinedData::instance.clockwiseCardinalTranslationMatrix[_direction + 3]
                                      .short_.yOffset
                                + sVar3;
                            this->searchQueue.tilesQueue[this->searchQueue.writeIndex] = iVar9;
                            this->searchQueue.writeIndex = this->searchQueue.writeIndex + 1;
                            if (0x13a0f < this->searchQueue.writeIndex) {
                                this->searchQueue.writeIndex = 0;
                            }
                        }
                    }

                    this->searchQueue.readIndex = this->searchQueue.readIndex + 1;
                    if (80400 < this->searchQueue.readIndex) {
                        this->searchQueue.readIndex = 0;
                    }
                    if (this->searchQueue.readIndex == this->searchQueue.writeIndex) {
                        return (undefined4)(0);
                    }
                }
            }
            return (undefined4)(0);
        }

    }
}
}
