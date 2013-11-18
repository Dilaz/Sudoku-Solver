#include "sudokusolver.h"
#include "ui_sudokusolver.h"

SudokuSolver::SudokuSolver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SudokuSolver), m_activeWidget(nullptr), m_picker(nullptr)
{
    ui->setupUi(this);

    // Add layout
    QGridLayout *layout = new QGridLayout(this);
    setLayout(layout);

    // Add some boxes
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            NumberWidget *widget = new NumberWidget(this);
            QObject::connect(widget, SIGNAL(clicked(NumberWidget *)), this, SLOT(numberClicked(NumberWidget *)));
            layout->addWidget(widget, y, x);
        }
    }

    // Link them together
    linkNumbers();
}

SudokuSolver::~SudokuSolver()
{
    delete ui;

    // Make sure numberpicker is deleted
    if (m_picker) {
        m_picker->close();
        delete m_picker;
        m_picker = nullptr;
    }
}

void SudokuSolver::linkNumbers()
{
    // Get layout
    QGridLayout *grid = qobject_cast<QGridLayout *>(layout());

    // Loop all widgets
    for (int y = 0; y < 9; y++) {
        for (int x = 0; x < 9; x++) {
            // Get widget by coordinates
            NumberWidget *current = qobject_cast<NumberWidget *>(grid->itemAtPosition(y, x)->widget());

            // Find all widgets in the same row & column
            for (int i = 0; i < 9; i++) {
                // Row
                NumberWidget *widget = qobject_cast<NumberWidget *>(grid->itemAtPosition(y, i)->widget());
                if (widget != current) {
                    QObject::connect(current, SIGNAL(numberChanged(int)), widget, SLOT(addDisabledNumber(int)));
                    QObject::connect(current, SIGNAL(changedToUnknown(int)), widget, SLOT(removeDisabledNumber(int)));
                }

                // Column
                widget = qobject_cast<NumberWidget *>(grid->itemAtPosition(i, x)->widget());
                if (widget != current) {
                    QObject::connect(current, SIGNAL(numberChanged(int)), widget, SLOT(addDisabledNumber(int)));
                    QObject::connect(current, SIGNAL(changedToUnknown(int)), widget, SLOT(removeDisabledNumber(int)));
                }
            }

            // Find all widgets in the same box
            int firstX = 3 * int(x / 3);
            int firstY = 3 * int(y / 3);
            for (int i = 0; i < 9; i++) {
                // Get widget by position
                NumberWidget *widget = qobject_cast<NumberWidget *>(grid->itemAtPosition(firstY + (i / 3), firstX + (i % 3))->widget());

                // Skip current
                if (widget != current) {
                    QObject::connect(current, SIGNAL(numberChanged(int)), widget, SLOT(addDisabledNumber(int)));
                    QObject::connect(current, SIGNAL(changedToUnknown(int)), widget, SLOT(removeDisabledNumber(int)));
                }
            }
        }
    }
}

void SudokuSolver::numberClicked(NumberWidget *widget)
{
    // Widget should not be solved
    if (widget->solved()) {
        return;
    }

    m_activeWidget = widget;
    m_picker = new NumberPicker(widget->disabledNumbers());
    m_picker->move(x() + widget->x(), y() + widget->y());
    QObject::connect(m_picker, SIGNAL(closed(const QString &)), this, SLOT(numberChosen(const QString &)));
    m_picker->show();
}

void SudokuSolver::numberChosen(const QString &str)
{
    // Check that active widget is not already used
    if (!m_activeWidget) {
        return;
    }

    // User wants to set widget to unknown
    if (str == "?") {
        m_activeWidget->setUnknown();
    }

    // Convert string to number
    bool ok = false;
    int num = str.toInt(&ok);

    if (ok) {
        m_activeWidget->setNum(num);
    }

    // Disable numberwidget usage
    m_activeWidget = nullptr;

    // Delete number picker
    QObject::disconnect(m_picker, SIGNAL(closed(QString)), this, SLOT(numberChosen(QString)));
    m_picker->close();
    delete m_picker;
    m_picker = nullptr;
}

void SudokuSolver::resizeEvent(QResizeEvent *event)
{
    QSize size = event->size();
    if (size.width() != size.height()) {
        int max = qMax(size.width(), size.height());
        resize(max, max);
    }
}

void SudokuSolver::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    // Setup painter
    QPainter painter(this);
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::black, Qt::NoBrush));

    // Draw 9 rects to group 3x3 area of numberwidgets
    QGridLayout *grid= qobject_cast<QGridLayout *>(layout());
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {

            // Get first and last widget in rect
            QRect start(grid->itemAtPosition(y * 3, x * 3)->geometry());
            QRect end(grid->itemAtPosition(y * 3 + 2 , x * 3 + 2)->geometry());

            // Draw rect around all of them
            painter.drawRect(start.x(), start.y(), end.x() + end.width() - start.x(), end.y() + end.height() - start.y());
        }
    }
}
