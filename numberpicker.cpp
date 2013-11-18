#include "numberpicker.h"

NumberPicker::NumberPicker(const QSet<int> &disabled) :
    QDialog(nullptr, Qt::Dialog)
{
    // Add layout
    QGridLayout *layout = new QGridLayout(this);
    setLayout(layout);

    // Add numbers
    for (int i = 0; i < 9; i++) {
        ClickableLabel *label = new ClickableLabel(QString::number(i + 1), this);
        label->setFont(QFont("Arial", 20));
        layout->addWidget(label, i / 3, i % 3);

        // Check if number is in disabled numbers
        if (disabled.contains(i + 1)) {
            // Disable current label
            label->setDisabled(true);
        }

        // Connect signal
        QObject::connect(label, SIGNAL(clicked(const QString &)), this, SLOT(labelClicked(const QString &)));
    }

    // Add undefined
    ClickableLabel *label = new ClickableLabel("?", this);
    label->setFont(QFont("Arial", 20));
    layout->addWidget(label, 3, 1);
    QObject::connect(label, SIGNAL(clicked(const QString &)), this, SLOT(labelClicked(const QString &)));

    // Set window to fixed size
    setFixedSize(sizeHint());
    setWindowFlags(Qt::CustomizeWindowHint | Qt::Dialog);
    setModal(true);
}

void NumberPicker::labelClicked(const QString &str)
{
    emit(closed(str));
}
