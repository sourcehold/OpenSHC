#include "../IntroVideo.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/TIME_IntroVideo_Prepare.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "UnsortedBinkFlagInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00424AD0
        void IntroVideo::MenuView_IntroVideo_DoEveryFrame()
        {
            DWORD DVar1;
            DVar1 = timeGetTime();
            if (399 < DVar1 - TIME_IntroVideo_Prepare::instance) {
                if (DAT_MouseState::instance.draggingStopped != FALSE) {
                    MACRO_CALL_MEMBER(OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback,
                        DAT_BinkControlState::ptr)(0);
                }
                if (DAT_BinkControlState::instance.binkObjPtrArray[0] == (HBINK)0x0) {
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_GAME_START_ENTER_NAME, 0);
                }
            }
        }

    }
}
}
