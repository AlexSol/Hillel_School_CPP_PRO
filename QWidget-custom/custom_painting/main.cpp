/*
 * Custom Painting — кастомний прогрес-бар через QPainter / paintEvent
 *
 * Три варіанти:
 *  1. LinearProgressBar  — горизонтальний з градієнтом і підписом %
 *  2. CircularProgressBar — кругова шкала (arc)
 *  3. StepProgressBar    — покроковий індикатор (steps)
 *
 * Загальний контроль: QSlider змінює значення всіх трьох одночасно.
 */

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QSlider>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QBrush>
#include <QLinearGradient>
#include <QConicalGradient>
#include <QFont>
#include <QSizePolicy>
#include <QtMath>

// ═══════════════════════════════════════════════════════════════════════════
// 1. LinearProgressBar
// ═══════════════════════════════════════════════════════════════════════════
class LinearProgressBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue)
public:
    explicit LinearProgressBar(QWidget *parent = nullptr) : QWidget(parent)
    {
        setFixedHeight(36);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    }

    int  value() const   { return m_value; }
    void setValue(int v) { m_value = qBound(0, v, 100); update(); }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        const QRect r = rect().adjusted(1, 1, -1, -1);
        const int radius = r.height() / 2;

        // — Трек (фон) ——————————————————————————————————————————————
        p.setPen(Qt::NoPen);
        p.setBrush(QColor("#e2e8f0"));
        p.drawRoundedRect(r, radius, radius);

        // — Заповнений сегмент ————————————————————————————————————————
        if (m_value > 0) {
            const int fillW = int(r.width() * m_value / 100.0);
            QRect fill(r.left(), r.top(), fillW, r.height());

            QLinearGradient grad(fill.topLeft(), fill.topRight());
            grad.setColorAt(0.0, QColor("#4299e1"));
            grad.setColorAt(0.5, QColor("#63b3ed"));
            grad.setColorAt(1.0, QColor("#90cdf4"));

            p.setBrush(grad);
            p.setClipRect(fill);
            p.drawRoundedRect(r, radius, radius);
            p.setClipping(false);

            // — Блиск ——————————————————————————————————————————————
            QLinearGradient gloss(fill.topLeft(), fill.bottomLeft());
            gloss.setColorAt(0.0, QColor(255, 255, 255, 80));
            gloss.setColorAt(0.5, QColor(255, 255, 255, 0));
            p.setBrush(gloss);
            p.setClipRect(fill);
            p.drawRoundedRect(r, radius, radius);
            p.setClipping(false);
        }

        // — Текст % ————————————————————————————————————————————————
        p.setPen(m_value > 55 ? Qt::white : QColor("#2d3748"));
        p.setFont(QFont("Segoe UI", 10, QFont::Bold));
        p.drawText(r, Qt::AlignCenter, QString("%1 %").arg(m_value));
    }

private:
    int m_value = 0;
};

// ═══════════════════════════════════════════════════════════════════════════
// 2. CircularProgressBar
// ═══════════════════════════════════════════════════════════════════════════
class CircularProgressBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue)
public:
    explicit CircularProgressBar(QWidget *parent = nullptr) : QWidget(parent)
    {
        setFixedSize(160, 160);
    }

    int  value() const   { return m_value; }
    void setValue(int v) { m_value = qBound(0, v, 100); update(); }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        const int   pen   = 14;
        const QRect r     = rect().adjusted(pen, pen, -pen, -pen);
        const qreal start = 90;                         // 12 годин
        const qreal span  = -360.0 * m_value / 100.0;  // за годинниковою

        // — Трек ——————————————————————————————————————————————————————
        p.setPen(QPen(QColor("#e2e8f0"), pen, Qt::SolidLine, Qt::RoundCap));
        p.setBrush(Qt::NoBrush);
        p.drawArc(r, int(start * 16), int(-360 * 16));

        // — Прогрес (конічний градієнт) ————————————————————————————————
        if (m_value > 0) {
            QConicalGradient cg(r.center(), start);
            cg.setColorAt(0.0,  QColor("#4299e1"));
            cg.setColorAt(0.5,  QColor("#805ad5"));
            cg.setColorAt(1.0,  QColor("#4299e1"));

            p.setPen(QPen(QBrush(cg), pen, Qt::SolidLine, Qt::RoundCap));
            p.drawArc(r, int(start * 16), int(span * 16));
        }

        // — Центральний текст ——————————————————————————————————————————
        p.setPen(QColor("#2d3748"));
        p.setFont(QFont("Segoe UI", 20, QFont::Bold));
        p.drawText(rect(), Qt::AlignCenter, QString("%1%").arg(m_value));

        // — Мітка ——————————————————————————————————————————————————————
        QRect labelRect = rect().adjusted(0, rect().height() / 2 + 10, 0, 0);
        p.setFont(QFont("Segoe UI", 8));
        p.setPen(QColor("#718096"));
        p.drawText(labelRect, Qt::AlignTop | Qt::AlignHCenter, "Progress");
    }

private:
    int m_value = 0;
};

