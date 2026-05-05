/*
 * Composition demo: simple Card widget.
 *
 * Ідея: не перевизначати paintEvent, а зібрати красивий віджет
 * зі стандартних компонентів Qt (QLabel, QPushButton, Layout).
 */

#include <QApplication>
#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QFont>

class CardWidget : public QFrame
{
public:
	explicit CardWidget(QWidget *parent = nullptr) : QFrame(parent)
	{
		setObjectName("Card");
		setMinimumWidth(340);

		auto *root = new QVBoxLayout(this);
		root->setContentsMargins(16, 16, 16, 16);
		root->setSpacing(12);

		auto *image = new QLabel(this);
		image->setFixedHeight(140);
		image->setPixmap(makePreviewPixmap(image->size()));
		image->setScaledContents(true);
		image->setObjectName("CardImage");

		auto *title = new QLabel("Card Widget", this);
		title->setObjectName("CardTitle");

		auto *subtitle = new QLabel("Простий приклад composition: QWidget + QLabel + QPushButton", this);
		subtitle->setWordWrap(true);
		subtitle->setObjectName("CardSubtitle");

		auto *metaRow = new QHBoxLayout;
		auto *tag1 = new QLabel("Qt Widgets", this);
		auto *tag2 = new QLabel("Composition", this);
		tag1->setObjectName("Tag");
		tag2->setObjectName("Tag");
		metaRow->addWidget(tag1);
		metaRow->addWidget(tag2);
		metaRow->addStretch();

		auto *buttons = new QHBoxLayout;
		auto *btnOpen = new QPushButton("Відкрити", this);
		auto *btnLike = new QPushButton("Подобається", this);
		btnOpen->setObjectName("PrimaryButton");
		btnLike->setObjectName("GhostButton");
		buttons->addWidget(btnOpen);
		buttons->addWidget(btnLike);

		root->addWidget(image);
		root->addWidget(title);
		root->addWidget(subtitle);
		root->addLayout(metaRow);
		root->addLayout(buttons);
	}

private:
	static QPixmap makePreviewPixmap(const QSize &size)
	{
		QSize s = size.isValid() ? size : QSize(340, 140);
		QPixmap pix(s);
		pix.fill(Qt::transparent);

		QPainter p(&pix);
		p.setRenderHint(QPainter::Antialiasing);

		QLinearGradient bg(0, 0, s.width(), s.height());
		bg.setColorAt(0.0, QColor("#2b6cb0"));
		bg.setColorAt(1.0, QColor("#63b3ed"));
		p.fillRect(pix.rect(), bg);

		p.setBrush(QColor(255, 255, 255, 35));
		p.setPen(Qt::NoPen);
		p.drawEllipse(QPointF(s.width() * 0.8, s.height() * 0.25), 54, 54);
		p.drawEllipse(QPointF(s.width() * 0.3, s.height() * 0.85), 42, 42);

		p.setPen(QPen(QColor("#ebf8ff"), 2));
		p.setFont(QFont("Segoe UI", 13, QFont::Bold));
		p.drawText(pix.rect().adjusted(16, 10, -16, -10), Qt::AlignLeft | Qt::AlignTop, "Simple Card");
		p.setFont(QFont("Segoe UI", 10));
		p.drawText(pix.rect().adjusted(16, 0, -16, -14), Qt::AlignLeft | Qt::AlignBottom, "Built with composition");

		return pix;
	}
};

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	app.setStyle("Fusion");

	QWidget window;
	window.setWindowTitle("Composition: Card Widget");

	auto *layout = new QVBoxLayout(&window);
	layout->setContentsMargins(24, 24, 24, 24);
	layout->addWidget(new CardWidget(&window));

	window.setStyleSheet(R"(
		QWidget {
			background: #edf2f7;
			font-family: "Segoe UI", Arial, sans-serif;
			color: #1a202c;
		}

		#Card {
			background: #ffffff;
			border: 1px solid #e2e8f0;
			border-radius: 14px;
		}

		#CardImage {
			border-radius: 10px;
		}

		#CardTitle {
			font-size: 19px;
			font-weight: 700;
		}

		#CardSubtitle {
			color: #4a5568;
			font-size: 13px;
		}

		#Tag {
			background: #ebf8ff;
			color: #2b6cb0;
			border: 1px solid #bee3f8;
			border-radius: 10px;
			padding: 3px 8px;
			font-size: 12px;
		}

		#PrimaryButton {
			background: #2b6cb0;
			color: white;
			border: none;
			border-radius: 8px;
			padding: 7px 16px;
			font-weight: 600;
		}
		#PrimaryButton:hover {
			background: #2c5282;
		}

		#GhostButton {
			background: transparent;
			color: #2b6cb0;
			border: 1px solid #90cdf4;
			border-radius: 8px;
			padding: 7px 16px;
		}
		#GhostButton:hover {
			background: #ebf8ff;
		}
	)");

	window.resize(420, 360);
	window.show();
	return app.exec();
}
