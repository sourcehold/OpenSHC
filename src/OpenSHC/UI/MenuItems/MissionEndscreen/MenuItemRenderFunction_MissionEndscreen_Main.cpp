#include "../MissionEndscreen.func.hpp"

#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/CHAR_00eb0e44.hpp"
#include "OpenSHC/Globals/DAT_00eb9af8.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_FinalResultsOrderByColumn.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/INT_00ec082c.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D6D20
        void MissionEndscreen::MenuItemRenderFunction_MissionEndscreen_Main(int buttonID, ...)
        {
            DAT_ButtonUnknownZero::instance = TRUE;
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER) {
                return;
            }
            DAT_ButtonUnknownZero::instance = FALSE;
            if (CHAR_00eb0e44::instance != 0 && (buttonID == -100 || buttonID == -101)) {
                return;
            }
            if (buttonID == -2) {
                return;
            }
            // the two tabs, -100 and -101: the selected one (0 or 2 for the first, 1 or 3 for the second) is drawn
            // pressed
            if ((buttonID == -100 && (INT_00ec082c::instance == 0 || INT_00ec082c::instance == 2))
                || (buttonID == -101 && (INT_00ec082c::instance == 1 || INT_00ec082c::instance == 3))) {
                DAT_ButtonUnknownZero::instance = TRUE;
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)DAT_UIButtonDefinedData::instance
                                                          .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                                          .gmId_0x0,
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm,
                        &DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance])(
                        FALSE)
                        + 2,
                    DAT_ButtonX::instance, DAT_ButtonY::instance);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return;
            }
            if (buttonID >= 0 && buttonID <= 15) {
                // the results table's column headers: the one the table is sorted by is drawn pressed
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    DAT_00eb9af8::instance = buttonID;
                }
                if (buttonID == DAT_FinalResultsOrderByColumn::instance) {
                    DAT_ButtonCurrentlyInteracting::instance = TRUE;
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    if (DAT_FinalResultsOrderByColumn::instance < 13) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            (OpenSHC::DE::SHCDE::eGM)DAT_UIButtonDefinedData::instance
                                .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                .gmId_0x0,
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm,
                                &DAT_UIButtonDefinedData::instance
                                    .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance])(TRUE)
                                + 14,
                            DAT_ButtonX::instance, DAT_ButtonY::instance);
                        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                            = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                        return;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)DAT_UIButtonDefinedData::instance
                                                              .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                                              .gmId_0x0,
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm,
                            &DAT_UIButtonDefinedData::instance
                                .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance])(TRUE)
                            + 1,
                        DAT_ButtonX::instance, DAT_ButtonY::instance);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
            }
            if (DAT_ButtonCurrentlyInteracting::instance) {
                switch (buttonID) {
                case -10:
                    DAT_00eb9af8::instance = 17;
                    break;
                case -1:
                    DAT_00eb9af8::instance = 16;
                    break;
                }
            }
            MACRO_CALL(General_Func::
                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
        }

    }
}
}
