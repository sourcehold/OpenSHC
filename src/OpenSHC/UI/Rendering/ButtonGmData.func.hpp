/**
  path: 'OpenSHC/UI/Rendering/ButtonGmData.func.hpp'
*/

#include "OpenSHC/UI/Rendering/ButtonGmData.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace UI {
    namespace Rendering {
        namespace ButtonGmData_Func {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(int (ButtonGmData::*)(BOOLEnum), false, Address::SHC_3BB0A8C1_0x004630B0,
                &ButtonGmData::getPictureNumberInGm)
            getPictureNumberInGm;

        } // namespace ButtonGmData_Func
    } // namespace Rendering
} // namespace UI
} // namespace OpenSHC
