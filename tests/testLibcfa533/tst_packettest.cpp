#include <QString>
#include <QtTest>
#include "packet.h"

using namespace crystalfontz::cfa533;

class PacketTest : public QObject
{
    Q_OBJECT

public:
    PacketTest() = default;

private Q_SLOTS:
    void testCase1();
};

void PacketTest::testCase1()
{
    Packet p;
    QVERIFY(is_valid(p) == false);
}

QTEST_APPLESS_MAIN(PacketTest)

#include "tst_packettest.moc"
