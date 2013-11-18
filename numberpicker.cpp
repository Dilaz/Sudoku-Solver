#include "numberpicker.h"

NumberPicker::NumberPicker(QWidget *parent) :
    QWidget(parent)
{
    // Add layout
    QGridLayout *layout = new QGridLayout(this);
    setLayout(layout);

    // Add numbers
    for (int i = 0; i < 9; i++) {
        layout->addWidget(new QLabel(QString::number(i + 1), this), i / 3, i % 3);
    }
}
