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

            CNSPBA_EXIT_ALTUnk = -10000, // 0x-0002710
            CNSPBA_NEXT_IP_ADDRESSUnk = -1000, // 0x-00003E8
            CNSPBA_GAMESPY_ARCADEUnk = -10, // 0x-000000A
            CNSPBA_SCROLL_DOWNUnk = -2, // 0x-0000002
            CNSPBA_SCROLL_UPUnk = -1, // 0x-0000001
            CNSPBA_EXIT = 3, // 0x00000003
            CNSPBA_HOST_GAME = 7, // 0x00000007
            CNSPBA_JOIN_GAME = 8 // 0x00000008

        } ChooseNetworkServiceProviderButtonActions;

        static_assert_cpp98_obj(
            sizeof(ChooseNetworkServiceProviderButtonActions) == 4, ChooseNetworkServiceProviderButtonActions);
    } // namespace ChooseNetworkServiceProvider
} // namespace UI
} // namespace OpenSHC
