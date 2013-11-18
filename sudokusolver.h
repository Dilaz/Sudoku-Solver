#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <QWidget>
#include <QLayout>
#include <QResizeEvent>
#include <QDebug>
#include "numberwidget.h"
#include "numberpicker.h"

namespace Ui {
class SudokuSolver;
}

class SudokuSolver : public QWidget
{
    Q_OBJECT

public:
    explicit SudokuSolver(QWidget *parent = 0);
    ~SudokuSolver();

private:
    void linkNumbers();

    Ui::SudokuSolver *ui;

    NumberWidget *m_activeWidget;
    NumberPicker *m_picker;

private slots:
    void numberClicked(NumberWidget *widget);
    void numberChosen(const QString &str);

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // SUDOKUSOLVER_H
