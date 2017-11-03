// TODO: Append namespace name
#ifndef CONFIRMATION_H
#define CONFIRMATION_H

#include <QObject>
#include "cfa533.h"

// Wondering if this is overkill.
namespace cfa533 {
namespace screens {
namespace dialogs {

class Confirmation : public QObject
{
    Q_OBJECT
public:
    explicit Confirmation(crystalfontz::cfa533::CFA533 &lcd,
                          QObject *parent = nullptr);

    QString caption() const;
    void setCaption(const QString caption);

    void show() const;

signals:
    void accepted();
    void canceled();

public slots:

private:
    crystalfontz::cfa533::CFA533 &m_lcd;
    QString m_caption;

};

} // dialogs
} // screens
} // cfa533

#endif // CONFIRMATION_H
