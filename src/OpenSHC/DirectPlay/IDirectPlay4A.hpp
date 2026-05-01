/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/DirectPlay/IDirectPlay4A.hpp'
*/

#pragma once

#include "OpenSHC/DirectPlay/CancelMessage.hpp"
#include "OpenSHC/DirectPlay/Close.hpp"
#include "OpenSHC/DirectPlay/CreatePlayer.hpp"
#include "OpenSHC/DirectPlay/DestroyPlayer.hpp"
#include "OpenSHC/DirectPlay/EnumConnections.hpp"
#include "OpenSHC/DirectPlay/EnumSessions.hpp"
#include "OpenSHC/DirectPlay/GetPlayerAddress.hpp"
#include "OpenSHC/DirectPlay/Open.hpp"
#include "OpenSHC/DirectPlay/QueryInterface.hpp"
#include "OpenSHC/DirectPlay/Receive.hpp"
#include "OpenSHC/DirectPlay/Release.hpp"
#include "OpenSHC/DirectPlay/SendEx.hpp"
#include "OpenSHC/DirectPlay/SetSessionDesc.hpp"
#include "OpenSHC/DirectPlay/lobby/InitializeConnection.hpp"

namespace OpenSHC {
namespace DirectPlay {

    using OpenSHC::DirectPlay::CancelMessage;
    using OpenSHC::DirectPlay::Close;
    using OpenSHC::DirectPlay::CreatePlayer;
    using OpenSHC::DirectPlay::DestroyPlayer;
    using OpenSHC::DirectPlay::EnumConnections;
    using OpenSHC::DirectPlay::EnumSessions;
    using OpenSHC::DirectPlay::GetPlayerAddress;
    using OpenSHC::DirectPlay::Open;
    using OpenSHC::DirectPlay::QueryInterface;
    using OpenSHC::DirectPlay::Receive;
    using OpenSHC::DirectPlay::Release;
    using OpenSHC::DirectPlay::SendEx;
    using OpenSHC::DirectPlay::SetSessionDesc;
    using OpenSHC::DirectPlay::lobby::InitializeConnection;

#pragma pack(push, 1)
    // SIZE: 0x000000D4
    typedef struct IDirectPlay4A {

        QueryInterface* QueryInterface; // 0x00000000 length: 4
        undefined1 padding_0x4[4]; // 0x00000004 length: 4
        Release* Release; // 0x00000008 length: 4
        undefined1 padding_0xc[4]; // 0x0000000C length: 4
        Close* Close; // 0x00000010 length: 4
        undefined1 padding_0x14[4]; // 0x00000014 length: 4
        CreatePlayer* CreatePlayer; // 0x00000018 length: 4
        undefined1 padding_0x1c[8]; // 0x0000001C length: 8
        DestroyPlayer* DestroyPlayer; // 0x00000024 length: 4
        undefined1 padding_0x28[12]; // 0x00000028 length: 12
        EnumSessions* EnumSessions; // 0x00000034 length: 4
        undefined1 padding_0x38[16]; // 0x00000038 length: 16
        GetPlayerAddress* GetPlayerAddress; // 0x00000048 length: 4
        undefined1 padding_0x4c[20]; // 0x0000004C length: 20
        Open* Open; // 0x00000060 length: 4
        Receive* Receive; // 0x00000064 length: 4
        undefined1 padding_0x68[20]; // 0x00000068 length: 20
        SetSessionDesc* SetSessionDesc; // 0x0000007C length: 4
        undefined1 padding_0x80[12]; // 0x00000080 length: 12
        EnumConnections* EnumConnections; // 0x0000008C length: 4
        undefined1 padding_0x90[8]; // 0x00000090 length: 8
        InitializeConnection* InitializeConnection; // 0x00000098 length: 4
        undefined1 padding_0x9c[40]; // 0x0000009C length: 40
        SendEx* SendEx; // 0x000000C4 length: 4
        undefined1 padding_0xc8[4]; // 0x000000C8 length: 4
        CancelMessage* CancelMessage; // 0x000000CC length: 4
        undefined1 padding_0xd0[4]; // 0x000000D0 length: 4

    } IDirectPlay4A;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(IDirectPlay4A) == 212, IDirectPlay4A);
} // namespace DirectPlay
} // namespace OpenSHC
