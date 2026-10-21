#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WildlifeState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::SomeTribeBehaviorType;
        using Map::Units::UnitType;
        using Map::Units::Instructions::UnitMatchSpeedEnum;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052B390
        void TribesState::updateRabbitTribeBehavior(int tribeID)
        {
            /*
              Base cached as the original does (`lea`, two registers, no displacement), so
              the field displacements are unchanged - the subscript already matches those.
              Worth +1.4 here, and that is the whole of it. The same change on the three
              nearest siblings loses: updateCamelTribeBehavior -14.2,
              updateLionWolfTribeBehavior -6.0, computeTribePercentages -2.1. Across the
              namespace caching the base now stands at two clear wins (trimTribeToSize and
              createTribe, +11.8 each, the latter also fixing displacements), this +1.4, one
              flat, and five losses from -2.1 to -40.8. There is no predictor; measure.
             */
            TribesState* const _tb = (TribesState*)((char*)this + tribeID * sizeof(Tribe));
            short* psVar1;
            int sVar2;
            SomeTribeBehaviorTypeShort SVar3;
            int sVar4;
            int iVar5;
            int iVar6;
            BOOLEnum BVar7;
            int iVar8;
            int _x10;
            int _y10;
            int _targetUnitID;
            sVar2 = _tb->tribes[0].selectionTargetUnitID;
            _x10 = (int)DAT_UnitsState::instance.units[sVar2].x / 10;
            _y10 = (int)DAT_UnitsState::instance.units[sVar2].y / 10;
            iVar5 = DAT_WildlifeState::instance.grid[_x10][_y10].rockyTiles;
            iVar6 = DAT_WildlifeState::instance.grid[_x10][_y10].marshTiles;
            BVar7 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::isTribeFreeOfTunnelingUnits, this)(
                tribeID, _tb->tribes[0].uid);
            _tb->tribes[0].unkIsAnimalTribe = 1;
            iVar8 = 80;
            if (DAT_GameState::instance.mapAndTime.eventCountdownRabbitInfestation) {
                iVar8 = 3;
            }
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::spawnDeerLionOrRabbit, this)(
                tribeID, iVar8, Map::Units::UT_RABBIT);
            if (_tb->tribes[0].initialMoveOrderGiven == 0) {
                _targetUnitID = _tb->tribes[0].selectionTargetUnitID;
                _tb->tribes[0].initialMoveOrderGiven = 1;
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::standUpAllTribeUnits, this)(tribeID);
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(tribeID,
                    (uint)(DAT_UnitsState::instance.units[_targetUnitID].x),
                    (uint)(DAT_UnitsState::instance.units[_targetUnitID].y), 0, 0, Map::Units::Instructions::UMSE_0);
                _tb->tribes[0].tribeBehaviorType = Map::Units::STBT_1;
                /*
                  And from this one: the block at 0x52b440 ends in `ret 4` after setting
                  the behaviour type, like its three sibling updaters.
                 */
                return;
            }
            /*
              The original returns from this one: the block at 0x52b489 ends in `ret 4`
              right after zeroing the counter.
             */
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                _tb->tribes[0].unknownCounter01 = 0;
                return;
            }
            sVar2 = _tb->tribes[0].predatorNearby;
            if (!sVar2) {
                SVar3 = _tb->tribes[0].tribeBehaviorType;
                if (SVar3 == (SomeTribeBehaviorType)0) {
                    sVar4 = _tb->tribes[0].unknownAttackRelatedUpdateCounter;
                    sVar2 = sVar4 + 1;
                    _tb->tribes[0].unknownAttackRelatedUpdateCounter = sVar2;
                    if (!sVar4) {
                        BVar7 = MACRO_CALL_MEMBER(
                            Map::WildlifeState_Func::buildRallyPointPathForTribe, DAT_WildlifeState::ptr)(tribeID, 4);
                        if (!BVar7) {
                            MACRO_CALL_MEMBER(Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                                DAT_WildlifeState::ptr)(tribeID, 2, 1);
                        }
                        if (0 < _tb->tribes[0].rallyPointCount) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::standUpAllTribeUnits, this)(tribeID);
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::applyLadderDestructionToTribeUnits, this)(
                                tribeID);
                        }
                    } else if (sVar2 == 0x96) {
                        /*
                          Signed: `cmp ax, dx` with a `jle`, and the index that follows is
                          `movsx ax`, so a negative count does not wrap into a huge index.
                         */
                        sVar2 = (int)_tb->tribes[0].rallyPointCount;
                        if (0 < sVar2) {
                            MACRO_CALL_MEMBER(
                                Map::Units::TribesState_Func::giveUnitSelectionMoveInstructionNoMatchedSpeed, this)(
                                tribeID, (uint)((int)_tb->tribes[0].rallyPointArray[sVar2 + -1][0]),
                                (uint)((int)_tb->tribes[0].rallyPointArray[sVar2 + -1][1]), 0, 0);
                        }
                    } else if (BVar7) {
                        _tb->tribes[0].tribeBehaviorType = Map::Units::STBT_1;
                        _tb->tribes[0].unknownAttackRelatedUpdateCounter = 0;
                    }
                } else if (SVar3 == Map::Units::STBT_1) {
                    /*
                      The marsh-tile arm comes first: `cmp ebp, edx; jz` falls into the
                      0x14 store and jumps away to the rocky-tile test.
                     */
                    if (iVar6) {
                        _tb->tribes[0].wanderIntervalTicks = 0x14;
                    } else if (0x14 < iVar5) {
                        _tb->tribes[0].wanderIntervalTicks = 0x14;
                    } else {
                        _tb->tribes[0].wanderIntervalTicks = 400;
                    }
                    psVar1 = (short*)&_tb->tribes[0].unknownAttackRelatedUpdateCounter;
                    *psVar1 = *psVar1 + 1;
                    if (_tb->tribes[0].wanderIntervalTicks
                        <= _tb->tribes[0].unknownAttackRelatedUpdateCounter) {
                        _tb->tribes[0].tribeBehaviorType = ((SomeTribeBehaviorType)0);
                        _tb->tribes[0].unknownAttackRelatedUpdateCounter = 0;
                    }
                }
            } else {
                if (sVar2 == 1) {
                    MACRO_CALL_MEMBER(Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                        DAT_WildlifeState::ptr)(tribeID, 3, 0);
                    if (_tb->tribes[0].rallyPointCount <= 0) {
                        MACRO_CALL_MEMBER(Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                            DAT_WildlifeState::ptr)(tribeID, 3, 1);
                    }
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::standUpAllTribeUnits, this)(tribeID);
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::scatterTribeUnitsRandomly, this)(tribeID);
                }
                psVar1 = (short*)&_tb->tribes[0].predatorNearby;
                *psVar1 = *psVar1 + 1;
                if (2999 < _tb->tribes[0].predatorNearby) {
                    _tb->tribes[0].predatorNearby = 0;
                }
            }
        }

    }
}
}
