#include "../../Game.func.hpp"

#include "OpenSHC/Game/Skirmish.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_00eb9b60.hpp"
#include "OpenSHC/Globals/DAT_00ed3124.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2DataArray.hpp"
#include "OpenSHC/Globals/DAT_SkMasters2Data_Count.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/INT_00eb0e44.hpp"
#include "OpenSHC/Globals/INT_00ed2bdc.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00eb0e48.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00eb96d8.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed27f0.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00ed2be0.hpp"

namespace OpenSHC {
namespace Game {

    using DE::SHCDE::eTextSections;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D9400
    void Skirmish::Skirmish_PrepareLeaderboardView()
    {
        char cVar1;
        int iVar2;
        byte bVar3;
        int _index;
        SkMasterDataEntry* puVar7;
        char* pcVar4;
        int _index2;
        SkMasterDataEntry* _pSkMasters_01;
        SkMasterDataEntry* _pSkMasters_02;
        int* piVar5;
        byte bVar6;
        int iVar7;
        SkMasterDataEntry* pSVar8;
        char* pcVar9;
        int _count;
        uint _month;
        uint _year;
        _count = DAT_SkMasters2Data_Count::instance;
        /*
          Phase 1: Initialize visibility filter
         */
        if (0 < DAT_SkMasters2Data_Count::instance) {
            piVar5 = INT_ARRAY_00eb0e48::instance;
            for (_index2 = DAT_SkMasters2Data_Count::instance; _index2 != 0; _index2 = _index2 + -1) {
                *piVar5 = 1;
                piVar5 = piVar5 + 1;
            }
        }
        iVar7 = DAT_00ed3124::instance;
        if (DAT_00ed3124::instance == 1) {
            _index = 0;
            if (0 < _count) {
                _pSkMasters_01 = DAT_SkMasters2DataArray::instance;
                do {
                    if (!_pSkMasters_01->score) {
                        INT_ARRAY_00eb0e48::instance[_index] = 0;
                    }
                    _index = _index + 1;
                    _pSkMasters_01 = _pSkMasters_01 + 1;
                } while (_index < _count);
            }
        } else if ((DAT_00ed3124::instance == 2) && (_index = 0, 0 < _count)) {
            _pSkMasters_02 = DAT_SkMasters2DataArray::instance;
            do {
                if (_pSkMasters_02->score) {
                    INT_ARRAY_00eb0e48::instance[_index] = 0;
                }
                _index = _index + 1;
                _pSkMasters_02 = _pSkMasters_02 + 1;
            } while (_index < _count);
        }
        /*
          Phase 2: Sort column dispatch
         */
        if (DAT_MissionDefinedData::instance.sortColumn < 2) {
            iVar7 = 0;
            DAT_00eb9b60::instance = 0;
            if (DAT_MissionDefinedData::instance.descending == 1) {
                _index = 0;
                if (0 < _count) {
                    do {
                        if (INT_ARRAY_00eb0e48::instance[_index] != 0) {
                            INT_ARRAY_00eb96d8::instance[iVar7] = _index;
                            iVar7 = iVar7 + 1;
                        }
                        _index = _index + 1;
                    } while (_index < _count);
                    DAT_00eb9b60::instance = iVar7;
                }
            } else if ((!DAT_MissionDefinedData::instance.descending) && (0 < _count)) {
                piVar5 = INT_00eb0e44::ptr + _count;
                _index = _count;
                do {
                    _index = _index + -1;
                    if (*piVar5 != 0) {
                        INT_ARRAY_00eb96d8::instance[iVar7] = _index;
                        iVar7 = iVar7 + 1;
                    }
                    piVar5 = piVar5 + -1;
                    _count = _count + -1;
                } while (_count);
                DAT_00eb9b60::instance = iVar7;
            }
        } else {
            if (DAT_MissionDefinedData::instance.sortColumn == 4) {
                _index = 0;
                iVar7 = 0;
                DAT_00eb9b60::instance = 0;
                if (0 < _count) {
                    puVar7 = DAT_SkMasters2DataArray::ptr[0];
                    do {
                        if (INT_ARRAY_00eb0e48::instance[iVar7] != 0) {
                            _year = puVar7->localTimeYear;
                            _month = puVar7->localTimeMonth;
                            INT_ARRAY_00ed27f0::instance[_index] = iVar7;
                            _index = _index + 1;
                            (INT_00ed2bdc::ptr)[_index]
                                = ((_year - 2000) * 0x10 + _month) * 0x20 + puVar7->localTimeDay;
                        }
                        iVar7 = iVar7 + 1;
                        puVar7 = puVar7 + 0x2fc;
                        DAT_00eb9b60::instance = _index;
                    } while (iVar7 < _count);
                }
                MACRO_CALL(Game::Skirmish_Func::Skirmish_SortAIOpponentOrder)(DAT_MissionDefinedData::instance.descending);
            }
            if (DAT_MissionDefinedData::instance.sortColumn == 2) {
                _index = 0;
                DAT_00eb9b60::instance = 0;
                if (iVar7 == 1) {
                    iVar7 = 0;
                    if (0 < _count) {
                        pSVar8 = DAT_SkMasters2DataArray::instance;
                        do {
                            if (INT_ARRAY_00eb0e48::instance[iVar7] != 0) {
                                iVar2 = pSVar8->score;
                                INT_ARRAY_00ed27f0::instance[_index] = iVar7;
                                INT_ARRAY_00ed2be0::instance[_index] = 0x50 - iVar2;
                                _index = _index + 1;
                            }
                            iVar7 = iVar7 + 1;
                            pSVar8 = pSVar8 + 1;
                        } while (iVar7 < _count);
                        DAT_00eb9b60::instance = _index;
                        MACRO_CALL(Game::Skirmish_Func::Skirmish_SortAIOpponentOrder)(DAT_MissionDefinedData::instance.descending);
                    }
                } else {
                    iVar7 = 0;
                    if (0 < _count) {
                        pSVar8 = DAT_SkMasters2DataArray::instance;
                        do {
                            if (INT_ARRAY_00eb0e48::instance[iVar7] != 0) {
                                if (pSVar8->score) {
                                    pcVar4 = MACRO_CALL_MEMBER(
                                        Text::TextManager_Func::getTextStringInGroupAtOffset,
                                        DAT_TextManagerObject::ptr)(
                                        DE::SHCDE::TEXT_TRAIL_NAMES_CRU, pSVar8->score);
                                    pcVar9 = pSVar8->mapName;
                                    do {
                                        cVar1 = *pcVar4;
                                        *pcVar9 = cVar1;
                                        pcVar4 = pcVar4 + 1;
                                        pcVar9 = pcVar9 + 1;
                                        _index = DAT_00eb9b60::instance;
                                        _count = DAT_SkMasters2Data_Count::instance;
                                    } while (cVar1 != '\0');
                                }
                                bVar6 = pSVar8->mapName[0];
                                if ((byte)(bVar6 + 0xbf) < 0x1a) {
                                    bVar6 = bVar6 + 0x20;
                                }
                                bVar3 = pSVar8->mapName[1];
                                if ((byte)(bVar3 + 0xbf) < 0x1a) {
                                    bVar3 = bVar3 + 0x20;
                                }
                                INT_ARRAY_00ed2be0::instance[_index] = ((uint)bVar6 * -0x100 + -1) - (uint)bVar3;
                                INT_ARRAY_00ed27f0::instance[_index] = iVar7;
                                _index = _index + 1;
                                DAT_00eb9b60::instance = _index;
                            }
                            iVar7 = iVar7 + 1;
                            pSVar8 = pSVar8 + 1;
                        } while (iVar7 < _count);
                    }
                }
                MACRO_CALL(Game::Skirmish_Func::Skirmish_SortAIOpponentOrder)(DAT_MissionDefinedData::instance.descending);
            }
            if (DAT_MissionDefinedData::instance.sortColumn == 3) {
                _index = 0;
                iVar7 = 0;
                DAT_00eb9b60::instance = 0;
                if (0 < _count) {
                    piVar5 = &DAT_SkMasters2DataArray::instance[0].gameDurationInMinutes;
                    do {
                        if (INT_ARRAY_00eb0e48::instance[iVar7] != 0) {
                            iVar2 = *piVar5;
                            INT_ARRAY_00ed27f0::instance[_index] = iVar7;
                            INT_ARRAY_00ed2be0::instance[_index] = -1 - iVar2;
                            _index = _index + 1;
                        }
                        iVar7 = iVar7 + 1;
                        piVar5 = piVar5 + 0x2fc;
                        DAT_00eb9b60::instance = _index;
                    } while (iVar7 < _count);
                }
                MACRO_CALL(Game::Skirmish_Func::Skirmish_SortAIOpponentOrder)(DAT_MissionDefinedData::instance.descending);
            }
        }
    }

}
}
