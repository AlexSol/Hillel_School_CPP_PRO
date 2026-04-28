#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QSlider>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("QProgressBar + Widgets Demo");

    QVBoxLayout *mainLayout = new QVBoxLayout(&window);

    QLabel *title = new QLabel("Progress demo with slider, timer and controls");
    mainLayout->addWidget(title);

    QProgressBar *progressBar = new QProgressBar;
    progressBar->setRange(0, 100);
    progressBar->setValue(25);
    progressBar->setFormat("Progress: %p% (%v/%m)");
    mainLayout->addWidget(progressBar);

    QLabel *valueLabel = new QLabel("Current value: 25");
    mainLayout->addWidget(valueLabel);

    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 100);
    slider->setValue(progressBar->value());
    mainLayout->addWidget(slider);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    QPushButton *minusButton = new QPushButton("-10");
    QPushButton *plusButton = new QPushButton("+10");
    QPushButton *resetButton = new QPushButton("Reset");
    QPushButton *startStopButton = new QPushButton("Start auto");
    buttonsLayout->addWidget(minusButton);
    buttonsLayout->addWidget(plusButton);
    buttonsLayout->addWidget(resetButton);
    buttonsLayout->addWidget(startStopButton);
    mainLayout->addLayout(buttonsLayout);

    QHBoxLayout *settingsLayout = new QHBoxLayout;
    QCheckBox *showTextCheck = new QCheckBox("Show text");
    showTextCheck->setChecked(true);
    settingsLayout->addWidget(showTextCheck);

    QLabel *orientationLabel = new QLabel("Orientation:");
    settingsLayout->addWidget(orientationLabel);

    QComboBox *orientationBox = new QComboBox;
    orientationBox->addItem("Horizontal");
    orientationBox->addItem("Vertical");
    settingsLayout->addWidget(orientationBox);
    settingsLayout->addStretch();
    mainLayout->addLayout(settingsLayout);

    QTimer *timer = new QTimer(&window);
    timer->setInterval(120);

    QObject::connect(slider, &QSlider::valueChanged, progressBar, &QProgressBar::setValue);

    QObject::connect(progressBar, &QProgressBar::valueChanged, [valueLabel, slider](int value) {
        valueLabel->setText(QString("Current value: %1").arg(value));
        if (slider->value() != value) {
            slider->setValue(value);
        }
    });

    QObject::connect(minusButton, &QPushButton::clicked, [progressBar]() {
        progressBar->setValue(progressBar->value() - 10);
    });

    QObject::connect(plusButton, &QPushButton::clicked, [progressBar]() {
        progressBar->setValue(progressBar->value() + 10);
    });

    QObject::connect(resetButton, &QPushButton::clicked, [progressBar]() {
        progressBar->reset();
    });

    QObject::connect(showTextCheck, &QCheckBox::toggled, progressBar, &QProgressBar::setTextVisible);

    QObject::connect(orientationBox, qOverload<int>(&QComboBox::currentIndexChanged), [progressBar](int index) {
        if (index == 0) {
            progressBar->setOrientation(Qt::Horizontal);
        } else {
            progressBar->setOrientation(Qt::Vertical);
        }
    });

    QObject::connect(startStopButton, &QPushButton::clicked, [timer, startStopButton]() {
        if (timer->isActive()) {
            timer->stop();
            startStopButton->setText("Start auto");
        } else {
            timer->start();
            startStopButton->setText("Stop auto");
        }
    });

    QObject::connect(timer, &QTimer::timeout, [progressBar]() {
        int next = progressBar->value() + 1;
        if (next > progressBar->maximum()) {
            next = progressBar->minimum();
        }
        progressBar->setValue(next);
    });

    window.resize(460, 260);
    window.show();

    return app.exec();
}
