#ifndef JSONMANAGER_H
#define JSONMANAGER_H

// QT
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QString>
#include <QList>
#include <QUrl>

// Qt JSON
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

// STL
#include <iostream>
#include <functional>

namespace data
{

class JsonManager
{
    public:
        JsonManager(const QString fileName);

        // ### Basic JSON operations ###
        // Save a object to JSON to a file with a custom save function
        void save(const QString parent, const std::function<void(QJsonObject &)> saveFunction) const;

        // Save a list of objects to JSON to a file with a custom save function
        void saveList(const QString parent, const std::function<void(QJsonArray &)> saveFunction) const;

        // Save a variable type T to a JSON value in a file
        template<typename T>
        void saveValue(QString key, T value) const;

        // Replace a list of objects to JSON to a file with a custom save function
        void replaceList(const QString parent, const std::function<void(QJsonArray &)> saveFunction) const;
        
        // Load a JSON object from file with custom load function
        void load(const QString parent, const std::function<void(QJsonValue &)> loadFunction) const;

        // Load a JsonValue from file and return it
        QJsonValue loadValue(QString key) const;
        
        // Remove a JSON object from file with a custom remove function
        void remove(const QString parent, const std::function<void(QJsonArray &)> removeFunction) const;


        // ### SEARCH FUNCTIONS ###
        // Find a JSON object with given key-value-pair in array
        //int findIndexByKeyValueInArray(const QString key, const QString value, QJsonArray &arr) const;

        // Find a JSON object with given key-value-pair in a file
        //int findIndexByKeyValueInJsonFile(const QString arrayName, const QString key, const QString value) const;
   

    private:
        // Get path to JSON file from application folder
        QString getJsonPath(const QString fileName) const;

        // Read a QJsonDocument from a JSON file
        QJsonDocument read(const QString pathToFile) const;

        // ### Read and write ###
        // Write QJsonDocument to a JSON file
        void write(const QString pathToFile, const QJsonDocument &doc) const;

        // JSON settings
        const QString mDataFolderName = "data";
        QString mFileName;
        QString mPathToJson;
};

}

#endif // JSONMANAGER_H
