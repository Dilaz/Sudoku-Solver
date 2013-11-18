#include "clickablelabel.h"

ClickableLabel::ClickableLabel(const QString &text, QWidget *parent) :
    QLabel(text, parent)
{
}

void ClickableLabel::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit(clicked(text()));
}
