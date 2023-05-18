#include "databaseform.h"
#include "ui_databaseform.h"

DatabaseForm::DatabaseForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseForm)
{
    ui->setupUi(this);

    ui->stopPushButton->setEnabled(false);
}

DatabaseForm::~DatabaseForm()
{
    delete ui;
}

void DatabaseForm::on_startPushButton_pressed()
{
    QFuture future = QtConcurrent::run(
                [this]()
    {
        database = QSqlDatabase::addDatabase("QPSQL");
        database.setHostName(ui->hostNameLineEdit->text());

        if (ui->portLineEdit->text() != "")
            database.setPort(ui->portLineEdit->text().toInt());

        database.setDatabaseName(ui->databaseNameLineEdit->text());
        database.setUserName(ui->userNameLineEdit->text());
        database.setPassword(ui->passwordLineEdit->text());

        pQueryModel = new QSqlQueryModel();

        if (!database.open())
        {
            delete pQueryModel;
            pQueryModel = nullptr;
            return pQueryModel;
        }

        database.driver()->subscribeToNotification("postgrestable_insert");
        database.driver()->subscribeToNotification("postgrestable_update");
        database.driver()->subscribeToNotification("postgrestable_delete");

        QObject::connect(database.driver(), SIGNAL(notification(QString,QSqlDriver::NotificationSource,QVariant)), this, SLOT(slotUpdateDatabaseTableView()));

        ui->startPushButton->setEnabled(false);
        ui->stopPushButton->setEnabled(true);

        pQueryModel->setQuery("SELECT * FROM public.\"postgresTable\"");

        return pQueryModel;
    });

    future.waitForFinished();

    ui->databaseTableView->setModel(future.result());

    future.cancel();
}

void DatabaseForm::slotUpdateDatabaseTableView()
{
    QFuture future = QtConcurrent::run(
                [this]()
    {
        pQueryModel->setQuery("SELECT * FROM public.\"postgresTable\"");
    });

    future.waitForFinished();
}


void DatabaseForm::on_stopPushButton_pressed()
{
    database.close();
    ui->databaseTableView->setModel(nullptr);
    ui->stopPushButton->setEnabled(false);
    ui->startPushButton->setEnabled(true);
    delete pQueryModel;
}

