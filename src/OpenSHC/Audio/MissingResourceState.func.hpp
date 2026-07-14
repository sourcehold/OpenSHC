/**
  path: 'OpenSHC/Audio/MissingResourceState.func.hpp'
*/

#include "OpenSHC/Audio/MissingResourceState.hpp"
#include "OpenSHC/Audio/SFX/ResourceLackSFXInt.hpp"
namespace OpenSHC {
namespace Audio {
    namespace MissingResourceState_Func {

        using OpenSHC::Audio::SFX::ResourceLackSFXInt;

        MACRO_FUNCTION_RESOLVER(void (MissingResourceState::*)(int, ResourceLackSFXInt), false,
            Address::SHC_3BB0A8C1_0x00471720, &MissingResourceState::playResourceLackSFX)
        playResourceLackSFX;

        MACRO_FUNCTION_RESOLVER(void (MissingResourceState::*)(int, int, dword, dword), false,
            Address::SHC_3BB0A8C1_0x004761E0, &MissingResourceState::renderResourceMissingText)
        renderResourceMissingText;

    } // namespace MissingResourceState_Func
} // namespace Audio
} // namespace OpenSHC
