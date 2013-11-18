#ifndef NUMBERPICKER_H
#define NUMBERPICKER_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QMap>

#include "clickablelabel.h"

class NumberPicker : public QDialog
{
    Q_OBJECT
public:
    explicit NumberPicker(const QMap<int, int> &disabled);

signals:
    void closed(const QString &);
public slots:

private slots:
    void labelClicked(const QString &str);

};

#endif // NUMBERPICKER_H
