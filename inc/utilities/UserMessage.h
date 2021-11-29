#ifndef USERMESSAGE_H
#define USERMESSAGE_H

#include <QObject>
#include <QUrl>
#include <QMap>

namespace utilities
{

// enum for selecting diferent icon types
enum class Icons
{
    ERROR,
    CONFIRMATION,
};

// utility class that contains the information necessary to display a message box
class UserMessage : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QString message READ message CONSTANT)
    Q_PROPERTY(QUrl iconPath READ iconPath CONSTANT)

    public:

        // delete default constructor
        UserMessage() = delete;

        // custom constructor
        UserMessage(const QString title, const QString message, Icons icon, QObject *parent = nullptr);

        // default destructor
        ~UserMessage();

        // Getter for title
        QString title() const;

        // Getter for message
        QString message() const;

        // Getter for icon path
        QUrl iconPath() const;

    private:

        // map for mapping icon types to their path
        QMap <Icons, QUrl> mIconPathMap {{Icons::ERROR, QUrl("qrc:/error-color.png")},
                                        {Icons::CONFIRMATION, QUrl("qrc:/check-color.png")}};

        // constant attributes
        const QString mTitle;
        const QString mMessage;
        const QUrl mIconPath;

};

} // namespace utilities

#endif // USERMESSAGE_H
