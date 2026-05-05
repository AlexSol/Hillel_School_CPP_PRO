#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QKeyEvent>

class KeyPressWidget : public QWidget
{
public:
    explicit KeyPressWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        setFocusPolicy(Qt::StrongFocus);
        auto *layout = new QVBoxLayout(this);
        m_label = new QLabel("Фокус на вікні. Ctrl+L або Esc", this);
        layout->addWidget(m_label);
    }

protected:
    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->modifiers() & Qt::ControlModifier && event->key() == Qt::Key_L) {
            m_label->setText("keyPressEvent: Ctrl+L");
            return;
        }

        if (event->key() == Qt::Key_Escape) {
            m_label->setText("keyPressEvent: Esc");
            return;
        }

        QWidget::keyPressEvent(event);
    }

private:
    QLabel *m_label = nullptr;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    KeyPressWidget window;
    window.setWindowTitle("keyPressEvent demo");
    window.resize(340, 120);
    window.show();

    return app.exec();
}
