#include <QApplication>
#include <QPushButton>
#include <QIcon>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QPushButton* roundButton = new QPushButton("Styled Button");
    roundButton->setStyleSheet("QPushButton { "
                         "  border-radius: 20px; "
                         "  background-color: #4CAF50;"
                         "  color: white; "
                         "  font-size: 16px;"
                         "  font-weight: bold;"
                         "  padding: 12px 24px;"
                         "}"
                         "QPushButton:hover {"
                         "  background-color: #45a049;"
                         "}");


    QVBoxLayout* layout = new QVBoxLayout;

    layout->addWidget(roundButton);

    QWidget window;
    window.setLayout(layout);

    window.setFixedSize(430, 270);

    window.show();

    return app.exec();
}
