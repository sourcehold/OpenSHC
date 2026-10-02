#include "../CrusadeMissionIntro.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Game::TrailType;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004D8C10
        void CrusadeMissionIntro::MenuItemActionHandler_CrusadeMissionIntro_Main(int param_1, ...)
        {
            dword skirmishTrailMission;
            bool bVar1;
            bool bVar2;
            if (param_1 != 10) {
                if (param_1 == 0xb) {
                    if (DAT_GameCore::instance.field22_0x64 == 1) {
                        DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 7;
                        MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                            DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_YES_NO_DIALOG);
                    }
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_CRUSADE_MAP, 0);
                }
            }
            if (DAT_GameCore::instance.field22_0x64 == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
            }
            if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                bVar2 = (DAT_GameCore::instance.extremeTrailProgress < 20);
                bVar1 = DAT_GameCore::instance.extremeTrailProgress + 20 < 0;
                skirmishTrailMission = DAT_GameCore::instance.extremeTrailProgress;
            } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                bVar2 = (DAT_GameCore::instance.warchestTrailProgress < 30);
                bVar1 = (int)(DAT_GameCore::instance.warchestTrailProgress - 30) < 0;
                skirmishTrailMission = DAT_GameCore::instance.warchestTrailProgress;
            } else {
                bVar2 = (DAT_GameCore::instance.skirmishTrailProgress < 50);
                bVar1 = (int)(DAT_GameCore::instance.skirmishTrailProgress - 50) < 0;
                skirmishTrailMission = DAT_GameCore::instance.skirmishTrailProgress;
            }
            if (bVar2 != bVar1) {
                MACRO_CALL(OpenSHC::Game::Skirmish_Func::SetupSkirmishMode)(skirmishTrailMission);
            }
            MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
        }

    }
}
}
