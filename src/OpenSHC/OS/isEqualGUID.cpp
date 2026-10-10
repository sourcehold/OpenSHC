#include "../OS.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {

using WindowsHelper::Enums::BOOLEnum;

/*
  Library Function - Multiple Matches With Different Base Names   Name: ??8@YAHABU_GUID@@0@Z,
  ?IsEqualGUID@@YAHABU_GUID@@0@Z   Library: Visual Studio 2005 Release   decompilerscript: committed: 2025-01-30
  21:57:43.216000
 */
// FUNCTION: STRONGHOLDCRUSADER 0x0047C5D0
BOOLEnum OS::isEqualGUID(GUID* param_1, GUID* param_2)
{
    bool bVar1;
    uint uVar3 = 0x10;
    do {
        if (param_1->Data1 != param_2->Data1)
            goto LAB_0047c5f8;
        uVar3 = uVar3 - 4;
        param_2 = (GUID*)&param_2->Data2;
        param_1 = (GUID*)&param_1->Data2;
    } while (3 < uVar3);
    if (!uVar3) {
    LAB_0047c65f:
        bVar1 = false;
    } else {
    LAB_0047c5f8:
        int iVar2 = (uint)(byte)param_1->Data1 - (uint)(byte)param_2->Data1;
        if (!iVar2) {
            if (uVar3 == 1)
                goto LAB_0047c65f;
            iVar2 = (uint) * (byte*)((int)&param_1->Data1 + 1) - (uint) * (byte*)((int)&param_2->Data1 + 1);
            if (!iVar2) {
                if (uVar3 == 2)
                    goto LAB_0047c65f;
                iVar2 = (uint) * (byte*)((int)&param_1->Data1 + 2) - (uint) * (byte*)((int)&param_2->Data1 + 2);
                if (!iVar2) {
                    if (uVar3 == 3
                        || (iVar2
                            = (uint) * (byte*)((int)&param_1->Data1 + 3) - (uint) * (byte*)((int)&param_2->Data1 + 3),
                            iVar2 == 0))
                        goto LAB_0047c65f;
                }
            }
        }
        bVar1 = true;
        if (iVar2 < 1) {
            return FALSE;
        }
    }
    return (uint)!bVar1;
}

}
