/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/HoveredState.hpp'
*/

#pragma once

#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/UI/HoveredStateElement.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Commands::CommandBuildingTypeInt;
    using OpenSHC::UI::HoveredStateElement;

#pragma pack(push, 1)

    // SIZE: 0x000001E0
    class HoveredState {
    public:
        HoveredStateElement elements[20]; // 0x00000000 length: 480

    private:
        HoveredState(HoveredState const&);
        void operator=(HoveredState const&);

        HoveredState();
        ~HoveredState();

    public:
        // Constructor
        HoveredState* Constructor_HoveredState();

        void clearHoveredState();

        void clearInvalidatedHoverStates();

        void createHoverStateElement(int x, int y, CommandBuildingTypeInt type, int size, int flag);

        void calculateHoveredTile();
    };

    static_assert_cpp98_obj(sizeof(HoveredState) == 480, HoveredState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(HoveredState, false, Address::SHC_3BB0A8C1_0x00F2C7D0) pDAT_HoveredState;

} // namespace UI
} // namespace OpenSHC
