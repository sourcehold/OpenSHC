/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItems/MapEditorLandscaping.hpp'
*/

#pragma once

#include "OpenSHC/Commands/MappersEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace MapEditorLandscaping {

            using OpenSHC::Commands::MappersEnum;

            void __cdecl MenuItemActionHandler_MapEditorLandscaping_CategoryButtons(int param_1, ...);

            void __cdecl MenuItemActionHandler_MapEditorLandscaping_GeneralButtons(MappersEnum param_1, ...);

            void __cdecl MenuItemActionHandler_MapEditorLandscaping_QueueCommandCallback();

            void __cdecl MenuItemRenderFunction_MapEditorLandscaping_GeneralButtons(int param_1, ...);

        } // namespace MapEditorLandscaping
    } // namespace MenuItems
} // namespace UI
} // namespace OpenSHC
