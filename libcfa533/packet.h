/**
  * @author Zee Ahmed
  * @date   2017/10/15
  * @brief Encapsulates data sent and received from a Crystalfontz CFA533 LCD (hardware).
  */

#ifndef CRYSTALFONTZ_CFA533_PACKET_H
#define CRYSTALFONTZ_CFA533_PACKET_H

#include <QByteArray>

namespace crystalfontz {
namespace cfa533 {

class Packet
{
public:
    enum class Type {
        Request = 0,
        Response,
        Report,
        Error
    };

    explicit Packet();
    explicit Packet(const Type type, const int command, const QByteArray &data);

    Type type() const;
    void setType(Type value);

    int command() const;
    void setCommand(int value);

    QByteArray data() const;
    void setData(QByteArray value);

private:
    Type m_type;
    int m_command;
    QByteArray m_data;

};

// Serializes packet with crc, i.e., array will contain packet plus 2 bytes of CRC.
bool serialize(const Packet &packet, QByteArray &array);
bool deserialize(const QByteArray &array, Packet &packet);
bool is_valid(const Packet &packet);

} // cfa533
} // crystalfontz

#endif // CRYSTALFONTZ_CFA533_PACKET_H
