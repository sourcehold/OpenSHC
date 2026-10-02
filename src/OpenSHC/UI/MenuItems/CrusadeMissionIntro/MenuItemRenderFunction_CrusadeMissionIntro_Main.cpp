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

        using OpenSHC::Game::TrailType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004D8BB0
        void CrusadeMissionIntro::MenuItemRenderFunction_CrusadeMissionIntro_Main(int param_1, ...)
        {
            bool bVar1;
            bool bVar2;
            bool bVar3;
            bVar1 = false;
            DAT_ButtonUnknownZero::instance = 0;
            if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_EXTREME) {
                bVar3 = (DAT_GameCore::instance.extremeTrailProgress < 0x14);
                bVar2 = DAT_GameCore::instance.extremeTrailProgress + -0x14 < 0;
            } else if (DAT_GameCore::instance.currentTrailType == OpenSHC::Game::TT_WARCHEST) {
                bVar3 = (DAT_GameCore::instance.warchestTrailProgress < 0x1e);
                bVar2 = (int)(DAT_GameCore::instance.warchestTrailProgress - 0x1e) < 0;
            } else {
                if (DAT_GameCore::instance.currentTrailType != OpenSHC::Game::TT_FIRST_EDITION)
                    goto LAB_004d8bee;
                bVar3 = (DAT_GameCore::instance.skirmishTrailProgress < 0x32);
                bVar2 = (int)(DAT_GameCore::instance.skirmishTrailProgress - 0x32) < 0;
            }
            if (bVar3 == bVar2) {
                bVar1 = true;
            }
        LAB_004d8bee:
            if ((param_1 == 10) && (bVar1)) {
                DAT_ButtonUnknownZero::instance = 1;
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
            }
            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
        }

    }
}
}
