#include <QApplication>
#include <QColorDialog>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QColorDialog colorDialog;
    colorDialog.show();

    return app.exec();
}
