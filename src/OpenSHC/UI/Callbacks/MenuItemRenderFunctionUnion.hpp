/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Callbacks/MenuItemRenderFunctionUnion.hpp'
*/

#pragma once

#include "OpenSHC/UI/Callbacks/GMDataImageRenderFunction.hpp"
#include "OpenSHC/UI/Callbacks/ScrollbarRenderFunction.hpp"
#include "OpenSHC/UI/Callbacks/SimpleRenderFunction.hpp"
#include "OpenSHC/UI/Callbacks/SliderRenderFunction.hpp"

namespace OpenSHC {
namespace UI {
    namespace Callbacks {

        using OpenSHC::UI::Callbacks::GMDataImageRenderFunction;
        using OpenSHC::UI::Callbacks::ScrollbarRenderFunction;
        using OpenSHC::UI::Callbacks::SimpleRenderFunction;
        using OpenSHC::UI::Callbacks::SliderRenderFunction;

#pragma pack(push, 1)
        // SIZE: 0x00000004
        typedef union MenuItemRenderFunctionUnion {

            SimpleRenderFunction* simple; // 0x00000000 length: 4
            GMDataImageRenderFunction* gmDataImage; // 0x00000000 length: 4
            SliderRenderFunction* slider; // 0x00000000 length: 4
            ScrollbarRenderFunction* scrollbar; // 0x00000000 length: 4
            pointer pointer; // 0x00000000 length: 4
            ulong address; // 0x00000000 length: 4

        } MenuItemRenderFunctionUnion;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(MenuItemRenderFunctionUnion) == 4, MenuItemRenderFunctionUnion);
    } // namespace Callbacks
} // namespace UI
} // namespace OpenSHC
