#include <QApplication>
#include <QPushButton>
#include <QIcon>
#include <QLabel>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("QPushButton Signals Demo");

    QVBoxLayout *layout = new QVBoxLayout(&window);

    QLabel *hint = new QLabel("Try both buttons and observe signals:\npressed() -> released() -> clicked(bool), toggled(bool)");
    hint->setWordWrap(true);
    layout->addWidget(hint);

    QPushButton *actionButton = new QPushButton(QIcon("icon-tools.png"), "Styled Button");
    actionButton->setStyleSheet("QPushButton { background-color: blue; color: white; padding: 8px 12px; }");
    layout->addWidget(actionButton);

    QPushButton *toggleButton = new QPushButton("Checkable Button");
    toggleButton->setCheckable(true);
    layout->addWidget(toggleButton);

    QPlainTextEdit *logView = new QPlainTextEdit;
    logView->setReadOnly(true);
    logView->setPlaceholderText("Signal log will appear here...");
    layout->addWidget(logView);

    QObject::connect(actionButton, &QPushButton::pressed, [logView]() {
        logView->appendPlainText("actionButton: pressed()");
    });

    QObject::connect(actionButton, &QPushButton::released, [logView]() {
        logView->appendPlainText("actionButton: released()");
    });

    QObject::connect(actionButton, &QPushButton::clicked, [logView](bool checked) {
        logView->appendPlainText(QString("actionButton: clicked(%1)").arg(checked ? "true" : "false"));
    });

    QObject::connect(toggleButton, &QPushButton::toggled, [logView](bool checked) {
        logView->appendPlainText(QString("toggleButton: toggled(%1)").arg(checked ? "true" : "false"));
    });

    window.resize(420, 320);
    window.show();

    return app.exec();
}
