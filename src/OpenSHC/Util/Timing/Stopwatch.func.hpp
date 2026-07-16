/**
  path: 'OpenSHC/Util/Timing/Stopwatch.func.hpp'
*/

#include "OpenSHC/Util/Timing/Stopwatch.hpp"
namespace OpenSHC {
namespace Util {
    namespace Timing {
        namespace Stopwatch_Func {

            // Constructor

            MACRO_FUNCTION_RESOLVER(
                Stopwatch* (Stopwatch::*)(), false, Address::SHC_3BB0A8C1_0x0046CEC0, &Stopwatch::Cosntructor_Stopwatch)
            Cosntructor_Stopwatch;

            MACRO_FUNCTION_RESOLVER(void (Stopwatch::*)(), false, Address::SHC_3BB0A8C1_0x0046CED0, &Stopwatch::start)
            start;

            MACRO_FUNCTION_RESOLVER(void (Stopwatch::*)(), false, Address::SHC_3BB0A8C1_0x0046CEF0, &Stopwatch::stop)
            stop;

        } // namespace Stopwatch_Func
    } // namespace Timing
} // namespace Util
} // namespace OpenSHC
