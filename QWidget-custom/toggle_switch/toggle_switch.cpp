#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QLabel>

class ToggleSwitch : public QWidget
{
public:
    ToggleSwitch(QWidget* parent = nullptr) : QWidget(parent)
    {
        setFixedSize(60, 30);
    }

    bool isChecked() const { return checked; }

protected:
    void mousePressEvent(QMouseEvent*) override
    {
        checked = !checked;
        update();
    }

    void paintEvent(QPaintEvent*) override
    {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        // background
        QColor bg = checked ? QColor("#2ecc71") : QColor("#bdc3c7");
        p.setBrush(bg);
        p.setPen(Qt::NoPen);
        p.drawRoundedRect(rect(), 15, 15);

        // knob
        int x = checked ? width() - 28 : 2;

        p.setBrush(Qt::white);
        p.drawEllipse(x, 2, 26, 26);
    }

private:
    bool checked = false;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle("Fusion");

    QWidget window;
    window.setWindowTitle("Toggle Switch Demo");

    auto *layout = new QVBoxLayout(&window);
    layout->setContentsMargins(20, 20, 20, 20);
    layout->setSpacing(10);

    auto *title = new QLabel("Простий toggle switch через custom painting", &window);
    auto *toggle = new ToggleSwitch(&window);
    title->setWordWrap(true);

    layout->addWidget(title);
    layout->addWidget(toggle, 0, Qt::AlignLeft);

    window.show();
    return app.exec();
}