/**
  * @copyright  Copyright (C) 2017 All Rights Reserved.
  * @author Zee Ahmed
  * @date   2017/10/15
  * @brief  Encapsulates data sent and received from a Crystalfontz CFA533 LCD (hardware).
  */

#ifndef CRYSTALFONTZ_CFA533_PACKET_H
#define CRYSTALFONTZ_CFA533_PACKET_H

#include <QByteArray>
#include <QLoggingCategory>

namespace crystalfontz {
namespace cfa533 {

// This header file is referenced by almost all the other files in this
// project. So it seemed like a good (or central) place to declare the
// logging category.
Q_DECLARE_LOGGING_CATEGORY(cfa533logging)

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
bool deserialize(const QByteArray &array, Packet &packet, bool checkCRC = false);
bool is_valid(const Packet &packet);
bool is_valid(const QByteArray &array);

QDebug operator <<(QDebug debug, const Packet &packet);

} // cfa533
} // crystalfontz

#endif // CRYSTALFONTZ_CFA533_PACKET_H
