#ifndef CRYSTALFONTZ_CFA533_PACKETHELPER_H
#define CRYSTALFONTZ_CFA533_PACKETHELPER_H

#include "packet.h"

namespace crystalfontz {
namespace cfa533 {

enum class KeyType {
    UpPress = 1,
    DownPress = 2,
    LeftPress = 3,
    RightPress = 4,
    OkPress = 5,
    CancelPress = 6,
    UpRelease = 7
};

// TODO
class PacketHelper
{
public:

private:
    // Static class.
    explicit PacketHelper() = delete;
};

ushort compute_crc(const QByteArray &array);

} // cfa533
} // crystalfontz

#endif // CRYSTALFONTZ_CFA533_PACKETHELPER_H
