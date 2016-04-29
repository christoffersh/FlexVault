#include "login.h"
#include "ui_login.h"
#include "adminmainmenu.h"
#include "loginfaileddialog.h"

Login::Login(QWidget *parent, QSqlDatabase*) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    connect(ui->idLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(lineEdit_textChanged()));
    connect(ui->passwordLineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(lineEdit_textChanged()));

    lineEdit_textChanged();

    //resetSafeDB();
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()
{
    if(dbi.validateLogin(ui->idLineEdit->text(), ui->passwordLineEdit->text()))
    {
    amm = new AdminMainMenu(NULL, fv_db);
    amm->show(); // change to showFullScreen() for BeagleBone
    this->hide();
    }

    else
    {
        lfd = new LoginFailedDialog(this);
        lfd->show();
    }
}

void Login::lineEdit_textChanged()
{
    if(ui->idLineEdit->text().length() == 0 || ui->passwordLineEdit->text().length() == 0)
        ui->loginButton->setEnabled(false);

    else
        ui->loginButton->setEnabled(true);
}
