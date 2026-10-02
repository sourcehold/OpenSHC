#include "../InGameMenu.func.hpp"

#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eGM;
        using OpenSHC::Rendering::Enums::RenderTarget;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004B65F0
        void InGameMenu::MenuItemRenderFunction_InGameMenu_BikMessagePlayerShield(int param_1, ...)
        {
            dword dVar1;
            if (DAT_VideoBikQueue::instance.mbr_0x928 != 0) {
                dVar1 = DAT_VideoBikQueue::instance.mbr_0x928;
                if ((int)DAT_VideoBikQueue::instance.mbr_0x928 < 0) {
                    dVar1 = -DAT_VideoBikQueue::instance.mbr_0x928;
                }
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                    (int)((int)(dVar1 + 0x1d5)), (int)((int)(DAT_ButtonX::instance)),
                    (int)((int)(DAT_ButtonY::instance)));
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
        }

    }
}
}
