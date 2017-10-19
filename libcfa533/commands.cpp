#include "commands.h"

#include <QDebug>

namespace crystalfontz {
namespace cfa533 {

namespace {
const Packet::Type kRequest = Packet::Type::Request;
const QByteArray kEmpty;
const Packet kInvalid;

bool in_bounds(int col, int row) {
    // Applied DeMorgan's theorem to get invert and ORs.
    return !(col < 0 || col > 15 || row < 0 || row > 1);
}
}

Packet ping_command(const QByteArray &data)
{
    return Packet(kRequest, 0x00, data);
}

Packet get_hardware_firmware_version()
{
    return Packet(kRequest, 0x01, kEmpty);
}

Packet clear_lcd_screen()
{
    return Packet(kRequest, 0x06, kEmpty);
}

Packet set_lcd_cursor_position(int col, int row)
{
    if (!in_bounds(col, row)) {
        qDebug() << "Row or col out of bounds";
        return kInvalid;
    }

    QByteArray array;
    array.append((char)col);
    array.append((char)row);
    return Packet(kRequest, 0x0B, array);
}

Packet set_lcd_cursor_style(Cfa533Cursor style)
{
    return Packet(kRequest, 0x0C, QByteArray(1, (char)style));
}

//Packet send_data_to_lcd(int col, int row, const QString &text)
//{
//    if (!in_bounds(col, row)) {
//        qDebug() << "Row or col out of bounds";
//        return kInvalid;
//    }

//    if (text.isNull() || text.isEmpty()) {
//        qDebug() << "Must send 1 or more characters";
//    }

//    const int kMaxTextSize = 16;
//    if (text.length() > kMaxTextSize) {
//        qDebug() << "Text too long, truncating to 16";
//    }

//    QByteArray array;
//    array.append((char)col);
//    array.append((char)row);
//    array.append(text);
//    return Packet(kRequest, 0x1F, array);
//}

Packet send_data_to_lcd(int col, int row, const QByteArray data)
{
    if (!in_bounds(col, row)) {
        qDebug() << "Row or col out of bounds";
        return kInvalid;
    }

    if (data.length() < 1) {
        qDebug() << "Must send 1 or more characters";
        return kInvalid;
    }

    const int kMaxTextSize = 16;
    if (data.length() > kMaxTextSize) {
        qDebug() << "Text too long, truncating to 16";
    }

    QByteArray array;
    array.append((char)col);
    array.append((char)row);
    array.append(data.left(kMaxTextSize));
    Q_ASSERT(array.length() <= 18);
    return Packet(kRequest, 0x1F, array);
}

} // cfa533
} // crystalfontz
