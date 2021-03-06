#ifndef USERCREATIONDIALOG_H
#define USERCREATIONDIALOG_H

#include "dbinterface.h"
#include <QDialog>
#include <QPushButton>

class UserConfiguration;
class ActivityLog;

namespace Ui {
class UserCreationDialog;
}

class UserCreationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserCreationDialog(QWidget *parent = 0);
    ~UserCreationDialog();
    bool eventFilter(QObject* object, QEvent* event);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void lineEdit_textChanged();

private:
    Ui::UserCreationDialog *ui;
    ActivityLog* log;
    DBInterface dbi;

signals:
    void updateUserConfig();
    void textChanged(const QString &);
};

#endif // USERCREATIONDIALOG_H
