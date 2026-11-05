#include "../MapEditorLandscaping.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace MapEditorLandscaping {

            // FUNCTION: STRONGHOLDCRUSADER 0x00431460
            void MenuItemActionHandler_MapEditorLandscaping_CategoryButtons(int category, ...)
            {
                // -1 opens the pause menu when no dialog is open.
                if (category == -1) {
                    if (DAT_MenuTextInputState::instance.currentModalDialog == Enums::MMT_NO_MENU) {
                        MACRO_CALL_MEMBER(MenuTextInputState_Func::activateModalDialogAndClearText,
                            DAT_MenuTextInputState::ptr)(Enums::MMT_PAUSE_MENU);
                    }
                    return;
                }
                // On a multiplayer map the feature tab opens its multiplayer version.
                if (category == Commands::M_MAPPER_SUB_MODE_FEATURE
                    && DAT_GameCore::instance.U2_mapType_singleOrMulti >= 1) {
                    category = Commands::M_MAPPER_SUB_MODE_FEATURE_MP;
                }
                if (DAT_GameCore::instance.currentMenuViewType == Enums::MVT_MAP_EDITOR_LANDSCAPING
                    && category == DAT_GameCore::instance.activeMenuTab.buildMenuTab) {
                    return;
                }
                DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo.buildMenuTab = category;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    Enums::MVT_MAP_EDITOR_LANDSCAPING, 0);
                DAT_TileMapState::instance.currentMapperCommand = Commands::M_MAPPER_NULL;
                DAT_UIDragDropDefinedData::instance.MenuView_TriggerInitial = TRUE;
                DAT_WindowAndDirectDraw::instance.unk_resetViewportRelated = 1;
            }

        }
    }
}
}
