#include "../../../Map.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using IO::Graphics::GmID;
        using Map::Units::UnitInstructionType;
        using Map::Units::UnitLogicState;

        /*
          The `short` local stays narrow: widening it costs 3.9 points
          (41.8% -> 37.9%). Splitting it so that only the three target-ID uses get an `int`
          - which is where our `movzx` plus `movsx` pairs are against the original's single
          `movsx` - costs 1.3 points too (47.0% -> 45.7%).
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00523A30
        void TribesState::drawFlagsAndUnitDestinations(int tribeID)
        {
            UnitInstructionTypeShort UVar2;
            int _unitID;
            int iVar4;
            short (*_pRallyPoints)[2];
            int tile;
            short _isRallying;
            _isRallying = this->tribes[tribeID].isRallyingUnk;
            /*
              Three nested tests, not one chain: the original has three separate forward
              jumps (0x523a53, 0x523a62, 0x523a7d). The player ID is loaded first and the
              tribe's owner compared to it (`mov esi, [..]`, `cmp [ebp + 0x2c], esi`), and
              the starting index is a branch rather than a `setl`
              (`test ax, ax`, `jge`, `mov esi, 1`).
             */
            if (_isRallying && DAT_GameSynchronyState::instance.currentPlayerSlotID == this->tribes[tribeID].owner) {
                uint _rallyIndex = 0;
                if (_isRallying < 0) {
                    _rallyIndex = 1;
                }
                if ((int)_rallyIndex < (int)this->tribes[tribeID].rallyPointCount) {
                    _pRallyPoints = this->tribes[tribeID].rallyPointArray + _rallyIndex;
                    do {
                        /*
                          spawn the rally point flag
                         */
                        MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                            DAT_ViewportRenderState::ptr)(IO::Graphics::GID_FLOATS_NEW,
                            (int)(((*_pRallyPoints)[0] + DAT_TileMapState::instance.flagAnimationFrame + _rallyIndex
                                      + (*_pRallyPoints)[1])
                                    % 10
                                + 0x61),
                            0x12, -1,
                            (int)(DAT_ViewportRenderState::instance.translationMatrix[(*_pRallyPoints)[1]].addXgetTile
                                + (*_pRallyPoints)[0]),
                            0xa0022);
                        _rallyIndex = _rallyIndex + 1;
                        _pRallyPoints = _pRallyPoints + 1;
                    } while ((int)_rallyIndex < (int)this->tribes[tribeID].rallyPointCount);
                }
            }
            int iVar5 = 0;
            if (0 < this->tribes[tribeID].size) {
                do {
                    _unitID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getSpecificUnitFromTribe, this)(
                        tribeID, iVar5);
                    iVar5 = iVar5 + 1;
                    if (DAT_UnitsState::instance.units[_unitID].logicalState == Map::Units::ULS_NORMAL
                        && DAT_UnitsState::instance.units[_unitID].dying == 0
                        && DAT_UnitsState::instance.units[_unitID].unknownTestAgainst0_2 == 0
                        && DAT_UnitsState::instance.units[_unitID].owner
                            == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        short sVar1 = DAT_UnitsState::instance.units[_unitID].unitSpeedMatchingRelatedUnk;
                        /*
                          The speed-matching arm is the fall-through. The original reads
                          the field and tests it sixteen bits wide, then jumps 0x91 forward
                          when it is zero (`test dx, dx; je 0x91`), so the arm that draws
                          the speed cursor follows the test and the planned-destination arm
                          goes in the far block.
                         */
                        if (sVar1) {
                            /*
                              The zero is the fall-through. The original has
                              `cmp dx, 8; jl 0x4` - jumping over `xor eax, eax` into the
                              scaling - so `iVar4 = 0` sits under the test and the
                              `(8 - speed) * 4` arm comes after it. Written `sVar1 < 8`
                              first they swap and the test inverts to `jge`.
                             */
                            if (sVar1 >= 8) {
                                iVar4 = 0;
                            } else {
                                iVar4 = (8 - sVar1) * 4;
                            }
                            tile = (int)DAT_UnitsState::instance.units[_unitID].plannedDestinationX
                                + DAT_ViewportRenderState::instance
                                      .translationMatrix[DAT_UnitsState::instance.units[_unitID].plannedDestinationY]
                                      .addXgetTile;
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                                DAT_ViewportRenderState::ptr)(
                                IO::Graphics::GID_CURSORS, (int)(0x6a - sVar1), 10, 6, tile, iVar4 << 0x10 | 2);
                            iVar4 = DAT_TileMapState::instance.cursorOverlayAnimationFrame + -1;
                            if (7 < iVar4) {
                                iVar4 = 0xf - iVar4;
                            }
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                                DAT_ViewportRenderState::ptr)(IO::Graphics::GID_CURSORS, iVar4 + 0x52, 0xc, 6, tile,
                                (int)(DAT_UnitsState::instance.units[_unitID].unitSpeedMatchingRelatedUnk << 0x11 | 2));
                        } else {
                            if (DAT_UnitsState::instance.units[_unitID].currentIndexInPathPlan
                                    < DAT_UnitsState::instance.units[_unitID].totalSizeOfPathPlan
                                && (UVar2 = DAT_UnitsState::instance.units[_unitID].targetingType,
                                    UVar2 != Map::Units::UIT_UNIT_ATTACK_UNIT)
                                && UVar2 != Map::Units::UIT_ATTACK_LAND
                                && UVar2 != Map::Units::UIT_MAN_SIEGE_EQUIPMENT) {
                                iVar4 = DAT_TileMapState::instance.cursorOverlayAnimationFrame + -1;
                                if (7 < iVar4) {
                                    iVar4 = 0xf - iVar4;
                                }
                                MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingLayerElement,
                                    DAT_ViewportRenderState::ptr)(IO::Graphics::GID_CURSORS, iVar4 + 0x52, 0xc, 6,
                                    (int)DAT_UnitsState::instance.units[_unitID].plannedDestinationX
                                        + DAT_ViewportRenderState::instance
                                            .translationMatrix[DAT_UnitsState::instance.units[_unitID]
                                                    .plannedDestinationY]
                                            .addXgetTile,
                                    2);
                            }
                        }
                        UVar2 = DAT_UnitsState::instance.units[_unitID].targetingType;
                        if ((UVar2 == Map::Units::UIT_ATTACK_LAND) || (UVar2 == Map::Units::UIT_THROW_COW)) {
                            MACRO_CALL_MEMBER(Map::TileMapState_Func::spawnFloatingNumberAroundTile,
                                DAT_TileMapState::ptr)((int)DAT_UnitsState::instance.units[_unitID].attackAtTileX,
                                (int)(DAT_UnitsState::instance.units[_unitID].attackAtTileY),
                                (int)(DAT_UnitsState::instance.units[_unitID].unkAttackRelated));
                        } else {
                            if (UVar2 == Map::Units::UIT_FILL_MOAT) {
                                iVar4 = (int)DAT_UnitsState::instance.units[_unitID].targetX
                                    + DAT_ViewportRenderState::instance
                                          .translationMatrix[DAT_UnitsState::instance.units[_unitID].targetY]
                                          .addXgetTile;
                            } else {
                                if (UVar2 != Map::Units::UIT_DIG_MOAT) {
                                    if (UVar2 == Map::Units::UIT_UNIT_ATTACK_UNIT) {
                                        sVar1 = DAT_UnitsState::instance.units[_unitID]
                                                    .targetedUnitID__OR__engineerMannedSiegeEngineRef;
                                        if ((DAT_UnitsState::instance.units[sVar1].uid
                                                == DAT_UnitsState::instance.units[_unitID]
                                                    .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID)
                                            && (DAT_UnitsState::instance.units[sVar1].logicalState
                                                == Map::Units::ULS_NORMAL)) {
                                            DAT_UnitsState::instance.units[sVar1].field45_0x6c = 1;
                                        }
                                    } else if (UVar2 == Map::Units::UIT_ATTACK_BUILDING) {
                                        sVar1 = DAT_UnitsState::instance.units[_unitID].targetID_OR_targetBuildingID;
                                        if ((sVar1)
                                            && (DAT_BuildingsState::instance.buildings[sVar1].uid
                                                == DAT_UnitsState::instance.units[_unitID]
                                                    .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID)) {
                                            DAT_BuildingsState::instance.buildings[sVar1].field68_0xc2 = 1;
                                        }
                                    } else if (UVar2 == Map::Units::UIT_LIGHT_PITCH) {
                                        sVar1 = DAT_UnitsState::instance.units[_unitID].targetID_OR_targetBuildingID;
                                        if ((sVar1)
                                            && (DAT_TileMapState::instance.pitchDitches[sVar1].uid
                                                == DAT_UnitsState::instance.units[_unitID]
                                                    .targetedUnitUIDUnk_OR_someAppearTileUnk_OR_buildingUID_OR_pitchDitchUID_OR_entityUID)) {
                                            DAT_TileMapState::instance
                                                .MiscDisplayLayer[DAT_TileMapState::instance.pitchDitches[sVar1].tile]
                                                = DAT_TileMapState::instance.MiscDisplayLayer
                                                      [DAT_TileMapState::instance.pitchDitches[sVar1].tile]
                                                | 0x4000;
                                        }
                                    } else {
                                        uint uVar3 = DAT_UnitsState::instance.units[_unitID].targetedBuildingTile;
                                        if ((uVar3) && (DAT_TileMapState::instance.BuildingLayer[uVar3] != 0)) {
                                            DAT_BuildingsState::instance
                                                .buildings[DAT_TileMapState::instance.BuildingLayer[uVar3]]
                                                .field68_0xc2 = 1;
                                        }
                                    }
                                    continue;
                                }
                                iVar4 = (int)DAT_UnitsState::instance.units[_unitID].targetX
                                    + DAT_ViewportRenderState::instance
                                          .translationMatrix[DAT_UnitsState::instance.units[_unitID].targetY]
                                          .addXgetTile;
                            }
                            MACRO_CALL_MEMBER(Rendering::ViewportRenderState_Func::createFloatingTextElement,
                                DAT_ViewportRenderState::ptr)(0x4e, 6, -0x20, iVar4, 2);
                        }
                    }
                } while (iVar5 < this->tribes[tribeID].size);
            }
            return;
        }

    }
}
}
