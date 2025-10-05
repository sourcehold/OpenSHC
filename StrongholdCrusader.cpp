// StrongholdCrusader.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ViewportRenderState.h"

#pragma optimize("", off)
static ViewportRenderState DAT_ViewportRenderState;


int main(int argc, char** argv)
{
	std::cout << "Hello CMake." << std::endl;

	if (argc > 399) {
		argc = 200;
	}

	BOOL result = DAT_ViewportRenderState.xyAreValid(199, argc);
	std::cout << "The answer is: " << result << " " << sizeof(ViewportRenderState) << std::endl;
	std::cout << "The answer is: " << DAT_ViewportRenderState.translateXYToTile(200, argc) << std::endl;
	std::cout << "The answer is: " << DAT_ViewportRenderState.meth_0x4092e0(200, argc) << std::endl;
	DAT_ViewportRenderState.setupMouseTileXY();
	DAT_ViewportRenderState.setupMouseTileXY2();
	DAT_ViewportRenderState.meth_0x4e5a90();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
