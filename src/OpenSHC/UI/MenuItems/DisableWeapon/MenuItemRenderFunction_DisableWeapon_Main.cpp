#include "../DisableWeapon.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace DisableWeapon {

            // FUNCTION: STRONGHOLDCRUSADER 0x004BB7B0
            void MenuItemRenderFunction_DisableWeapon_Main(int button, ...)
            {
                // Before the range test: the Exit block reuses its zero (inside the if: quick_diff 0.8889 -> 0.7273)
                int iconOffsetY = 0;
                // Guarded, not an early return (early return: quick_diff 0.8889 -> 0.8673)
                // One unsigned test for 0..7 (button >= 0 && button <= 7: reccmp 100.0% -> 90.0%)
                if ((uint)button <= 7) {
                    // Button 1 moves down a pixel while hovered; its icon stays where it was.
                    if (button == 1 && DAT_ButtonCurrentlyInteracting::instance) {
                        ++DAT_ButtonY::instance;
                        iconOffsetY = -1;
                    }
                    MACRO_CALL(General_Func::
                            MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
                    // The weapons 0 to 5 get the disabled icon only while they cannot be made.
                    // Break to the icon, then return (the return first: quick_diff 0.8889 -> 0.7527)
                    switch (button) {
                    case 0:
                        if (!DAT_MapPropertiesState::instance.SEC_XbowProducible_save) {
                            break;
                        }
                        return;
                    case 1:
                        if (!DAT_MapPropertiesState::instance.SEC_PikeProducible_save) {
                            break;
                        }
                        return;
                    case 2:
                        if (!DAT_MapPropertiesState::instance.SEC_SwordProducible_save) {
                            break;
                        }
                        return;
                    case 3:
                        if (!DAT_MapPropertiesState::instance.SEC_BowProducible_save) {
                            break;
                        }
                        return;
                    case 4:
                        if (!DAT_MapPropertiesState::instance.SEC_SpearProducible_save) {
                            break;
                        }
                        return;
                    case 5:
                        if (!DAT_MapPropertiesState::instance.SEC_MaceProducible_save) {
                            break;
                        }
                        return;
                    // An explicit default keeps every return's epilogue (without it: quick_diff 0.8889 -> 0.8673)
                    default:
                        break;
                    }
                    if (button != 0) {
                        DAT_ButtonX::instance -= 4;
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 45,
                        DAT_ButtonX::instance + 6, DAT_ButtonY::instance + iconOffsetY - 5, 12);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    return;
                }
                if (button == -3) {
                    // "Exit"
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::renderBasicButton,
                        AlphaAndButtonSurfaceObj::ptr)(0, OpenSHC::Rendering::Enums::RT_CONTEXT_BASED);
                    // One call per colour (one call with a colour local: quick_diff 0.8889 -> 0.7839)
                    // The position in each branch (once, before the test: quick_diff 0.8889 -> 0.8788)
                    if (!DAT_ButtonCurrentlyInteracting::instance) {
                        int const textY = DAT_ButtonY::instance + 6;
                        int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 3),
                            textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_C2F0EB, 18, FALSE,
                            0);
                    } else {
                        int const textY = DAT_ButtonY::instance + 6;
                        int const textX = DAT_ButtonW::instance / 2 + DAT_ButtonX::instance;
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                                DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SCENARIO, 3),
                            textX, textY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE,
                            0);
                    }
                }
            }

        }
    }
}
}
