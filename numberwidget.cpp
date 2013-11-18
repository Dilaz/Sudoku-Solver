#include "numberwidget.h"

NumberWidget::NumberWidget(QWidget *parent) :
    QWidget(parent), m_label(new QLabel("?", this)), m_solved(false)
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
    m_num = num;
    m_label->setText(QString::number(num));
}

void NumberWidget::setUnknown()
{
    m_num = -1;
    m_unknown = true;
    m_label->setText("?");
    m_solved = false;
}

int NumberWidget::num() const
{
    return m_num;
}

bool NumberWidget::unknown() const
{
    return m_unknown;
}

void NumberWidget::addDisabledNumber(int num)
{
    // Check if number is already disabled
    if (m_disabledNumbers.contains(num)) {
        return;
    }

    // Add number to list
    m_disabledNumbers.insert(num);

    // Check if widget already have 8 disabled numbers
    if (m_disabledNumbers.size() == 8 && m_unknown) {
        // Check which one is missing
        int i = 1;
        for (; i <= 9; i++) {
            if (!m_disabledNumbers.contains(i)) {
                break;
            }
        }

        // Set current number to the one that is missing
        m_label->setText(QString::number(i));

        // Set color to red
        QPalette palette;
        palette.setColor(QPalette::WindowText,Qt::red);
        m_label->setPalette(palette);

        // Set to solved
        m_solved = true;
    }
}

void NumberWidget::removeDisabledNumber(int num)
{
    // Find number
    for (QSet<int>::Iterator iter = m_disabledNumbers.begin(); iter != m_disabledNumbers.end(); iter++) {
        if (*iter == num) {
            m_disabledNumbers.erase(iter);
            break;
        }
    }

    // Check if this is disabled
    if (m_solved) {
        // Set label palette back to black
        m_label->setPalette(QPalette(QPalette::WindowText,Qt::black));

        // Reset symbol
        setUnknown();
    }
}

const QSet<int> &NumberWidget::disabledNumbers() const
{
    return m_disabledNumbers;
}

bool NumberWidget::solved() const
{
    return m_solved;
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
