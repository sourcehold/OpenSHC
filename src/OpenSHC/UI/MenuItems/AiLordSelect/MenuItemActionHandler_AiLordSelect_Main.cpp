#include "../AiLordSelect.func.hpp"

#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LobbyAddAICurrentlyHoveredAI.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Commands::GameCommandType;
        using UI::Enums::MenuModalType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AE7D0
        void AiLordSelect::MenuItemActionHandler_AiLordSelect_Main(int param_1, ...)
        {
            int iVar1;
            if (param_1 == 100) {
                MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                DAT_MenuModalComposition1::instance.activeModalDialogID = UI::Enums::MMT_NONE;
            }
            if (param_1 <= DAT_GameCore::instance.numOfAIsWithCastleUnk) {
                DAT_LobbyAddAICurrentlyHoveredAI::instance
                    = DAT_GameCore::instance.arrayOfLordIdsWithAIVsUnk[param_1 + -1];
                iVar1 = 1;
                while (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[iVar1] != -1
                    || DAT_GameSynchronyState::instance.currentAIArray[iVar1] != 0) {
                    iVar1 = iVar1 + 1;
                    if (8 < iVar1) {
                        DAT_MenuModalComposition1::instance.activeModalDialogID = UI::Enums::MMT_NONE;
                    }
                }
                if (iVar1) {
                    DAT_GameSynchronyState::instance.currentAIArray[iVar1] = DAT_LobbyAddAICurrentlyHoveredAI::instance;
                    MACRO_CALL(Synchrony_Func::ResetAiVariationArrayValue)(iVar1);
                    DAT_GameSynchronyState::instance.DAT_PlayerSlotArraySomeValue[iVar1] = 1;
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0 = iVar1;
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                        (Commands::GameCommandType)(Commands::GCT_SEND_RESYNC_TILEMAPDATA2
                            | Commands::GCT_LOAD_MAP_HEADER));
                    DAT_GameSynchronyState::instance.reparseMaps = TRUE;
                    MACRO_CALL(UI::Helpers_Func::PlayAMessageFromAI)(
                        DAT_GameSynchronyState::instance.currentAIArray[iVar1], 0x16);
                    MACRO_CALL_MEMBER(
                        Synchrony::GameSynchronyState_Func::reorderTeamsAndPositions, DAT_GameSynchronyState::ptr)();
                    iVar1 = 0;
                    if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] != -1)
                        || (DAT_GameSynchronyState::instance.currentAIArray[1] != 0)) {
                        iVar1 = 1;
                    }
                    if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] != -1)
                        || (DAT_GameSynchronyState::instance.currentAIArray[2] != 0)) {
                        iVar1 = iVar1 + 1;
                    }
                    if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] != -1)
                        || (DAT_GameSynchronyState::instance.currentAIArray[3] != 0)) {
                        iVar1 = iVar1 + 1;
                    }
                    if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] != -1)
                        || (DAT_GameSynchronyState::instance.currentAIArray[4] != 0)) {
                        iVar1 = iVar1 + 1;
                    }
                    if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] != -1)
                        || (DAT_GameSynchronyState::instance.currentAIArray[5] != 0)) {
                        iVar1 = iVar1 + 1;
                    }
                    if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] != -1)
                        || (DAT_GameSynchronyState::instance.currentAIArray[6] != 0)) {
                        iVar1 = iVar1 + 1;
                    }
                    if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] != -1)
                        || (DAT_GameSynchronyState::instance.currentAIArray[7] != 0)) {
                        iVar1 = iVar1 + 1;
                    }
                    if ((DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] != -1)
                        || (DAT_GameSynchronyState::instance.currentAIArray[8] != 0)) {
                        iVar1 = iVar1 + 1;
                    }
                    if (iVar1 != 8) {}
                    MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                }
                DAT_MenuModalComposition1::instance.activeModalDialogID = UI::Enums::MMT_NONE;
            }
        }

    }
}
}
