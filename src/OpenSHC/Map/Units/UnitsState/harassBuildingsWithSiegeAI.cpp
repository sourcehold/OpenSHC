#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Synchrony/Actions.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Map/Units/Pathfinding/DestinationNeededEnum.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Map::Units::UnitInstructionType;
        using OpenSHC::Map::Units::UnitType;
        using OpenSHC::Map::Units::Pathfinding::DestinationNeededEnum;
        using OpenSHC::Map::Units::States::UnitState;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0053D030
        undefined4 UnitsState::harassBuildingsWithSiegeAI(int unitID)
        {
            int _playerID = this->units[unitID].owner;
            int _siegeKind = 0;
            int _searchRange = 200;
            int _isFireBallista = 0;
            switch (this->units[unitID].unitType) {
            case OpenSHC::Map::Units::UT_S_CATAPULT:
                _siegeKind = 2;
                _searchRange = 0x50;
                if (this->units[unitID].stoneAmmunition < 1) {
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                        && MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                               DAT_GameSynchronyState::ptr)(_playerID)
                            != FALSE) {
                        MACRO_CALL(OpenSHC::Synchrony::Actions_Func::TryAcquireAmmunitionOrPlanToBuyStone)(
                            _playerID, unitID);
                    }
                    return 0;
                }
                break;
            case OpenSHC::Map::Units::UT_S_TREBUCHET:
                _siegeKind = 3;
                if (this->units[unitID].stoneAmmunition < 1) {
                    if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                        && MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer,
                               DAT_GameSynchronyState::ptr)(_playerID)
                            != FALSE) {
                        MACRO_CALL(OpenSHC::Synchrony::Actions_Func::TryAcquireAmmunitionOrPlanToBuyStone)(
                            _playerID, unitID);
                    }
                    return 0;
                }
                break;
            case OpenSHC::Map::Units::UT_S_MANGONEL:
            case OpenSHC::Map::Units::UT_S_BALLISTA:
                _siegeKind = 4;
                break;
            case OpenSHC::Map::Units::UT_S_FBALLISTA:
                _siegeKind = 0x25;
                _isFireBallista = 1;
            }
            uint _defaultHeightAtTarget = 0;
            uint _heightAtTarget = 0;
            if (this->units[unitID].field248_0x3bc > 0) {
                _defaultHeightAtTarget
                    = DAT_TileMapState::instance.DefaultHeightLayer[this->units[unitID].field248_0x3bc];
                _heightAtTarget = DAT_TileMapState::instance.HeightLayer[this->units[unitID].field248_0x3bc];
            }
            int _shootAtMicroX;
            int _shootAtMicroY;
            int _shootAtZ;
            if (this->units[unitID].targetingType == OpenSHC::Map::Units::UIT_ATTACK_BUILDING) {
                if (DAT_BuildingsState::instance.buildings[this->units[unitID].targetID_OR_targetBuildingID].uid
                    != this->units[unitID]
                        .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID) {
                    this->units[unitID].targetingType = OpenSHC::Map::Units::UIT_NO_INSTRUCTION_OR_MOVEUnk;
                    return 0;
                }
                int _halfBuildingSize
                    = (DAT_BuildingsState::instance.buildings[this->units[unitID].targetID_OR_targetBuildingID]
                              .widthOrHeight
                          * 8)
                    / 2;
                _shootAtMicroX = _halfBuildingSize
                    + (short)DAT_BuildingsState::instance.buildings[this->units[unitID].targetID_OR_targetBuildingID].x
                        * 8;
                _shootAtMicroY = _halfBuildingSize
                    + (short)DAT_BuildingsState::instance.buildings[this->units[unitID].targetID_OR_targetBuildingID].y
                        * 8;
                _shootAtZ = DAT_BuildingsState::instance.buildings[this->units[unitID].targetID_OR_targetBuildingID]
                                .terrainHeightUnk;
            } else if (this->units[unitID].field248_0x3bc > 0
                && (DAT_TileMapState::instance.LogicLayer[this->units[unitID].field248_0x3bc] & 0x100U) != 0
                && (int)(_heightAtTarget - _defaultHeightAtTarget) >= 0x1f && _siegeKind != 0x25
                && DAT_GameState::instance.mapAndTime.playerTeams[_playerID]
                    != DAT_GameState::instance.mapAndTime
                        .playerTeams[(DAT_TileMapState::instance.WallOwnerLayer[this->units[unitID].field248_0x3bc] & 7)
                            + 1]) {
                _shootAtZ = (int)(_heightAtTarget - _defaultHeightAtTarget) / 2 + _defaultHeightAtTarget;
                _shootAtMicroX = (this->units[unitID].field248_0x3bc
                                     - DAT_ViewportRenderState::instance
                                         .translationMatrix[DAT_ViewportRenderState::instance
                                                 .tileTranslationMatrix_YComponent[this->units[unitID].field248_0x3bc]]
                                         .addXgetTile)
                    * 8;
                _shootAtMicroY = DAT_ViewportRenderState::instance
                                     .tileTranslationMatrix_YComponent[this->units[unitID].field248_0x3bc]
                    * 8;
            } else {
                DAT_PathFindingState::instance.ALG_TargetTile = 0;
                int _maxTargetDistance = 200;
                if (this->units[unitID].aiUnitBehaviourType == 0x15
                    || this->units[unitID].unknownSiegeTentRelated02 == 3) {
                    _maxTargetDistance = 0x14;
                }
                int _searchFlags;
                if (_siegeKind == 0x25) {
                    _searchFlags = 0x34;
                } else if (_siegeKind == 3) {
                    _searchFlags = 83;
                } else {
                    _searchFlags = 73;
                }
                int _attackFacingDirection = this->units[unitID].attackFacingDirection;
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                    _maxTargetDistance = *(int*)((int)DAT_TroopValueState::instance.attackInfo.scaleValuesArray
                                             + _playerID * 0x177bc + -0x1c)
                        + 0xf;
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::findBestAttackTargetTileWithHeightAndOwner,
                    DAT_PathFindingState::ptr)(_searchFlags, this->units[unitID].x, this->units[unitID].y,
                    (uint)(ushort)this->units[unitID].facingDirection + _attackFacingDirection & 7, _searchRange,
                    _attackFacingDirection, this->units[unitID].siegeTargetPlayerID, _maxTargetDistance,
                    _isFireBallista);
                if (DAT_PathFindingState::instance.ALG_TargetTile == 0) {
                    this->units[unitID].attackFacingDirection = this->units[unitID].attackFacingDirection + '\x01';
                    if (this->units[unitID].attackFacingDirection > '\x0f'
                        && (this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_CATAPULT
                            || this->units[unitID].unitType == OpenSHC::Map::Units::UT_S_FBALLISTA)
                        && (this->units[unitID].aiUnitBehaviourType == 0x15
                            || DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                            || this->units[unitID].unknownSiegeTentRelated02 == 3)) {
                        this->units[unitID].state.generic
                            = (OpenSHC::Map::Units::States::US_STAND_UPUnk | OpenSHC::Map::Units::States::US_IDLEUnk);
                        this->units[unitID].destinationNeeded
                            = OpenSHC::Map::Units::Pathfinding::DNE_DESTINATION_NEEDED;
                    }
                } else {
                    this->units[unitID].facingDirection
                        = this->units[unitID].facingDirection + (short)this->units[unitID].attackFacingDirection;
                    this->units[unitID].facingDirection = this->units[unitID].facingDirection & 7;
                    this->units[unitID].attackFacingDirection = '\0';
                    this->units[unitID].shootTargetedUnit = 0;
                    this->units[unitID].facingDirectionMapOrientationCorrected
                        = this->units[unitID].facingDirection - (short)DAT_TileMapState::instance.mapOrientation;
                    if (this->units[unitID].facingDirectionMapOrientationCorrected < 0) {
                        this->units[unitID].facingDirectionMapOrientationCorrected
                            = this->units[unitID].facingDirectionMapOrientationCorrected + 8;
                    }
                }
                _shootAtMicroX = DAT_PathFindingState::instance.ALG_TargetX * 8;
                _shootAtMicroY = DAT_PathFindingState::instance.ALG_TargetY * 8;
                _shootAtZ
                    = DAT_TileMapState::instance.HeightLayer[DAT_PathFindingState::instance.ALG_TargetTile] - 0x2d;
                this->units[unitID].field248_0x3bc = DAT_PathFindingState::instance.ALG_TargetTile;
                if (DAT_PathFindingState::instance.ALG_TargetTile == 0) {
                    this->units[unitID].field248_0x3bc = -0x32;
                    return 0;
                }
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setRandomShootLocation, this)(
                unitID, _shootAtMicroX, _shootAtMicroY, _shootAtZ);
            return 1;
        }

    }
}
}
