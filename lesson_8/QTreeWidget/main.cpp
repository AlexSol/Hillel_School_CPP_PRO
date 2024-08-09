#include <QApplication>
#include <QTreeWidget>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QTreeWidget treeWidget;
    treeWidget.setColumnCount(1);
    treeWidget.setHeaderLabels(QStringList() << "Елементи");
    treeWidget.show();

    return app.exec();
}


