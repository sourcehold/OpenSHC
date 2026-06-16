/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/HoveredState.hpp'
*/

#pragma once

#include "OpenSHC/Commands/CommandBuildingType.hpp"
#include "OpenSHC/UI/HoveredStateElement.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Commands::CommandBuildingType;
    using OpenSHC::UI::HoveredStateElement;

#pragma pack(push, 1)

    // SIZE: 0x000001E0
    class HoveredState {
    public:
        HoveredStateElement elements[20]; // 0x00000000 length: 480

    private:
        HoveredState(HoveredState const&);
        void operator=(HoveredState const&);

    public:
        HoveredState() {};
        ~HoveredState() {};

        // Constructor
        HoveredState* Constructor_HoveredState();

        void clearHoveredState();

        void clearInvalidatedHoverStates();

        void createHoverStateElement(int x, int y, CommandBuildingType type, int size, int flag);

        void calculateHoveredTile();
    };

    static_assert_cpp98_obj(sizeof(HoveredState) == 480, HoveredState);

#pragma pack(pop)

} // namespace UI
} // namespace OpenSHC
