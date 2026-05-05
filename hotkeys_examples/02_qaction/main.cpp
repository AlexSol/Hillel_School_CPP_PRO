#include <QApplication>
#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QLabel>
#include <QStatusBar>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QMainWindow window;
    window.setWindowTitle("QAction demo");

    auto *label = new QLabel("Натисни Ctrl+S (через QAction)", &window);
    label->setAlignment(Qt::AlignCenter);
    window.setCentralWidget(label);

    auto *fileMenu = window.menuBar()->addMenu("File");
    auto *saveAction = fileMenu->addAction("Save");
    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    saveAction->setShortcutContext(Qt::WindowShortcut);

    QObject::connect(saveAction, &QAction::triggered, [&window, label] {
        label->setText("QAction: Ctrl+S спрацював");
        window.statusBar()->showMessage("Saved", 1200);
    });

    window.resize(420, 220);
    window.show();
    return app.exec();
}
