#include "../ChooseRandomNumberOfEnemies.func.hpp"

#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/Actions.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004B18D0
        void ChooseRandomNumberOfEnemies::MenuItemActionHandler_ChooseRandomNumberOfEnemies_Main(int enemyCount, ...)
        {
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            if (enemyCount < 1) {
                return;
            }
            for (int slot = 2; slot < 9; ++slot) {
                DAT_GameSynchronyState::instance.currentAIArray[slot] = 0;
                DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[slot] = 0;
                MACRO_CALL(OpenSHC::Synchrony::Actions_Func::RemovePositionOfPlayer)(slot);
            }
            // i from 1 with slot = i + 1 gives the original's cmp 1 / jl guard (0x004B191F)
            for (int i = 1; i <= enemyCount; ++i) {
                int const slot = i + 1;
                DAT_GameSynchronyState::instance.currentAIArray[slot]
                    = DAT_GameCore::instance.arrayOfLordIdsWithAIVsUnk[SEC_RNG::instance.currentNumber2
                        % DAT_GameCore::instance.numOfAIsWithCastleUnk];
                MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                MACRO_CALL(OpenSHC::Synchrony_Func::ResetAiVariationArrayValue)(slot);
                DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[slot] = 1;
                MACRO_CALL(OpenSHC::Synchrony_Func::PutPlayerIntoRandomSlot)(slot);
            }
            MACRO_CALL_MEMBER(
                OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions, DAT_GameSynchronyState::ptr)();
            DAT_GameSynchronyState::instance.reparseMaps = TRUE;
        }

    }
}
}
