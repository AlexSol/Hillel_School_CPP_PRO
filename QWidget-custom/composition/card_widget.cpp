#include <QApplication>
#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QFont>

class CardWidget : public QWidget
{
public:
    CardWidget()
    {
        auto layout = new QVBoxLayout(this);

        title = new QLabel("Title");
        desc  = new QLabel("Description");

        layout->addWidget(title);
        layout->addWidget(desc);

        setStyleSheet(R"(
            QWidget {
                background: white;
                border-radius: 10px;
                padding: 10px;
            }
        )");
    }

private:
    QLabel* title;
    QLabel* desc;
};

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setStyle("Fusion");

	CardWidget cardWidget;

	cardWidget.resize(420, 360);
	cardWidget.show();
	return app.exec();
}
