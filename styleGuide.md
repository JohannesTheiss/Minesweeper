# Style Guide

### C++
##### File Names: UpperCamelCase
e.g. `ViewBackendProxy.cpp`
and  `ViewBackendProxy.h`

##### Interface Names: UpperCamelCase preceded by capital `I`
e.g. `class IPatient {...}` 

##### Class Names: UpperCamelCase
e.g. `class ViewBackendProxy {...}`

##### Function Names: lowerCamelCase
e.g. `void savePatient() {...}`

##### Variable Names: lowerCamelCase
e.g. `std::string tableName;`
###### Member Variable Names: UpperCamelCase preceded by lower `m`
e.g.
```
private:
    std::string mTableName;
```
###### Const Variable Names: UpperCamelCase preceded by lower `c`
e.g. `const std::string cTableName;`


### QML
##### File Names: UpperCamelCase
e.g. `StyleSheet.qml`

##### QML Components: UpperCamelCase
e.g. `IconButton.qml`

##### Variable/ID Names: lowerCamelCase
e.g. `std::string tableName;`

