#include <QApplication>
#include <QHeaderView>
#include <QPainter>
#include <QSpinBox>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QTableView>

// ─────────────────────────────────────────────────────────────────────────────
// 1. Delegate — inherits QStyledItemDelegate and overrides three methods:
//      paint()         — custom rendering
//      createEditor()  — widget used while editing
//      setEditorData() — populate editor from model
//      setModelData()  — write editor value back to model
// ─────────────────────────────────────────────────────────────────────────────
class ProgressDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit ProgressDelegate(QObject* parent = nullptr)
        : QStyledItemDelegate(parent) {}

    // ── paint ─────────────────────────────────────────────────────────────────
    // Draws a filled progress bar instead of plain text.
    void paint(QPainter*                   painter,
               const QStyleOptionViewItem& option,
               const QModelIndex&          index) const override
    {
        const int value = index.data(Qt::DisplayRole).toInt();

        painter->save();

        // background
        const QColor bg = (option.state & QStyle::State_Selected)
                              ? option.palette.highlight().color()
                              : option.palette.base().color();
        painter->fillRect(option.rect, bg);

        // progress fill
        QRect fill = option.rect.adjusted(2, 3, -2, -3);
        fill.setWidth(static_cast<int>(fill.width() * value / 100.0));
        painter->fillRect(fill, QColor(60, 160, 80));

        // percentage text, centred
        painter->setPen((option.state & QStyle::State_Selected)
                            ? option.palette.highlightedText().color()
                            : Qt::black);
        painter->drawText(option.rect, Qt::AlignCenter, QString("%1 %").arg(value));

        painter->restore();
    }

    // ── editor ────────────────────────────────────────────────────────────────
    // Return a QSpinBox for editing the progress value (0–100).
    QWidget* createEditor(QWidget*                    parent,
                          const QStyleOptionViewItem& /*option*/,
                          const QModelIndex&          /*index*/) const override
    {
        auto* spin = new QSpinBox(parent);
        spin->setRange(0, 100);
        spin->setSuffix(" %");
        return spin;
    }

    void setEditorData(QWidget* editor, const QModelIndex& index) const override
    {
        auto* spin = static_cast<QSpinBox*>(editor);
        spin->setValue(index.data(Qt::EditRole).toInt());
    }

    void setModelData(QWidget*            editor,
                      QAbstractItemModel* model,
                      const QModelIndex&  index) const override
    {
        auto* spin = static_cast<QSpinBox*>(editor);
        spin->interpretText();
        model->setData(index, spin->value(), Qt::EditRole);
    }
};

// ─────────────────────────────────────────────────────────────────────────────
// 2. Main
// ─────────────────────────────────────────────────────────────────────────────
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Simple model: task name + progress (0-100)
    auto* model = new QStandardItemModel(5, 2);
    model->setHorizontalHeaderLabels({"Task", "Progress"});

    const QStringList tasks = {
        "Download assets", "Compile sources",
        "Run unit tests",  "Deploy to server", "Send report"
    };
    const QList<int> progress = {100, 75, 40, 10, 0};

    for (int i = 0; i < tasks.size(); ++i) {
        model->setItem(i, 0, new QStandardItem(tasks[i]));
        model->setItem(i, 1, new QStandardItem(QString::number(progress[i])));
    }

    // View
    auto* view = new QTableView();
    view->setModel(model);
    view->setWindowTitle("Basic Delegate — progress bar (double-click to edit)");

    // Attach delegate only to column 1
    view->setItemDelegateForColumn(1, new ProgressDelegate(view));

    view->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    view->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    view->setColumnWidth(1, 160);
    view->verticalHeader()->setDefaultSectionSize(32);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    view->resize(580, 230);
    view->show();

    return app.exec();
}

#include "main.moc"
