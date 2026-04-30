/**
  path: 'OpenSHC/Game/Skirmish/SkirmishLobbySetupStructure.func.hpp'
*/

#include "OpenSHC/Game/Skirmish/SkirmishLobbySetupStructure.hpp"
namespace OpenSHC {
namespace Game {
    namespace Skirmish {
        namespace SkirmishLobbySetupStructure_Func {

            MACRO_FUNCTION_RESOLVER(void (SkirmishLobbySetupStructure::*)(), false, Address::SHC_3BB0A8C1_0x00486C40,
                &SkirmishLobbySetupStructure::commitSkirmishSettings)
            commitSkirmishSettings;

            MACRO_FUNCTION_RESOLVER(void (SkirmishLobbySetupStructure::*)(), false, Address::SHC_3BB0A8C1_0x00490060,
                &SkirmishLobbySetupStructure::restoreSkirmishLobbySetup)
            restoreSkirmishLobbySetup;

        } // namespace SkirmishLobbySetupStructure_Func
    } // namespace Skirmish
} // namespace Game
} // namespace OpenSHC
