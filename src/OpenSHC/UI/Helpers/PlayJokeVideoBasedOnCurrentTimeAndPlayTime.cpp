#include "../Helpers.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/GreatestLord.func.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/UI/Enums/JokeAIMessageIndex.hpp"

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
        // A function-local static (the last check's time) with its initialisation guard bit.
        if (!(BOOLEnum_02427470::instance & TRUE)) {
            BOOLEnum_02427470::instance |= TRUE;
            DWORD_0242746c::instance = timeGetTime();
        }
        if (!MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()
            || DAT_GameSynchronyState::instance.currentGameMode == Game::GM_SOLITARY
            || TIME_ReceivedMessage_1::instance != 0) {
            return;
        }
        DWORD const now = timeGetTime();
        if (now - DWORD_0242746c::instance < 10 * 1000) {
            return;
        }
        DWORD_0242746c::instance = now;
        __time64_t currentTime;
        MACRO_CALL(OS_Func::__time64)(&currentTime);
        tm* const localTime = MACRO_CALL(OS_Func::_localtime)(&currentTime);
        if (!FLAG_JokeAIMessageArray::instance[Enums::JAMI_CHRISTMAS_RAT_SNAKE_PIG_WOLF] && localTime->tm_mon == 11
            && localTime->tm_mday == 25) {
            // Christmas day
            for (int aiType = AI::AITA_WOLF; aiType > AI::AITA_NULL; --aiType) {
                if (MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(aiType)) {
                    MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                        DAT_GameSynchronyState::instance.currentPlayerSlotID, aiType);
                    FLAG_JokeAIMessageArray::instance[Enums::JAMI_CHRISTMAS_RAT_SNAKE_PIG_WOLF] = TRUE;
                    break;
                }
            }
        }
        // The rest depends on how long the game has been running.
        if (!FLAG_JokeAIMessageArray::instance[Enums::JAMI_ABBOT]
            && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(AI::AITA_ABBOT)
            && now - TIME_Sum_1::instance > 24 * 60 * 60 * 1000) {
            MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, AI::AITA_ABBOT);
            FLAG_JokeAIMessageArray::instance[Enums::JAMI_ABBOT] = TRUE;
        }
        if (!FLAG_JokeAIMessageArray::instance[Enums::JAMI_CALIPH]
            && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(AI::AITA_CALIPH)
            && now - TIME_Sum_1::instance > 3 * 60 * 60 * 1000
            && MACRO_CALL(UI::GreatestLord_Func::IfAiGreatestLordGetAiType)() == AI::AITA_CALIPH) {
            MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, AI::AITA_CALIPH);
            FLAG_JokeAIMessageArray::instance[Enums::JAMI_CALIPH] = TRUE;
        }
        if (!FLAG_JokeAIMessageArray::instance[Enums::JAMI_EMIR]
            && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(AI::AITA_EMIR)
            && now - TIME_Sum_1::instance > 5 * 60 * 60 * 1000) {
            MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, AI::AITA_EMIR);
            FLAG_JokeAIMessageArray::instance[Enums::JAMI_EMIR] = TRUE;
        }
        if (!FLAG_JokeAIMessageArray::instance[Enums::JAMI_FREDERICK]
            && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(AI::AITA_FREDERICK)
            && now - TIME_Sum_1::instance > 2 * 60 * 60 * 1000 && localTime->tm_hour == 2 && localTime->tm_min == 0) {
            MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, AI::AITA_FREDERICK);
            FLAG_JokeAIMessageArray::instance[Enums::JAMI_FREDERICK] = TRUE;
        }
        if (!FLAG_JokeAIMessageArray::instance[Enums::JAMI_MARSHAL]
            && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(AI::AITA_MARSHAL)
            && now - TIME_Sum_1::instance > 4 * 60 * 60 * 1000) {
            MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, AI::AITA_MARSHAL);
            FLAG_JokeAIMessageArray::instance[Enums::JAMI_MARSHAL] = TRUE;
        }
        if (!FLAG_JokeAIMessageArray::instance[Enums::JAMI_NIZAR]
            && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(AI::AITA_NIZAR)
            && now - TIME_Sum_1::instance > 2 * 60 * 60 * 1000 && localTime->tm_hour == 3 && localTime->tm_min == 0) {
            MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, AI::AITA_NIZAR);
            FLAG_JokeAIMessageArray::instance[Enums::JAMI_NIZAR] = TRUE;
        }
        if (!FLAG_JokeAIMessageArray::instance[Enums::JAMI_PHILIPP]
            && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(AI::AITA_PHILIPP)
            && now - TIME_Sum_1::instance > 2 * 60 * 60 * 1000 && localTime->tm_hour == 0 && localTime->tm_min == 0) {
            MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, AI::AITA_PHILIPP);
            FLAG_JokeAIMessageArray::instance[Enums::JAMI_PHILIPP] = TRUE;
        }
        if (!FLAG_JokeAIMessageArray::instance[Enums::JAMI_RICHARD]
            && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(AI::AITA_RICHARD)
            && now - TIME_Sum_1::instance > 2 * 60 * 60 * 1000 && localTime->tm_hour == 4 && localTime->tm_min == 0) {
            MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, AI::AITA_RICHARD);
            FLAG_JokeAIMessageArray::instance[Enums::JAMI_RICHARD] = TRUE;
        }
        if (!FLAG_JokeAIMessageArray::instance[Enums::JAMI_SALADIN]
            && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(AI::AITA_SALADIN)
            && now - TIME_Sum_1::instance > 2 * 60 * 60 * 1000 && localTime->tm_hour == 5 && localTime->tm_min == 0) {
            MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, AI::AITA_SALADIN);
            FLAG_JokeAIMessageArray::instance[Enums::JAMI_SALADIN] = TRUE;
        }
        if (!FLAG_JokeAIMessageArray::instance[Enums::JAMI_SHERIFF]
            && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(AI::AITA_SHERIFF)
            && now - TIME_Sum_1::instance > 200 * 60 * 1000
            && MACRO_CALL(UI::GreatestLord_Func::IfAiGreatestLordGetAiType)() == AI::AITA_SHERIFF) {
            MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, AI::AITA_SHERIFF);
            FLAG_JokeAIMessageArray::instance[Enums::JAMI_SHERIFF] = TRUE;
        }
        if (!FLAG_JokeAIMessageArray::instance[Enums::JAMI_SULTAN]
            && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(AI::AITA_SULTAN)
            && now - TIME_Sum_1::instance > 2 * 60 * 60 * 1000 && localTime->tm_hour == 1 && localTime->tm_min == 0) {
            MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, AI::AITA_SULTAN);
            FLAG_JokeAIMessageArray::instance[Enums::JAMI_SULTAN] = TRUE;
        }
        if (!FLAG_JokeAIMessageArray::instance[Enums::JAMI_WAZIR]
            && MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(AI::AITA_WAZIR)
            && now - TIME_Sum_1::instance > 210 * 60 * 1000
            && MACRO_CALL(UI::GreatestLord_Func::IfAiGreatestLordGetAiType)() == AI::AITA_WAZIR) {
            MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID, AI::AITA_WAZIR);
            FLAG_JokeAIMessageArray::instance[Enums::JAMI_WAZIR] = TRUE;
        }
    }

}
}
