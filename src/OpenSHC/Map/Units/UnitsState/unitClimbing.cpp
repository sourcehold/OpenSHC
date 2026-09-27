#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitPropertiesDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Map::Units::States::UnitState;

        // FUNCTION: STRONGHOLDCRUSADER 0x0054C1C0
        void UnitsState::unitClimbing(int unitID)
        {
            /* Offsets:
               0x25E(0x364): climbingState (0 to 5, climbing stops at 5)
               0x6CE(0x0BA): groundHeight
               0x70A(0x0F6): currentIndexInPathPlan
               0x8B2(0x29E): unknown
               0x972(0x35E): climbingDirection */
            short _climbDataID = this->units[unitID].climbDataID;
            if (DAT_PathFindingState::instance.climbData[_climbDataID].canBeUsed == 0
                || DAT_PathFindingState::instance.climbData[_climbDataID].climbDataRelated
                    != this->units[unitID].climbDataRelated) {
                if (this->units[unitID].usingTeleport == 1) {
                    int _climbingState = this->units[unitID].climbingState;
                    this->units[unitID].animationCycleNumber = 0;
                    this->units[unitID].tunnelerFinishedDigging = 1;
                    this->units[unitID].usingTeleport = 0;
                    if ((short)_climbingState < 0) {
                        this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_DETERMINE_NEXT_STATEUnk;
                        return;
                    }
                    this->units[unitID].dying = 1;
                    this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_DEATH_02;
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::exitLadder, this)(unitID);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, this)(
                    unitID, this->units[unitID].destinationX_2Unk, this->units[unitID].destinationY_2Unk, 0);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByLeftover, this)(unitID);
                return;
            }
            if (DAT_PathFindingState::instance.climbData[_climbDataID].type != 1) {
                if (DAT_PathFindingState::instance.climbData[_climbDataID].type != 6
                    && DAT_PathFindingState::instance.climbData[_climbDataID].type != 5
                    && DAT_PathFindingState::instance.climbData[_climbDataID].type != 4
                    && DAT_PathFindingState::instance.climbData[_climbDataID].type != 3
                    && DAT_PathFindingState::instance.climbData[_climbDataID].type != 7) {
                    return;
                }
                if (this->units[unitID].state.generic == (UnitState)0x6c) {
                    this->units[unitID].dying = 1;
                    this->units[unitID].state.generic = OpenSHC::Map::Units::States::US_STONE_DEATH_01;
                    this->units[unitID].animationCycleNumber = 0;
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::exitLadder, this)(unitID);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, this)(
                    unitID, this->units[unitID].destinationX_2Unk, this->units[unitID].destinationY_2Unk, 0);
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByLeftover, this)(unitID);
                return;
            }
            this->units[unitID].field203_0x35c = this->units[unitID].field203_0x35c + 1;
            if (this->units[unitID].field203_0x35c > 0x5f) {
                *(short*)&this->units[unitID].climbingState = (short)this->units[unitID].climbingState + 1;
                this->units[unitID].field203_0x35c = 0;
                if (this->units[unitID].climbingDirection == 1) {
                    /* Climbing up */
                    this->units[unitID].terrainOrClimbHeight = this->units[unitID].terrainOrClimbHeight - 0xf;
                } else {
                    /* Climbing down */
                    this->units[unitID].terrainOrClimbHeight = this->units[unitID].terrainOrClimbHeight + 0xf;
                }
                if ((short)(ushort)DAT_TileMapState::instance
                        .HeightLayer[DAT_ViewportRenderState::instance
                                         .translationMatrix[this->units[unitID].mimicCurrentYPosition]
                                         .addXgetTile
                            + this->units[unitID].mimicCurrentXPosition]
                    < this->units[unitID].terrainOrClimbHeight) {
                    *(undefined2*)&this->units[unitID].climbingState = 5;
                }
            }
            if (this->units[unitID].climbingDirection == 1) {
                /* Climbing up */
                if (this->units[unitID].facingDirectionMapOrientationCorrected == 0) {
                    this->units[unitID].field41_0x5c = (-4 - (short)this->units[unitID].climbingState) * 2;
                } else if (this->units[unitID].facingDirectionMapOrientationCorrected == 2) {
                    this->units[unitID].field41_0x5c = (short)this->units[unitID].climbingState * -2;
                } else if (this->units[unitID].facingDirectionMapOrientationCorrected == 4) {
                    this->units[unitID].field41_0x5c = (short)this->units[unitID].climbingState * 2;
                } else if (this->units[unitID].facingDirectionMapOrientationCorrected == 6) {
                    this->units[unitID].field41_0x5c = (short)this->units[unitID].climbingState * 2 + 8;
                }
            } else {
                /* Climbing down */
                if (this->units[unitID].facingDirectionMapOrientationCorrected == 0) {
                    this->units[unitID].field41_0x5c = (short)this->units[unitID].climbingState * 2 + -3;
                } else if (this->units[unitID].facingDirectionMapOrientationCorrected == 2) {
                    this->units[unitID].field41_0x5c = (short)this->units[unitID].climbingState * 2 + -8;
                } else if (this->units[unitID].facingDirectionMapOrientationCorrected == 4) {
                    this->units[unitID].field41_0x5c = (-4 - (short)this->units[unitID].climbingState) * 2;
                } else if (this->units[unitID].facingDirectionMapOrientationCorrected == 6) {
                    this->units[unitID].field41_0x5c = (2 - (short)this->units[unitID].climbingState) * 2;
                }
            }
            if (this->units[unitID].climbingDirection == 1) {
                /* Climbing up */
                this->units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance.Frames_Shared_UnitClimbingUp
                          .ANIM_Frames_Shared_UnitClimbingUp[(this->units[unitID].field203_0x35c
                                                                 + (this->units[unitID].field203_0x35c >> 0x1f & 7U))
                              >> 3];
            } else {
                /* Climbing down */
                this->units[unitID].animationFrame
                    = (char)DAT_UnitPropertiesDefinedData::instance
                          .Frames_Shared_UnitClimbingDown[(this->units[unitID].field203_0x35c
                                                              + (this->units[unitID].field203_0x35c >> 0x1f & 7U))
                              >> 3];
            }
            this->units[unitID].gfxNumber = this->units[unitID].animationSheetFrameOffset
                + this->units[unitID].animationFrame * 8 + -8
                + this->units[unitID].facingDirectionMapOrientationCorrected;
            this->units[unitID].vanish = 0;
            if (this->units[unitID].facingDirectionMapOrientationCorrected == 0
                || this->units[unitID].facingDirectionMapOrientationCorrected == 6) {
                this->units[unitID].field43_0x64 = 2;
            } else {
                this->units[unitID].vanish = 1;
            }
            /* Stop climbing at climbingState = 5 */
            if ((short)this->units[unitID].climbingState < 5) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::exitLadder, this)(unitID);
            this->units[unitID].state.generic = this->units[unitID].unknownStateCopyClimbRelated;
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::setDestinationForUnit, this)(
                unitID, this->units[unitID].destinationX_2Unk, this->units[unitID].destinationY_2Unk, 0);
            MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::changeDestinationByLeftover, this)(unitID);
        }

    }
}
}
