#include "../ChooseRandomNumberOfEnemies.func.hpp"

#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/Actions.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004B18D0
        void ChooseRandomNumberOfEnemies::MenuItemActionHandler_ChooseRandomNumberOfEnemies_Main(int param_1, ...)
        {
            int iVar1;
            int* piVar2;
            MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
            if (0 < param_1) {
                iVar1 = 2;
                do {
                    DAT_GameSynchronyState::instance.currentAIArray[iVar1] = 0;
                    DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[iVar1] = 0;
                    MACRO_CALL(OpenSHC::Synchrony::Actions_Func::RemovePositionOfPlayer)(iVar1);
                    iVar1 = iVar1 + 1;
                } while (iVar1 < 9);
                if (0 < param_1) {
                    piVar2 = DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue + 2;
                    iVar1 = 2;
                    do {
                        piVar2[-0x419a7]
                            = DAT_GameCore::instance.arrayOfLordIdsWithAIVsUnk[(int)SEC_RNG::instance.currentNumber2
                                % DAT_GameCore::instance.numOfAIsWithCastleUnk];
                        MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
                        MACRO_CALL(OpenSHC::Synchrony_Func::ResetAiVariationArrayValue)(iVar1);
                        *piVar2 = 1;
                        MACRO_CALL(OpenSHC::Synchrony_Func::PutPlayerIntoRandomSlot)(iVar1);
                        piVar2 = piVar2 + 1;
                        iVar1 = iVar1 + 1;
                        param_1 = param_1 + -1;
                    } while (param_1 != 0);
                }
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions,
                    DAT_GameSynchronyState::ptr)();
                DAT_GameSynchronyState::instance.reparseMaps = TRUE;
            }
        }

    }
}
}
