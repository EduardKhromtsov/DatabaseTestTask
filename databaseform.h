#ifndef DATABASEFORM_H
#define DATABASEFORM_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlDriver>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>

namespace Ui {
class DatabaseForm;
}

class DatabaseForm : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseForm(QWidget* parent = nullptr);
    ~DatabaseForm() override;

private slots:
    void on_startPushButton_pressed();
    void slotUpdateDatabaseTableView();

    void on_stopPushButton_pressed();

private:
    Ui::DatabaseForm* ui;
    QSqlDatabase database;
    QSqlQueryModel* pQueryModel;
};

#endif // DATABASEFORM_H
