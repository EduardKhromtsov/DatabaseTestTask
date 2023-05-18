
#include <QApplication>
#include "databaseform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DatabaseForm databaseForm;

    databaseForm.show();

    return a.exec();
}
