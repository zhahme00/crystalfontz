/**
  * @copyright Copyright (C) 2017 All Rights Reserved
  * @author Zee Ahmed
  * @date   2017/10/18
  * @brief  Testing cfa533 lcd.
  */

#include <QCoreApplication>

#include <QObject>
#include <QDebug>
#include <QByteArray>
#include "packet.h"
#include "packethelper.h"
#include "cfa533.h"
#include "commands.h"

#include "dialogs/confirmation.h"

using namespace crystalfontz::cfa533;
using namespace cfa533::screens::dialogs;

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    QCoreApplication app(argc, argv);

    // Display something on the hardware directly.
    CFA533 lcd;
    QObject::connect(&lcd, &CFA533::received, [](const Packet &p) {
        qDebug() << p;
    });
    lcd.open();
    lcd.send(get_hardware_firmware_version());
    lcd.send(ping_command("Hello world.."));
    lcd.send(clear_lcd_screen());
    lcd.send(set_lcd_cursor_position(12, 0));
    lcd.send(set_lcd_cursor_style(Cfa533Cursor::BlinkingUnderscore));
    lcd.send(send_data_to_lcd(2, 0, "testing..."));
    lcd.send(store_current_state_as_boot_state());


    // Display scrolling text on to the hardware implicitly.
//    screen::Scrolling sc1;
//    sc1.line1 = "a very long long long long line";
//    sc1.line2 = "a short line";
//    sc1.setLines(QStringList() << "a long line 1"
//                 << "Another line"
//                 << "Some more lines"
//                 << "one last line");
//    Confirmation confirm(lcd, nullptr);
//    confirm.setCaption("OK?");
//    confirm.show();


    return app.exec();
    lcd.close();
}
