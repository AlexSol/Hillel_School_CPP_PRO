/*
 * Subclass + Events — кастомізація QWidget через перевизначення подій
 *
 * Приклади:
 *  1. HoverButton    — кнопка з плавною анімацією при наведенні
 *  2. ClickRipple    — кнопка з "ripple"-ефектом при кліку
 *  3. DragLabel      — мітка, яку можна перетягувати мишею
 *  4. KeyDisplay     — поле, що відображає останню натиснуту клавішу
 *  5. ResizeOverlay  — панель, що малює розміри при зміні розміру вікна
 */

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QEnterEvent>
#include <QTimerEvent>
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QFont>
#include <QFontMetrics>
#include <QColor>
#include <QRect>
#include <cmath>

// ═══════════════════════════════════════════════════════════════════════════
// 1. HoverButton — плавна зміна кольору через enterEvent / leaveEvent
//    + QPropertyAnimation для анімації власної Q_PROPERTY
// ═══════════════════════════════════════════════════════════════════════════
class HoverButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal hover READ hover WRITE setHover)

public:
    explicit HoverButton(const QString &text, QWidget *parent = nullptr)
        : QWidget(parent), m_text(text)
    {
        setFixedHeight(44);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        setCursor(Qt::PointingHandCursor);

        m_anim = new QPropertyAnimation(this, "hover", this);
        m_anim->setDuration(200);
        m_anim->setEasingCurve(QEasingCurve::InOutQuad);
    }

    qreal hover() const { return m_hover; }
    void  setHover(qreal v) { m_hover = v; update(); }

protected:
    void enterEvent(QEnterEvent *) override
    {
        m_anim->stop();
        m_anim->setStartValue(m_hover);
        m_anim->setEndValue(1.0);
        m_anim->start();
    }

    void leaveEvent(QEvent *) override
    {
        m_anim->stop();
        m_anim->setStartValue(m_hover);
        m_anim->setEndValue(0.0);
        m_anim->start();
    }

    void mousePressEvent(QMouseEvent *e) override
    {
        if (e->button() == Qt::LeftButton) {
            emit clicked();
        }
    }

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        const QColor base  = QColor(66, 153, 225);   // #4299e1
        const QColor hover = QColor(49, 130, 206);   // #3182ce
        QColor bg = QColor(
            int(base.red()   + (hover.red()   - base.red())   * m_hover),
            int(base.green() + (hover.green() - base.green()) * m_hover),
            int(base.blue()  + (hover.blue()  - base.blue())  * m_hover)
        );

        // Тінь при наведенні
        if (m_hover > 0.01) {
            QColor shadow(0, 0, 0, int(60 * m_hover));
            p.setPen(Qt::NoPen);
            p.setBrush(shadow);
            p.drawRoundedRect(rect().adjusted(4, 6, -4, 2), 8, 8);
        }

        QPainterPath path;
        path.addRoundedRect(rect().adjusted(0, 0, 0, -4), 8, 8);
        p.fillPath(path, bg);

        p.setPen(Qt::white);
        p.setFont(QFont("Segoe UI", 11, QFont::Medium));
        p.drawText(path.boundingRect().toRect(), Qt::AlignCenter, m_text);
    }

signals:
    void clicked();

private:
    QString            m_text;
    qreal              m_hover = 0.0;
    QPropertyAnimation *m_anim = nullptr;
};

// ═══════════════════════════════════════════════════════════════════════════
// 2. ClickRipple — ripple-ефект через mousePressEvent + таймер
// ═══════════════════════════════════════════════════════════════════════════
class ClickRipple : public QWidget
{
    Q_OBJECT
public:
    explicit ClickRipple(const QString &text, QWidget *parent = nullptr)
        : QWidget(parent), m_text(text)
    {
        setFixedHeight(44);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        setCursor(Qt::PointingHandCursor);
    }

protected:
    void mousePressEvent(QMouseEvent *e) override
    {
        m_ripplePos    = e->pos();
        m_rippleRadius = 0;
        m_rippleAlpha  = 180;
        if (m_timerId == 0)
            m_timerId = startTimer(16);   // ~60 fps
        update();
    }

