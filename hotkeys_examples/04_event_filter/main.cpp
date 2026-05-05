#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QKeyEvent>
#include <QObject>

class AppHotkeyFilter : public QObject
{
public:
    explicit AppHotkeyFilter(QLabel *label, QObject *parent = nullptr)
        : QObject(parent), m_label(label) {}

protected:
    bool eventFilter(QObject *obj, QEvent *event) override
    {
        Q_UNUSED(obj);
        if (event->type() != QEvent::KeyPress) {
            return false;
        }

        auto *key = static_cast<QKeyEvent *>(event);
        const bool combo = (key->modifiers() == (Qt::ControlModifier | Qt::ShiftModifier)
                            && key->key() == Qt::Key_F);

        if (combo) {
            m_label->setText("EventFilter: Ctrl+Shift+F (глобально в межах app)");
            return true;
        }

        return false;
    }

private:
    QLabel *m_label = nullptr;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Event Filter demo");

    auto *layout = new QVBoxLayout(&window);
    auto *label = new QLabel("Спробуй Ctrl+Shift+F", &window);
    layout->addWidget(label);

    auto *filter = new AppHotkeyFilter(label, &app);
    app.installEventFilter(filter);

    window.resize(400, 120);
    window.show();
    return app.exec();
}
