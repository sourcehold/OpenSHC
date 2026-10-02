#include "../Unknown61ReturnToSkrimishMenuUnk.func.hpp"

#include "OpenSHC/Game/Skirmish/SkirmishLobbySetupStructure.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuItems/SelectCrusade.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/SEC_SkirmishLobbySetupStructure.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004409C0
        void Unknown61ReturnToSkrimishMenuUnk::MenuView_Unknown61ReturnToSkrimishMenuUnk_Prepare()
        {
            Menu* pMVar1;
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::loadGfxFile,
                DAT_TextureRenderCoreObject::ptr)("frontend_combat3.tgx");
            MACRO_CALL(OpenSHC::UI::Helpers_Func::LoadTGX_shc_back)();
            DAT_MenuHandlerState::instance.y = DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            DAT_MenuHandlerState::instance.x = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1 = DAT_MenuHandlerState::instance.currentMenu;
            (DAT_MenuHandlerState::instance.currentMenu)->xPosition
                = DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            pMVar1->yPosition = DAT_MenuHandlerState::instance.y;
            MACRO_CALL(OpenSHC::UI::Rendering_Func::DrawOuterMenuBorder)();
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(0,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                    / 2);
            MACRO_CALL(OpenSHC::UI::MenuItems::SelectCrusade_Func::MenuItemActionHandler_SelectCrusade_Main)(2);
            MACRO_CALL_MEMBER(OpenSHC::Game::Skirmish::SkirmishLobbySetupStructure_Func::restoreSkirmishLobbySetup,
                SEC_SkirmishLobbySetupStructure::ptr)();
            return;
        }

    }
}
}
