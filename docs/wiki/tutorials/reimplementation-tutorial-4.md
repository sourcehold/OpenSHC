## Tutorial 4: debugging, investigating, and logging

This tutorial does not directly provide information about how to reimplement.
Instead, it shows other abilities of the OpenSHC resolver approach.  
This tutorial assumes you have read the other tutorials and have a general grasp of what a function resolver is.

#### Step 0: Have a working UCP3 setup that can load OpenSHC

This tutorial will not detail how to install the UCP3.
However, after the installation, the following things need to be performed:
1. The UCP3 needs to be configured to start in development mode.
2. The "OpenSHC.dll.deploy" target of "OpenSHC" needs to be run at least once to setup the UCP3 module.
3. Use the UCP3 GUI to activate the OpenSHC module.

### Debugging

The resolver approach allows to activate specific functions in DLL mode.
The actual functions in the game are then detoured to the functions in the DLL,
which allows to debug the own implementation and see how the game behaves.

#### Step 1: Make OpenSHC debuggable

This depends largely on your environment. Two IDEs where tested successfully:

- Visual Studio
- Visual Studio Code

The repository contains a Visual Studio Code setup that already provides a debug target for OpenSHC using the `_original`
folder that should be created during project setup. This task is called "Debug OpenSHC.dll".  
A setup for other environments needs to be created manually.

The environment needs to roughly perform the following steps:

1. "Build" the "OpenSHC.dll.deploy" target with the "Debug" preset.
2. Launch "Stronghold Crusader.exe".
3. Have the environment attach to the DLL.

Step 2 and 3 can usually be configured to be performed together.

If everything is successful, you usually end up in the debugging view of your IDE.
However. without anything active, there is not much to debug yet.

#### Step 2: Debug a function

It is recommended to already have implemented the function to 100% before you debug it, at least,
if the intention is to analyze runtime behavior. Then, two steps need to be performed:

- Make sure the cpp-file of the function is compiled in by placing it in either the main or the local "openshc-sources.txt".
Recommended for tests is the local version.
- Set the function resolver to use the own implementation. This of course requires the specific `.func.hpp` header of the function to be included.

For example:


{lineno-start=1}
```cpp
MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(SHC_SoundStreamInt, int), false,
    Address::SHC_3BB0A8C1_0x00479AF0, &SoundSystem::setStreamAndSampleVolumeUnk)
setStreamAndSampleVolumeUnk;
```

would be set to


{lineno-start=1}
```cpp
MACRO_FUNCTION_RESOLVER(void (SoundSystem::*)(SHC_SoundStreamInt, int), true,
    Address::SHC_3BB0A8C1_0x00479AF0, &SoundSystem::setStreamAndSampleVolumeUnk)
setStreamAndSampleVolumeUnk;
```

After this you should be able to place a breakpoint in the implemented function, launch the game like configured in step 1
and check around until the breakpoint is hit.

#### Step 3: Make debugging easier

Without any modifications, the game actually runs in a non-shared fullscreen mode that even changes the resolution.
Additionally, it has special handling when it loses focus, interrupting the current logic of the game.
This makes debugging a lot harder. There are currently two known workarounds, although in both cases it is recommended
to not have the IDE over your game window.

##### Graphics API Replacer

This module comes with the UCP3 and can modify the way the game is displayed.
Recommended is to set the game to a windowed mode and set the losing focus behavior to "Continue and Render".
This way, the game will just keep on running if the focus is lost, and will not stop or minimize itself.

The downside is, that the game is directly modified. This can cause unexpected behavior should the reimplemented
function effect a function modified by the module. Rule of thumb is to not do this for functions that interact with
rendering, mouse input or focus switching.

##### DXWnd

[This program](https://sourceforge.net/projects/dxwnd/) can be used to run old games in window modes.
Naturally, it some options need to be set, and even then it has some issues. However, there are workarounds.

1. Options -> Extended Mode
2. Edit -> Add -> Select "Stronghold Crusader.exe"
3. Right click on Icon -> Modify options

The following options need to be set to have a relatively smooth experience. Leave the other options as they are:

- Main -> Activate "Do not modify on task switch" and "No banner"
- Video -> Set "Window style" to "thick frame"
- Directx -> Renderer to "D3D9" and VSync to "ON" and "WaitForVerticalBlank"
- Compat. -> Activate "Win Insulation"

This should already produce a window similar to the Graphics API Replacer.
However, make sure the game is set to the resolution in "Main" before.

One issue remains, though. SHC uses the "GetCursorPos" API to handle the scrolling.
No workaround is yet known to deactivate the scrolling outside the games box, but we can use a trick:

- Mouse -> Deactivate "Correct Mouse Position"
- Video -> Select "Native", activate "Initial" and set the resolution to something big, for example your monitor resolution.

This should still launch the game in window mode with the click positions working, but the scroll border will be the monitor border.

This method is recommended over the Graphics API Replacer in all cases where it can not be guaranteed
that the current function does not interfere with rendering.

### Log Wrapper

The function resolver has yet another ability. It can be used to log calls to a function.
This can be useful if debugging is to invasive, or you just want to check the pattern of calls.
It supports all but one of the function types the resolver supports: Variadic functions can not be wrapped.
Note, that only implemented functions can be properly wrapped.
Activating the logging for an unimplemented function will only log calls made from implemented functions to it.

#### Step 1: Activate logging wrapper

The wrapping requires a different macro. The following example from above was extended to also wrap the function:


{lineno-start=1}
```cpp
MACRO_FUNCTION_RESOLVER_EXT(void (SoundSystem::*)(SHC_SoundStreamInt, int), true,
    Address::SHC_3BB0A8C1_0x00479AF0, &SoundSystem::setStreamAndSampleVolumeUnk, FunctionResolver::Option::USE_WRAPPER)
setStreamAndSampleVolumeUnk;
```

#### Step 2: Activate the proper logging level

Function resolver hooking logs are written as "DEBUG" logs. To see the wrapper logs, however, the logging needs to be 
set to "VERBOSE". This is already configured for the Visual Studio Code debug setup, which starts the game with the 
flags `--ucp-verbosity 2 --ucp-console-verbosity 2`. Other setups need to find a way to provide these flags.

Launching the game now should produce the specific logs whenever the function is called.

#### Step 3: Consider what you wrap

Some functions are called an enormous amount of times per frame. This can result in the game seemingly freezing, while
giant log files are written (if file log is active). So always check via debugging first if the function is often called.
