/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Audio/MissingResourceState.hpp'
*/

#pragma once

#include "OpenSHC/Audio/SFX/ResourceLackSFXInt.hpp"

namespace OpenSHC {
namespace Audio {

    using OpenSHC::Audio::SFX::ResourceLackSFXInt;

#pragma pack(push, 1)

    // SIZE: 0x00000001
    class MissingResourceState {
    public:
        undefined1 padding_0x0[1]; // 0x00000000 length: 1

    private:
        MissingResourceState(MissingResourceState const&);
        void operator=(MissingResourceState const&);

        MissingResourceState();
        ~MissingResourceState();

    public:
        void playResourceLackSFX(int resourceTextElement, ResourceLackSFXInt resourceType);

        void renderResourceMissingText(int posX, int posY, dword textGroup, dword unusedUnk);
    };

    static_assert_cpp98_obj(sizeof(MissingResourceState) == 1, MissingResourceState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(MissingResourceState, false, Address::SHC_3BB0A8C1_0x00EE1098) pDAT_MissingResourceState;

} // namespace Audio
} // namespace OpenSHC
