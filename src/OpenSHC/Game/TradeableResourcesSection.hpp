/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Game/TradeableResourcesSection.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)
    // SIZE: 0x00000064
    typedef struct TradeableResourcesSection {

        BOOLEnum tradeabilityArray[25]; // 0x00000000 length: 100

    } TradeableResourcesSection;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(TradeableResourcesSection) == 100, TradeableResourcesSection);
} // namespace Game
} // namespace OpenSHC