// ═══════════════════════════════════════════════════════════════════════════
// 3. StepProgressBar
// ═══════════════════════════════════════════════════════════════════════════
class StepProgressBar : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue)
public:
    explicit StepProgressBar(int steps = 5, QWidget *parent = nullptr)
        : QWidget(parent), m_steps(steps)
    {
        setFixedHeight(60);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    }

    int  value() const   { return m_value; }
    void setValue(int v) { m_value = qBound(0, v, 100); update(); }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        const int   r    = 16;                // радіус кола
        const int   lineY = height() / 2 - 4;
        const qreal step  = (width() - 2.0 * r) / (m_steps - 1);

        // Активний крок (0-based)
        const int active = int(m_value / 100.0 * (m_steps - 1) + 0.5);

        for (int i = 0; i < m_steps; ++i) {
            const int cx = int(r + i * step);

            // — Лінія до наступного кроку ——————————————————————————————
            if (i < m_steps - 1) {
                const int nextX = int(r + (i + 1) * step);
                // завершена частина
                if (i < active) {
                    p.setPen(QPen(QColor("#4299e1"), 3));
                    p.drawLine(cx, lineY, nextX, lineY);
                } else {
                    p.setPen(QPen(QColor("#e2e8f0"), 3));
                    p.drawLine(cx, lineY, nextX, lineY);
                }
            }

            // — Коло кроку ————————————————————————————————————————————
            QRect circle(cx - r, lineY - r, 2 * r, 2 * r);
            if (i < active) {
                // завершений
                p.setBrush(QColor("#4299e1"));
                p.setPen(Qt::NoPen);
                p.drawEllipse(circle);
                // галочка
                p.setPen(QPen(Qt::white, 2.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                QPointF c = circle.center();
                p.drawPolyline(QPolygonF({
                    c + QPointF(-5,  0),
                    c + QPointF(-1,  5),
                    c + QPointF( 5, -5)
                }));
            } else if (i == active) {
                // поточний
                p.setBrush(Qt::white);
                p.setPen(QPen(QColor("#4299e1"), 3));
                p.drawEllipse(circle);
                p.setPen(Qt::NoPen);
                p.setBrush(QColor("#4299e1"));
                p.drawEllipse(circle.adjusted(5, 5, -5, -5));
            } else {
                // майбутній
                p.setBrush(QColor("#edf2f7"));
                p.setPen(QPen(QColor("#cbd5e0"), 2));
                p.drawEllipse(circle);
            }

            // — Номер кроку (під колом) ————————————————————————————————
            p.setPen(i <= active ? QColor("#2d3748") : QColor("#a0aec0"));
            p.setFont(QFont("Segoe UI", 8));
            p.drawText(QRect(cx - 20, lineY + r + 2, 40, 16),
                       Qt::AlignCenter, QString("Крок %1").arg(i + 1));
        }
    }

private:
    int m_steps = 5;
    int m_value = 0;
};

// ═══════════════════════════════════════════════════════════════════════════
// MainWindow
// ═══════════════════════════════════════════════════════════════════════════
class MainWindow : public QWidget
{
public:
    explicit MainWindow(QWidget *parent = nullptr) : QWidget(parent)
    {
        setWindowTitle("Custom Painting — Progress Bar Demo");
        setMinimumWidth(520);

        auto *root = new QVBoxLayout(this);
        root->setSpacing(16);
        root->setContentsMargins(20, 20, 20, 20);

        // ── 1. Linear ────────────────────────────────────────────────────
        auto *g1 = new QGroupBox("1. LinearProgressBar  (градієнт + текст)", this);
        auto *l1 = new QVBoxLayout(g1);
        m_linear = new LinearProgressBar(this);
        l1->addWidget(m_linear);
        root->addWidget(g1);

        // ── 2. Circular ──────────────────────────────────────────────────
        auto *g2 = new QGroupBox("2. CircularProgressBar  (конічний градієнт)", this);
        auto *l2 = new QHBoxLayout(g2);
        m_circular = new CircularProgressBar(this);
        l2->addStretch();
        l2->addWidget(m_circular);
        l2->addStretch();
        root->addWidget(g2);

        // ── 3. Step ──────────────────────────────────────────────────────
        auto *g3 = new QGroupBox("3. StepProgressBar  (покрокова шкала)", this);
        auto *l3 = new QVBoxLayout(g3);
        m_step = new StepProgressBar(5, this);
        l3->addWidget(m_step);
        l3->addSpacing(16);   // місце для підписів кроків
        root->addWidget(g3);

        // ── Слайдер ──────────────────────────────────────────────────────
        auto *ctrlGroup = new QGroupBox("Значення (0–100)", this);
        auto *ctrlLayout = new QHBoxLayout(ctrlGroup);
        m_slider = new QSlider(Qt::Horizontal, this);
        m_slider->setRange(0, 100);
        m_slider->setValue(40);
        m_valueLabel = new QLabel("40 %", this);
        m_valueLabel->setFixedWidth(40);
        ctrlLayout->addWidget(m_slider);
        ctrlLayout->addWidget(m_valueLabel);
        root->addWidget(ctrlGroup);

        // Синхронізація
        connect(m_slider, &QSlider::valueChanged, this, [this](int v){
            m_linear->setValue(v);
            m_circular->setValue(v);
            m_step->setValue(v);
            m_valueLabel->setText(QString("%1 %").arg(v));
        });
        m_slider->valueChanged(40);   // початкове значення
    }

private:
    LinearProgressBar   *m_linear   = nullptr;
    CircularProgressBar *m_circular = nullptr;
    StepProgressBar     *m_step     = nullptr;
    QSlider             *m_slider   = nullptr;
    QLabel              *m_valueLabel = nullptr;
};

// ═══════════════════════════════════════════════════════════════════════════
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle("Fusion");

    MainWindow w;
    w.show();
    return app.exec();
}

#include "main.moc"
