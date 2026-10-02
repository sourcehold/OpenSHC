#include "../CustomScenarios.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/MenuViews/CustomScenarios.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnknownGFXIndex.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00425FF0
        void CustomScenarios::MenuView_CustomScenarios_DoEveryFrame()
        {
            DAT_UnknownGFXIndex::instance
                = (int)(DAT_MenuModalComposition1::instance.activeModalDialogID != OpenSHC::UI::Enums::MMT_NONE);
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(DAT_UnknownGFXIndex::instance,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[DAT_UnknownGFXIndex::instance].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[DAT_UnknownGFXIndex::instance].height)
                    / 2);
            if (DAT_MenuTextInputState::instance.dialogResult == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAP_EDITOR_PROPERTIES, 0);
            }
            if (DAT_MenuTextInputState::instance.dialogResult == -1) {
                MACRO_CALL(OpenSHC::UI::MenuViews::CustomScenarios_Func::MenuView_CustomScenarios_Prepare)();
                return;
            }
            return;
        }

    }
}
}
