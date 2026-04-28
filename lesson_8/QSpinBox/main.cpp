#include <QApplication>
#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("QSpinBox Extended Demo");

    QVBoxLayout *mainLayout = new QVBoxLayout(&window);

    QLabel *title = new QLabel("QSpinBox in combination with other widgets");
    mainLayout->addWidget(title);

    QFormLayout *formLayout = new QFormLayout;

    QSpinBox *spinBox = new QSpinBox;
    spinBox->setRange(0, 500);
    spinBox->setSingleStep(5);
    spinBox->setValue(50);
    spinBox->setPrefix("Qty: ");
    spinBox->setSuffix(" pcs");
    formLayout->addRow("Main spin:", spinBox);

    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(spinBox->minimum(), spinBox->maximum());
    slider->setValue(spinBox->value());
    formLayout->addRow("Slider sync:", slider);

    QProgressBar *progressBar = new QProgressBar;
    progressBar->setRange(spinBox->minimum(), spinBox->maximum());
    progressBar->setValue(spinBox->value());
    progressBar->setFormat("%v units");
    formLayout->addRow("Progress view:", progressBar);

    mainLayout->addLayout(formLayout);

    QHBoxLayout *actionsLayout = new QHBoxLayout;
    QPushButton *minusButton = new QPushButton("-step");
    QPushButton *plusButton = new QPushButton("+step");
    QPushButton *resetButton = new QPushButton("Reset");
    actionsLayout->addWidget(minusButton);
    actionsLayout->addWidget(plusButton);
    actionsLayout->addWidget(resetButton);
    mainLayout->addLayout(actionsLayout);

    QHBoxLayout *settingsLayout = new QHBoxLayout;
    QCheckBox *wrappingCheck = new QCheckBox("Wrapping");
    settingsLayout->addWidget(wrappingCheck);

    QLabel *stepLabel = new QLabel("Step:");
    settingsLayout->addWidget(stepLabel);

    QComboBox *stepCombo = new QComboBox;
    stepCombo->addItem("1");
    stepCombo->addItem("5");
    stepCombo->addItem("10");
    stepCombo->addItem("25");
    stepCombo->setCurrentText("5");
    settingsLayout->addWidget(stepCombo);
    settingsLayout->addStretch();
    mainLayout->addLayout(settingsLayout);

    QLabel *stateLabel = new QLabel("Signals: valueChanged(50)");
    mainLayout->addWidget(stateLabel);

    QObject::connect(spinBox, qOverload<int>(&QSpinBox::valueChanged),
                     [slider, progressBar, stateLabel](int value) {
        if (slider->value() != value) {
            slider->setValue(value);
        }
        progressBar->setValue(value);
        stateLabel->setText(QString("Signals: valueChanged(%1)").arg(value));
    });

    QObject::connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);

    QObject::connect(minusButton, &QPushButton::clicked, spinBox, &QSpinBox::stepDown);
    QObject::connect(plusButton, &QPushButton::clicked, spinBox, &QSpinBox::stepUp);

    QObject::connect(resetButton, &QPushButton::clicked, [spinBox]() {
        spinBox->setValue(0);
    });

    QObject::connect(wrappingCheck, &QCheckBox::toggled, spinBox, &QSpinBox::setWrapping);

    QObject::connect(stepCombo, qOverload<int>(&QComboBox::currentIndexChanged),
                     [spinBox, stepCombo](int) {
        spinBox->setSingleStep(stepCombo->currentText().toInt());
    });

    window.resize(520, 290);
    window.show();

    return app.exec();
}


