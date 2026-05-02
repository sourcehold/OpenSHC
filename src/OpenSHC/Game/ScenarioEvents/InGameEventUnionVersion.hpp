/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/ScenarioEvents/InGameEventUnionVersion.hpp'
*/

#pragma once

#include "OpenSHC/Game/ScenarioEvents/InGameEventUnion.hpp"
#include "OpenSHC/Game/ScenarioEvents/IngameEventHeader.hpp"
#include "OpenSHC/Game/ScenarioEvents/ScenarioEventCondition.hpp"

namespace OpenSHC {
namespace Game {
    namespace ScenarioEvents {

        using OpenSHC::Game::ScenarioEvents::IngameEventHeader;
        using OpenSHC::Game::ScenarioEvents::InGameEventUnion;
        using OpenSHC::Game::ScenarioEvents::ScenarioEventCondition;

#pragma pack(push, 1)

        // SIZE: 0x000000E4
        class InGameEventUnionVersion {
        public:
            IngameEventHeader header; // 0x00000000 length: 16
            InGameEventUnion data; // 0x00000010 length: 212

        private:
            InGameEventUnionVersion(InGameEventUnionVersion const&);
            void operator=(InGameEventUnionVersion const&);

            InGameEventUnionVersion();
            ~InGameEventUnionVersion();

        public:
            undefined4 resetEvent();

            ScenarioEventCondition* initializeScenarioEvent();
        };

        static_assert_cpp98_obj(sizeof(InGameEventUnionVersion) == 228, InGameEventUnionVersion);

#pragma pack(pop)

    } // namespace ScenarioEvents
} // namespace Game
} // namespace OpenSHC
