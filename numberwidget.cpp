#include "numberwidget.h"

NumberWidget::NumberWidget(QWidget *parent) :
    QWidget(parent), m_label(new QLabel(DEFAULT_CHAR, this)), m_num(-1), m_unknown(true), m_solved(false)
{
    // Add laout
    setLayout(new QVBoxLayout(this));

    // Add label
    m_label->setFont(QFont("Arial", 20));
    m_label->setAlignment(Qt::AlignCenter);
    layout()->addWidget(m_label);
}

void NumberWidget::setNum(int num)
{
    // Check if this already had a number
    if (!m_unknown) {
        // Set it to unknown first
        setUnknown();
    }

    // Set number
    m_num = num;
    m_unknown = false;
    m_label->setText(QString::number(num));

    // Emit signal
    emit(numberChanged(num));
}

void NumberWidget::setUnknown()
{
    m_unknown = true;
    m_label->setText(DEFAULT_CHAR);
    m_solved = false;

    // Emit signal
    emit(changedToUnknown(m_num));

    m_num = -1;
}

int NumberWidget::num() const
{
    return m_num;
}

bool NumberWidget::unknown() const
{
    return m_unknown;
}


const QMap<int, int> &NumberWidget::disabledNumbers() const
{
    return m_disabledNumbers;
}

bool NumberWidget::solved() const
{
    return m_solved;
}

void NumberWidget::addDisabledNumber(int num)
{
    qDebug() << "Change number " << num <<  " from " << m_disabledNumbers[num];
    // Add number to list
    m_disabledNumbers[num]++;
    qDebug() << " to " << m_disabledNumbers[num];

    // Check if widget already have 8 disabled numbers
    int found = 0;
    int lastEmpty = 0;
    for (int i = 1; i <= 9; i++) {
        if (m_disabledNumbers[i] != 0) {
            found++;
        }
        else {
            lastEmpty = i;
        }
    }

    if (found == 8 && m_unknown) {
        // Set current number to the one that is missing
        m_label->setText(QString::number(lastEmpty));

        // Set color to red
        QPalette palette;
        palette.setColor(QPalette::WindowText, Qt::red);
        m_label->setPalette(palette);

        // Set to solved
        m_solved = true;
        m_unknown = false;

        // Set number
        setNum(lastEmpty);
    }
}

void NumberWidget::removeDisabledNumber(int num)
{
    // Reduce number
    qDebug() << "Change number " << num <<  " from " << m_disabledNumbers[num];
    m_disabledNumbers[num]--;
    qDebug() << " to " << m_disabledNumbers[num];

    // Check if this is solved
    if (m_solved) {
        // Set label palette back to black
        QPalette palette;
        palette.setColor(QPalette::WindowText, Qt::black);
        m_label->setPalette(palette);

        // Reset symbol
        setUnknown();
    }
}


void NumberWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::color1));
    painter.setBrush(QBrush(Qt::black, Qt::NoBrush));
    QRect rect = event->rect();
    painter.drawRect(0, 0, rect.width() - 1, rect.height() - 1);
}

void NumberWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit(clicked(this));
}
