/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace Enums {
        typedef enum DisplayElementPositionModifier {

            DEPM_MAIN_MENU_X_Y = 0, // 0x00000000
            DEPM_RESOLUTION_Y = 1, // 0x00000001
            DEPM_TOWARDS_MID_Y = 2, // 0x00000002
            DEPM_RESOLUTION_X = 4, // 0x00000004
            DEPM_TOWARDS_MID_X = 8 // 0x00000008

        } DisplayElementPositionModifier;

        static_assert_cpp98_obj(sizeof(DisplayElementPositionModifier) == 4, DisplayElementPositionModifier);
    } // namespace Enums
} // namespace UI
} // namespace OpenSHC
