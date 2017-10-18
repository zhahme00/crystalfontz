#include "cfa533.h"

#include <QDebug>
#include <QByteArray>

namespace crystalfontz {
namespace cfa533 {

CFA533::CFA533(QSerialPort &serialPort, QObject *parent) :
    QObject(parent),
    m_serialPort(serialPort)
{
    QObject::connect(&serialPort, &QSerialPort::readyRead, this, &CFA533::onSerialPortReadyRead);
    QObject::connect(&serialPort, &QSerialPort::errorOccurred, this, &CFA533::onSerialPortErrorOccurred);
}

bool CFA533::isReady() const
{
    return m_serialPort.isOpen();
}

bool CFA533::send(const Packet &packet)
{
    if (!is_valid(packet)) {
        qDebug() << "Cannot send invalid packet";
        return false;
    }

    QByteArray bytes;
    if (!cfa533::serialize(packet, bytes)) {
        qDebug() << "Failed to serialize packet";
        return false;
    }

    return m_serialPort.write(bytes) > -1;
}

bool CFA533::open()
{
    if (m_serialPort.isOpen()) {
        return true;
    }

    if (!m_serialPort.open(QSerialPort::ReadWrite)) {
        qWarning() << "Failed to open serial port";
        return false;
    }

    return true;
}

void CFA533::close()
{
    if (m_serialPort.isOpen()) {
        m_serialPort.close();
    }

    m_serialPort.deleteLater();
}

void CFA533::onSerialPortReadyRead()
{
    if (m_serialPort.bytesAvailable() <= 0) {
        return;
    }

    QByteArray bytes = m_serialPort.readAll();
    Q_ASSERT(bytes.length() > 0);
    qDebug() << bytes;

    Packet p;
    if (cfa533::deserialize(bytes, p) && is_valid(p)) {
        qDebug() << "Emitting";
        emit received(p);
    }

//    // Serial port packets can be fragmented so we always queue
//    // inbound bytes before attempting to parse and packetize.
//    m_ingressBytes += bytes;
//    if (m_ingressBytes.length() < 4) {
//        return;
//    }

//    QVector<Packet> packets = packets_from_bytes(m_ingressBytes);
//    foreach(auto p, packets) {
//        emit received(p);
//    }

//    // OLD!!
//    if (!m_ingressBytes.isEmpty()) {
//        m_ingressBytes += bytes;
//    } else {
//        Q_ASSERT(m_ingressBytes.isEmpty());

//        if (bytes.length() < 4) {
//            m_ingressBytes += bytes;
//            qDebug() << "Fragmented packet received";
//            return;
//        }
//    }

//    // All packets are 4 or more bytes.
//    if (m_ingressBytes.length() < 4) {
//        qDebug() << "Packet length still too small";
//        return;
//    }

//    // TODO: proces
//    qDebug() << m_ingressBytes;
//    m_ingressBytes.clear();
}

void CFA533::onSerialPortErrorOccurred(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError) {
        return;
    }

    qWarning() << "Error from serial port" << m_serialPort.portName() << ":" << error;
}

CFA533 *create_instance(QObject *parent, QString port, int baudRate)
{
    // TODO: Consider using & returning shared pointers.
    auto serial = new QSerialPort(port, parent);
    serial->setBaudRate(baudRate);
    return new CFA533(*serial, parent);
}

} // cfa533
} // crystalfontz
