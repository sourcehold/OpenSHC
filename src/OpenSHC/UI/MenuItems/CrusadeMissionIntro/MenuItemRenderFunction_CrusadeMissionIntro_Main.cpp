#include "../CrusadeMissionIntro.func.hpp"

#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/Game/TrailType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004D8BB0
        void CrusadeMissionIntro::MenuItemRenderFunction_CrusadeMissionIntro_Main(int button, ...)
        {
            // the trail is finished once its progress reaches its length: 20, 30 and 50 missions
            BOOLEnum trailComplete = FALSE;
            DAT_ButtonUnknownZero::instance = FALSE;
            if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                if (DAT_GameCore::instance.extremeTrailProgress >= 20) {
                    trailComplete = TRUE;
                }
            } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                if (DAT_GameCore::instance.warchestTrailProgress >= 30) {
                    trailComplete = TRUE;
                }
            } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_FIRST_EDITION) {
                if (DAT_GameCore::instance.skirmishTrailProgress >= 50) {
                    trailComplete = TRUE;
                }
            }
            if (button == 10 && trailComplete) {
                DAT_ButtonUnknownZero::instance = TRUE;
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
            }
            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
        }

    }
}
}
