#include "confirmation.h"

#include "commands.h"

namespace cfa533 {
namespace screens {
namespace dialogs {

using namespace crystalfontz::cfa533;

Confirmation::Confirmation(crystalfontz::cfa533::CFA533 *lcd,
                           QObject *parent) :
    QObject(parent),
    m_lcd(lcd),
    m_caption("Confirm?")
{
    lcd->send(send_data_to_lcd(2, 1, "helloworld"));
    lcd->send(send_data_to_lcd(2, 2, "v-Yes   x-No"));
}

QString Confirmation::caption() const
{
    return m_caption;
}

void Confirmation::setCaption(const QString caption)
{
    m_caption = caption;
}

} // dialogs
} // screens
} // cfa533
