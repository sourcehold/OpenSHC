/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/Bink/BinkDrawingSurface.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Rendering {
    namespace Bink {
        typedef enum BinkDrawingSurface {

            BDS_GameSurface = 0, // 0x00000000
            BDS_MapSurface = 1 // 0x00000001

        } BinkDrawingSurface;

        static_assert_cpp98_obj(sizeof(BinkDrawingSurface) == 4, BinkDrawingSurface);
    } // namespace Bink
} // namespace Rendering
} // namespace OpenSHC
