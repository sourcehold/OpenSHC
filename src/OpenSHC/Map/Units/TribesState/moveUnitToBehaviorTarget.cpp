#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::SomeTribeBehaviorType;
        using Map::Units::UnitLogicState;
        using Map::Units::States::UnitState;

        /*
          The gotos stay here, against the style list, because the original really does
          duplicate these tails and three goto-free shapes all measure worse: merging the
          two `local_c = y` tails into one `if (iVar4)` block gives quick_diff 0.2730 at 137
          instructions against the original's 156, duplicating the success tail into all
          eight arms gives 0.2951 at 149, and this form gives 0.4092 at 147.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00521280
        undefined4 TribesState::moveUnitToBehaviorTarget(int unitID, int param_2)
        {
            int iVar4;
            int sVar1 = DAT_UnitsState::instance.units[unitID].tribeID;
            int bVar3 = 0;
            uint x = 0;
            uint uVar6 = 0;
            uint local_c = 0;
            if (DAT_UnitsState::instance.units[unitID].logicalState != Map::Units::ULS_NORMAL) {
                return (undefined4)(0);
            }
            if (DAT_UnitsState::instance.units[unitID].dying != 0) {
                return (undefined4)(0);
            }
            if (DAT_UnitsState::instance.units[unitID].usingTeleport != 0) {
                return (undefined4)(0);
            }
            if (DAT_UnitsState::instance.units[unitID].field303_0x413 != 0) {
                return (undefined4)(0);
            }
            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[DAT_UnitsState::instance.units[unitID].owner]
                != -1) {
                return (undefined4)(0);
            }
            if (param_2 == 0x3f2) {
                iVar4 = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::findEnemyWalls, DAT_TroopValueState::ptr)(
                    unitID);
            LAB_0052130b:
                if (!iVar4)
                    goto LAB_0052143b;
                local_c = DAT_TroopValueState::instance.y;
            } else if (param_2 == 0x3f5) {
                iVar4 = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::findEnemyBuildingsClosestToUnit,
                    DAT_TroopValueState::ptr)(unitID);
            LAB_00521333:
                if (!iVar4)
                    goto LAB_0052143b;
                local_c = DAT_TroopValueState::instance.y;
            } else {
                if (param_2 == 0x3fb) {
                    iVar4 = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::calculateTile2PeoplValueClosestToUnit,
                        DAT_TroopValueState::ptr)(unitID);
                    if (!iVar4) {
                        iVar4 = MACRO_CALL_MEMBER(
                            Map::Units::TroopValueState_Func::findEnemyWalls, DAT_TroopValueState::ptr)(unitID);
                        if (!iVar4)
                            goto LAB_0052143b;
                        if (this->tribes[sVar1].selectionTargetUnitID == unitID) {
                            DAT_TribesState::instance.tribes[sVar1].tribeBehaviorType = Map::Units::STBT_0x3f2;
                        }
                        local_c = DAT_TroopValueState::instance.y;
                        DAT_UnitsState::instance.units[unitID].unknownDigMoatOrWallAttackFlag1015 = 0x3f2;
                        goto LAB_0052142a;
                    }
                } else {
                    if (param_2 == 0x3fd) {
                        iVar4 = MACRO_CALL_MEMBER(
                            Map::Units::TroopValueState_Func::findEnemyLord, DAT_TroopValueState::ptr)(unitID);
                        goto LAB_00521333;
                    }
                    if (param_2 == 0x3f6) {
                        iVar4 = MACRO_CALL_MEMBER(
                            Map::Units::TroopValueState_Func::findEnemyTowersOrGates, DAT_TroopValueState::ptr)(unitID);
                    } else {
                        if (param_2 == 0x413) {
                            iVar4
                                = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getClosestWideValueBasedOnPlayer,
                                    DAT_TroopValueState::ptr)(unitID);
                            goto LAB_0052130b;
                        }
                        if (param_2 == 0x414) {
                            iVar4
                                = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::getClosestWideValueBasedOnPlayer,
                                    DAT_TroopValueState::ptr)(unitID);
                            goto LAB_00521333;
                        }
                        if (param_2 != 0x3f7)
                            goto LAB_0052143b;
                        iVar4 = MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::findNearestDiggableMoatPoint,
                            DAT_TroopValueState::ptr)(unitID);
                    }
                    if (!iVar4)
                        goto LAB_0052143b;
                }
                local_c = DAT_TroopValueState::instance.y;
            }
        LAB_0052142a:
            bVar3 = 1;
            x = DAT_TroopValueState::instance.x;
            uVar6 = DAT_TroopValueState::instance.tile;
        LAB_0052143b:
            DAT_UnitsState::instance.units[unitID].targetedBuildingTile = 0;
            if (!bVar3) {
                return (undefined4)(0);
            }
            short sVar5 = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[uVar6];
            short sVar2 = DAT_UnitsState::instance.units[unitID].selectionTargetUnitID;
            DAT_UnitsState::instance.units[unitID].attackAtTileY = sVar5;
            DAT_UnitsState::instance.units[unitID].targetedBuildingTile = uVar6;
            sVar5 = (short)uVar6 - (short)DAT_ViewportRenderState::instance.translationMatrix[sVar5].addXgetTile;
            DAT_UnitsState::instance.units[unitID].state.generic = Map::Units::States::US_MOVE_TO_DESTINATION;
            DAT_UnitsState::instance.units[unitID].attackAtTileX = sVar5;
            /*
              Reached through `this`, which the original keeps in a stack slot
              ([esp + 0x18]) across the whole dispatch; only the behaviour-type store in the
              0x3fb arm goes through the global's absolute address.
             */
            if (sVar2 == unitID) {
                this->tribes[sVar1].targetX = sVar5;
                this->tribes[sVar1].targetY = DAT_UnitsState::instance.units[unitID].attackAtTileY;
            }
            iVar4 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::stopUnitIfNextToTarget, DAT_UnitsState::ptr)(unitID);
            if (!iVar4) {
                MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::setDestinationForUnit, DAT_UnitsState::ptr)(
                    unitID, x, local_c, 0);
            }
            return (undefined4)(1);
        }

    }
}
}
