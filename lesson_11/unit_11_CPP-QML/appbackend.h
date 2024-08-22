#ifndef APPBACKEND_H
#define APPBACKEND_H

#include <QObject>
#include <QDebug>

class AppBackend : public QObject
{    
    Q_OBJECT
private:
    static constexpr auto credentialsFile = "credentials.json";
public:
    explicit AppBackend(QObject *parent = nullptr);
    int init();

    Q_PROPERTY(QString version READ version WRITE setVersion NOTIFY versionChanged)
    // Q_PROPERTY(QString user_name)

    QString version() const { return m_version; }
public slots:
    void userLogin(const QString& aUserName);
    void setVersion(const QString& aVersion);

signals:
    void versionChanged(const QString& aVersion);
    void loginResult(int aResCode, const QString& aDescriptions);

private:
    QString m_version = "0.1.1";
    QString user_name;

    QMap<QString, QString> m_credentials;
};

#endif // APPBACKEND_H
