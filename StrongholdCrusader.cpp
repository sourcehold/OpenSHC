// StrongholdCrusader.cpp : This file contains the 'main' function. Program
// execution begins and ends there.
//

#include "StructTest.h"
#include "ViewportRenderState.func.h"
#include "ViewportRenderState.h"

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

int main(int argc, char** argv)
{
    std::cout << "Hello CMake." << std::endl;

    if (argc > 399) {
        argc = 200;
    }

    // We might get multiple definition if it appears in other headers, putting it
    // in a anonymous namespace might help
    BOOL result = MACRO_CALL_MEMBER(ViewportRenderState_Func::xyAreValid, ViewportRenderState_Struct::ptr)(100, 100);
    std::cout << "The answer is: " << result << " " << sizeof(ViewportRenderState) << std::endl;
    std::cout << "The answer is: "
              << MACRO_CALL_MEMBER(ViewportRenderState_Func::translateXYToTile, ViewportRenderState_Struct::ptr)(
                     200, argc)
              << std::endl;
    std::cout << "The answer is: "
              << MACRO_CALL_MEMBER(ViewportRenderState_Func::meth_0x4092e0, ViewportRenderState_Struct::ptr)(200, argc)
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add
//   Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project
//   and select the .sln file
