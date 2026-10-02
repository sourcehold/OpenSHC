#include "../InGameMenu.func.hpp"

#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Game::GameMode2;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00433370
        void InGameMenu::MenuItemActionHandler_InGameMenu_ProcessScribeAnimationChange(int param_1, ...)
        {
            int iVar1;
            DWORD _currentTime;
            int iVar2;
            iVar1 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {}
            if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_SIEGE_THAT) {}
            if (DAT_GameCore::instance.taxesSettingUnk != 0) {
                _currentTime = timeGetTime();
                if ((int)(_currentTime - DAT_GameCore::instance.taxestimeUnk) < 0x3c) {}
                DAT_GameCore::instance.taxestimeUnk = _currentTime;
                if (DAT_GameCore::instance.unknownScribeRelatedFlag_0x130 == FALSE) {
                    if (DAT_GameCore::instance.scribeAnimationFrame < 6) {
                        DAT_GameCore::instance.scribeAnimationFrame = DAT_GameCore::instance.scribeAnimationFrame + 1;
                    } else if (DAT_GameCore::instance.scribeAnimationFrame < 7) {
                        DAT_GameCore::instance.unknownScribeRelatedFlag_0x130 = TRUE;
                    } else {
                        DAT_GameCore::instance.scribeAnimationFrame = DAT_GameCore::instance.scribeAnimationFrame + -1;
                    }
                } else if (DAT_GameCore::instance.unknownScribeRelatedFlag_0x130 == TRUE) {
                    DAT_GameCore::instance.scribeAnimationFrame2 = DAT_GameCore::instance.scribeAnimationFrame2 + 1;
                } else if (DAT_GameCore::instance.unknownScribeRelatedFlag_0x130 == 2) {
                    iVar2 = (100 - DAT_GameState::instance.playerDataArray[iVar1].popularity / 100) / 10 + 1;
                    if (DAT_GameCore::instance.scribeAnimationFrame < 0xc) {
                        if (iVar2 < DAT_GameCore::instance.scribeAnimationFrame) {
                            DAT_GameCore::instance.scribeAnimationFrame
                                = DAT_GameCore::instance.scribeAnimationFrame + -1;
                        } else if (DAT_GameCore::instance.scribeAnimationFrame < iVar2) {
                            DAT_GameCore::instance.scribeAnimationFrame
                                = DAT_GameCore::instance.scribeAnimationFrame + 1;
                        } else {
                            DAT_GameCore::instance.taxesSettingUnk = 0;
                        }
                    } else {
                        DAT_GameCore::instance.scribeAnimationFrame = 6;
                    }
                }
            }
            iVar2 = DAT_GameCore::instance.scribeAnimationFrame;
            switch (DAT_GameCore::instance.taxesSettingUnk) {
            case 0:
                iVar2 = (100 - DAT_GameState::instance.playerDataArray[iVar1].popularity / 100) / 10 + 1;
                goto switchD_00433499_caseD_4;
            case 1:
                if (DAT_GameCore::instance.unknownScribeRelatedFlag_0x130 != TRUE)
                    goto switchD_00433499_caseD_4;
                iVar2 = DAT_RenderingDefinedData::instance
                            .field1027_0x5493c[DAT_GameCore::instance.scribeAnimationFrame2];
                break;
            case 2:
                if (DAT_GameCore::instance.unknownScribeRelatedFlag_0x130 != TRUE)
                    goto switchD_00433499_caseD_4;
                iVar2 = DAT_RenderingDefinedData::instance
                            .field1028_0x5499c[DAT_GameCore::instance.scribeAnimationFrame2];
                break;
            case 3:
                if (DAT_GameCore::instance.unknownScribeRelatedFlag_0x130 != TRUE)
                    goto switchD_00433499_caseD_4;
                iVar2 = DAT_RenderingDefinedData::instance
                            .field1029_0x549fc[DAT_GameCore::instance.scribeAnimationFrame2];
                break;
            default:
                goto switchD_00433499_caseD_4;
            }
            if (iVar2 == 0) {
                DAT_GameCore::instance.taxesSettingUnk = 0;
                iVar2 = DAT_GameCore::instance.scribeAnimationFrame;
            }
        switchD_00433499_caseD_4:
            DAT_GameCore::instance.scribeAnimationFrame = iVar2;
            if ((DAT_GameCore::instance.scribeAnimationFrameCopy != DAT_GameCore::instance.scribeAnimationFrame)
                || (DAT_GameState::instance.mapAndTime.monthChanged != 0)) {
                DAT_GameCore::instance.countdown = 1;
                DAT_GameCore::instance.scribeAnimationFrameCopy = DAT_GameCore::instance.scribeAnimationFrame;
            }
        }

    }
}
}
