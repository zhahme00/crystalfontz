#include "packet.h"

#include <QDebug>
#include "packethelper.h"

namespace crystalfontz {
namespace cfa533 {

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
        qWarning() << "Invalid assignment" << value << ". command must be >= 0";
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

bool is_valid(const Packet &packet)
{
    return packet.command() >= 0 && packet.data().length() > 0;
}

bool serialize(const Packet &packet, QByteArray &array)
{
    if (!is_valid(packet)) {
        qDebug() << "Invalid packet, serialization failed";
        return false;
    }

    const auto dataLength = packet.data().length();
    Q_ASSERT(dataLength > 0);

    // 1 byte for type and command, 1 byte for data (or payload) length, 2 bytes for CRC.
    const auto size = 2 + dataLength + 2;
    QByteArray buffer(size, '\0');
    buffer[0] = ((int)packet.type() << 6) | packet.command();
    buffer[1] = dataLength;
    buffer.replace(2, dataLength, packet.data());

    // Last two bytes contain the CRC.
    ushort crc = compute_crc(buffer);
    buffer[size - 2] = crc & 0xFF;
    buffer[size - 1] = crc >> 8;

    Q_ASSERT(buffer.length() == size);
    array.append(buffer);
    return true;
}

bool deserialize(const QByteArray &array, Packet &packet)
{
    if (array.length() < 5) {
        qDebug() << "Failed to deserialize as byte array does not have enough bytes";
        return false;
    }

    throw std::string("not implemented");
}

} // cfa533
} // crystalfontz
