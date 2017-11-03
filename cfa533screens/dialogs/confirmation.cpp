#include "confirmation.h"

#include "commands.h"

namespace cfa533 {
namespace screens {
namespace dialogs {

using namespace crystalfontz::cfa533;

Confirmation::Confirmation(crystalfontz::cfa533::CFA533 &lcd,
                           QObject *parent) :
    QObject(parent),
    m_lcd(lcd),
    m_caption("Confirm?")
{
    show();
}

QString Confirmation::caption() const
{
    return m_caption;
}

void Confirmation::setCaption(const QString caption)
{
    m_caption = caption;
}

void Confirmation::show() const
{
    m_lcd.send(clear_lcd_screen());
    m_lcd.send(send_data_to_lcd(5, 0, caption().toLocal8Bit()));
    m_lcd.send(send_data_to_lcd(1, 1, "v-Yes x-No"));
}

} // dialogs
} // screens
} // cfa533
