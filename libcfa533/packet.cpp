#include "packet.h"

#include <QDebug>
#include "packethelper.h"

namespace crystalfontz {
namespace cfa533 {

// Is this the optimal way to declare private functions?
namespace {
// Type and command are embedded in the same byte to extracting at the same time.
void extract(const char byte1, Packet::Type &type, int &command)
{
    type = (Packet::Type)(byte1 & 0xC0);
    command = byte1 & 0x3F;
}
}

const int kTotalCommands = 0x23;
const int kMinPacketSize = 4;
const int kMaxDataLength = 18;

Packet::Packet() :
    Packet(Type::Request, -1, QByteArray())
{
}

Packet::Packet(const Packet::Type type, const int command, const QByteArray &data) :
    m_type(type),
    m_command(command),
    m_data(data)
{
}

Packet::Type Packet::type() const
{
    return m_type;
}

void Packet::setType(Packet::Type value)
{
    m_type = value;
}

int Packet::command() const
{
    return m_command;
}

void Packet::setCommand(int value)
{
    if (value < 0) {
        qWarning() << "Invalid assignment" << value
                   << ". command must be 0 <= value <=" << kTotalCommands;
        return;
    }

    m_command = value;
}

QByteArray Packet::data() const
{
    return m_data;
}

void Packet::setData(QByteArray value)
{
    m_data = value;
}

bool serialize(const Packet &packet, QByteArray &array)
{
    if (!is_valid(packet)) {
        qDebug() << "Invalid packet, serialization failed";
        return false;
    }

    const auto dataLength = packet.data().length();
    Q_ASSERT(dataLength <= kMaxDataLength);

    // 1 byte for type and command, 1 byte for data (or payload) length, x bytes of data, 2 bytes for CRC.
    const auto size = 2 + dataLength + 2;
    QByteArray buffer(size, '\0');
    buffer[0] = ((int)packet.type() << 6) | packet.command();
    buffer[1] = dataLength;
    buffer.replace(2, dataLength, packet.data());

    // Last two bytes contain the CRC and are excluded from the computation.
    ushort crc = compute_crc(buffer, size - 2);
    buffer[size - 2] = crc & 0xFF;
    buffer[size - 1] = (crc >> 8) & 0xFF;

    Q_ASSERT(buffer.length() == size);
    array.append(buffer);
    return true;
}

bool deserialize(const QByteArray &array, Packet &packet, bool checkCRC)
{
    Q_UNUSED(checkCRC);

    if (!is_valid(array)) {
        qDebug() << "Byte array is not deserializabe to a packet";
        return false;
    }

    Packet::Type type;
    int command;
    extract(array[0], type, command);
    packet.setType(type);
    packet.setCommand(command);

    const auto length = (int)array[1];
    Q_ASSERT(length >= 0 && length <= kMaxDataLength);
    packet.setData(array.mid(2, (int)array[1]));
    return true;
    //throw std::string("not implemented");
}

bool is_valid(const Packet &packet)
{
    return packet.command() >= 0 && packet.command() <= kTotalCommands
            && packet.data().length() <= kMaxDataLength;
}

bool is_valid(const QByteArray &array)
{
    if (array.length() < 4) {
        qDebug() << "Not enough data to form a packet";
        return false;
    }

    // Currently, there are 35 (0x23) supported commands. The command is embedded
    // inside the first byte along with the type of the packet.
    //
    // Validation can be improved by taking the packet type into consideration as well.
    Packet::Type type;
    int command;
    extract(array[0], type, command);
    if (command > kTotalCommands) {
        qDebug() << "Command type is outside range: 0 <= type <= " << kTotalCommands;
        return false;
    }

    auto dataLength = (int)array[1];
    if (dataLength < 0 || dataLength > kMaxDataLength) {
        qDebug() << "Data length is out of bounds, current size = " << dataLength;
        return false;
    }

    if (array.length() < kMinPacketSize + dataLength) {
        qDebug() << "Packet does not contain enough 'data' bytes";
        return false;
    }

    return true;
}

QDebug operator <<(QDebug debug, const Packet &packet)
{
    debug.nospace() << "Type=" << (int)packet.type()
                    << ", Command=" << packet.command()
                    << ", Data=" << packet.data();
    return debug;
}

} // cfa533
} // crystalfontz
