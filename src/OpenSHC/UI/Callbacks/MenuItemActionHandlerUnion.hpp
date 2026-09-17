/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Callbacks/MenuItemActionHandlerUnion.hpp'
*/

#pragma once

#include "OpenSHC/UI/Callbacks/ScrollbarActionHandler.hpp"
#include "OpenSHC/UI/Callbacks/SimpleActionHandler.hpp"
#include "OpenSHC/UI/Callbacks/SliderActionHandler.hpp"

namespace OpenSHC {
namespace UI {
    namespace Callbacks {

        using OpenSHC::UI::Callbacks::ScrollbarActionHandler;
        using OpenSHC::UI::Callbacks::SimpleActionHandler;
        using OpenSHC::UI::Callbacks::SliderActionHandler;

#pragma pack(push, 1)
        // SIZE: 0x00000004
        typedef union MenuItemActionHandlerUnion {

            SimpleActionHandler* simple; // 0x00000000 length: 4
            ScrollbarActionHandler* scrollbar; // 0x00000000 length: 4
            SliderActionHandler* slider; // 0x00000000 length: 4
            pointer pointer; // 0x00000000 length: 4
            ulong address; // 0x00000000 length: 4

        } MenuItemActionHandlerUnion;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(MenuItemActionHandlerUnion) == 4, MenuItemActionHandlerUnion);
    } // namespace Callbacks
} // namespace UI
} // namespace OpenSHC
