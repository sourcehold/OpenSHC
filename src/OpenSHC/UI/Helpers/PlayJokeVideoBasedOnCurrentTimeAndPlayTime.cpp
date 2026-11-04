#include "../Helpers.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/GreatestLord.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/BOOLEnum_02427470.hpp"
#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DWORD_0242746c.hpp"
#include "OpenSHC/Globals/FLAG_JokeAIMessageArray.hpp"
#include "OpenSHC/Globals/TIME_ReceivedMessage_1.hpp"
#include "OpenSHC/Globals/TIME_Sum_1.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x0057B9C0
    void Helpers::PlayJokeVideoBasedOnCurrentTimeAndPlayTime()
    {
        DWORD now;
        tm* localTime;
        __time64_t currentTime;
        // The original's function-local static (the last check's time) with its initialisation guard bit.
        if (!(BOOLEnum_02427470::instance & TRUE)) {
            BOOLEnum_02427470::instance |= TRUE;
            DWORD_0242746c::instance = timeGetTime();
        }
        if (MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()
            && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
            && !TIME_ReceivedMessage_1::instance && (now = timeGetTime(), now - DWORD_0242746c::instance >= 10000)) {
            DWORD_0242746c::instance = now;
            MACRO_CALL(OS_Func::__time64)(&currentTime);
            localTime = MACRO_CALL(OS_Func::_localtime)(&currentTime);
            if (!FLAG_JokeAIMessageArray::instance[1] && localTime->tm_mon == 11 && localTime->tm_mday == 25) {
                // Christmas day
                for (int aiType = 4; aiType > 0; --aiType) {
                    if (MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(aiType)) {
                        MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                            DAT_GameSynchronyState::instance.currentPlayerSlotID, aiType);
                        FLAG_JokeAIMessageArray::instance[1] = TRUE;
                        break;
                    }
                }
            }
            // The rest depends on how long the game has been running.
            if (!FLAG_JokeAIMessageArray::instance[16]
                && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(16)
                && 86400000 < now - TIME_Sum_1::instance) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 16);
                FLAG_JokeAIMessageArray::instance[16] = TRUE;
            }
            if (!FLAG_JokeAIMessageArray::instance[6]
                && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(6)
                && 10800000 < now - TIME_Sum_1::instance
                && MACRO_CALL(UI::GreatestLord_Func::IfAiGreatestLordGetAiType)() == 6) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 6);
                FLAG_JokeAIMessageArray::instance[6] = TRUE;
            }
            if (!FLAG_JokeAIMessageArray::instance[12]
                && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(12)
                && 18000000 < now - TIME_Sum_1::instance) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 12);
                FLAG_JokeAIMessageArray::instance[12] = TRUE;
            }
            if (!FLAG_JokeAIMessageArray::instance[9]
                && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(9)
                && 7200000 < now - TIME_Sum_1::instance && localTime->tm_hour == 2 && !localTime->tm_min) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 9);
                FLAG_JokeAIMessageArray::instance[9] = TRUE;
            }
            if (!FLAG_JokeAIMessageArray::instance[15]
                && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(15)
                && 14400000 < now - TIME_Sum_1::instance) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 15);
                FLAG_JokeAIMessageArray::instance[15] = TRUE;
            }
            if (!FLAG_JokeAIMessageArray::instance[13]
                && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(13)
                && 7200000 < now - TIME_Sum_1::instance && localTime->tm_hour == 3 && !localTime->tm_min) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 13);
                FLAG_JokeAIMessageArray::instance[13] = TRUE;
            }
            if (!FLAG_JokeAIMessageArray::instance[10]
                && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(10)
                && 7200000 < now - TIME_Sum_1::instance && !localTime->tm_hour && !localTime->tm_min) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 10);
                FLAG_JokeAIMessageArray::instance[10] = TRUE;
            }
            if (!FLAG_JokeAIMessageArray::instance[8]
                && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(8)
                && 7200000 < now - TIME_Sum_1::instance && localTime->tm_hour == 4 && !localTime->tm_min) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 8);
                FLAG_JokeAIMessageArray::instance[8] = TRUE;
            }
            if (!FLAG_JokeAIMessageArray::instance[5]
                && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(5)
                && 7200000 < now - TIME_Sum_1::instance && localTime->tm_hour == 5 && !localTime->tm_min) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 5);
                FLAG_JokeAIMessageArray::instance[5] = TRUE;
            }
            if (!FLAG_JokeAIMessageArray::instance[14]
                && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(14)
                && 12000000 < now - TIME_Sum_1::instance
                && MACRO_CALL(UI::GreatestLord_Func::IfAiGreatestLordGetAiType)() == 14) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 14);
                FLAG_JokeAIMessageArray::instance[14] = TRUE;
            }
            if (!FLAG_JokeAIMessageArray::instance[7]
                && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(7)
                && 7200000 < now - TIME_Sum_1::instance && localTime->tm_hour == 1 && !localTime->tm_min) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 7);
                FLAG_JokeAIMessageArray::instance[7] = TRUE;
            }
            if (!FLAG_JokeAIMessageArray::instance[11]
                && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(11)
                && 12600000 < now - TIME_Sum_1::instance
                && MACRO_CALL(UI::GreatestLord_Func::IfAiGreatestLordGetAiType)() == 11) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 11);
                FLAG_JokeAIMessageArray::instance[11] = TRUE;
            }
        }
    }

}
}
