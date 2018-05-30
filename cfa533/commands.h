/**
  * @copyright Copyright (C) 2017 All Rights Reserved
  * @author Zee Ahmed
  * @date   2017/10/14
  * @brief  Helper functions that create Packets to send to the CFA-533.
  */

#ifndef CRYSTALFONTZ_CFA533_COMMANDS_H
#define CRYSTALFONTZ_CFA533_COMMANDS_H

#include <QByteArray>
#include "packet.h"

namespace crystalfontz {
namespace cfa533 {

enum class Cfa533Cursor {
    NoCursor = 0,
    BlinkingBlock,
    Underscore,
    BlinkingUnderscore
};

// Various commands to send to the hardware. Some of the packets are very simple
// and one may wonder why even wrap a method around it.. I think the method names
// add clarity to the type of packet one is constructing.
Packet ping_command(const QByteArray &data);
Packet get_hardware_firmware_version();
Packet store_current_state_as_boot_state();
Packet clear_lcd_screen();
Packet set_lcd_cursor_position(int col, int row);
Packet set_lcd_cursor_style(Cfa533Cursor style);
//Packet send_data_to_lcd(int col, int row, const QString &text);
Packet send_data_to_lcd(int col, int row, const QByteArray data);

} // cfa533
} // crystalfontz

#endif // CRYSTALFONTZ_CFA533_COMMANDS_H
