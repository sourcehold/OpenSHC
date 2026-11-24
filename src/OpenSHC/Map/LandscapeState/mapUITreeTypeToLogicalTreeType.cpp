#include "../../Map.func.hpp"
#include "../LandscapeState.func.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F1A60
    undefined4 LandscapeState::mapUITreeTypeToLogicalTreeType(undefined4 param_1)
    {
        switch (param_1) {
        case 0x28:
            return (undefined4)(1);
        case 0x29:
            return (undefined4)(2);
        case 0x2a:
            return (undefined4)(3);
        case 0x2b:
            return (undefined4)(4);
        default:
            return (undefined4)(0);
        case 0x82:
            return (undefined4)(5);
        case 0x83:
            return (undefined4)(6);
        case 0x84:
            return (undefined4)(7);
        case 0x85:
            return (undefined4)(8);
        case 0x86:
            return (undefined4)(9);
        case 0x87:
            return (undefined4)(10);
        case 0x88:
            return (undefined4)(0xb);
        case 0x89:
            return (undefined4)(0xc);
        case 0x8a:
            return (undefined4)(0xd);
        case 0x8b:
            return (undefined4)(0xe);
        case 0x99:
            return (undefined4)(0x10);
        case 0x9a:
            return (undefined4)(0x11);
        case 0x9b:
            return (undefined4)(0x12);
        case 0x9c:
            return (undefined4)(0x13);
        }
    }

}
}
