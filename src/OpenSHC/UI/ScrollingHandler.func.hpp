/**
  path: 'OpenSHC/UI/ScrollingHandler.func.hpp'
*/

#include "OpenSHC/UI/ScrollingHandler.hpp"
namespace OpenSHC {
namespace UI {
    namespace ScrollingHandler_Func {

        MACRO_FUNCTION_RESOLVER(
            void (ScrollingHandler::*)(), false, Address::SHC_3BB0A8C1_0x00468AD0, &ScrollingHandler::handleScrolling)
        handleScrolling;

        MACRO_FUNCTION_RESOLVER(int (ScrollingHandler::*)(), false, Address::SHC_3BB0A8C1_0x00468C30,
            &ScrollingHandler::getScrollDistanceBaseUnk)
        getScrollDistanceBaseUnk;

    } // namespace ScrollingHandler_Func
} // namespace UI
} // namespace OpenSHC
