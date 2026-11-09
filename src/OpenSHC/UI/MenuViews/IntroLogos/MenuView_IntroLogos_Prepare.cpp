#include "../IntroLogos.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_IntroBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_IntroStep.hpp"
#include "OpenSHC/Globals/DAT_IntroTimestamp.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x00424720
        void IntroLogos::MenuView_IntroLogos_Prepare()
        {
            if (!DAT_IntroStep::instance) {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("logo1.tgx");
            } else if (DAT_IntroStep::instance == 1) {
                DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                    DAT_TextureRenderCoreObject::ptr)("logo2.tgx");
            }
            DAT_IntroBlendStrength::instance = 0;
            DAT_IntroTimestamp::instance = timeGetTime();
        }

    }
}
}
