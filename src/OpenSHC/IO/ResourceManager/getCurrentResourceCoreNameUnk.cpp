#include "../ResourceManager.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentResourceCoreName.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471D30
    char* ResourceManager::getCurrentResourceCoreNameUnk()
    {
        char const* _resourceName = MACRO_CALL_MEMBER(ResourceManager_Func::getFileNameOfCurrentActiveResource, this)();
        int basenameEnd = strlen(_resourceName);
        DAT_CurrentResourceCoreName::instance[0] = '\0';

        for (int basenameStart = basenameEnd + -1; basenameStart >= 0; --basenameStart) {
            if (_resourceName[basenameStart] == '.') {
                basenameEnd = basenameStart;
            }
            if (_resourceName[basenameStart] != '\\') {
                continue;
            }
            ++basenameStart;
            int basenameLength = 0;
            if (basenameStart < basenameEnd) {
                basenameLength = basenameEnd - basenameStart;
                for (int i = basenameStart; i < basenameEnd; ++i) {
                    DAT_CurrentResourceCoreName::instance[i - basenameStart] = _resourceName[i];
                }
            }
            DAT_CurrentResourceCoreName::instance[basenameLength] = '\0';
            break;
        }
        return DAT_CurrentResourceCoreName::instance;
    }

} // namespace IO
} // namespace OpenSHC
