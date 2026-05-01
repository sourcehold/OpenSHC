/**
  path: 'OpenSHC/IO/SettingsFileState.func.hpp'
*/

#include "OpenSHC/IO/SettingsFileState.hpp"
namespace OpenSHC {
namespace IO {
    namespace SettingsFileState_Func {

        MACRO_FUNCTION_RESOLVER(
            void (SettingsFileState::*)(), false, Address::SHC_3BB0A8C1_0x00495A30, &SettingsFileState::readUserConfig)
        readUserConfig;

        MACRO_FUNCTION_RESOLVER(
            void (SettingsFileState::*)(), false, Address::SHC_3BB0A8C1_0x00496400, &SettingsFileState::writeUserConfig)
        writeUserConfig;

        MACRO_FUNCTION_RESOLVER(
            void (SettingsFileState::*)(), false, Address::SHC_3BB0A8C1_0x004D5010, &SettingsFileState::readSkMasters2)
        readSkMasters2;

        MACRO_FUNCTION_RESOLVER(
            void (SettingsFileState::*)(), false, Address::SHC_3BB0A8C1_0x004D5180, &SettingsFileState::writeSkMasters2)
        writeSkMasters2;

    } // namespace SettingsFileState_Func
} // namespace IO
} // namespace OpenSHC
