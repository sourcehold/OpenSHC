/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/AI/AINervousDestroyBuildingCategory.hpp'
*/

#pragma once

namespace OpenSHC {
namespace AI {
    typedef enum AINervousDestroyBuildingCategory {

        AINDBC_FEAR_FACTOR_BUILDINGS = 1, // 0x00000001
        AINDBC_WORKSHOPS_AND_RELIGIOUS_BUILDINGS = 2, // 0x00000002
        AINDBC_GATEHOUSES_TOWERS_GUILDS = 3, // 0x00000003
        AINDBC_BARRACKS_MERCPOST_STABLES = 4, // 0x00000004
        AINDBC_WATER_BUILDINGS = 5, // 0x00000005
        AINDBC_RESOURCE_BUILDINGS = 6, // 0x00000006
        AINDBC_FARMS = 7 // 0x00000007

    } AINervousDestroyBuildingCategory;

    static_assert_cpp98_obj(sizeof(AINervousDestroyBuildingCategory) == 4, AINervousDestroyBuildingCategory);
} // namespace AI
} // namespace OpenSHC
