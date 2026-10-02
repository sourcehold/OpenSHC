#include "../MapEditorLandscaping.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/UI/Enums/UserControlID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Commands::MappersEnum;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00431460
        void MapEditorLandscaping::MenuItemActionHandler_MapEditorLandscaping_CategoryButtons(int param_1, ...)
        {
            if (param_1 == -1) {
                if (DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                        DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_PAUSE_MENU);
                }
            } else {
                if ((param_1 == 0xed) && (0 < (int)DAT_GameCore::instance.U2_mapType_singleOrMulti)) {
                    param_1 = OpenSHC::UI::Enums::UCID_TTS_MACEMEN;
                }
                if ((DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING)
                    || (param_1 != DAT_GameCore::instance.activeMenuTab.tabType)) {
                    DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo = param_1;
                    MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING, 0);
                    DAT_TileMapState::instance.currentMapperCommand = OpenSHC::Commands::M_MAPPER_NULL;
                    DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                    DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 1;
                }
            }
        }

    }
}
}
