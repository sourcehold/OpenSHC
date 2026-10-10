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
            sVar2 = this->tribes[tribeID].selectionTargetUnitID;
            _x10 = (int)DAT_UnitsState::instance.units[sVar2].x / 10;
            _y10 = (int)DAT_UnitsState::instance.units[sVar2].y / 10;
            iVar5 = DAT_WildlifeState::instance.grid[_x10][_y10].rockyTiles;
            iVar6 = DAT_WildlifeState::instance.grid[_x10][_y10].marshTiles;
            BVar7 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::isTribeFreeOfTunnelingUnits, this)(
                tribeID, this->tribes[tribeID].uid);
            this->tribes[tribeID].unkIsAnimalTribe = 1;
            iVar8 = 80;
            if (DAT_GameState::instance.mapAndTime.eventCountdownRabbitInfestation) {
                iVar8 = 3;
            }
            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::spawnDeerLionOrRabbit, this)(
                tribeID, iVar8, Map::Units::UT_RABBIT);
            if (this->tribes[tribeID].initialMoveOrderGiven == 0) {
                _targetUnitID = this->tribes[tribeID].selectionTargetUnitID;
                this->tribes[tribeID].initialMoveOrderGiven = 1;
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::standUpAllTribeUnits, this)(tribeID);
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(tribeID,
                    (uint)((int)((int)DAT_UnitsState::instance.units[_targetUnitID].x)),
                    (uint)((int)((int)DAT_UnitsState::instance.units[_targetUnitID].y)), 0, 0,
                    Map::Units::Instructions::UMSE_0);
                this->tribes[tribeID].tribeBehaviorType = Map::Units::STBT_1;
            }
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                this->tribes[tribeID].unknownCounter01 = 0;
            }
            sVar2 = this->tribes[tribeID].predatorNearby;
            if (!sVar2) {
                SVar3 = this->tribes[tribeID].tribeBehaviorType;
                if (SVar3 == (SomeTribeBehaviorType)0) {
                    sVar4 = this->tribes[tribeID].unknownAttackRelatedUpdateCounter;
                    sVar2 = sVar4 + 1;
                    this->tribes[tribeID].unknownAttackRelatedUpdateCounter = sVar2;
                    if (!sVar4) {
                        BVar7 = MACRO_CALL_MEMBER(
                            Map::WildlifeState_Func::buildRallyPointPathForTribe, DAT_WildlifeState::ptr)(tribeID, 4);
                        if (!BVar7) {
                            MACRO_CALL_MEMBER(Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                                DAT_WildlifeState::ptr)(tribeID, 2, 1);
                        }
                        if (0 < this->tribes[tribeID].rallyPointCount) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::standUpAllTribeUnits, this)(tribeID);
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::applyLadderDestructionToTribeUnits, this)(
                                tribeID);
                        }
                    } else if (sVar2 == 0x96) {
                        sVar2 = this->tribes[tribeID].rallyPointCount;
                        if (0 < sVar2) {
                            MACRO_CALL_MEMBER(
                                Map::Units::TribesState_Func::giveUnitSelectionMoveInstructionNoMatchedSpeed, this)(
                                tribeID, (uint)((int)((int)this->tribes[tribeID].rallyPointArray[sVar2 + -1][0])),
                                (uint)((int)((int)this->tribes[tribeID].rallyPointArray[sVar2 + -1][1])), 0, 0);
                        }
                    } else if (BVar7) {
                        this->tribes[tribeID].tribeBehaviorType = Map::Units::STBT_1;
                        this->tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                    }
                } else if (SVar3 == Map::Units::STBT_1) {
                    if (!iVar6) {
                        if (iVar5 < 0x15) {
                            this->tribes[tribeID].wanderIntervalTicks = 400;
                        } else {
                            this->tribes[tribeID].wanderIntervalTicks = 0x14;
                        }
                    } else {
                        this->tribes[tribeID].wanderIntervalTicks = 0x14;
                    }
                    psVar1 = (short*)&this->tribes[tribeID].unknownAttackRelatedUpdateCounter;
                    *psVar1 = *psVar1 + 1;
                    if (this->tribes[tribeID].wanderIntervalTicks
                        <= this->tribes[tribeID].unknownAttackRelatedUpdateCounter) {
                        this->tribes[tribeID].tribeBehaviorType = ((SomeTribeBehaviorType)0);
                        this->tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                    }
                }
            } else {
                if (sVar2 == 1) {
                    MACRO_CALL_MEMBER(Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                        DAT_WildlifeState::ptr)(tribeID, 3, 0);
                    if (this->tribes[tribeID].rallyPointCount < 1) {
                        MACRO_CALL_MEMBER(Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                            DAT_WildlifeState::ptr)(tribeID, 3, 1);
                    }
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::standUpAllTribeUnits, this)(tribeID);
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::scatterTribeUnitsRandomly, this)(tribeID);
                }
                psVar1 = (short*)&this->tribes[tribeID].predatorNearby;
                *psVar1 = *psVar1 + 1;
                if (2999 < this->tribes[tribeID].predatorNearby) {
                    this->tribes[tribeID].predatorNearby = 0;
                }
            }
        }

    }
}
}
