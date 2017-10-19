/**
  * @copyright  Copyright (C) 2017 All Rights Reserved.
  * @author Zee Ahmed
  * @date   2017/10/16
  * @brief  Abstraction of Crystalfontz CFA-533 LCD hardware.
  */

#ifndef CRYSTALFONTZ_CFA533_CFA533_H
#define CRYSTALFONTZ_CFA533_CFA533_H

#include <QObject>
#include <QSerialPort>
#include <QByteArray>
#include "packet.h"

namespace crystalfontz {
namespace cfa533 {

class CFA533 : public QObject
{
    Q_OBJECT
public:
    explicit CFA533(QString port = "/dev/ttyUSB0", int baudrate = QSerialPort::Baud19200,
                    QObject *parent = nullptr);

    bool isReady() const;
    bool send(const Packet &packet);
    bool open();
    void close();

signals:
    void received(const Packet packet);

private slots:
    void onSerialPortReadyRead();
    void onSerialPortErrorOccurred(QSerialPort::SerialPortError error);

private:
    QSerialPort m_serialPort;
    // Fragmented packets can arrive from the serial port. Fragmented data bytes
    // are queued and processed when all are available.
    QByteArray m_ingressBytes;
};

} // cfa533
} // crystalfontz

#endif // CRYSTALFONTZ_CFA533_CFA533_H
