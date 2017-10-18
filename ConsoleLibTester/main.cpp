#include <QCoreApplication>

#include <QDebug>
#include "packet.h"
#include "packethelper.h"

using namespace crystalfontz::cfa533;

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);


    Packet p(Packet::Type::Report, 0, QByteArray());
    QByteArray a;
    a[0] = 8;
    p.setData(a);
    qDebug() << is_valid(p);
    QByteArray s;
    qDebug() << serialize(p, s) << s;


    //QCoreApplication a(argc, argv);
    //return a.exec();
}
