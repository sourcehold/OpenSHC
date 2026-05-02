/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/IO/SettingsFileState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace IO {

#pragma pack(push, 1)

    // SIZE: 0x00000002
    class SettingsFileState {
    public:
        undefined1 padding_0x0[2]; // 0x00000000 length: 2

    private:
        SettingsFileState(SettingsFileState const&);
        void operator=(SettingsFileState const&);

        SettingsFileState();
        ~SettingsFileState();

    public:
        void readUserConfig();

        void writeUserConfig();

        void readSkMasters2();

        void writeSkMasters2();
    };

    static_assert_cpp98_obj(sizeof(SettingsFileState) == 2, SettingsFileState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(SettingsFileState, false, Address::SHC_3BB0A8C1_0x00EE109A) pDAT_SettingsFileState;

} // namespace IO
} // namespace OpenSHC
