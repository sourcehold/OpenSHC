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

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D1A00
    void AICState ::decideOnTribeAttackLocation(uint tribeID_OR_moatWasHit)

    {

        short* psVar1;

        short sVar2;

        bool bVar3;

        BOOLEnum _canHaveActivity;

        int _unitID;

        BOOLEnum BVar4;

        int _targetBuilding;

        int _buildingID;

        int _buildingID_2;

        int iVar5;

        int _destinationX;

        int _targetPlayer;

        int _destinationY;

        int _y;

        int _x;

        int _buildingUID;

        int _rng;

        int _destinationTile;

        uint _tribeID;

        _tribeID = tribeID_OR_moatWasHit;

        _canHaveActivity
            = MACRO_CALL(OpenSHC::Global_Func::CheckTribeActivityPercentages)(tribeID_OR_moatWasHit, FALSE, TRUE);

        if (_canHaveActivity != FALSE) {

            DAT_TribesState::instance.tribes[_tribeID].counter = 0;

            return;
        }

        _targetPlayer = (int)DAT_TribesState::instance.tribes[_tribeID].targetPlayer_outpost;

        if (DAT_TribesState::instance.tribes[_tribeID].randomNumber == 0) {

            DAT_TribesState::instance.tribes[_tribeID].randomNumber = (int)SEC_RNG::instance.currentNumber2;

            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
        }

        _rng = DAT_TribesState::instance.tribes[_tribeID].randomNumber;

        psVar1 = &DAT_TribesState::instance.tribes[_tribeID].counter;

        *psVar1 = *psVar1 + 1;

        if ((int)DAT_TribesState::instance.tribes[_tribeID].counter == _rng % 6 + 7) {

            DAT_TribesState::instance.tribes[_tribeID].counter = 0;

            /*
                  WARNING: tribeID has a new purpose */

            tribeID_OR_moatWasHit = tribeID_OR_moatWasHit & 0xffffff00;

            _x = 0;

            _y = 0;

            _unitID = MACRO_CALL_MEMBER(
                OpenSHC::Map::Units::TribesState_Func::getUnitIDForIndexInTribe, DAT_TribesState::ptr)(_tribeID, 0);

            if ((_unitID != 0)
                && (bVar3 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::pathFindingToAttackCastleIncludingMoat,
                        DAT_PathFindingState::ptr)(DAT_TribesState::instance.tribes[_tribeID].owner, _targetPlayer,
                        (uint)((int)((int)DAT_UnitsState::instance.units[_unitID].x)),
                        (uint)((int)((int)DAT_UnitsState::instance.units[_unitID].y)), (byte*)&tribeID_OR_moatWasHit,
                        &_x, &_y),
                    bVar3)) {

                if ((char)tribeID_OR_moatWasHit != '\0') {

                    /*
                              moat was not hit */

                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::relayTribeInstruction, DAT_UnitsState::ptr)(
                        _tribeID, ((UnitInstructionType)0x23),
                        DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile + _x, 0, 0);

                    return;
                }

                /*
                        moat was hit */

                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::relayTribeInstruction, DAT_UnitsState::ptr)(
                    _tribeID, OpenSHC::Map::Units::UIT_FILL_MOAT, _x, _y, 1000);

                return;
            }
        }

        sVar2 = DAT_TribesState::instance.tribes[_tribeID].tribeSubtype1;

        if ((sVar2 != 0xb6) && (sVar2 != 0xb9)) {

            BVar4 = MACRO_CALL(OpenSHC::Global_Func::CheckTribeActivityPercentages)(_tribeID, FALSE, FALSE);

            if (BVar4 != FALSE) {

                return;
            }

            _targetBuilding = (int)DAT_TribesState::instance.tribes[_tribeID].targetBuildingID;

            if ((((_targetBuilding != 0)
                     && (DAT_BuildingsState::instance.buildings[_targetBuilding].uid
                         == DAT_TribesState::instance.tribes[_tribeID].targetBuildingUID))
                    && (DAT_BuildingsState::instance.buildings[_targetBuilding].fireDuration == 0))
                && (BVar4 = MACRO_CALL(OpenSHC::Global_Func::CheckTribeActivityPercentages)(_tribeID, FALSE, TRUE),
                    BVar4 != FALSE)) {

                if (DAT_GameState::instance.mapAndTime.yearChanged == 0) {

                    return;
                }

                DAT_TribesState::instance.tribes[_tribeID].targetBuildingID = 0;

                return;
            }

            _buildingID = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::selectARandomBuildingOwnedByPlayer,
                DAT_GameState::ptr)(_targetPlayer);

            if (_buildingID != 0) {

                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::relayTribeInstruction, DAT_UnitsState::ptr)(
                    _tribeID, OpenSHC::Map::Units::UIT_ATTACK_BUILDING, _buildingID,
                    DAT_BuildingsState::instance.buildings[_buildingID].uid, 0);

                _buildingUID = DAT_BuildingsState::instance.buildings[_buildingID].uid;

                DAT_TribesState::instance.tribes[_tribeID].targetBuildingID = (short)_buildingID;

                DAT_TribesState::instance.tribes[_tribeID].targetBuildingUID = _buildingUID;

                return;
            }

            _destinationX = DAT_GameState::instance.playerDataArray[_targetPlayer].campground.xEntry;

            DAT_TribesState::instance.tribes[_tribeID].targetBuildingID = 0;

            _destinationY = DAT_GameState::instance.playerDataArray[_targetPlayer].campground.yEntry;

            BVar4 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::canNavigateUnitsFromTileToTargetTile, this)(_tribeID,
                DAT_ViewportRenderState::instance.translationMatrix[_destinationY].addXgetTile + _destinationX);

            if (BVar4 == FALSE) {

                return;
            }

            goto LAB_004d1c59;
        }

        _buildingID_2 = MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::selectARandomBuildingOwnedByPlayer,
            DAT_GameState::ptr)(_targetPlayer);

        if (_buildingID_2 == 0) {

            iVar5 = DAT_ViewportRenderState::instance
                        .translationMatrix[DAT_GameState::instance.playerDataArray[_targetPlayer].campground.yEntry]
                        .addXgetTile;

        LAB_004d1d11:
            _destinationTile = iVar5 + DAT_GameState::instance.playerDataArray[_targetPlayer].campground.xEntry;

        }

        else {

            iVar5 = (int)DAT_TribesState::instance.tribes[_tribeID].selectionTargetUnitID;

            if (iVar5 == 0) {

                _destinationTile = (int)DAT_BuildingsState::instance.buildings[_buildingID_2].buildingEntryX
                    + DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_BuildingsState::instance.buildings[_buildingID_2].buildingEntryY]
                          .addXgetTile;

            }

            else {

                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::pathfindingForAttacksUnk,
                    DAT_PathFindingState::ptr)(_tribeID, _buildingID_2, 1,
                    (dword)((int)((int)(short)DAT_TileMapState::instance
                            .PathConnectionLayer[DAT_UnitsState::instance.units[iVar5].tile])),
                    _targetPlayer);

                _destinationTile = DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile1;

                if (DAT_PathFindingState::instance.searchQueue.destinationsArray[0].tile2OrAHelper == 0) {

                    iVar5 = DAT_ViewportRenderState::instance
                                .translationMatrix[DAT_GameState::instance.playerDataArray[_targetPlayer]
                                        .campground.yEntry]
                                .addXgetTile;

                    goto LAB_004d1d11;
                }
            }
        }

        if (_destinationTile != 0) {

            _destinationY
                = (int)DAT_ViewportRenderState::instance.DAT_TileTranslationMatrix_YComponent[_destinationTile];

            _destinationX
                = _destinationTile - DAT_ViewportRenderState::instance.translationMatrix[_destinationY].addXgetTile;

            BVar4 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::canNavigateUnitsFromTileToTargetTile, this)(
                _tribeID, _destinationTile);

            if (BVar4 != FALSE) {

            LAB_004d1c59:
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::commandUnitsToLocation, DAT_TribesState::ptr)(
                    _tribeID, (uint)((int)(_destinationX)), (uint)((int)(_destinationY)), 1);

                return;
            }

            MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToCampfire, this)(_tribeID, _targetPlayer);
        }

        return;
    }

}
}
