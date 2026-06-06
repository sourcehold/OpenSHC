/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Input/ModifierKeyState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Input {

#pragma pack(push, 1)

    // SIZE: 0x00000018
    class ModifierKeyState {
    public:
        int keyDownUnk; // 0x00000000 length: 4
        int ctrl; // 0x00000004 length: 4
        int shift; // 0x00000008 length: 4
        int alt; // 0x0000000C length: 4
        int downArrow; // 0x00000010 length: 4
        int v; // 0x00000014 length: 4

    private:
        ModifierKeyState(ModifierKeyState const&);
        void operator=(ModifierKeyState const&);

    public:
        ModifierKeyState();
        ~ModifierKeyState();

        // Constructor
        ModifierKeyState* Constructor_ModifierKeyState();

        void updateCtrlShiftAltKeyStateMemory();
    };

    static_assert_cpp98_obj(sizeof(ModifierKeyState) == 24, ModifierKeyState);

#pragma pack(pop)

} // namespace Input
} // namespace OpenSHC
