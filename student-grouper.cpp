#include "student-grouper.h"
#include "ui_student-grouper.h"

student_grouper::student_grouper(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::student_grouper)
{
    m_ui->setupUi(this);
}

student_grouper::~student_grouper() = default;

#include "moc_student-grouper.cpp"