    void timerEvent(QTimerEvent *) override
    {
        m_rippleRadius += 8;
        m_rippleAlpha  -= 10;
        if (m_rippleAlpha <= 0) {
            killTimer(m_timerId);
            m_timerId = 0;
            m_rippleAlpha = 0;
        }
        update();
    }

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        // Фон
        QPainterPath bg;
        bg.addRoundedRect(rect(), 8, 8);
        p.fillPath(bg, QColor("#e53e3e"));

        // Ripple
        if (m_rippleAlpha > 0) {
            p.setClipPath(bg);
            p.setPen(Qt::NoPen);
            p.setBrush(QColor(255, 255, 255, m_rippleAlpha));
            p.drawEllipse(m_ripplePos, m_rippleRadius, m_rippleRadius);
        }

        p.setPen(Qt::white);
        p.setFont(QFont("Segoe UI", 11, QFont::Medium));
        p.drawText(rect(), Qt::AlignCenter, m_text);
    }

private:
    QString m_text;
    QPoint  m_ripplePos;
    int     m_rippleRadius = 0;
    int     m_rippleAlpha  = 0;
    int     m_timerId      = 0;
};

// ═══════════════════════════════════════════════════════════════════════════
// 3. DragLabel — мітка, яку можна перетягувати мишею
//    mousePressEvent / mouseMoveEvent
// ═══════════════════════════════════════════════════════════════════════════
class DragLabel : public QWidget
{
public:
    explicit DragLabel(const QString &text, QWidget *parent = nullptr)
        : QWidget(parent), m_text(text)
    {
        setFixedSize(160, 50);
        setCursor(Qt::OpenHandCursor);
    }

protected:
    void mousePressEvent(QMouseEvent *e) override
    {
        if (e->button() == Qt::LeftButton) {
            m_dragOffset = e->pos();
            setCursor(Qt::ClosedHandCursor);
        }
    }

    void mouseMoveEvent(QMouseEvent *e) override
    {
        if (e->buttons() & Qt::LeftButton) {
            QPoint newPos = mapToParent(e->pos()) - m_dragOffset;
            // Обмежуємо в межах батьківського віджета
            if (parentWidget()) {
                QRect bounds = parentWidget()->rect().adjusted(0, 0, -width(), -height());
                newPos.setX(qBound(bounds.left(), newPos.x(), bounds.right()));
                newPos.setY(qBound(bounds.top(),  newPos.y(), bounds.bottom()));
            }
            move(newPos);
        }
    }

    void mouseReleaseEvent(QMouseEvent *) override
    {
        setCursor(Qt::OpenHandCursor);
    }

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        QPainterPath path;
        path.addRoundedRect(rect().adjusted(1,1,-1,-1), 10, 10);
        p.fillPath(path, QColor("#805ad5"));
        p.setPen(QColor("#e9d8fd"));
        p.drawPath(path);
        p.setPen(Qt::white);
        p.setFont(QFont("Segoe UI", 10));
        p.drawText(rect(), Qt::AlignCenter, m_text);
    }

private:
    QString m_text;
    QPoint  m_dragOffset;
};

// ═══════════════════════════════════════════════════════════════════════════
// 4. KeyDisplay — перехоплення keyPressEvent, показ клавіші
// ═══════════════════════════════════════════════════════════════════════════
class KeyDisplay : public QWidget
{
public:
    explicit KeyDisplay(QWidget *parent = nullptr) : QWidget(parent)
    {
        setFocusPolicy(Qt::StrongFocus);
        setFixedSize(220, 70);
    }

protected:
    void keyPressEvent(QKeyEvent *e) override
    {
        m_key  = e->text().isEmpty()
                 ? QKeySequence(e->key()).toString()
                 : e->text().toUpper();
        m_mod  = e->modifiers();
        update();
    }

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        // Рамка
        bool focused = hasFocus();
        p.setPen(QPen(focused ? QColor("#38a169") : QColor("#cbd5e0"), 2));
        p.setBrush(focused ? QColor("#f0fff4") : QColor("#f7fafc"));
        p.drawRoundedRect(rect().adjusted(1,1,-1,-1), 8, 8);

