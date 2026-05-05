#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QProgressBar>
#include <QSlider>
#include <QRadioButton>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QStyleFactory>
#include <QDebug>

// ─── 1. Inline QSS — стиль, заданий прямо у коді ────────────────────────────
static const QString INLINE_STYLE = R"(
QWidget {
    background-color: #f0f4f8;
    font-family: "Segoe UI", Arial, sans-serif;
    font-size: 13px;
    color: #2d3748;
}

QGroupBox {
    border: 2px solid #4299e1;
    border-radius: 8px;
    margin-top: 10px;
    padding-top: 6px;
    font-weight: bold;
    color: #2b6cb0;
}
QGroupBox::title {
    subcontrol-origin: margin;
    subcontrol-position: top left;
    padding: 0 6px;
}

QPushButton {
    background-color: #4299e1;
    color: white;
    border: none;
    border-radius: 6px;
    padding: 6px 16px;
    min-width: 80px;
}
QPushButton:hover    { background-color: #3182ce; }
QPushButton:pressed  { background-color: #2b6cb0; }
QPushButton:disabled { background-color: #a0aec0; color: #e2e8f0; }

QLineEdit {
    border: 1px solid #cbd5e0;
    border-radius: 5px;
    padding: 4px 8px;
    background: white;
    selection-background-color: #bee3f8;
}
QLineEdit:focus { border-color: #4299e1; }

QCheckBox::indicator {
    width: 16px;
    height: 16px;
    border: 2px solid #4299e1;
    border-radius: 3px;
    background: white;
}
QCheckBox::indicator:checked {
    background-color: #4299e1;
    image: url(:/icons/check.png);   /* опціонально */
}

QComboBox {
    border: 1px solid #cbd5e0;
    border-radius: 5px;
    padding: 4px 8px;
    background: white;
}
QComboBox::drop-down { border: none; }

QProgressBar {
    border: 1px solid #cbd5e0;
    border-radius: 5px;
    text-align: center;
    background: #edf2f7;
    height: 18px;
}
QProgressBar::chunk {
    background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                                      stop:0 #4299e1, stop:1 #63b3ed);
    border-radius: 4px;
}

QSlider::groove:horizontal {
    height: 6px;
    background: #e2e8f0;
    border-radius: 3px;
}
QSlider::handle:horizontal {
    background: #4299e1;
    width: 16px;
    height: 16px;
    margin: -5px 0;
    border-radius: 8px;
}
QSlider::sub-page:horizontal {
    background: #4299e1;
    border-radius: 3px;
}
)";

// ─── Helpers ─────────────────────────────────────────────────────────────────

// Завантаження QSS з файлу
static QString loadQssFile(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Cannot open QSS file:" << path;
        return {};
    }
    return QTextStream(&file).readAll();
}

// ─── MainWindow ──────────────────────────────────────────────────────────────
class MainWindow : public QWidget
{
public:
    explicit MainWindow(QWidget *parent = nullptr) : QWidget(parent)
    {
        setWindowTitle("QSS Customization Demo");
        setMinimumWidth(480);

        auto *root = new QVBoxLayout(this);
        root->setSpacing(12);
        root->setContentsMargins(16, 16, 16, 16);

        // ── Вибір QSS-теми ────────────────────────────────────────────────────
        auto *themeGroup = new QGroupBox("QSS теми", this);
        auto *themeLayout = new QHBoxLayout(themeGroup);

        auto *btnInline = new QPushButton("Inline (код)", this);
        auto *btnLight  = new QPushButton("Light (файл)", this);
        auto *btnDark   = new QPushButton("Dark  (файл)", this);
        auto *btnClear  = new QPushButton("Скинути QSS",  this);

        themeLayout->addWidget(btnInline);
        themeLayout->addWidget(btnLight);
        themeLayout->addWidget(btnDark);
        themeLayout->addWidget(btnClear);

        root->addWidget(themeGroup);

        // ── Вбудовані стилі Qt (QStyleFactory) ───────────────────────────────
        auto *builtinGroup = new QGroupBox("Вбудовані стилі Qt (QStyleFactory)", this);
        auto *builtinLayout = new QHBoxLayout(builtinGroup);

        m_styleCombo = new QComboBox(this);
        // QStyleFactory::keys() повертає всі доступні стилі: Fusion, Windows, …
        const QStringList styles = QStyleFactory::keys();
        m_styleCombo->addItems(styles);
        // Показуємо поточний стиль як вибраний
        const QString current = QApplication::style()->objectName();
        const int idx = m_styleCombo->findText(current, Qt::MatchFixedString);
        if (idx >= 0) m_styleCombo->setCurrentIndex(idx);

        auto *btnApplyStyle = new QPushButton("Застосувати", this);

        builtinLayout->addWidget(new QLabel("Стиль:", this));
        builtinLayout->addWidget(m_styleCombo, 1);
        builtinLayout->addWidget(btnApplyStyle);

        root->addWidget(builtinGroup);

        // ── Демо-віджети ──────────────────────────────────────────────────────
        auto *widgetsGroup = new QGroupBox("Демо-віджети", this);
        auto *wLayout = new QVBoxLayout(widgetsGroup);

        wLayout->addWidget(new QLabel("Введіть текст:", this));
        wLayout->addWidget(new QLineEdit("Текст за замовчуванням", this));

        auto *row1 = new QHBoxLayout;
        row1->addWidget(new QCheckBox("Опція 1", this));
        row1->addWidget(new QCheckBox("Опція 2", this));
        row1->addWidget(new QRadioButton("Варіант A", this));
        row1->addWidget(new QRadioButton("Варіант B", this));
        wLayout->addLayout(row1);

        auto *combo = new QComboBox(this);
        combo->addItems({"Елемент 1", "Елемент 2", "Елемент 3"});
        wLayout->addWidget(combo);

        m_progress = new QProgressBar(this);
        m_progress->setRange(0, 100);
        m_progress->setValue(60);
        wLayout->addWidget(m_progress);

        m_slider = new QSlider(Qt::Horizontal, this);
        m_slider->setRange(0, 100);
        m_slider->setValue(60);
        connect(m_slider, &QSlider::valueChanged,
                m_progress, &QProgressBar::setValue);
        wLayout->addWidget(m_slider);

        auto *row2 = new QHBoxLayout;
        row2->addWidget(new QPushButton("OK", this));
        auto *btnDisabled = new QPushButton("Disabled", this);
        btnDisabled->setDisabled(true);
        row2->addWidget(btnDisabled);
        wLayout->addLayout(row2);

        root->addWidget(widgetsGroup);

        // ── Статус ────────────────────────────────────────────────────────────
        m_statusLabel = new QLabel("Активна тема: inline (код)", this);
        m_statusLabel->setAlignment(Qt::AlignCenter);
        root->addWidget(m_statusLabel);

        // ── Підключення кнопок ────────────────────────────────────────────────
        connect(btnInline,    &QPushButton::clicked, this, &MainWindow::applyInline);
        connect(btnLight,     &QPushButton::clicked, this, &MainWindow::applyLightFile);
        connect(btnDark,      &QPushButton::clicked, this, &MainWindow::applyDarkFile);
        connect(btnClear,     &QPushButton::clicked, this, &MainWindow::clearStyle);
        connect(btnApplyStyle, &QPushButton::clicked, this, &MainWindow::applyBuiltinStyle);

        // Застосовуємо inline-стиль при запуску
        applyInline();
    }

private:
    QProgressBar *m_progress    = nullptr;
    QSlider      *m_slider      = nullptr;
    QLabel       *m_statusLabel = nullptr;
    QComboBox    *m_styleCombo  = nullptr;

    // 1) Стиль прямо у коді
    void applyInline()
    {
        qApp->setStyleSheet(INLINE_STYLE);
        m_statusLabel->setText("Активна тема: inline (код)");
    }

    // 2) Завантаження з файлу — світла тема
    void applyLightFile()
    {
        const QString qss = loadQssFile(":/themes/light.qss");
        if (qss.isEmpty()) {
            QMessageBox::warning(this, "Помилка", "Не вдалося завантажити light.qss");
            return;
        }
        qApp->setStyleSheet(qss);
        m_statusLabel->setText("Активна тема: Light (із файлу)");
    }

    // 3) Завантаження з файлу — темна тема
    void applyDarkFile()
    {
        const QString qss = loadQssFile(":/themes/dark.qss");
        if (qss.isEmpty()) {
            QMessageBox::warning(this, "Помилка", "Не вдалося завантажити dark.qss");
            return;
        }
        qApp->setStyleSheet(qss);
        m_statusLabel->setText("Активна тема: Dark (із файлу)");
    }

    // 4) Скидання QSS (залишаємо поточний QStyle)
    void clearStyle()
    {
        qApp->setStyleSheet({});
        m_statusLabel->setText("Активна тема: системна (без QSS)");
    }

    // 5) Вбудований стиль Qt через QStyleFactory
    void applyBuiltinStyle()
    {
        const QString name = m_styleCombo->currentText();
        // Скидаємо QSS, щоб вбудований стиль відображався без перекриття
        qApp->setStyleSheet({});
        QApplication::setStyle(QStyleFactory::create(name));
        m_statusLabel->setText("Активна тема: " + name + " (QStyleFactory)");
    }
};

// ─── main ─────────────────────────────────────────────────────────────────────
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
