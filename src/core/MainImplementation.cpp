
#include "MainResolver.h"

#include "StructTest.h"
#include "ViewportRenderState.func.h"
#include "ViewportRenderState.h"
#include "OpenSHC.hpp"

#include "Mss32.h"
#include "binkw32.h"
#include "pklib.h"

#include <iostream>

void MSS_cleanup() { AIL_shutdown(); }

__declspec(noinline) int MSS_auto_cleanup()
{
    atexit(MSS_cleanup);
    return 0;
}

// in theory, our main function also needs to be handled as resolver function, which means, the main-main function would
// need to call it. the entry will then decide if it is a dll, or main, by either providing a main function, or the lua
// entry point

int WINAPI Main::WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
    std::cout << "Hello CMake." << std::endl;

    // We might get multiple definition if it appears in other headers, putting it
    // in a anonymous namespace might help
    BOOL result = MACRO_CALL_MEMBER(ViewportRenderState_Func::xyAreValid, ViewportRenderState_Struct::ptr)(100, 100);
    std::cout << "The answer is: " << result << " " << sizeof(ViewportRenderState) << std::endl;
    std::cout << "The answer is: "
              << MACRO_CALL_MEMBER(ViewportRenderState_Func::translateXYToTile, ViewportRenderState_Struct::ptr)(
                     200, 150)
              << std::endl;
    std::cout << "The answer is: "
              << MACRO_CALL_MEMBER(ViewportRenderState_Func::meth_0x4092e0, ViewportRenderState_Struct::ptr)(200, 150)
              << std::endl;
    MACRO_CALL_MEMBER(ViewportRenderState_Func::setupMouseTileXY, ViewportRenderState_Struct::ptr)();
    MACRO_CALL_MEMBER(ViewportRenderState_Func::setupMouseTileXY2, ViewportRenderState_Struct::ptr)();
    MACRO_CALL_MEMBER(ViewportRenderState_Func::meth_0x4e5a90, ViewportRenderState_Struct::ptr)();

    const HBINK bink = BinkOpen("..\\_original\\binks\\abbot_angry.bik", BINKNOSKIP);
    std::cout << bink->Width << " " << bink->Height << " " << bink->Frames << " " << bink->FrameNum << std::endl;
    BinkClose(bink);

    const int ret = AIL_startup();
    std::cout << ret << std::endl;

    char testText[] = "Hello World";
    unsigned int testTextSize = sizeof(testText);
    unsigned long fakeOldCrc = 0;
    std::cout << crc32_pklib(testText, &testTextSize, &fakeOldCrc) << std::endl;

    return 0;
}
