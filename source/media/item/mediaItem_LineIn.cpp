
#include <raumkernel/media/item/mediaItem_LineIn.h>

namespace Raumkernel
{
    namespace Media
    {
        namespace Item
        {
            MediaItem_LineIn::MediaItem_LineIn() : MediaItem()
            {
                type = MediaItemType::MIT_LINEIN;
            }

            MediaItem_LineIn::~MediaItem_LineIn()
            {
            }

        }
    }
}

