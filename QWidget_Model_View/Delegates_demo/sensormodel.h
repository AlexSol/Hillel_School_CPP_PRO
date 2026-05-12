#pragma once

#include <QAbstractTableModel>
#include <QRandomGenerator>
#include <QTimer>
#include <vector>

struct SensorData {
    int     id;
    QString location;
    double  temperature;
};

class SensorModel : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit SensorModel(QObject* parent = nullptr)
        : QAbstractTableModel(parent)
    {
        sensors_ = {
            {1, "Kyiv - Center",   22.5},
            {2, "Kyiv - North",    18.3},
            {3, "Lviv - Old Town", 15.7},
            {4, "Odesa - Port",    38.4},
            {5, "Kharkiv - East",  41.2},
            {6, "Dnipro - South",  29.8},
            {7, "Zaporizhzhia",    33.1},
            {8, "Mykolaiv",        36.5},
        };

        auto* timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &SensorModel::simulateUpdate);
        timer->start(1000);
    }

    int rowCount(const QModelIndex&) const override
    {
        return static_cast<int>(sensors_.size());
    }
    int columnCount(const QModelIndex&) const override { return 4; }

    QVariant data(const QModelIndex& index, int role) const override
    {
        if (!index.isValid()) return {};
        const auto& s = sensors_[index.row()];

        if (role == Qt::DisplayRole) {
            switch (index.column()) {
            case 0: return s.id;
            case 1: return s.location;
            case 2: return QString("%1 °C").arg(s.temperature, 0, 'f', 1);
            case 3: return statusText(s.temperature);
            }
        }
        if (role == Qt::TextAlignmentRole) {
            if (index.column() == 0 || index.column() == 2)
                return QVariant(Qt::AlignCenter);
        }
        return {};
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override
    {
        if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return {};
        switch (section) {
        case 0: return "ID";
        case 1: return "Location";
        case 2: return "Temperature";
        case 3: return "Status";
        }
        return {};
    }

private slots:
    void simulateUpdate()
    {
        auto* rng   = QRandomGenerator::global();
        int   count = rng->bounded(2, 4);
        for (int n = 0; n < count; ++n) {
            int    row   = rng->bounded(static_cast<int>(sensors_.size()));
            double delta = (rng->generateDouble() - 0.5) * 4.0;
            sensors_[row].temperature =
                qBound(-10.0, sensors_[row].temperature + delta, 60.0);
            emit dataChanged(index(row, 2), index(row, 3), {Qt::DisplayRole});
        }
    }

    static QString statusText(double t)
    {
        if (t < 15.0) return "Cold";
        if (t < 30.0) return "Normal";
        if (t < 40.0) return "Warning";
        return "Critical";
    }

private:
    std::vector<SensorData> sensors_;
};
