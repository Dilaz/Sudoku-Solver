#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <QWidget>

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
    Ui::SudokuSolver *ui;
};

#endif // SUDOKUSOLVER_H
