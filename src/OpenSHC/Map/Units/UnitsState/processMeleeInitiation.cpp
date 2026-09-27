#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_CurrentUnitSlotID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Units::UnitLogicState;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x00549C70
        void UnitsState::processMeleeInitiation(int unitID)

        {
            uint _neighbourHeights[8];
            int _totalHeight;
            uint* _occupancyRow;
            int _adjacentTiles[24];
            int _otherUnitID;
            if (this->units[unitID].someUnitStat2_meleeDamageUnk != 0 && this->units[unitID].unknownTestAgainst0_2 == 0
                && this->units[unitID].unknownMovementRelated_0x2d2 == 0
                && this->units[unitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL && this->units[unitID].dying == 0
                && this->units[unitID].moveRelatedFlag != 1) {
                int _distanceThreshold;
                if (this->units[unitID].stateBasedSpeed <= 0) {
                    /*
                      50 or 150 depending on selectable
                     */

                    if (this->units[unitID].isSelectable_OR_matchTime != 0) {
                        _distanceThreshold = 150;
                    } else {
                        _distanceThreshold = 50;
                    }
                } else {
                    _distanceThreshold = 270;
                }
                if (this->units[unitID].closestEnemyMicroDistance <= _distanceThreshold
                    || this->units[unitID].attackedUnitID != 0
                    || this->units[unitID].unitType == OpenSHC::Map::Units::UT_LIONSHWOLF
                    || (this->units[unitID].isStalked != 0
                        && (((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                                 || (100 < (int)this->unitCount))
                            && (((this->units[unitID].fixedRng ^ DAT_GameState::instance.mapAndTime.totalGameTicksUnk)
                                    & 0xf)
                                == 0))))) {
                    _totalHeight
                        = (int)this->units[unitID].buildingHeight + (int)this->units[unitID].terrainOrClimbHeight;
                    int _playerID = (int)this->units[unitID].owner;
                    DAT_TileMapState::instance.DAT_SomeTile = this->units[unitID].tile;
                    DAT_TileMapState::instance.DAT_SomeY
                        = (int)DAT_ViewportRenderState::instance
                              .tileTranslationMatrix_YComponent[DAT_TileMapState::instance.DAT_SomeTile];
                    int _hasEnemyOnOwnTile = 0;
                    uint _teamBitFlags = MACRO_CALL_MEMBER(
                        OpenSHC::Game::GameStateStructures_Func::teamToBitFlagsUnk, DAT_GameState::ptr)(unitID);
                    uint _enemyNeighbourFlags = 0;
                    if ((*(uint*)((uchar*)DAT_TileMapState::instance.ptr_OccupancyLayer
                             + DAT_TileMapState::instance.DAT_SomeTile + 1)
                            & _teamBitFlags)
                        != 0) {
                        _enemyNeighbourFlags = 0x20;
                    }
                    if ((*(uint*)((uchar*)DAT_TileMapState::instance.ptr_OccupancyLayer
                             + DAT_TileMapState::instance.DAT_SomeTile + -1)
                            & _teamBitFlags)
                        != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 2;
                    }
                    if ((*(uint*)((uchar*)DAT_TileMapState::instance.ptr_OccupancyLayer
                             + DAT_TileMapState::instance.DAT_SomeTile + 2)
                            & _teamBitFlags)
                        != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 0x80000;
                    }
                    if ((*(uint*)((uchar*)DAT_TileMapState::instance.ptr_OccupancyLayer
                             + DAT_TileMapState::instance.DAT_SomeTile + -2)
                            & _teamBitFlags)
                        != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 0x800;
                    }
                    _occupancyRow = (uint*)((uchar*)DAT_TileMapState::instance.ptr_OccupancyLayer
                        + *(int*)((uchar*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix
                            + DAT_TileMapState::instance.DAT_SomeY * 0x20)
                        + DAT_TileMapState::instance.DAT_SomeTile);
                    if ((*(uint*)((int)_occupancyRow + -1) & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 1;
                    }
                    if ((*(uint*)((int)_occupancyRow + 1) & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 0x40;
                    }
                    if ((*_occupancyRow & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 0x80;
                    }
                    if ((*(uint*)((int)_occupancyRow + -2) & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 0x400;
                    }
                    if ((*(uint*)((int)_occupancyRow + 2) & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 0x100000;
                    }
                    _occupancyRow = (uint*)((uchar*)DAT_TileMapState::instance.ptr_OccupancyLayer
                        + *(int*)((int)((uchar*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix
                                      + DAT_TileMapState::instance.DAT_SomeY * 0x20)
                            + 0x10)
                        + DAT_TileMapState::instance.DAT_SomeTile);
                    if ((*(uint*)((int)_occupancyRow + -1) & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 4;
                    }
                    if ((*(uint*)((int)_occupancyRow + 1) & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 0x10;
                    }
                    if ((*_occupancyRow & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 8;
                    }
                    if ((*(uint*)((int)_occupancyRow + -2) & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 0x1000;
                    }
                    if ((*(uint*)((int)_occupancyRow + 2) & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 0x40000;
                    }
                    _occupancyRow = (uint*)((uchar*)DAT_TileMapState::instance.ptr_OccupancyLayer
                        + *(int*)((uchar*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix
                            + DAT_TileMapState::instance.DAT_SomeY * 0x20 + -0x20)
                        + *(int*)((uchar*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix
                            + DAT_TileMapState::instance.DAT_SomeY * 0x20)
                        + DAT_TileMapState::instance.DAT_SomeTile);
                    if ((*(uint*)((int)_occupancyRow + -1) & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 0x100;
                    }
                    if ((*(uint*)((int)_occupancyRow + 1) & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 0x400000;
                    }
                    if ((*_occupancyRow & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 0x800000;
                    }
                    if ((*(uint*)((int)_occupancyRow + -2) & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 0x200;
                    }
                    if ((*(uint*)((int)_occupancyRow + 2) & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 0x200000;
                    }
                    _occupancyRow = (uint*)((uchar*)DAT_TileMapState::instance.ptr_OccupancyLayer
                        + *(int*)((uchar*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix
                            + DAT_TileMapState::instance.DAT_SomeY * 0x20 + 0x30)
                        + *(int*)((uchar*)DAT_TileMapState::instance.ptr_MovementDirectionTranslationMatrix
                            + DAT_TileMapState::instance.DAT_SomeY * 0x20 + 0x10)
                        + DAT_TileMapState::instance.DAT_SomeTile);
                    if ((*(uint*)((int)_occupancyRow + -1) & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 0x4000;
                    }
                    if ((*(uint*)((int)_occupancyRow + 1) & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 0x10000;
                    }
                    if ((*_occupancyRow & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 0x8000;
                    }
                    if ((*(uint*)((int)_occupancyRow + -2) & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 0x2000;
                    }
                    if ((*(uint*)((int)_occupancyRow + 2) & _teamBitFlags) != 0) {
                        _enemyNeighbourFlags = _enemyNeighbourFlags | 0x20000;
                    }
                    DAT_TileMapState::instance.field213_0x554a48 = _enemyNeighbourFlags;
                    for (_otherUnitID
                        = (short)DAT_TileMapState::instance.UnitLayer[DAT_TileMapState::instance.DAT_SomeTile];
                        _otherUnitID > 0; _otherUnitID = (short)this->units[_otherUnitID].nextUnitOnTheSameTile) {
                        if (_otherUnitID != unitID) {
                            bool _isFriendly;
                            if (this->units[unitID].owner == 0) {
                                _isFriendly = this->units[unitID].unitType == this->units[_otherUnitID].unitType;
                            } else {
                                _isFriendly = DAT_GameState::instance.mapAndTime.playerTeams[_playerID]
                                    == DAT_GameState::instance.mapAndTime.playerTeams[this->units[_otherUnitID].owner];
                            }
                            if (!_isFriendly) {
                                _hasEnemyOnOwnTile = 1;
                                break;
                            }
                        }
                    }
                    if ((DAT_TileMapState::instance.field213_0x554a48 != 0) || (_hasEnemyOnOwnTile != 0)) {
                        for (int i = 0; i < 24; ++i) {
                            _adjacentTiles[i] = 0;
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 1) != 0) {
                            _adjacentTiles[0] = DAT_TileMapState::instance
                                                    .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][7]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 2) != 0) {
                            _adjacentTiles[1] = DAT_TileMapState::instance
                                                    .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][6]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 4) != 0) {
                            _adjacentTiles[2] = DAT_TileMapState::instance
                                                    .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][5]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 8) != 0) {
                            _adjacentTiles[3] = DAT_TileMapState::instance
                                                    .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][4]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 0x10) != 0) {
                            _adjacentTiles[4] = DAT_TileMapState::instance
                                                    .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][3]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 0x20) != 0) {
                            _adjacentTiles[5] = DAT_TileMapState::instance
                                                    .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][2]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 0x40) != 0) {
                            _adjacentTiles[6] = DAT_TileMapState::instance
                                                    .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][1]
                                + this->units[unitID].tile;
                        }
                        if ((char)DAT_TileMapState::instance.field213_0x554a48 < '\0') {
                            _adjacentTiles[7] = DAT_TileMapState::instance
                                                    .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][0]
                                + this->units[unitID].tile;
                        }
                        _neighbourHeights[0] = MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                            DAT_TileMapState::instance
                                .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][7]
                            + this->units[unitID].tile);
                        _neighbourHeights[1] = MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                            DAT_TileMapState::instance
                                .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][6]
                            + this->units[unitID].tile);
                        _neighbourHeights[2] = MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                            DAT_TileMapState::instance
                                .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][5]
                            + this->units[unitID].tile);
                        _neighbourHeights[3] = MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                            DAT_TileMapState::instance
                                .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][4]
                            + this->units[unitID].tile);
                        _neighbourHeights[4] = MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                            DAT_TileMapState::instance
                                .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][3]
                            + this->units[unitID].tile);
                        _neighbourHeights[5] = MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                            DAT_TileMapState::instance
                                .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][2]
                            + this->units[unitID].tile);
                        _neighbourHeights[6] = MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                            DAT_TileMapState::instance
                                .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][1]
                            + this->units[unitID].tile);
                        _neighbourHeights[7] = MACRO_CALL_MEMBER(
                            OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile, DAT_TileMapState::ptr)(
                            DAT_TileMapState::instance
                                .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][0]
                            + this->units[unitID].tile);
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 0x100) != 0) {
                            _adjacentTiles[8] = DAT_MinimapViewState::instance
                                                    .spawnMoment[DAT_TileMapState::instance.DAT_SomeY * 8 + 0x14]
                                + this->units[unitID].tile
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][0];
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 0x200) != 0) {
                            _adjacentTiles[9] = DAT_MinimapViewState::instance
                                                    .spawnMoment[DAT_TileMapState::instance.DAT_SomeY * 8 + 0x13]
                                + DAT_MinimapViewState::instance
                                      .spawnMoment[DAT_TileMapState::instance.DAT_SomeY * 8 + 0x14]
                                + this->units[unitID].tile
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][0];
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 0x400) != 0) {
                            _adjacentTiles[10]
                                = DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][6]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][7]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 0x800) != 0) {
                            _adjacentTiles[0xb] = this->units[unitID].tile
                                + DAT_TileMapState::instance
                                        .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][6]
                                    * 2;
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 0x1000) != 0) {
                            _adjacentTiles[0xc]
                                = DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][5]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][6]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 0x2000) != 0) {
                            _adjacentTiles[0xd]
                                = DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY + 1][6]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY + 1][5]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][4]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 0x4000) != 0) {
                            _adjacentTiles[0xe]
                                = DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY + 1][5]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][4]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 0x8000) != 0) {
                            _adjacentTiles[0xf]
                                = DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY + 1][4]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][4]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 0x10000) != 0) {
                            _adjacentTiles[0x10]
                                = DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY + 1][3]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][4]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 0x20000) != 0) {
                            _adjacentTiles[0x11]
                                = DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY + 1][2]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY + 1][3]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][4]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 0x40000) != 0) {
                            _adjacentTiles[0x12]
                                = DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][2]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][3]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 0x80000) != 0) {
                            _adjacentTiles[0x13] = this->units[unitID].tile
                                + DAT_TileMapState::instance
                                        .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][2]
                                    * 2;
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 0x100000) != 0) {
                            _adjacentTiles[0x14]
                                = DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][1]
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][2]
                                + this->units[unitID].tile;
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 0x200000) != 0) {
                            _adjacentTiles[0x15] = DAT_MinimapViewState::instance
                                                       .spawnMoment[DAT_TileMapState::instance.DAT_SomeY * 8 + 0xe]
                                + DAT_MinimapViewState::instance
                                      .spawnMoment[DAT_TileMapState::instance.DAT_SomeY * 8 + 0xf]
                                + this->units[unitID].tile
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][0];
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 0x400000) != 0) {
                            _adjacentTiles[0x16] = DAT_MinimapViewState::instance
                                                       .spawnMoment[DAT_TileMapState::instance.DAT_SomeY * 8 + 0xe]
                                + this->units[unitID].tile
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][0];
                        }
                        if ((DAT_TileMapState::instance.field213_0x554a48 & 0x800000) != 0) {
                            _adjacentTiles[0x17] = DAT_MinimapViewState::instance
                                                       .spawnMoment[DAT_TileMapState::instance.DAT_SomeY * 8 + 0xd]
                                + this->units[unitID].tile
                                + DAT_TileMapState::instance
                                      .directionTranslationMatrix[DAT_TileMapState::instance.DAT_SomeY][0];
                        }
                        if (this->units[unitID].attackedUnitID != 0) {
                            _otherUnitID = this->units[unitID].attackedUnitID;
                            if (this->units[_otherUnitID].uid == this->units[unitID].field191_0x340
                                && this->units[_otherUnitID].logicalState == OpenSHC::Map::Units::ULS_NORMAL
                                && this->units[_otherUnitID].dying == 0) {
                                /* -- CHECK 24 TILES AROUND UNIT -- is the unit we already fight still in reach? */
                                for (int _slot = -1; _slot < 24; ++_slot) {
                                    int _candidateTile;
                                    if (_slot == -1) {
                                        if (_hasEnemyOnOwnTile == 0) {
                                            continue;
                                        }
                                        _candidateTile = this->units[unitID].tile;
                                    } else {
                                        _candidateTile = _adjacentTiles[DAT_UnitPropertiesDefinedData::instance
                                                .field117_0x11cf4[this->units[unitID].facingDirection][_slot]];
                                    }
                                    if (_candidateTile == 0) {
                                        continue;
                                    }
                                    int _heightDelta = _totalHeight
                                        - MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTotalHeightAtTile,
                                            DAT_TileMapState::ptr)(_candidateTile);
                                    if (_heightDelta < 0) {
                                        _heightDelta = -_heightDelta;
                                    }
                                    if (_heightDelta >= 0x20) {
                                        continue;
                                    }
                                    if (_otherUnitID
                                        == MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getEnemyUnitIDNearby,
                                            this)(unitID, _candidateTile, _totalHeight)) {
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::Map::Units::UnitsState_Func::setFacingDirectionTowardUnitMicro,
                                            this)(unitID, _otherUnitID);
                                        if (this->units[unitID].state.generic
                                            != OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
                                            if (this->units[unitID].movementRelated == 8) {
                                                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::
                                                                      saveUnitStateBeforeInterruption,
                                                    this)(unitID);
                                                this->units[unitID].movementRelated = 8;
                                                this->units[unitID].state.generic
                                                    = OpenSHC::Map::Units::States::US_MELEE_ATTACK;
                                                this->units[unitID].SA = 0;
                                                this->units[unitID].animationCycleNumber = 0;
                                                this->units[DAT_CurrentUnitSlotID::instance].substate = 0;
                                            } else {
                                                this->units[unitID].field259_0x3d2 = 1;
                                            }
                                        }
                                        MACRO_CALL_MEMBER(
                                            OpenSHC::Map::Units::UnitsState_Func::processUnitAttackOtherUnit, this)(
                                            DAT_CurrentUnitSlotID::instance, this->units[unitID].attackedUnitID);
                                        return;
                                    }
                                }
                            }
                            this->units[unitID].attackedUnitID = 0;
                            this->units[unitID].field191_0x340 = 0;
                            this->units[unitID].field259_0x3d2 = 0;
                        }
                        /* -- CHECK 24 TILES AROUND UNIT -- look for someone new to fight */
                        for (int _slot = -1; _slot < 24; ++_slot) {
                            int _candidateTile;
                            int _tileSlot;
                            if (_slot == -1) {
                                if (_hasEnemyOnOwnTile == 0) {
                                    continue;
                                }
                                _tileSlot = this->units[unitID].facingDirection;
                                _candidateTile = this->units[unitID].tile;
                            } else {
                                _tileSlot = DAT_UnitPropertiesDefinedData::instance
                                                .field117_0x11cf4[this->units[unitID].facingDirection][_slot];
                                _candidateTile = _adjacentTiles[_tileSlot];
                            }
                            if (_candidateTile == 0) {
                                continue;
                            }
                            if (_tileSlot >= 8) {
                                int _firstHeightDelta = _totalHeight
                                    - _neighbourHeights
                                        [DAT_UnitPropertiesDefinedData::instance.field118_0x12054[_tileSlot].x];
                                if (_firstHeightDelta < 0) {
                                    _firstHeightDelta = -_firstHeightDelta;
                                }
                                if (_firstHeightDelta >= 0x21) {
                                    continue;
                                }
                                int _secondHeightIndex
                                    = DAT_UnitPropertiesDefinedData::instance.field118_0x12054[_tileSlot].y;
                                if (_secondHeightIndex != -1) {
                                    int _secondHeightDelta = _totalHeight - _neighbourHeights[_secondHeightIndex];
                                    if (_secondHeightDelta < 0) {
                                        _secondHeightDelta = -_secondHeightDelta;
                                    }
                                    if (_secondHeightDelta >= 0x21) {
                                        continue;
                                    }
                                }
                            }
                            _otherUnitID = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getEnemyUnitIDNearby,
                                this)(unitID, _candidateTile, _totalHeight);
                            if (_otherUnitID <= 0) {
                                continue;
                            }
                            if (this->units[_otherUnitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                                continue;
                            }
                            if (this->units[_otherUnitID].dying != 0) {
                                continue;
                            }
                            int _targetHeightDelta = (_totalHeight - this->units[_otherUnitID].buildingHeight)
                                - this->units[_otherUnitID].terrainOrClimbHeight;
                            if (_targetHeightDelta < 0) {
                                _targetHeightDelta = -_targetHeightDelta;
                            }
                            if (_targetHeightDelta >= 0x21) {
                                continue;
                            }
                            if ((this->units[unitID].unitType == OpenSHC::Map::Units::UT_LIONSHWOLF
                                    || this->units[unitID].unitType == OpenSHC::Map::Units::UT_CAGEDOG)
                                && this->units[_otherUnitID].isStalked != 0 && _slot >= 8) {
                                continue;
                            }
                            this->units[unitID].attackedUnitID = (short)_otherUnitID;
                            this->units[unitID].field191_0x340 = this->units[_otherUnitID].uid;
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setFacingDirectionTowardUnitMicro,
                                this)(unitID, _otherUnitID);
                            break;
                        }
                        if (this->units[unitID].attackedUnitID != 0) {
                            if (this->units[_otherUnitID].someUnitStat2_meleeDamageUnk != 0
                                && this->units[_otherUnitID].attackedUnitID == 0
                                && this->units[_otherUnitID].unknownMovementRelated_0x2d2 == 0) {
                                this->units[_otherUnitID].attackedUnitID = (short)unitID;
                                this->units[_otherUnitID].field191_0x340 = this->units[unitID].uid;
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Map::Units::UnitsState_Func::setFacingDirectionTowardUnitMicro, this)(
                                    _otherUnitID, unitID);
                            }
                            if (this->units[unitID].state.generic != OpenSHC::Map::Units::States::US_MELEE_ATTACK) {
                                if (this->units[unitID].movementRelated == 8) {
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::Map::Units::UnitsState_Func::saveUnitStateBeforeInterruption, this)(
                                        unitID);
                                    this->units[unitID].movementRelated = 8;
                                    this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_MELEE_ATTACK;
                                    this->units[unitID].SA = 0;
                                    this->units[unitID].animationCycleNumber = 0;
                                    this->units[DAT_CurrentUnitSlotID::instance].substate = 0;
                                } else {
                                    this->units[unitID].field259_0x3d2 = 1;
                                }
                            }
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::processUnitAttackOtherUnit, this)(
                                DAT_CurrentUnitSlotID::instance, this->units[unitID].attackedUnitID);
                            return;
                        }
                        this->units[unitID].field259_0x3d2 = 0;
                        this->units[unitID].attackedUnitID = 0;
                        this->units[unitID].field191_0x340 = 0;
                        return;
                    }
                }
                this->units[unitID].field191_0x340 = 0;
                this->units[unitID].attackedUnitID = 0;
                this->units[unitID].field259_0x3d2 = 0;
            }
        }
    }
}
}
