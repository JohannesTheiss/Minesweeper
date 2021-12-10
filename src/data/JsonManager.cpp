#include "../../inc/data/JsonManager.h"

namespace data 
{

JsonManager::JsonManager(const QString fileName)
    : mFileName(fileName)
{
    mPathToJson = getJsonPath(fileName);
}

// <summary>Get path to JSON file from application folder</summary>
// <param name="fileName">Name of the JSON file</param>
// <returns>Absolute path to the JSON file</returns>
QString JsonManager::getJsonPath(QString fileName) const
{
    // get path to json source 
    QDir dir(QCoreApplication::applicationDirPath());
    QString d = "../" + mDataFolderName;

    if(!dir.exists(d)) {
        dir.mkdir(d);
    }

    dir.cd("../" + mDataFolderName);
    return dir.filePath(fileName);
}


/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * 
 * ############################# READ AND WRITE ###############################
 *
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
// <summary>Read a QJsonDocument from a JSON file</summary>
// <param name="pathToFile">JSON file to read from</param>
// <returns>QJsonDocument from the JSON file</returns>
QJsonDocument JsonManager::read(const QString pathToFile) const
{
    QFile file(pathToFile);
    QByteArray jsonData;

    if(file.exists())
    {
        try
        {
            // open 
            if(file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                // read the JSON file
                jsonData = file.readAll();
            }
            else
            {
                throw std::runtime_error("Die JSON-Datei konnte nicht geöffnet werden. (lesen)");
            }

            file.close();
        }
        catch(...)
        {
            throw std::runtime_error("Es konnte nicht von der JSON-Datei gelesen werden.");
        }
    }

    return QJsonDocument::fromJson(jsonData);
}

// <summary>Write QJsonDocument to a JSON file</summary>
// <param name="pathToFile">JSON file to write to</param>
// <param name="doc">JSON document to save</param>
// <returns>Nothing</returns>
void JsonManager::write(const QString pathToFile, const QJsonDocument &doc) const
{
    try
    {
        QFile file(pathToFile);
        
        // open
        if (file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate))
        {
            // write to JSON
            file.write(doc.toJson());
        }
        else
        {
            throw std::runtime_error("Die JSON-Datei konnte nicht geöffnet werden. (schreiben)");
        }

        file.close();
    }
    catch(...)
    {
        throw std::runtime_error("Es konnte nicht in die JSON-Datei geschrieben werden.");
    }
}

// <summary>Save a object to JSON to a file with a custom save function</summary>
// <param name="fileName">JSON file name to save the object to</param>
// <param name="parent">JSON parent of the new object</param>
// <param name="saveFunction">Custom function to save an object</param>
// <returns>Nothing</returns>
void JsonManager::save(const QString parent, const std::function<void(QJsonObject &)> saveFunction) const
{
    // read data if existing
    QJsonDocument document = read(mPathToJson);
    QJsonObject root = document.object();
    QJsonValue value = root.value(parent);
    QJsonArray jsonArray = value.toArray(); 

    // create and fill buffer object
    QJsonObject bufferObject;
    saveFunction(bufferObject);

    // append the buffer object
    jsonArray.push_back(QJsonValue(bufferObject));
    root.insert(parent, QJsonValue(jsonArray));

    // write to json
    document.setObject(root);
    write(mPathToJson, document);
}

// <summary>Save a list of objects to JSON to a file with a custom save function</summary>
// <param name="fileName">JSON file name to save the objects to</param>
// <param name="parent">JSON parent of the new objects</param>
// <param name="saveFunction">Custom function to save the list of objects</param>
// <returns>Nothing</returns>
void JsonManager::saveList(const QString parent, const std::function<void(QJsonArray &)> saveFunction) const
{
    // read data if existing
    QJsonDocument document = read(mPathToJson);
    QJsonObject root = document.object();
    QJsonValue value = root.value(parent);
    QJsonArray jsonArray = value.toArray(); 

    // create and fill buffer object
    saveFunction(jsonArray);

    root.insert(parent, QJsonValue(jsonArray));

    // write to json
    document.setObject(root);
    write(mPathToJson, document);
}

