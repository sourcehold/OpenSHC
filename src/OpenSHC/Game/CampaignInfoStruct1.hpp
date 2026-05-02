/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/CampaignInfoStruct1.hpp'
*/

#pragma once

#include "OpenSHC/Game/CampaignInfoSubStructure1.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Game::CampaignInfoSubStructure1;

#pragma pack(push, 1)
    // SIZE: 0x00000058
    typedef struct CampaignInfoStruct1 {

        CampaignInfoSubStructure1 sub; // 0x00000000 length: 84
        undefined4 field1_0x54; // 0x00000054 length: 4

    } CampaignInfoStruct1;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(CampaignInfoStruct1) == 88, CampaignInfoStruct1);
} // namespace Game
} // namespace OpenSHC