        if (m_key.isEmpty()) {
            p.setPen(QColor("#a0aec0"));
            p.setFont(QFont("Segoe UI", 10));
            p.drawText(rect(), Qt::AlignCenter,
                       focused ? "Натисніть клавішу…" : "Клікніть для фокусу");
        } else {
            QStringList parts;
            if (m_mod & Qt::ControlModifier) parts << "Ctrl";
            if (m_mod & Qt::ShiftModifier)   parts << "Shift";
            if (m_mod & Qt::AltModifier)     parts << "Alt";
            parts << m_key;

            p.setPen(QColor("#2d3748"));
            p.setFont(QFont("Segoe UI", 14, QFont::Bold));
            p.drawText(rect(), Qt::AlignCenter, parts.join(" + "));
        }
    }

    void focusInEvent(QFocusEvent *)  override { update(); }
    void focusOutEvent(QFocusEvent *) override { update(); }

private:
    QString          m_key;
    Qt::KeyboardModifiers m_mod;
};

// ═══════════════════════════════════════════════════════════════════════════
// 5. ResizeOverlay — відображає поточний розмір при кожній зміні вікна
//    перевизначає resizeEvent
// ═══════════════════════════════════════════════════════════════════════════
class ResizeOverlay : public QWidget
{
public:
    explicit ResizeOverlay(QWidget *parent = nullptr) : QWidget(parent)
    {
        setMinimumSize(160, 60);
    }

protected:
    void resizeEvent(QResizeEvent *e) override
    {
        m_size = e->size();
        update();
        QWidget::resizeEvent(e);
    }

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(QPen(QColor("#dd6b20"), 2));
        p.setBrush(QColor("#fffaf0"));
        p.drawRoundedRect(rect().adjusted(1,1,-1,-1), 8, 8);

        p.setPen(QColor("#7b341e"));
        p.setFont(QFont("Segoe UI", 10));
        p.drawText(rect(), Qt::AlignCenter,
                   QString("resizeEvent\n%1 × %2 px")
                       .arg(m_size.width()).arg(m_size.height()));
    }

private:
    QSize m_size;
};

// ═══════════════════════════════════════════════════════════════════════════
// MainWindow
// ═══════════════════════════════════════════════════════════════════════════
class MainWindow : public QWidget
{
public:
    explicit MainWindow(QWidget *parent = nullptr) : QWidget(parent)
    {
        setWindowTitle("Subclass + Events Demo");
        setMinimumWidth(520);

        auto *root = new QVBoxLayout(this);
        root->setSpacing(14);
        root->setContentsMargins(16, 16, 16, 16);

        // ── 1 + 2: Кнопки ─────────────────────────────────────────────────
        auto *btnGroup = new QGroupBox("1. HoverButton  |  2. ClickRipple", this);
        auto *btnLayout = new QHBoxLayout(btnGroup);

        auto *hoverBtn  = new HoverButton("Hover мене", this);
        auto *rippleBtn = new ClickRipple("Клікни (ripple)", this);

        m_log = new QLabel("—", this);
        m_log->setAlignment(Qt::AlignCenter);
        m_log->setStyleSheet("color:#718096; font-style:italic;");

        connect(hoverBtn, &HoverButton::clicked, m_log, [this]{
            m_log->setText("HoverButton: clicked!");
        });

        btnLayout->addWidget(hoverBtn);
        btnLayout->addWidget(rippleBtn);
        root->addWidget(btnGroup);
        root->addWidget(m_log);

        // ── 3: DragLabel ──────────────────────────────────────────────────
        auto *dragGroup = new QGroupBox("3. DragLabel  (перетягуй мишею)", this);
        dragGroup->setMinimumHeight(100);
        // DragLabel позиціонується абсолютно всередині dragGroup
        auto *dragLabel = new DragLabel("✥ Перетягни мене", dragGroup);
        dragLabel->move(20, 30);

        root->addWidget(dragGroup);

        // ── 4: KeyDisplay ─────────────────────────────────────────────────
        auto *keyGroup = new QGroupBox("4. KeyDisplay  (keyPressEvent)", this);
        auto *keyLayout = new QHBoxLayout(keyGroup);
        keyLayout->addStretch();
        keyLayout->addWidget(new KeyDisplay(this));
        keyLayout->addStretch();
        root->addWidget(keyGroup);

        // ── 5: ResizeOverlay ──────────────────────────────────────────────
        auto *resGroup = new QGroupBox("5. ResizeOverlay  (resizeEvent)", this);
        auto *resLayout = new QHBoxLayout(resGroup);
        resLayout->addWidget(new ResizeOverlay(this));
        root->addWidget(resGroup);
    }

private:
    QLabel *m_log = nullptr;
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