// <summary>Save a variable type T to a JSON value in a file</summary>
// <param name="fileName">JSON file name to save the value in</param>
// <param name="key">Key name of the property</param>
// <param name="value">New value of the property</param>
// <returns>Nothing</returns>
template<typename T>
void JsonManager::saveValue(QString key, T value) const
{
    // read data if existing
    QJsonDocument document = read(mPathToJson);
    QJsonObject root = document.object();

    if(!root.contains(key)) {
        root.insert(key, "");
    }

    QJsonValueRef valueRef = root.find(key).value();

    // change value
    valueRef = value;

    // write to json
    document.setObject(root);
    write(mPathToJson, document);
}

// <summary>Replace a list of objects in JSON to a file with a custom save function</summary>
// <param name="fileName">JSON file name to replace the objects in</param>
// <param name="parent">JSON parent of the list of objects</param>
// <param name="saveFunction">Custom function to replace the list of objects</param>
// <returns>Nothing</returns>
void JsonManager::replaceList(const QString parent, const std::function<void(QJsonArray &)> saveFunction) const
{


    // read data if existing
    QJsonDocument document = read(mPathToJson);
    QJsonObject root = document.object();

    // create and fill buffer object
    QJsonArray bufferArray;
    saveFunction(bufferArray);

    // insert the new list
    root.insert(parent, QJsonValue(bufferArray));

    // write to json
    document.setObject(root);
    write(mPathToJson, document);
}

// <summary>Load a JSON object from file with custom load function</summary>
// <param name="fileName">JSON file name to read the object from</param>
// <param name="parent">JSON parent to read the object from</param>
// <param name="loadFunction">Custom load function to read a custom object</param>
// <returns>Nothing</returns
void JsonManager::load(const QString parent, const std::function<void(QJsonArray &)> loadFunction) const
{
    try
    {
        // read json
        QJsonObject root = read(mPathToJson).object();

        // load data
        if(root.contains(parent))
        {
            QJsonValue value = root.value(parent);
            QJsonArray jsonArray = value.toArray(); 

            // load a custom object
            loadFunction(jsonArray);
        }
    }
    catch (...)
    {
        throw std::runtime_error("Es konnte nicht von der JSON-Datei gelesen werden.");
    }
}

// <summary>Load a JsonValue from file and return it</summary>
// <param name="fileName">JSON file name to load the value from</param>
// <param name="key">Key name of the property</param>
// <returns>The value for the given key</returns>
QJsonValue JsonManager::loadValue(QString key) const
{
    // read json
    QJsonObject root = read(mPathToJson).object();

    return root.contains(key) ? root.value(key) : QJsonValue(-1);
}

// <summary>Remove a JSON object from file with a custom remove function</summary>
// <param name="fileName">JSON file name to remove the object from</param>
// <param name="parent">JSON parent of the object</param>
// <param name="removeFunction">Custom remove function to remove a object</param>
// <returns>Nothing</returns>
void JsonManager::remove(const QString parent, const std::function<void(QJsonArray &)> removeFunction) const
{
    // read json
    QJsonDocument document = read(mPathToJson);
    QJsonObject root = document.object();

    // get reference from the array
    QJsonValueRef valueRef = root.find(parent).value();
    QJsonArray arr = valueRef.toArray(); 

    // make changes
    removeFunction(arr);

    // update the reference
    valueRef = arr;

    // write to json
    document.setObject(root);
    write(mPathToJson, document);
}


/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * 
 * #######################     SEARCH FUNCTIONS     ###########################
 *
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
// <summary>Find a JSON object with given key-value-pair in array</summary>
// <param name="key">Key to search for</param>
// <param name="value">Value to search for</param>
// <param name="arr">Array to search in</param>
// <returns>Index of the object with given key-value-pair</returns>
int JsonManager::findIndexByKeyValueInArray(const QString key, const QString value, QJsonArray &arr) const
{
    int index = 0;
    bool found = false;
    for (auto &&ref : arr) 
    {
        if (ref.toObject().value(key) == value)
        {
            found = true;
            break;
        }
        index++;
    }

    return found ? index : -1;
}

// <summary>Find a JSON object with given key-value-pair in a file</summary>
// <param name="fileName">JSON file name to search in</param>
// <param name="arrayName">Name of the array to search in</param>
// <param name="key">Key to search for</param>
// <param name="value">Value to search for</param>
// <returns>Index of the object with given key-value-pair in the file</returns>
int JsonManager::findIndexByKeyValueInJsonFile(const QString arrayName, const QString key, const QString value) const
{
    int index = -1;
    load(arrayName, [&](QJsonArray &root)
    {
        index = findIndexByKeyValueInArray(key, value, root);
    });

    return index;
}

}
