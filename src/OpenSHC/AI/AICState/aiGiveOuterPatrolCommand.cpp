#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Behavior/UnitStanceEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D28B0
    void AICState::aiGiveOuterPatrolCommand(int playerID)
    {
        int* piVar1;
        short sVar2;
        int iVar3;
        short* psVar4;
        int _buildingID;
        int _buildingID2;
        int _tile;
        BOOLEnum _canNavigate;
        int _aicOffset;
        int _tribeID;
        int _index;
        int _count;
        int _aiType = DAT_GameState::instance.playerDataArray[playerID].aiType;
        if (_aiType != 0) {
            _aicOffset = (_aiType + -1) * 0x2a4;
            _count = (int)this->aics[_aiType - 1].OuterPatrolGroupsCount;
            _index = 0;
            if (((0 < _count)
                    && (piVar1 = &DAT_GameState::instance.playerDataArray[playerID].outerPatrolRallyDelayTracker,
                        *piVar1 = *piVar1 + 1,
                        (int)this->aics[_aiType - 1].OuterPatrolRallyDelay
                            <= DAT_GameState::instance.playerDataArray[playerID].outerPatrolRallyDelayTracker))
                && (DAT_GameState::instance.playerDataArray[playerID].outerPatrolRallyDelayTracker = 0, 0 < _count)) {
                psVar4 = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs + 0xaa;
                do {
                    _tribeID = (int)*psVar4;
                    DAT_TribesState::instance.tribes[_tribeID].unitStance = Map::Units::Behavior::USE_AGGRESSIVE;
                    if (((_tribeID != 0)
                            && (DAT_TribesState::instance.tribes[_tribeID].uid
                                == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[_index + 0xaa]))
                        && ((DAT_TribesState::instance.tribes[_tribeID].percentageMovingUnk < 0xb
                            && ((DAT_TribesState::instance.tribes[_tribeID].percentageShootingUnk < 0xb
                                && (DAT_TribesState::instance.tribes[_tribeID].percentageAttackingUnk < 0xb)))))) {
                        if (((int)this->aics[_aiType - 1].OuterPatrolGroupsMove == 0)
                            || (_buildingID = MACRO_CALL_MEMBER(AICState_Func::getTargetableBuildingForPlayerID, this)(
                                    playerID, _index),
                                _buildingID == 0)) {
                            _buildingID2 = MACRO_CALL_MEMBER(
                                AICState_Func::selectBuildingFromAListOfBuildingTypes, this)(playerID);
                            if (_buildingID2 == 0)
                                goto LAB_004d2a44;
                            _tile = (int)DAT_BuildingsState::instance.buildings[_buildingID2].buildingEntryX
                                + DAT_ViewportRenderState::instance
                                      .translationMatrix[DAT_BuildingsState::instance.buildings[_buildingID2]
                                              .buildingEntryY]
                                      .addXgetTile;
                        } else {
                            _tile = (int)DAT_BuildingsState::instance.buildings[_buildingID].buildingEntryX
                                + DAT_ViewportRenderState::instance
                                      .translationMatrix[DAT_BuildingsState::instance.buildings[_buildingID]
                                              .buildingEntryY]
                                      .addXgetTile;
                        }
                        if (_tile != 0) {
                            sVar2 = DAT_ViewportRenderState::instance.DAT_TileTranslationMatrix_YComponent[_tile];
                            iVar3 = DAT_ViewportRenderState::instance.translationMatrix[sVar2].addXgetTile;
                            _canNavigate = MACRO_CALL_MEMBER(AICState_Func::canNavigateUnitsFromTileToTargetTile, this)(
                                _tribeID, _tile);
                            if (_canNavigate == FALSE) {
                                MACRO_CALL_MEMBER(AICState_Func::sendUnitsToCampfire, this)(_tribeID, playerID);
                            } else {
                                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::commandUnitsToLocation,
                                    DAT_TribesState::ptr)(_tribeID, _tile - iVar3, (int)sVar2, 0);
                            }
                        }
                    }
                LAB_004d2a44:
                    _index = _index + 1;
                    psVar4 = psVar4 + 1;
                } while (_index < _count);
            }
        }
    }
}
}
