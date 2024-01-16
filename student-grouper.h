#ifndef STUDENT_GROUPER_H
#define STUDENT_GROUPER_H

#include <QMainWindow>
#include <QScopedPointer>

namespace Ui {
class student_grouper;
}

class student_grouper : public QMainWindow
{
    Q_OBJECT

public:
    explicit student_grouper(QWidget *parent = nullptr);
    ~student_grouper() override;

private:
    QScopedPointer<Ui::student_grouper> m_ui;
};

#endif // STUDENT_GROUPER_H
