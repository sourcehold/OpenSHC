#include "../IntroVideo.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/TIME_IntroVideo_Prepare.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x00424AD0
        void IntroVideo::MenuView_IntroVideo_DoEveryFrame()
        {
            DWORD const now = timeGetTime();
            if (now - TIME_IntroVideo_Prepare::instance >= 400) {
                if (DAT_MouseState::instance.draggingStopped) {
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback,
                        DAT_BinkControlState::ptr)(0);
                }
                if (DAT_BinkControlState::instance.binkObjPtrArray[0] == NULL) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_GAME_START_ENTER_NAME, 0);
                }
            }
        }

    }
}
}
