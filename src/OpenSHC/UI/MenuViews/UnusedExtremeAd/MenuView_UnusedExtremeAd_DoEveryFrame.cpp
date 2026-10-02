#include "../UnusedExtremeAd.func.hpp"

#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_00ed278c.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkIndex.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00ed3140.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004E1AA0
        void UnusedExtremeAd::MenuView_UnusedExtremeAd_DoEveryFrame()
        {
            int iVar1;
            iVar1 = MACRO_CALL(OpenSHC::UI::Helpers_Func::TicksSinceCounterStart)();
            if (iVar1 != 0) {
                if (DAT_MouseState::instance.rightClickStop != 0) {
                    MACRO_CALL(OpenSHC::UI::Credits_Func::StopCreditsPlaybackAndSounds)();
                }
                if (DAT_MouseState::instance.leftClickStart != 0) {
                    iVar1 = MACRO_CALL(OpenSHC::UI::Helpers_Func::FindCampaignMapHotspotAtMouse)();
                    if (iVar1 == 1) {
                        MACRO_CALL(OpenSHC::UI::Credits_Func::EndCreditsSegmentAndAdvanceToNext)();
                        DAT_00ed278c::instance = DAT_00ed278c::instance + 1;
                        if (DAT_00ed278c::instance == 3) {
                            DAT_WindowAndDirectDraw::instance.postWindowCloseMessage = 1;
                        }
                    }
                }
                MACRO_CALL(OpenSHC::Rendering_Func::ProcessCreditsScriptCommands)();
                if (DAT_UnknownBinkIndex::instance < DAT_UnknownBinkCount::instance) {
                    MACRO_CALL(OpenSHC::Rendering_Func::RenderActiveCreditsElements)();
                }
                INT_00ed3140::instance = INT_00ed3140::instance + 1;
                if (DAT_UnknownBinkCount::instance <= DAT_UnknownBinkIndex::instance) {
                    DAT_WindowAndDirectDraw::instance.postWindowCloseMessage = 1;
                }
            }
        }

    }
}
}
