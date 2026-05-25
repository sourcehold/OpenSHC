/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Globals/DAT_SoundEffectsHelperData1.hpp'
*/

#pragma once

#include "OpenSHC/Audio/SoundEffectsHelperData1.hpp"
namespace OpenSHC {

using OpenSHC::Audio::SoundEffectsHelperData1;

MACRO_STRUCT_RESOLVER(SoundEffectsHelperData1, false, Address::SHC_3BB0A8C1_0x00DF37F0)
// GLOBAL: STRONGHOLDCRUSADER 0x00DF37F0
DAT_SoundEffectsHelperData1;

struct Test {
    int a;
    int b;
    int c;
    int d;
};

MACRO_STRUCT_RESOLVER(Test, false, 0x0)
// GLOBAL: STRONGHOLDCRUSADER 0x0
TestData;

} // namespace OpenSHC

// MACRO_STRUCT_INSTANCE(Address::SHC_3BB0A8C1_0x00DF37F0, )

// TODO: No support for direct struct instantiation.
MACRO_STRUCT_INSTANCE(0x0, OpenSHC::Test(1, 2, 3, 4))
