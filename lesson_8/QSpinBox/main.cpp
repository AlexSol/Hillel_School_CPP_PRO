#include <QApplication>
#include <QSpinBox>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QSpinBox spinBox;
    spinBox.show();
    spinBox.setFixedSize(100, 50);

    return app.exec();
}


