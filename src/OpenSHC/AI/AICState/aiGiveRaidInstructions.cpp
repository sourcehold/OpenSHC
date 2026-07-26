#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Map::Units::UnitInstructionType;
    using OpenSHC::Map::Units::Behavior::UnitStanceEnum;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004D2A70
    void AICState ::aiGiveRaidInstructions(int playerID)

    {

        int* piVar1;

        short sVar2;

        int iVar3;

        int _isAlive;

        int _buildingID_2;

        int _buildingID;

        int iVar4;

        int _buildingTile;

        BOOLEnum BVar5;

        int _tribeID3;

        BOOLEnum _indexTo6;

        short* _ptrTribeID3;

        int _aiType;

        _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;

        if (_aiType != 0) {

            piVar1 = &DAT_GameState::instance.playerDataArray[playerID].raidRetargetDelayCounter;

            *piVar1 = *piVar1 + 1;

            /*
                  AIC: RaidRetargetDelay */

            _indexTo6 = FALSE;

            if (*(int*)((int)this + (_aiType + -1) * 0x2a4 + 0x1f0)
                <= DAT_GameState::instance.playerDataArray[playerID].raidRetargetDelayCounter) {

                DAT_GameState::instance.playerDataArray[playerID].raidRetargetDelayCounter = 0;
            }

            if (DAT_GameState::instance.playerDataArray[playerID].totalRaidingTroopsUnk == 0) {

                DAT_GameState::instance.playerDataArray[playerID].someTotalDefenseTroopsRelatedCountdown = 0;

            }

            else {

                iVar4 = DAT_GameState::instance.playerDataArray[playerID].someTotalDefenseTroopsRelatedCountdown;

                if (0 < iVar4) {

                    DAT_GameState::instance.playerDataArray[playerID].someTotalDefenseTroopsRelatedCountdown
                        = iVar4 + -1;
                }
            }

            _ptrTribeID3 = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs + 0xb4;

            do {

                _tribeID3 = (int)*_ptrTribeID3;

                DAT_TribesState::instance.tribes[_tribeID3].unitStance = OpenSHC::Map::Units::Behavior::USE_AGGRESSIVE;

                if ((_tribeID3 != 0)
                    && (DAT_TribesState::instance.tribes[_tribeID3].uid
                        == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[_indexTo6 + 0xb4])) {

                    if ((DAT_GameState::instance.playerDataArray[playerID].requestStateUnk == 2)
                        && (_isAlive = MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::UnitsState_Func::getAliveLordForPlayer, DAT_UnitsState::ptr)(
                                DAT_GameState::instance.playerDataArray[playerID].playerID_askerUnk),
                            _isAlive != 0)) {

                        if (DAT_GameState::instance.playerDataArray[playerID].raidRetargetDelayCounter == 0) {

                            _buildingID_2 = MACRO_CALL_MEMBER(
                                OpenSHC::AI::AICState_Func::selectRandomBuildingIDFromListOfBuildingTypes, this)(
                                DAT_GameState::instance.playerDataArray[playerID].playerID_askerUnk,
                                (undefined4)((int)(_indexTo6)));

                            if (_buildingID_2 == 0) {

                                _buildingID = MACRO_CALL_MEMBER(
                                    OpenSHC::AI::AICState_Func::selectBuildingFromAListOfBuildingTypes, this)(playerID);

                            LAB_004d2d6b:
                                if (_buildingID != 0)
                                    goto LAB_004d2d6f;

                            }

                            else {

                            LAB_004d2c00:
                                _buildingTile
                                    = (int)DAT_BuildingsState::instance.buildings[_buildingID_2].buildingEntryX
                                    + DAT_ViewportRenderState::instance
                                          .translationMatrix[DAT_BuildingsState::instance.buildings[_buildingID_2]
                                                  .buildingEntryY]
                                          .addXgetTile;

                            LAB_004d2d8d:
                                if (_buildingTile != 0) {

                                    sVar2 = DAT_ViewportRenderState::instance
                                                .DAT_TileTranslationMatrix_YComponent[_buildingTile];

                                    iVar4 = DAT_ViewportRenderState::instance.translationMatrix[sVar2].addXgetTile;

                                    BVar5 = MACRO_CALL_MEMBER(
                                        OpenSHC::AI::AICState_Func::canNavigateUnitsFromTileToTargetTile, this)(
                                        _tribeID3, _buildingTile);

                                    if (BVar5 == FALSE) {

                                        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::sendUnitsToCampfire, this)(
                                            _tribeID3, playerID);

                                    }

                                    else {

                                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::commandUnitsToLocation,
                                            DAT_TribesState::ptr)(_tribeID3, (uint)((int)(_buildingTile - iVar4)),
                                            (uint)((int)((int)sVar2)), 0);
                                    }
                                }
                            }
                        }

                    }

                    else if ((DAT_GameState::instance.playerDataArray[playerID].someTotalDefenseTroopsRelatedCountdown
                                 == 0)
                        && (iVar4 = MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::getCurrentDesiredAttackRaidUnitCount,
                                this)(_aiType + -1, playerID),
                            DAT_GameState::instance.playerDataArray[playerID].totalRaidingTroopsUnk < iVar4)) {

                        if ((DAT_GameState::instance.playerDataArray[playerID].raidRetargetDelayCounter == 0)
                            && (BVar5 = MACRO_CALL(OpenSHC::Global_Func::CheckTribeActivityPercentages)(
                                    _tribeID3, _indexTo6, TRUE),
                                BVar5 == FALSE)) {

                            _buildingID = MACRO_CALL_MEMBER(
                                OpenSHC::AI::AICState_Func::selectRandomBuildingIDFromListOfBuildingTypes, this)(
                                playerID, (undefined4)((int)(_indexTo6)));

                            if (_buildingID != 0) {

                            LAB_004d2d6f:
                                _buildingTile = (int)DAT_BuildingsState::instance.buildings[_buildingID].buildingEntryX
                                    + DAT_ViewportRenderState::instance
                                          .translationMatrix[DAT_BuildingsState::instance.buildings[_buildingID]
                                                  .buildingEntryY]
                                          .addXgetTile;

                                goto LAB_004d2d8d;
                            }

                            _buildingID_2 = MACRO_CALL_MEMBER(
                                OpenSHC::AI::AICState_Func::selectBuildingFromAListOfBuildingTypes, this)(playerID);

                            if (_buildingID_2 != 0)
                                goto LAB_004d2c00;
                        }

                    }

                    else if ((DAT_SkirmishDefinedData::instance.DAT_TribeTypeID[_indexTo6] == 0xb6)
                        || (DAT_SkirmishDefinedData::instance.DAT_TribeTypeID[_indexTo6] == 0xb5)) {

                        if ((DAT_GameState::instance.playerDataArray[playerID].raidRetargetDelayCounter == 0)
                            && (BVar5 = MACRO_CALL(OpenSHC::Global_Func::CheckTribeActivityPercentages)(
                                    _tribeID3, _indexTo6, FALSE),
                                BVar5 == FALSE)) {

                            _buildingID = MACRO_CALL_MEMBER(
                                OpenSHC::AI::AICState_Func::selectRandomBuildingIDFromListOfBuildingTypes, this)(
                                DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID_2Unk,
                                (undefined4)((int)(_indexTo6)));

                            if (_buildingID == 0) {

                                _buildingID = MACRO_CALL_MEMBER(
                                    OpenSHC::AI::AICState_Func::chooseRandomBuildingIDFromPlayersArrayOfBuildings,
                                    this)(DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID_2Unk);

                                goto LAB_004d2d6b;
                            }

                            goto LAB_004d2d6f;
                        }

                    }

                    else {

                        BVar5 = MACRO_CALL(OpenSHC::Global_Func::CheckTribeActivityPercentages)(
                            _tribeID3, _indexTo6, FALSE);

                        if (BVar5 == FALSE) {

                            iVar4 = (int)DAT_TribesState::instance.tribes[_tribeID3].targetBuildingID;

                            if ((((iVar4 == 0)
                                     || (DAT_BuildingsState::instance.buildings[iVar4].uid
                                         != DAT_TribesState::instance.tribes[_tribeID3].targetBuildingUID))
                                    || (DAT_BuildingsState::instance.buildings[iVar4].fireDuration != 0))
                                || (BVar5 = MACRO_CALL(OpenSHC::Global_Func::CheckTribeActivityPercentages)(
                                        _tribeID3, _indexTo6, TRUE),
                                    BVar5 == FALSE)) {

                                iVar4 = MACRO_CALL_MEMBER(
                                    OpenSHC::AI::AICState_Func::chooseRandomBuildingIDFromPlayersArrayOfBuildings,
                                    this)(DAT_GameState::instance.playerDataArray[playerID].attackedPlayerID_2Unk);

                                if (iVar4 == 0) {

                                    DAT_TribesState::instance.tribes[_tribeID3].targetBuildingID = 0;

                                    DAT_GameState::instance.playerDataArray[playerID]
                                        .someTotalDefenseTroopsRelatedCountdown = 0;

                                }

                                else {

                                    MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::relayTribeInstruction,
                                        DAT_UnitsState::ptr)(_tribeID3, OpenSHC::Map::Units::UIT_ATTACK_BUILDING, iVar4,
                                        DAT_BuildingsState::instance.buildings[iVar4].uid, 0);

                                    iVar3 = DAT_BuildingsState::instance.buildings[iVar4].uid;

                                    DAT_TribesState::instance.tribes[_tribeID3].targetBuildingID = (short)iVar4;

                                    DAT_TribesState::instance.tribes[_tribeID3].targetBuildingUID = iVar3;

                                    DAT_GameState::instance.playerDataArray[playerID]
                                        .someTotalDefenseTroopsRelatedCountdown = 100;
                                }

                            }

                            else {

                                if (DAT_GameState::instance.mapAndTime.yearChanged != 0) {

                                    DAT_TribesState::instance.tribes[_tribeID3].targetBuildingID = 0;
                                }

                                DAT_GameState::instance.playerDataArray[playerID].someTotalDefenseTroopsRelatedCountdown
                                    = 100;
                            }
                        }
                    }
                }

                _ptrTribeID3 = _ptrTribeID3 + 1;

                _indexTo6 = _indexTo6 + TRUE;

            } while ((int)_indexTo6 < 6);
        }

        return;
    }

}
}
