#include "../AICState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    using namespace OpenSHC::Map::Units;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CFCD0
    void AICState::aiCommandSiegeEngineTribes(int playerID)
    {
        int shieldTargetTribeIDs[3];
        shieldTargetTribeIDs[0] = 0;
        shieldTargetTribeIDs[1] = 0;
        shieldTargetTribeIDs[2] = 0;
        int targetCount = 0;
        for (int i = 0; i < 3; i++) {
            int tribeID = DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[186 + i];
            if (tribeID == 0)
                continue;
            if (DAT_TribesState::instance.tribes[tribeID].uid
                != DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[186 + i])
                continue;
            shieldTargetTribeIDs[targetCount] = tribeID;
            targetCount++;
        }

        int shieldCount = 0;
        for (int unitID = 1; unitID < 2500; unitID++) {
            if (DAT_UnitsState::instance.units[unitID].logicalState == ULS_INVISIBLE)
                continue;
            if (DAT_UnitsState::instance.units[unitID].unitType != UT_S_TOWER
                && DAT_UnitsState::instance.units[unitID].unitType != UT_S_BATTERINGRAM
                && DAT_UnitsState::instance.units[unitID].unitType != UT_S_SHIELD)
                continue;
            if (DAT_UnitsState::instance.units[unitID].unknownSiegeTentRelated02 != 3)
                continue;
            if (DAT_UnitsState::instance.units[unitID].aiUnitBehaviourType == 21)
                continue;

            int tribeID = DAT_UnitsState::instance.units[unitID].tribeID;
            if (tribeID == 0)
                continue;

            if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_TOWER) {
                if (*(int*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray + playerID * 0x177bc - 4)
                    != 0)
                    MACRO_CALL_MEMBER(TribesState_Func::assignAttackTargetsForTribe, DAT_TribesState::ptr)(
                        tribeID, STBT_0x414);
            } else if (DAT_UnitsState::instance.units[unitID].unitType == UT_S_BATTERINGRAM) {
                if (*(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + playerID * 0x177bc - 4)
                    != 0)
                    MACRO_CALL_MEMBER(TribesState_Func::assignAttackTargetsForTribe, DAT_TribesState::ptr)(
                        tribeID, STBT_0x3f6);
                else if (*(int*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray + playerID * 0x177bc - 4)
                    != 0)
                    MACRO_CALL_MEMBER(TribesState_Func::assignAttackTargetsForTribe, DAT_TribesState::ptr)(
                        tribeID, STBT_0x413);
            } else {
                if (shieldCount >= 3)
                    continue;

                int targetTribeID = shieldTargetTribeIDs[shieldCount];
                DAT_TribesState::instance.tribes[tribeID].field56_0x1f2 = targetTribeID;
                DAT_TribesState::instance.tribes[tribeID].uid2 = DAT_TribesState::instance.tribes[targetTribeID].uid;
                int targetUnitID = DAT_TribesState::instance.tribes[targetTribeID].selectionTargetUnitID;
                DAT_TribesState::instance.tribes[targetTribeID].tribeID = tribeID;
                int tile = DAT_UnitsState::instance.units[targetUnitID].tile;
                shieldCount++;
                if (tile <= 0)
                    continue;

                int y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile];
                int x = tile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
                MACRO_CALL_MEMBER(TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                    tribeID, x, y, 0, 0, Instructions::UMSE_0);
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::calculatePreferredRelativeOrientation,
                    DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[targetUnitID].x,
                    DAT_UnitsState::instance.units[targetUnitID].y, x, y);
                DAT_TribesState::instance.tribes[tribeID].orientation
                    = DAT_DirectionAlgorithmState::instance.orientation;
            }
        }
    }
}
}
