/**
  path: 'OpenSHC/UI/UCPointerStruct.func.hpp'
*/

#include "OpenSHC/UI/UCPointerStruct.hpp"
namespace OpenSHC {
namespace UI {
    namespace UCPointerStruct_Func {

        MACRO_FUNCTION_RESOLVER(void (UCPointerStruct::*)(int, int*, int*, ushort*, int), false,
            Address::SHC_3BB0A8C1_0x004F4D70, &UCPointerStruct::loadMenuElement)
        loadMenuElement;

    } // namespace UCPointerStruct_Func
} // namespace UI
} // namespace OpenSHC
