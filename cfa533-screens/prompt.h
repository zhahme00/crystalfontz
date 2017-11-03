#ifndef CFA533_SCREENS_PROMPT_H
#define CFA533_SCREENS_PROMPT_H

#include <QObject>

namespace cfa533 {
namespace screens {

class Prompt : public QObject
{
    Q_OBJECT
public:
    explicit Prompt(QObject *parent = nullptr);

signals:

public slots:
};

} // screens
} // cfa533

#endif // CFA533_SCREENS_PROMPT_H
