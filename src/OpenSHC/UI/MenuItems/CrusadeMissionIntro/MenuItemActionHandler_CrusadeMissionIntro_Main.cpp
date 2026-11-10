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

        // FUNCTION: STRONGHOLDCRUSADER 0x004D8C10
        void CrusadeMissionIntro::MenuItemActionHandler_CrusadeMissionIntro_Main(int button, ...)
        {
            if (button == 10) {
                if (DAT_GameCore::instance.gameSuspended == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                    return;
                }
                // the next mission of the trail, while there is one: 20, 30 and 50 missions long
                // one call per trail, which MSVC merges (one call with mission and length locals: 100.0% -> 80.9%)
                if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                    if (DAT_GameCore::instance.extremeTrailProgress < 20) {
                        MACRO_CALL(OpenSHC::Game::Skirmish_Func::SetupSkirmishMode)(
                            DAT_GameCore::instance.extremeTrailProgress);
                    }
                } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                    if (DAT_GameCore::instance.warchestTrailProgress < 30) {
                        MACRO_CALL(OpenSHC::Game::Skirmish_Func::SetupSkirmishMode)(
                            DAT_GameCore::instance.warchestTrailProgress);
                    }
                } else {
                    if (DAT_GameCore::instance.skirmishTrailProgress < 50) {
                        MACRO_CALL(OpenSHC::Game::Skirmish_Func::SetupSkirmishMode)(
                            DAT_GameCore::instance.skirmishTrailProgress);
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                return;
            }
            if (button == 11) {
                if (DAT_GameCore::instance.gameSuspended == 1) {
                    // the yes/no dialog asks "Quit Mission"
                    DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 7;
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                        DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_YES_NO_DIALOG);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_CRUSADE_MAP, 0);
            }
        }
    }
}
}
