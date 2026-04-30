/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Input/InsertKeyState.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Input {

#pragma pack(push, 1)

    // SIZE: 0x00000008
    class InsertKeyState {
    public:
        int insert; // 0x00000000 length: 4
        int field1_0x4; // 0x00000004 length: 4

    private:
        InsertKeyState(InsertKeyState const&);
        void operator=(InsertKeyState const&);

        InsertKeyState();
        ~InsertKeyState();

    public:
        // Constructor
        InsertKeyState* Constructor_InsertKeyState();
    };

    static_assert_cpp98_obj(sizeof(InsertKeyState) == 8, InsertKeyState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(InsertKeyState, false, Address::SHC_3BB0A8C1_0x00EE239C) pDAT_InsertKeyState;

} // namespace Input
} // namespace OpenSHC
