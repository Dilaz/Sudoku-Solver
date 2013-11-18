#ifndef NUMBERWIDGET_H
#define NUMBERWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include <QSet>
#include <QDebug>

class NumberWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NumberWidget(QWidget *parent = 0);

    void setNum(int num);
    void setUnknown();

    int num() const;
    bool unknown() const;

    void addDisabledNumber(int num);
    void removeDisabledNumber(int num);
    const QSet<int> &disabledNumbers() const;

    bool solved() const;

private:
    QLabel *m_label;
    int m_num;
    bool m_unknown;
    QSet<int> m_disabledNumbers;
    bool m_solved;
signals:
    void clicked(NumberWidget *);
public slots:

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // NUMBERWIDGET_H
