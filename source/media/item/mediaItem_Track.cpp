
#include <raumkernel/media/item/mediaItem_Track.h>

namespace Raumkernel
{
    namespace Media
    {
        namespace Item
        {
            MediaItem_Track::MediaItem_Track() : MediaItem_Album()
            {
                type = MediaItemType::MIT_TRACK;
                title = "";
                duration = "";
            }

            MediaItem_Track::~MediaItem_Track()
            {
            }

        }
    }
}

