#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A9B20
        dword PathFindingState::doPathfinding(int param_1, int param_2)
        {
            ushort uVar1;
            dword dVar2;
            BOOLEnum BVar3;
            int iVar4;
            uVar1 = DAT_TileMapState::instance.PathConnectionLayer
                        [DAT_ViewportRenderState::instance.translationMatrix[this->destinationY].addXgetTile
                            + this->destinationX];
            if (((DAT_TileMapState::instance.PathConnectionLayer
                         [DAT_ViewportRenderState::instance.translationMatrix[this->unitY].addXgetTile + this->unitX]
                     != uVar1)
                    && (this->climbIsIllegal == 0))
                && (this->allAssassinsUnk == 0)) {
                if (uVar1 == 0) {
                    return (dword)(0);
                }
                dVar2 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::findConnectingAreaBetweenTwoAreas, this)(param_1,
                    (dword)((int)((int)(short)DAT_TileMapState::instance.PathConnectionLayer
                            [DAT_ViewportRenderState::instance.translationMatrix[this->unitY].addXgetTile
                                + this->unitX])),
                    (dword)((int)((int)(short)uVar1)));
                if (dVar2 == 0) {
                    return (dword)(0);
                }
            }
            this->searchQueue.pathPlanIndex = 0;
            this->field43_0x7c = 1;
            if (((this->climbIsIllegal == 0) && (this->allAssassinsUnk == 0))
                && (BVar3 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::tracePathPlanToDestinationViaUnoccupiedTiles,
                        this)(this->unitX, (uint)((int)(this->unitY)), (uint)((int)(this->destinationX)),
                        (uint)((int)(this->destinationY))),
                    BVar3 != FALSE)) {
                this->DAT_Easy = this->DAT_Easy + 1;
                return (dword)(this->searchQueue.pathPlanIndex);
            }
            this->DAT_Hard = this->DAT_Hard + 1;
            this->field43_0x7c = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                DAT_DirectionAlgorithmState::ptr)(this->unitX, this->unitY, this->destinationX, this->destinationY);
            iVar4 = (DAT_DirectionAlgorithmState::instance.distanceHigh + 4)
                * (DAT_DirectionAlgorithmState::instance.distanceHigh + 4) * 10;
            this->searchQueue.pathPlanIndex = 0;
            if (this->notAllAssassinsUnk == 0) {
                if (this->allAssassinsUnk == 0) {
                    BVar3 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::findSuitableSpawnLocationUnk, this)(
                        this->unitX, this->unitY, this->destinationX, this->destinationY, iVar4, 0);
                } else {
                    BVar3 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius, this)(
                        this->unitX, (uint)((int)(this->unitY)), this->destinationX, this->destinationY, iVar4, FALSE);
                }
                if (BVar3 != FALSE)
                    goto LAB_004a9cdd;
                if (this->allAssassinsUnk == 0) {
                    if (this->climbIsIllegal == 0)
                        goto LAB_004a9cce;
                    BVar3 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::findPathUsingClimbingWithHeightMargin16, this)(
                        this->unitX, (uint)((int)(this->unitY)), (uint)((int)(this->destinationX)),
                        (uint)((int)(this->destinationY)), 100000, FALSE);
                } else {
                    BVar3 = MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::PathFindingState_Func::pathFindingWithBuildingsIncluded, this)(
                        this->unitX, (uint)((int)(this->unitY)), (uint)((int)(this->destinationX)),
                        (uint)((int)(this->destinationY)), 100000, 0);
                }
            } else {
            LAB_004a9cce:
                BVar3 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius, this)(
                    this->unitX, (uint)((int)(this->unitY)), this->destinationX, this->destinationY, 100000, FALSE);
            }
            if (BVar3 == FALSE) {
                return (dword)(0);
            }
        LAB_004a9cdd:
            if (this->allAssassinsUnk == 0) {
                if (this->climbIsIllegal == 0) {
                    iVar4 = 1;
                } else {
                    iVar4 = 2;
                }
            } else {
                iVar4 = 3;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::traceAndCommitPathPlan, this)(
                this->unitX, (uint)((int)(this->unitY)), (uint)((int)(this->destinationX)),
                (uint)((int)(this->destinationY)), iVar4);
            if ((param_2 == 0) && (this->field49_0x94 != 0)) {
                this->searchQueue.pathPlanIndex = 0;
                iVar4 = MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::calculatePathKeepAndWallsGatesNotAllowed, this)(
                    this->unitX, this->unitY, this->destinationX, this->destinationY, 100000);
                if (iVar4 != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::traceAndCommitPathPlan, this)(
                        this->unitX, (uint)((int)(this->unitY)), (uint)((int)(this->destinationX)),
                        (uint)((int)(this->destinationY)), 1);
                    return (dword)(this->searchQueue.pathPlanIndex);
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius, this)(
                    this->unitX, (uint)((int)(this->unitY)), this->destinationX, this->destinationY, 100000, FALSE);
                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::traceAndCommitPathPlan, this)(
                    this->unitX, (uint)((int)(this->unitY)), (uint)((int)(this->destinationX)),
                    (uint)((int)(this->destinationY)), 1);
            }
            return (dword)(this->searchQueue.pathPlanIndex);
        }

    }
}
}
