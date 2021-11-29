#include "../../inc/utilities/UserMessage.h"

namespace utilities
{

// <summary> custom constructor for UserMessage </summary>
UserMessage::UserMessage(const QString title, const QString message, Icons icon, QObject *parent)
    : QObject(parent),
      mTitle(title),
      mMessage(message),
      mIconPath(mIconPathMap[icon])
{
}

// <summary> default destructor </summary>
UserMessage::~UserMessage()
{
}

// <summary> Getter for title </summary>
// <returns> String mTitle </returns>
QString UserMessage::title() const
{
    return mTitle;
}

// <summary> Getter for message </summary>
// <returns> String mMessage </returns>
QString UserMessage::message() const
{
    return mMessage;
}

// <summary> Getter for icon path </summary>
// <returns> String mIconPath </returns>
QUrl UserMessage::iconPath() const
{
    return mIconPath;
}

} // namespace utilities
