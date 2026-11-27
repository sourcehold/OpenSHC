#include "../UserTextHandler.func.hpp"

namespace OpenSHC {
namespace Text {

    /*
      Returns the font size for the currently active text slot (textArrayIndex) from   textArrayFontSizes. Pure getter
      with no side effects.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00469860
    int UserTextHandler::getCurrentFontSize() { return this->textArrayFontSizes[this->textArrayIndex]; }

}
}
