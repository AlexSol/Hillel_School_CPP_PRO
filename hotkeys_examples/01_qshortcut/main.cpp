#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QShortcut>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("QShortcut demo");

    auto *layout = new QVBoxLayout(&window);
    auto *label = new QLabel("Натисни Ctrl+N", &window);
    layout->addWidget(label);

    auto *shortcut = new QShortcut(QKeySequence("Ctrl+N"), &window);
    QObject::connect(shortcut, &QShortcut::activated, [label] {
        label->setText("QShortcut: Ctrl+N спрацював");
    });

    window.resize(320, 100);
    window.show();
    return app.exec();
}
