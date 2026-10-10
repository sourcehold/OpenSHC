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

        // FUNCTION: STRONGHOLDCRUSADER 0x00523A30
        void TribesState::drawFlagsAndUnitDestinations(int tribeID)
        {
            short sVar1;
            UnitInstructionTypeShort UVar2;
            uint uVar3;
            int _unitID;
            int iVar4;
            uint _rallyIndex;
            int iVar5;
            short (*_pRallyPoints)[2];
            int tile;
            short _isRallying;
            _isRallying = this->tribes[tribeID].isRallyingUnk;
            if (_isRallying && this->tribes[tribeID].owner == DAT_GameSynchronyState::instance.currentPlayerSlotID
                && (_rallyIndex = (uint)(_isRallying < 0),
                    (int)_rallyIndex < (int)this->tribes[tribeID].rallyPointCount)) {
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
            iVar5 = 0;
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
                        sVar1 = DAT_UnitsState::instance.units[_unitID].unitSpeedMatchingRelatedUnk;
                        if (!sVar1) {
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
                        } else {
                            if (sVar1 < 8) {
                                iVar4 = (8 - sVar1) * 4;
                            } else {
                                iVar4 = 0;
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
                                        uVar3 = DAT_UnitsState::instance.units[_unitID].targetedBuildingTile;
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
