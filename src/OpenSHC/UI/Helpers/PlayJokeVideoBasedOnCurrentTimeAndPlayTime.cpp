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
#include "OpenSHC/Globals/FLAG_ChristmasAIMessage01to04.hpp"
#include "OpenSHC/Globals/FLAG_JokeAIMessage05.hpp"
#include "OpenSHC/Globals/FLAG_JokeAIMessage06.hpp"
#include "OpenSHC/Globals/FLAG_JokeAIMessage09.hpp"
#include "OpenSHC/Globals/FLAG_JokeAIMessage12.hpp"
#include "OpenSHC/Globals/FLAG_JokeAIMessage16.hpp"
#include "OpenSHC/Globals/INT_00ee236c.hpp"
#include "OpenSHC/Globals/INT_00ee2370.hpp"
#include "OpenSHC/Globals/INT_00ee2378.hpp"
#include "OpenSHC/Globals/INT_00ee237c.hpp"
#include "OpenSHC/Globals/INT_00ee2384.hpp"
#include "OpenSHC/Globals/INT_00ee2388.hpp"
#include "OpenSHC/Globals/INT_00ee238c.hpp"
#include "OpenSHC/Globals/TIME_ReceivedMessage_1.hpp"
#include "OpenSHC/Globals/TIME_Sum_1.hpp"

namespace OpenSHC {
namespace UI {

    using Game::GameMode;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0057B9C0
    void Helpers::PlayJokeVideoBasedOnCurrentTimeAndPlayTime()
    {
        DWORD _now;
        tm* _localtime64;
        int iVar2;
        __time64_t _time64;
        if (!(BOOLEnum_02427470::instance & TRUE)) {
            BOOLEnum_02427470::instance = BOOLEnum_02427470::instance | TRUE;
            DWORD_0242746c::instance = timeGetTime();
        }
        BOOLEnum BVar1 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
        if (BVar1 && DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY
            && !TIME_ReceivedMessage_1::instance && (_now = timeGetTime(), 9999 < _now - DWORD_0242746c::instance)) {
            DWORD_0242746c::instance = _now;
            MACRO_CALL(OS_Func::__time64)(&_time64);
            _localtime64 = MACRO_CALL(OS_Func::_localtime)(&_time64);
            if (!FLAG_ChristmasAIMessage01to04::instance && _localtime64->tm_mon == 11 && _localtime64->tm_mday == 25) {
                /*
                  is christmas day
                 */
                iVar2 = 4;
                do {
                    BVar1 = MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(iVar2);
                    if (BVar1) {
                        MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                            DAT_GameSynchronyState::instance.currentPlayerSlotID, iVar2);
                        FLAG_ChristmasAIMessage01to04::instance = TRUE;
                        break;
                    }
                    iVar2 = iVar2 + -1;
                } while (0 < iVar2);
            }
            /*
              From here on it is all based on play time length
             */
            if (!FLAG_JokeAIMessage16::instance
                && (BVar1 = MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(16), BVar1)
                && 86400000 < _now - TIME_Sum_1::instance) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, (int)(16));
                FLAG_JokeAIMessage16::instance = TRUE;
            }
            if (!FLAG_JokeAIMessage06::instance
                && (BVar1 = MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(6), BVar1)
                && 10800000 < _now - TIME_Sum_1::instance
                && (iVar2 = MACRO_CALL(UI::GreatestLord_Func::IfAiGreatestLordGetAiType)(), iVar2 == 6)) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 6);
                FLAG_JokeAIMessage06::instance = TRUE;
            }
            if (!FLAG_JokeAIMessage12::instance
                && (BVar1 = MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(0xc), BVar1)
                && 18000000 < _now - TIME_Sum_1::instance) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 0xc);
                FLAG_JokeAIMessage12::instance = TRUE;
            }
            if (!FLAG_JokeAIMessage09::instance
                && (BVar1 = MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(9), BVar1)
                && 7200000 < _now - TIME_Sum_1::instance && _localtime64->tm_hour == 2 && !_localtime64->tm_min) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 9);
                FLAG_JokeAIMessage09::instance = TRUE;
            }
            if (!INT_00ee238c::instance
                && (BVar1 = MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(0xf), BVar1)
                && 14400000 < _now - TIME_Sum_1::instance) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 0xf);
                INT_00ee238c::instance = 1;
            }
            if (!INT_00ee2384::instance
                && (BVar1 = MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(0xd), BVar1)
                && 7200000 < _now - TIME_Sum_1::instance && _localtime64->tm_hour == 3 && !_localtime64->tm_min) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 0xd);
                INT_00ee2384::instance = 1;
            }
            if (!INT_00ee2378::instance
                && (BVar1 = MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(10), BVar1)
                && 7200000 < _now - TIME_Sum_1::instance && !_localtime64->tm_hour && !_localtime64->tm_min) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 10);
                INT_00ee2378::instance = 1;
            }
            if (!INT_00ee2370::instance
                && (BVar1 = MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(8), BVar1)
                && 7200000 < _now - TIME_Sum_1::instance && _localtime64->tm_hour == 4 && !_localtime64->tm_min) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 8);
                INT_00ee2370::instance = 1;
            }
            if (!FLAG_JokeAIMessage05::instance
                && (BVar1 = MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(5), BVar1)
                && 7200000 < _now - TIME_Sum_1::instance && _localtime64->tm_hour == 5 && !_localtime64->tm_min) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 5);
                FLAG_JokeAIMessage05::instance = TRUE;
            }
            if (!INT_00ee2388::instance
                && (BVar1 = MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(0xe), BVar1)
                && 12000000 < _now - TIME_Sum_1::instance
                && (iVar2 = MACRO_CALL(UI::GreatestLord_Func::IfAiGreatestLordGetAiType)(), iVar2 == 0xe)) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 0xe);
                INT_00ee2388::instance = 1;
            }
            if (!INT_00ee236c::instance
                && (BVar1 = MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(7), BVar1)
                && 7200000 < _now - TIME_Sum_1::instance && _localtime64->tm_hour == 1 && !_localtime64->tm_min) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 7);
                INT_00ee236c::instance = 1;
            }
            if (!INT_00ee237c::instance
                && (BVar1 = MACRO_CALL_MEMBER(AI::AICState_Func::aiOfTypeInCurrentGame, DAT_AICState::ptr)(0xb), BVar1)
                && 12600000 < _now - TIME_Sum_1::instance
                && (iVar2 = MACRO_CALL(UI::GreatestLord_Func::IfAiGreatestLordGetAiType)(), iVar2 == 0xb)) {
                MACRO_CALL_MEMBER(AI::AICState_Func::playJokeBikFromAIToHuman, DAT_AICState::ptr)(
                    DAT_GameSynchronyState::instance.currentPlayerSlotID, 0xb);
                INT_00ee237c::instance = 1;
            }
        }
    }

}
}
