#include "../MissionEndscreen.func.hpp"

#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00eb9af8.hpp"
#include "OpenSHC/Globals/DAT_00ec082c.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_FinalResultsOrderByColumn.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/INT_00eb0e44.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Game::GameMode2;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004D6D20
        void MissionEndscreen::MenuItemRenderFunction_MissionEndscreen_Main(int param_1, ...)
        {
            int iVar1;
            int iVar2;
            int iVar3;
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
                DAT_ButtonUnknownZero::instance = 1;
            }
            DAT_ButtonUnknownZero::instance = 0;
            if ((char)INT_00eb0e44::instance != '\0') {
                if (param_1 == -100) {
                    DAT_ButtonUnknownZero::instance = 0;
                }
                if (param_1 == -0x65) {
                    DAT_ButtonUnknownZero::instance = 0;
                }
            }
            if (param_1 == -2) {
                DAT_ButtonUnknownZero::instance = 0;
            }
            iVar2 = DAT_ButtonX::instance;
            iVar3 = DAT_ButtonY::instance;
            if (param_1 == -100) {
                if ((DAT_00ec082c::instance != 0) && (DAT_00ec082c::instance != 2))
                    goto LAB_004d6d83;
            } else {
                if (param_1 != -0x65) {
                    if (0xf < (uint)param_1) {
                    LAB_004d6d83:
                        if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                            if (param_1 == -10) {
                                DAT_00eb9af8::instance = 0x11;
                            } else if (param_1 == -1) {
                                DAT_00eb9af8::instance = 0x10;
                                MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                                        MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                            }
                        }
                        MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                                MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    }
                    if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
                        DAT_00eb9af8::instance = param_1;
                    }
                    if (param_1 != DAT_FinalResultsOrderByColumn::instance)
                        goto LAB_004d6d83;
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    if (DAT_FinalResultsOrderByColumn::instance < 0xd) {
                        iVar1 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm,
                            &DAT_UIButtonDefinedData::instance
                                .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance])(TRUE);
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            (OpenSHC::DE::SHCDE::eGM)(DAT_UIButtonDefinedData::instance
                                    .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                    .gmId_0x0),
                            iVar1 + 0xe, iVar2, iVar3);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    }
                    iVar1 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm,
                        &DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance])(
                        TRUE);
                    iVar1 = iVar1 + 1;
                    goto LAB_004d6eb5;
                }
                if ((DAT_00ec082c::instance != 1) && (DAT_00ec082c::instance != 3))
                    goto LAB_004d6d83;
            }
            DAT_ButtonUnknownZero::instance = 1;
            DAT_ButtonCurrentlyInteracting::instance = FALSE;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            iVar1 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm,
                &DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance])(FALSE);
            iVar1 = iVar1 + 2;
        LAB_004d6eb5:
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)DAT_UIButtonDefinedData::instance
                                                      .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                                      .gmId_0x0,
                iVar1, iVar2, iVar3);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
