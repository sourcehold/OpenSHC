/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/ChooseNetworkServiceProvider/ChooseNetworkServiceProviderButtonActions.hpp'
*/

#pragma once

namespace OpenSHC {
namespace UI {
    namespace ChooseNetworkServiceProvider {
        typedef enum ChooseNetworkServiceProviderButtonActions {

            CNSPBA_EXIT = 3, // 0x00000003
            CNSPBA_HOST_GAME = 7, // 0x00000007
            CNSPBA_JOIN_GAME = 8 // 0x00000008

        } ChooseNetworkServiceProviderButtonActions;

        static_assert_cpp98_obj(
            sizeof(ChooseNetworkServiceProviderButtonActions) == 4, ChooseNetworkServiceProviderButtonActions);
    } // namespace ChooseNetworkServiceProvider
} // namespace UI
} // namespace OpenSHC
