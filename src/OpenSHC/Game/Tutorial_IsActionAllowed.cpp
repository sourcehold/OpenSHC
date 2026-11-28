#include "../Game.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00df5558.hpp"
#include "OpenSHC/Globals/DAT_00df5560.hpp"
#include "OpenSHC/Globals/DAT_00df5590.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TutorialCurrentStep.hpp"
#include "OpenSHC/Globals/INT_DisableTutorialRestrictions.hpp"

namespace OpenSHC {

using WindowsHelper::Enums::BOOLEnum;

// FUNCTION: STRONGHOLDCRUSADER 0x004BD800
BOOLEnum Game::Tutorial_IsActionAllowed(undefined4 actionType, int actionParam)
{
    int iVar1;
    bool bVar2;
    if (INT_DisableTutorialRestrictions::instance) {
        return TRUE;
    }
    switch (actionType) {
    case 1:
        if (DAT_TutorialCurrentStep::instance == 2) {
            if (1 < DAT_00df5558::instance) {
                return FALSE;
            }
            bVar2 = actionParam == 0x28;
        } else if (DAT_TutorialCurrentStep::instance == 5) {
            if (DAT_00df5558::instance) {
                return FALSE;
            }
            bVar2 = actionParam == 0x13;
        } else if (DAT_TutorialCurrentStep::instance == 0x11) {
            if (actionParam != 3) {
                return FALSE;
            }
            bVar2 = DAT_00df5560::instance == 0;
        } else {
            if (DAT_TutorialCurrentStep::instance != 0x15) {
                if (DAT_TutorialCurrentStep::instance != 0x18) {
                    return FALSE;
                }
                if (actionParam != 1) {
                    return FALSE;
                }
                return TRUE;
            }
            bVar2 = actionParam == 7;
        }
        if (bVar2) {
            return TRUE;
        }
        return FALSE;
    case 2:
        if (DAT_TutorialCurrentStep::instance == 2) {
            if ((DAT_00df5558::instance < 2) && (actionParam == 0x28)) {
                return TRUE;
            }
        } else if (DAT_TutorialCurrentStep::instance == 5) {
            if (((!DAT_00df5558::instance) && (actionParam == 0x13)) && (!DAT_00df5560::instance)) {
                return TRUE;
            }
        } else {
            if (DAT_TutorialCurrentStep::instance == 0x11) {
                bVar2 = actionParam == 3;
            } else {
                if (DAT_TutorialCurrentStep::instance != 0x15) {
                    if (DAT_TutorialCurrentStep::instance != 0x18) {
                        return FALSE;
                    }
                    if (actionParam != 1) {
                        return FALSE;
                    }
                    if (DAT_00df5560::instance) {
                        return FALSE;
                    }
                    return TRUE;
                }
                bVar2 = actionParam == 7;
            }
            if ((bVar2) && (DAT_00df5590::instance < 4)) {
                return TRUE;
            }
        }
        return FALSE;
    case 3:
        if (DAT_TutorialCurrentStep::instance != 8) {
            return FALSE;
        }
        iVar1 = 4;
        bVar2 = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                    .rationsSetting
            == 4;
        break;
    case 4:
        if (DAT_TutorialCurrentStep::instance != 10) {
            return FALSE;
        }
        iVar1 = 7;
        bVar2
            = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].taxesSetting
            == 7;
        break;
    default:
        goto switchD_004bd819_caseD_4;
    }
    if ((bVar2) && (actionParam != iVar1)) {
        return FALSE;
    }
switchD_004bd819_caseD_4:
    return TRUE;
}

}
