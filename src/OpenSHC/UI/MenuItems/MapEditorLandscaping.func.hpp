/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/MapEditorLandscaping.func.hpp'
*/

#pragma once

#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/UI/MenuItems/MapEditorLandscaping.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace MapEditorLandscaping_Func {

            using OpenSHC::Commands::MappersEnum;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00431460,
                &OpenSHC::UI::MenuItems::MapEditorLandscaping::
                    MenuItemActionHandler_MapEditorLandscaping_CategoryButtons)
            MenuItemActionHandler_MapEditorLandscaping_CategoryButtons;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(MappersEnum param_1, ...), false, Address::SHC_3BB0A8C1_0x004314E0,
                &OpenSHC::UI::MenuItems::MapEditorLandscaping::
                    MenuItemActionHandler_MapEditorLandscaping_GeneralButtons)
            MenuItemActionHandler_MapEditorLandscaping_GeneralButtons;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x00443A30,
                &OpenSHC::UI::MenuItems::MapEditorLandscaping::
                    MenuItemActionHandler_MapEditorLandscaping_QueueCommandCallback)
            MenuItemActionHandler_MapEditorLandscaping_QueueCommandCallback;

            MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ...), false, Address::SHC_3BB0A8C1_0x00464860,
                &OpenSHC::UI::MenuItems::MapEditorLandscaping::
                    MenuItemRenderFunction_MapEditorLandscaping_GeneralButtons)
            MenuItemRenderFunction_MapEditorLandscaping_GeneralButtons;

        } // namespace MapEditorLandscaping_Func
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
