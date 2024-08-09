#include <QApplication>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QWidget win;

    QVBoxLayout *vbox = new QVBoxLayout;

    QPushButton* button_addItem = new QPushButton("Add Item");

    QListWidget* listWidget = new QListWidget;
    listWidget->addItem("Елемент 1");
    listWidget->addItem("Елемент 2");
    listWidget->addItem("Елемент 3");

    QPushButton::connect(button_addItem, &QPushButton::clicked, [listWidget](){

        listWidget->addItem(QString("Елемент %1").arg(listWidget->count() + 1));
    });

    vbox->addWidget(button_addItem);
    vbox->addWidget(listWidget);

    win.setLayout(vbox);

    win.show();

    return app.exec();
}
