#ifndef NUMBERWIDGET_H
#define NUMBERWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include <QMap>
#include <QTimer>
#include <QDebug>

static const QString DEFAULT_CHAR("?");

class NumberWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NumberWidget(QWidget *parent = 0);

    void setNum(int num);
    void setUnknown();

    int num() const;
    bool unknown() const;
    const QMap<int, int> &disabledNumbers() const;

    bool solved() const;

private:
    QLabel *m_label;
    int m_num;
    bool m_unknown;
    QMap<int, int> m_disabledNumbers;
    bool m_solved;
signals:
    void clicked(NumberWidget *);
    void numberChanged(int);
    void changedToUnknown(int);
public slots:
    void addDisabledNumber(int num);
    void removeDisabledNumber(int num);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // NUMBERWIDGET_H
