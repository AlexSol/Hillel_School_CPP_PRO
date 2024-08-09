#include <QApplication>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QGroupBox>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QGroupBox *groupBox = new QGroupBox("Exclusive Radio Buttons");

    QRadioButton* radioButton_1 = new QRadioButton("Виберіть мене 1");
    QRadioButton* radioButton_2 = new QRadioButton("Виберіть мене 2");
    QRadioButton* radioButton_3 = new QRadioButton("Виберіть мене 3");


    QVBoxLayout *vbox = new QVBoxLayout;

    vbox->addWidget(radioButton_1);
    vbox->addWidget(radioButton_2);
    vbox->addWidget(radioButton_3);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    groupBox->show();

    return app.exec();
}
