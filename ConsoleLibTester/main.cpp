/**
  * @copyright Copyright (C) 2017 All Rights Reserved
  * @author Zee Ahmed
  * @date   2017/10/18
  * @brief  Testing cfa533 lcd.
  */

#include <QCoreApplication>

#include <QDebug>
#include "packet.h"
#include "packethelper.h"
#include "cfa533.h"
#include "commands.h"

using namespace crystalfontz::cfa533;

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    QCoreApplication app(argc, argv);

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

    return app.exec();
    lcd.close();
}
