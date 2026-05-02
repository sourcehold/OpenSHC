/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/MenuItemSecondItemTypeData.hpp'
*/

#pragma once

#include "OpenSHC/UI/ButtonState.hpp"
#include "OpenSHC/UI/ScrollbarOrSliderState.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::ButtonState;
    using OpenSHC::UI::ScrollbarOrSliderState;

#pragma pack(push, 1)
    // SIZE: 0x00000010
    typedef union MenuItemSecondItemTypeData {

        ButtonState buttonState; // 0x00000000 length: 16
        ScrollbarOrSliderState scrollbarOrSliderState; // 0x00000000 length: 16

    } MenuItemSecondItemTypeData;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(MenuItemSecondItemTypeData) == 16, MenuItemSecondItemTypeData);
} // namespace UI
} // namespace OpenSHC
