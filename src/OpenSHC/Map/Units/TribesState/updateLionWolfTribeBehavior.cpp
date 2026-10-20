#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/WildlifeState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
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

        // FUNCTION: STRONGHOLDCRUSADER 0x0052B110
        void TribesState::updateLionWolfTribeBehavior(int param_1)
        {
            short* psVar1;
            int sVar2;
            SomeTribeBehaviorTypeShort SVar3;
            int sVar4;
            BOOLEnum BVar5;
            BOOLEnum BVar6;
            BVar5 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::isTribeFreeOfTunnelingUnits, this)(
                param_1, this->tribes[param_1].uid);
            this->tribes[param_1].unknownCounter01 = this->tribes[param_1].unknownCounter01 + 1;
            sVar2 = this->tribes[param_1].unknownCounter01;
            this->tribes[param_1].unkIsAnimalTribe = 1;
            if (8000 <= sVar2) {
                this->tribes[param_1].unknownCounter01 = 4000;
            }
            sVar2 = this->tribes[param_1].countdown;
            if (!sVar2) {
                if ((BVar5)
                    && (BVar6 = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::spawnDeerLionOrRabbit, this)(
                            param_1, 500, Map::Units::UT_LIONSHWOLF),
                        BVar6)) {
                    this->tribes[param_1].initialMoveOrderGiven = 1;
                    this->tribes[param_1].unknownAttackRelatedUpdateCounter = 0;
                }
                sVar2 = this->tribes[param_1].initialMoveOrderGiven;
                if (!sVar2) {
                    sVar2 = this->tribes[param_1].selectionTargetUnitID;
                    this->tribes[param_1].unknownAttackRelatedUpdateCounter = 0;
                    this->tribes[param_1].initialMoveOrderGiven = 2;
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(param_1,
                        (uint)(DAT_UnitsState::instance.units[sVar2].x),
                        (uint)(DAT_UnitsState::instance.units[sVar2].y), 0, 0, Map::Units::Instructions::UMSE_0);
                    this->tribes[param_1].tribeBehaviorType = Map::Units::STBT_1;
                }
                if (sVar2 == 1) {
                    this->tribes[param_1].unknownAttackRelatedUpdateCounter = 0;
                    this->tribes[param_1].initialMoveOrderGiven = 2;
                    MACRO_CALL_MEMBER(Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                        DAT_WildlifeState::ptr)(param_1, 2, 0);
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::standUpAllTribeUnits, this)(param_1);
                    sVar2 = this->tribes[param_1].currentRallyPointIndex;
                    MACRO_CALL_MEMBER(Map::Units::TribesState_Func::giveTribeMoveInstruction, this)(param_1,
                        (uint)((int)this->tribes[param_1].rallyPointArray[sVar2][0]),
                        (uint)((int)this->tribes[param_1].rallyPointArray[sVar2][1]), 0, 0,
                        Map::Units::Instructions::UMSE_0);
                    this->tribes[param_1].currentRallyPointIndex = this->tribes[param_1].currentRallyPointIndex + 1;
                    if (this->tribes[param_1].rallyPointCount <= this->tribes[param_1].currentRallyPointIndex) {
                        this->tribes[param_1].rallyPointCount = 0;
                        this->tribes[param_1].tribeBehaviorType = Map::Units::STBT_1;
                    }
                    this->tribes[param_1].tribeBehaviorType = Map::Units::STBT_1;
                }
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                    this->tribes[param_1].unknownCounter01 = 0;
                }
                SVar3 = this->tribes[param_1].tribeBehaviorType;
                if (SVar3 == (SomeTribeBehaviorType)0) {
                    sVar4 = this->tribes[param_1].unknownAttackRelatedUpdateCounter;
                    sVar2 = sVar4 + 1;
                    this->tribes[param_1].unknownAttackRelatedUpdateCounter = sVar2;
                    if (!sVar4) {
                        MACRO_CALL_MEMBER(Map::WildlifeState_Func::findAndSetNewRallyPointForDeerAndLions,
                            DAT_WildlifeState::ptr)(param_1, 2, 0);
                        if (0 < this->tribes[param_1].rallyPointCount) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::standUpAllTribeUnits, this)(param_1);
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::applyLadderDestructionToTribeUnits, this)(
                                param_1);
                        }
                    } else if (sVar2 == 0x96) {
                        if ((this->tribes[param_1].unknownBool02 == 0)
                            && (sVar2 = (ushort)this->tribes[param_1].rallyPointCount, 0 < sVar2)) {
                            MACRO_CALL_MEMBER(
                                Map::Units::TribesState_Func::giveUnitSelectionMoveInstructionNoMatchedSpeed, this)(
                                param_1, (uint)((int)this->tribes[param_1].rallyPointArray[sVar2 + -1][0]),
                                (uint)((int)this->tribes[param_1].rallyPointArray[sVar2 + -1][1]), 0, 0);
                        }
                    } else if (BVar5) {
                        this->tribes[param_1].tribeBehaviorType = Map::Units::STBT_1;
                        this->tribes[param_1].unknownAttackRelatedUpdateCounter = 0;
                    }
                } else if ((SVar3 == Map::Units::STBT_1)
                    && (psVar1 = (short*)&this->tribes[param_1].unknownAttackRelatedUpdateCounter,
                        *psVar1 = *psVar1 + 1, this->tribes[param_1].unknownAttackRelatedUpdateCounter == 300)) {
                    this->tribes[param_1].tribeBehaviorType = ((SomeTribeBehaviorType)0);
                    this->tribes[param_1].unknownAttackRelatedUpdateCounter = 0;
                }
            } else if (sVar2 == 100) {
                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::setStateForAllTribeUnits, this)(param_1, 0xd0);
                this->tribes[param_1].unknownBool01 = 1;
            }
        }

    }
}
}
