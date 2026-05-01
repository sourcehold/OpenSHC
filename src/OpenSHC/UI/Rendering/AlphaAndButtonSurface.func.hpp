/**
  path: 'OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp'
*/

#include "OpenSHC/Rendering/Enums/RenderTargetInt.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace Rendering {
        namespace AlphaAndButtonSurface_Func {

            using OpenSHC::Rendering::Enums::RenderTargetInt;
            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(void (AlphaAndButtonSurface::*)(int), false, Address::SHC_3BB0A8C1_0x004246E0,
                &AlphaAndButtonSurface::renderNonInteractingButtonBackground)
            renderNonInteractingButtonBackground;

            MACRO_FUNCTION_RESOLVER(void (AlphaAndButtonSurface::*)(), false, Address::SHC_3BB0A8C1_0x0045D0B0,
                &AlphaAndButtonSurface::freeMemory)
            freeMemory;

            MACRO_FUNCTION_RESOLVER(void (AlphaAndButtonSurface::*)(), false, Address::SHC_3BB0A8C1_0x00462FF0,
                &AlphaAndButtonSurface::prepareButtonAndAlphaSurface)
            prepareButtonAndAlphaSurface;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (AlphaAndButtonSurface::*)(), false, Address::SHC_3BB0A8C1_0x004630D0,
                &AlphaAndButtonSurface::isMouseOnButtonImageUnk)
            isMouseOnButtonImageUnk;

            MACRO_FUNCTION_RESOLVER(void (AlphaAndButtonSurface::*)(int), false, Address::SHC_3BB0A8C1_0x00463270,
                &AlphaAndButtonSurface::FUN_00463270)
            FUN_00463270;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (AlphaAndButtonSurface::*)(int), false, Address::SHC_3BB0A8C1_0x00463310,
                &AlphaAndButtonSurface::openBuildingStatusMenuForBuildingID)
            openBuildingStatusMenuForBuildingID;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (AlphaAndButtonSurface::*)(int), false, Address::SHC_3BB0A8C1_0x00463A00,
                &AlphaAndButtonSurface::FUN_00463a00)
            FUN_00463a00;

            MACRO_FUNCTION_RESOLVER(void (AlphaAndButtonSurface::*)(int, RenderTargetInt), false,
                Address::SHC_3BB0A8C1_0x00463A90, &AlphaAndButtonSurface::renderBasicButton)
            renderBasicButton;

        } // namespace AlphaAndButtonSurface_Func
    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
