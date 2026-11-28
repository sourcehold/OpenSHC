#include "../../Game.func.hpp"

#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/IO.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_SkMasterDataEntry.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2DataArray.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2Data_Count.hpp"

namespace OpenSHC {
namespace Game {

    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D52A0
    void Skirmish::StoreGameIntoSKMasters(int score)
    {
        BOOLEnum BVar1;
        int iVar2;
        int iVar3;
        int* piVar4;
        SkMasterDataEntry* pSVar5;
        int iVar6;
        SkMasterDataEntry* _ptrSrc;
        SkMasterDataEntry* _ptrDst;
        int _count;
        SkMasterDataEntry* _ptrDst2;
        SkMasterDataEntry* _ptrSrc2;
        BVar1 = MACRO_CALL(Game::Skirmish_Func::StoreCurrentGameIntoTemporarySKMasterEntry)(score);
        if (!BVar1) {}
        _count = -1;
        if (DAT_SkMasters2Data_Count::instance < 1) {
            _count = 0;
        }
        if (DAT_SkMasters2Data_Count::instance < 250) {
            _count = DAT_SkMasters2Data_Count::instance;
        }
        iVar6 = _count;
        if (_count) {
            iVar2 = 0;
            if (0 < DAT_SkMasters2Data_Count::instance) {
                piVar4 = &DAT_SkMasters2DataArray::instance[0].skMasterScore;
                do {
                    iVar6 = iVar2;
                    if (*piVar4 < DAT_SkMasterDataEntry::instance.skMasterScore)
                        break;
                    iVar2 = iVar2 + 1;
                    piVar4 = piVar4 + 764;
                    iVar6 = _count;
                } while (iVar2 < DAT_SkMasters2Data_Count::instance);
            }
            if (iVar6 == -1) {}
        }
        if (iVar6 < DAT_SkMasters2Data_Count::instance) {
            pSVar5 = DAT_SkMasters2DataArray::instance + DAT_SkMasters2Data_Count::instance;
            iVar2 = DAT_SkMasters2Data_Count::instance;
            do {
                if (iVar2 < 249) {
                    _ptrSrc = pSVar5 + -1;
                    _ptrDst = pSVar5;
                    for (iVar3 = 764; iVar3 != 0; iVar3 = iVar3 + -1) {
                        _ptrDst->score = _ptrSrc->score;
                        _ptrSrc = (SkMasterDataEntry*)_ptrSrc->mapName;
                        _ptrDst = (SkMasterDataEntry*)_ptrDst->mapName;
                    }
                }
                iVar2 = iVar2 + -1;
                pSVar5 = pSVar5 + -1;
            } while (iVar6 < iVar2);
        }
        _ptrSrc2 = DAT_SkMasterDataEntry::ptr;
        _ptrDst2 = DAT_SkMasters2DataArray::instance + iVar6;
        for (iVar2 = 764; iVar2 != 0; iVar2 = iVar2 + -1) {
            _ptrDst2->score = _ptrSrc2->score;
            _ptrSrc2 = (SkMasterDataEntry*)_ptrSrc2->mapName;
            _ptrDst2 = (SkMasterDataEntry*)_ptrDst2->mapName;
        }
        if (DAT_SkMasters2Data_Count::instance < 250) {
            DAT_SkMasters2Data_Count::instance = DAT_SkMasters2Data_Count::instance + 1;
        }
        MACRO_CALL(IO_Func::WriteSkMasters2)();
    }

}
}
