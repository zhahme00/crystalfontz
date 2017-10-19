/**
  * @copyright Copyright (C) 2017 All Rights Reserved
  * @author Zee Ahmed
  * @date   2017/10/15
  * @brief  Helper functions for Packets.
  */

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

ushort compute_crc(const QByteArray &array, int len = -1);
int packet_length(const Packet &packet);
bool is_reseponse(const Packet &request, const Packet &response);

} // cfa533
} // crystalfontz

#endif // CRYSTALFONTZ_CFA533_PACKETHELPER_H
