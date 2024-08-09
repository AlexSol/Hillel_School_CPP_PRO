#include <QApplication>
#include <QCheckBox>
#include <QDebug>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QCheckBox checkBox("Виберіть мене");
    checkBox.show();

    //enum Qt::CheckState
    QCheckBox::connect(&checkBox, &QCheckBox::stateChanged, [](int state){
        qDebug() << "signal stateChanged.  state:"<<  state;
    });

    return app.exec();
}
