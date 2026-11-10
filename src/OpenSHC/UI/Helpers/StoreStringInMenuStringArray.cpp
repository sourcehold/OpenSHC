// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_ArrayOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_NumberOfStoredMenuStrings.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DA750
    void Helpers::StoreStringInMenuStringArray(char* textToStore)
    {
        int const maxStrings
            = sizeof(DAT_ArrayOfStoredMenuStrings::instance) / sizeof(DAT_ArrayOfStoredMenuStrings::instance[0]);
        if (DAT_NumberOfStoredMenuStrings::instance >= maxStrings) {
            return;
        }
        if (strlen(textToStore) > sizeof(DAT_ArrayOfStoredMenuStrings::instance[0]) - 1) {
            return;
        }
        strcpy(DAT_ArrayOfStoredMenuStrings::instance[DAT_NumberOfStoredMenuStrings::instance++], textToStore);
    }

}
}
