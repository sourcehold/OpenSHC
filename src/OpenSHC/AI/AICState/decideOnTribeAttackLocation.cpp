#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Map::Units::UnitInstructionType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D1A00
    void AICState ::decideOnTribeAttackLocation(uint tribeID_OR_moatWasHit)
    {
        uint _tribeID = tribeID_OR_moatWasHit;

        BOOLEnum _canHaveActivity
            = MACRO_CALL(OpenSHC::Global_Func::CheckTribeActivityPercentages)(tribeID_OR_moatWasHit, FALSE, TRUE);
        if (_canHaveActivity != FALSE) {
            DAT_TribesState::instance.tribes[_tribeID].counter = 0;
            return;
        }

        int _targetPlayer = (int)DAT_TribesState::instance.tribes[_tribeID].targetPlayer_outpost;

        if (DAT_TribesState::instance.tribes[_tribeID].randomNumber == 0) {
            DAT_TribesState::instance.tribes[_tribeID].randomNumber = (int)SEC_RNG::instance.currentNumber2;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        }

        int _rng = DAT_TribesState::instance.tribes[_tribeID].randomNumber;
        short* psVar1 = &DAT_TribesState::instance.tribes[_tribeID].counter;
        *psVar1 = *psVar1 + 1;

        if ((int)DAT_TribesState::instance.tribes[_tribeID].counter == _rng % 6 + 7) {
            DAT_TribesState::instance.tribes[_tribeID].counter = 0;
            tribeID_OR_moatWasHit = tribeID_OR_moatWasHit & 0xffffff00;
            int _x = 0;
            int _y = 0;
            int _unitID = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, DAT_TribesState::ptr)(_tribeID, 0);
            if ((_unitID != 0)
                && MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathFindingToAttackCastleIncludingMoat,
                    DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[_tribeID].owner, _targetPlayer,
                    (uint)((int)((int)DAT_UnitsState::instance.units[_unitID].x)),
                    (uint)((int)((int)DAT_UnitsState::instance.units[_unitID].y)), (byte*)&tribeID_OR_moatWasHit,
                    &_x, &_y)) {
                if ((char)tribeID_OR_moatWasHit != '\0') {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::relayTribeInstruction, DAT_UnitsState::ptr)(
                        _tribeID, ((UnitInstructionType)0x23),
                        DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile + _x, 0, 0);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::relayTribeInstruction, DAT_UnitsState::ptr)(
                    _tribeID, OpenSHC::Map::Units::UIT_FILL_MOAT, _x, _y, 1000);
                return;
            }
        }

        short sVar2 = DAT_TribesState::instance.tribes[_tribeID].tribeSubtype1;

        if ((sVar2 != 0xb6) && (sVar2 != 0xb9)) {
            BOOLEnum BVar4 = MACRO_CALL(OpenSHC::Global_Func::CheckTribeActivityPercentages)(_tribeID, FALSE, FALSE);
            if (BVar4 != FALSE)
                return;

            int _targetBuilding = (int)DAT_TribesState::instance.tribes[_tribeID].targetBuildingID;
            if ((((_targetBuilding != 0)
                     && (DAT_BuildingsState::instance.buildings[_targetBuilding].uid
                         == DAT_TribesState::instance.tribes[_tribeID].targetBuildingUID))
                    && (DAT_BuildingsState::instance.buildings[_targetBuilding].fireDuration == 0))
                && (BVar4 = MACRO_CALL(OpenSHC::Global_Func::CheckTribeActivityPercentages)(_tribeID, FALSE, TRUE),
                    BVar4 != FALSE)) {
                if (DAT_GameState::instance.mapAndTime.yearChanged == 0)
                    return;
                DAT_TribesState::instance.tribes[_tribeID].targetBuildingID = 0;
                return;
            }

            int _buildingID = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::selectARandomBuildingOwnedByPlayer,
                DAT_GameState::ptr)(_targetPlayer);
            if (_buildingID != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::relayTribeInstruction, DAT_UnitsState::ptr)(
                    _tribeID, OpenSHC::Map::Units::UIT_ATTACK_BUILDING, _buildingID,
                    DAT_BuildingsState::instance.buildings[_buildingID].uid, 0);
                int _buildingUID = DAT_BuildingsState::instance.buildings[_buildingID].uid;
                DAT_TribesState::instance.tribes[_tribeID].targetBuildingID = (short)_buildingID;
                DAT_TribesState::instance.tribes[_tribeID].targetBuildingUID = _buildingUID;
                return;
            }

            int _destinationX = DAT_GameState::instance.playerDataArray[_targetPlayer].campground.xEntry;
            DAT_TribesState::instance.tribes[_tribeID].targetBuildingID = 0;
            int _destinationY = DAT_GameState::instance.playerDataArray[_targetPlayer].campground.yEntry;
            BVar4 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::canNavigateUnitsFromTileToTargetTile, this)(_tribeID,
                DAT_ViewportRenderState::instance.translationMatrix[_destinationY].addXgetTile + _destinationX);
            if (BVar4 == FALSE)
                return;
            // was LAB_004d1c59
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::commandUnitsToLocation, DAT_TribesState::ptr)(
                _tribeID, (uint)((int)(_destinationX)), (uint)((int)(_destinationY)), 1);
            return;
        }

        int _buildingID_2 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::selectARandomBuildingOwnedByPlayer,
            DAT_GameState::ptr)(_targetPlayer);

        int _destinationTile;
        int _destinationX2;
        int _destinationY2;

        if (_buildingID_2 == 0) {
            int iVar5 = DAT_ViewportRenderState::instance
                        .translationMatrix[DAT_GameState::instance.playerDataArray[_targetPlayer].campground.yEntry]
                        .addXgetTile;
            _destinationTile = iVar5 + DAT_GameState::instance.playerDataArray[_targetPlayer].campground.xEntry;
        } else {
            int iVar5 = (int)DAT_TribesState::instance.tribes[_tribeID].selectionTargetUnitID;
            if (iVar5 == 0) {
                _destinationTile = (int)DAT_BuildingsState::instance.buildings[_buildingID_2].buildingEntryX
                    + DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_BuildingsState::instance.buildings[_buildingID_2].buildingEntryY]
                          .addXgetTile;
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathfindingForAttacksUnk,
                    DAT_PathFindingState::ptr)(_tribeID, _buildingID_2, 1,
                    (dword)((int)((int)(short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_UnitsState::instance.units[iVar5].tile])),
                    _targetPlayer);
                _destinationTile = DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile1;
                if (DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile2OrAHelper == 0) {
                    // was LAB_004d1d11
                    int iVar5b = DAT_ViewportRenderState::instance
                                .translationMatrix[DAT_GameState::instance.playerDataArray[_targetPlayer].campground.yEntry]
                                .addXgetTile;
                    _destinationTile = iVar5b + DAT_GameState::instance.playerDataArray[_targetPlayer].campground.xEntry;
                }
            }
        }

        if (_destinationTile != 0) {
            _destinationY2 = (int)DAT_ViewportRenderState::instance.DAT_TileTranslationMatrix_YComponent[_destinationTile];
            _destinationX2 = _destinationTile - DAT_ViewportRenderState::instance.translationMatrix[_destinationY2].addXgetTile;
            BOOLEnum BVar4 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::canNavigateUnitsFromTileToTargetTile, this)(
                _tribeID, _destinationTile);
            if (BVar4 != FALSE) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::commandUnitsToLocation, DAT_TribesState::ptr)(
                    _tribeID, (uint)((int)(_destinationX2)), (uint)((int)(_destinationY2)), 1);
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToCampfire, this)(_tribeID, _targetPlayer);
        }
    }
}
}
