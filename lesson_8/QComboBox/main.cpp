#include <QApplication>
#include <QComboBox>
#include <QDebug>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QComboBox comboBox;
    comboBox.addItem("Варіант 1");
    comboBox.addItem("Варіант 2");
    comboBox.addItem("Варіант 3");
    comboBox.show();

    QComboBox::connect(&comboBox, &QComboBox::activated, [](int index){
        qDebug() << "signal activated. index:" << index;
    });

    return app.exec();
}
