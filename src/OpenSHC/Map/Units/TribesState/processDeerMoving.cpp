#include "../../../Map.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_WildlifeState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using DE::SHCDE::eSFX;
        using Map::Units::SomeTribeBehaviorType;
        using Map::Units::UnitType;
        using Map::Units::Instructions::UnitMatchSpeedEnum;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0052AD50
        void TribesState::processDeerMoving(int tribeID)
        {
            short* psVar1;
            int sVar2;
            SomeTribeBehaviorTypeShort SVar3;
            int iVar4;
            int iVar5;
            int iVar6;
            BOOLEnum BVar7;
            int iVar8;
            int _x10;
            int _y10;
            sVar2 = this->tribes[tribeID].selectionTargetUnitID;
            _x10 = (int)DAT_UnitsState::instance.units[sVar2].x / 10;
            _y10 = (int)DAT_UnitsState::instance.units[sVar2].y / 10;
            iVar8 = DAT_WildlifeState::instance.grid[_x10][_y10].rockyTiles;
            iVar4 = DAT_WildlifeState::instance.grid[_x10][_y10].lionCount;
            iVar5 = DAT_WildlifeState::instance.grid[_x10][_y10].marshTiles;
            iVar6 = DAT_WildlifeState::instance.grid[_x10][_y10].field18_0x48;
            sVar2 = this->tribes[tribeID].size;
            this->tribes[tribeID].unkIsAnimalTribe = 1;
            if (sVar2 < 0x1f) {
                this->tribes[tribeID].herdMinSize = sVar2 / 2;
                this->tribes[tribeID].herdMaxSize = sVar2 * 2;
            } else {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::trimTribeToSize, this)(
                    tribeID, (int)((int)(30)));
                this->tribes[tribeID].herdMinSize = 0xf;
                this->tribes[tribeID].herdMaxSize = 0x3c;
            }
            if ((iVar4 + iVar6 != 0) && (this->tribes[tribeID].predatorNearby == 0)) {
                this->tribes[tribeID].predatorNearby = 1;
            }
            BVar7 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::spawnDeerLionOrRabbit, this)(
                tribeID, 100, Map::Units::UT_ANTELOPESHDEER);
            if (!BVar7) {
                if (this->tribes[tribeID].initialMoveOrderGiven == 0) {
                    sVar2 = this->tribes[tribeID].selectionTargetUnitID;
                    this->tribes[tribeID].initialMoveOrderGiven = 1;
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(tribeID,
                        (uint)((int)((int)DAT_UnitsState::instance.units[sVar2].x)),
                        (uint)((int)((int)DAT_UnitsState::instance.units[sVar2].y)), 0, 0,
                        Map::Units::Instructions::UMSE_0);
                    this->tribes[tribeID].tribeBehaviorType = Map::Units::STBT_1;
                }
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                    this->tribes[tribeID].unknownCounter01 = 0;
                }
                sVar2 = this->tribes[tribeID].predatorNearby;
                if (!sVar2) {
                    SVar3 = this->tribes[tribeID].tribeBehaviorType;
                    if (SVar3 == ((SomeTribeBehaviorType)0)) {
                        if (iVar5) {
                            this->tribes[tribeID].wanderIntervalTicks = 200;
                        }
                        if (0x14 < iVar8) {
                            this->tribes[tribeID].wanderIntervalTicks = 200;
                        }
                        this->tribes[tribeID].unknownAttackRelatedUpdateCounter
                            = this->tribes[tribeID].unknownAttackRelatedUpdateCounter + 1;
                        if (this->tribes[tribeID].wanderIntervalTicks
                            <= this->tribes[tribeID].unknownAttackRelatedUpdateCounter) {
                            this->tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                            sVar2 = this->tribes[tribeID].rallyPointCount;
                            this->tribes[tribeID].wanderIntervalTicks
                                = (4 - ((byte)SEC_RNG::instance.currentNumber2 & 3)) * 200;
                            if (sVar2 < 1) {
                                MACRO_CALL_MEMBER(
                                    Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                                    DAT_WildlifeState::ptr)(tribeID, 5, 0);
                            }
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::standUpAllTribeUnits, this)(
                                tribeID);
                            sVar2 = this->tribes[tribeID].currentRallyPointIndex;
                            MACRO_CALL_MEMBER(
                                Map::Units::TribesState_Func::giveUnitSelectionMoveInstructionNoMatchedSpeed,
                                this)(tribeID, (uint)((int)((int)this->tribes[tribeID].rallyPointArray[sVar2][0])),
                                (uint)((int)((int)this->tribes[tribeID].rallyPointArray[sVar2][1])), 0, 0);
                            this->tribes[tribeID].currentRallyPointIndex
                                = this->tribes[tribeID].currentRallyPointIndex + 1;
                            if (this->tribes[tribeID].rallyPointCount <= this->tribes[tribeID].currentRallyPointIndex) {
                                this->tribes[tribeID].tribeBehaviorType = Map::Units::STBT_1;
                                this->tribes[tribeID].rallyPointCount = 0;
                            }
                        }
                    } else if ((SVar3 == Map::Units::STBT_1)
                        && (psVar1 = &this->tribes[tribeID].unknownAttackRelatedUpdateCounter, *psVar1 = *psVar1 + 1,
                            this->tribes[tribeID].unknownAttackRelatedUpdateCounter == 800)) {
                        this->tribes[tribeID].unknownAttackRelatedUpdateCounter = 0;
                        this->tribes[tribeID].tribeBehaviorType = ((SomeTribeBehaviorType)0);
                    }
                } else {
                    if (sVar2 == 1) {
                        MACRO_CALL_MEMBER(Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                            DAT_WildlifeState::ptr)(tribeID, 5, 0);
                        if ((this->tribes[tribeID].rallyPointCount < 1)
                            && (MACRO_CALL_MEMBER(
                                    Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                                    DAT_WildlifeState::ptr)(tribeID, 5, 1),
                                this->tribes[tribeID].rallyPointCount < 1)) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::scatterTribeUnitsRandomly, this)(
                                tribeID);
                        } else {
                            sVar2 = this->tribes[tribeID].selectionTargetUnitID;
                            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                                (int)DAT_UnitsState::instance.units[sVar2].x,
                                (int)((int)(DAT_UnitsState::instance.units[sVar2].y)), DE::SHCDE::FX_DEER_RUN);
                            iVar8 = (int)this->tribes[tribeID].rallyPointCount;
                            MACRO_CALL_MEMBER(
                                Map::Units::TribesState_Func::giveUnitSelectionMoveInstructionNoMatchedSpeed,
                                this)(tribeID, (uint)((int)((int)this->tribes[tribeID].rallyPointArray[iVar8 + -1][0])),
                                (uint)((int)((int)this->tribes[tribeID].rallyPointArray[iVar8 + -1][1])), 0, 0);
                        }
                    }
                    this->tribes[tribeID].predatorNearby = this->tribes[tribeID].predatorNearby + 1;
                    if (799 < this->tribes[tribeID].predatorNearby) {
                        this->tribes[tribeID].predatorNearby = 0;
                    }
                }
            } else {
                MACRO_CALL_MEMBER(Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                    DAT_WildlifeState::ptr)(tribeID, 2, 0);
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::standUpAllTribeUnits, this)(tribeID);
                sVar2 = this->tribes[tribeID].currentRallyPointIndex;
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(tribeID,
                    (uint)((int)((int)this->tribes[tribeID].rallyPointArray[sVar2][0])),
                    (uint)((int)((int)this->tribes[tribeID].rallyPointArray[sVar2][1])), 0, 0,
                    Map::Units::Instructions::UMSE_0);
                this->tribes[tribeID].currentRallyPointIndex = this->tribes[tribeID].currentRallyPointIndex + 1;
                if (this->tribes[tribeID].rallyPointCount <= this->tribes[tribeID].currentRallyPointIndex) {
                    this->tribes[tribeID].rallyPointCount = 0;
                    this->tribes[tribeID].tribeBehaviorType = Map::Units::STBT_1;
                }
            }
        }

    }
}
}
