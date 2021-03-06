#include "joycontrolstickpushbutton.h"

JoyControlStickPushButton::JoyControlStickPushButton(JoyControlStick *stick, bool displayNames, QWidget *parent) :
    FlashButtonWidget(displayNames, parent)
{
    this->stick = stick;

    refreshLabel();

    connect(stick, SIGNAL(active(int, int)), this, SLOT(flash()));
    connect(stick, SIGNAL(released(int, int)), this, SLOT(unflash()));
    connect(stick, SIGNAL(stickNameChanged()), this, SLOT(refreshLabel()));
}

JoyControlStick* JoyControlStickPushButton::getStick()
{
    return stick;
}

QString JoyControlStickPushButton::generateLabel()
{
    QString temp;
    if (!stick->getStickName().isEmpty() && displayNames)
    {
        temp.append(stick->getPartialName(false, true));
    }
    else
    {
        temp.append(stick->getPartialName(false));
    }

    return temp;
}

void JoyControlStickPushButton::disableFlashes()
{
    disconnect(stick, SIGNAL(active(int, int)), this, SLOT(flash()));
    disconnect(stick, SIGNAL(released(int, int)), this, SLOT(unflash()));
    this->unflash();
}

void JoyControlStickPushButton::enableFlashes()
{
    connect(stick, SIGNAL(active(int, int)), this, SLOT(flash()));
    connect(stick, SIGNAL(released(int, int)), this, SLOT(unflash()));
}
