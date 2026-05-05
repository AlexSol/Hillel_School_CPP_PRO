#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

#ifdef HAVE_QHOTKEY
#include <QHotkey>
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("QHotkey demo");

    auto *layout = new QVBoxLayout(&window);
    auto *label = new QLabel("", &window);
    layout->addWidget(label);

#ifdef HAVE_QHOTKEY
    label->setText("Системний hotkey: Ctrl+Alt+H");

    auto *hotkey = new QHotkey(QKeySequence("Ctrl+Alt+H"), true, &window);
    QObject::connect(hotkey, &QHotkey::activated, [label] {
        label->setText("QHotkey: Ctrl+Alt+H спрацював");
    });
#else
    label->setText("QHotkey не знайдено. Встанови бібліотеку QHotkey і перебудуй цей приклад.");
#endif

    window.resize(420, 120);
    window.show();
    return app.exec();
}
