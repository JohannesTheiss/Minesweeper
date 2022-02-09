##### THE APPLICATION #####
TEMPLATE = app
VERSION = 1.0

###### Qt modules ####### 
QT += qml     \
      gui     \
      quick   \
      core    \
      widgets \
      multimedia

###### view, scripts and images ###### 
RESOURCES += resourceCollection.qrc

RC_ICONS  += view/images/flagTransparent.ico

###### C++ ######
HEADERS = $$files(inc/*.h, true)
SOURCES = $$files(src/*.cpp, true)

###### build ###### 
# path to executable
DESTDIR = bin

# path to .o files
OBJECTS_DIR = .obj

# path to Qt Resource Compiler output files
RCC_DIR = .obj
MOC_DIR = .obj

# "make clean" settings
QMAKE_CLEAN = .obj/* \
               bin/*

# name of the executable
TARGET = minesweeper

###### prints ######
message(Qt version: $$[QT_VERSION])
message(Qt is installed in $$[QT_INSTALL_PREFIX])
message($$HEADERS)
message($$RESOURCES)
message($$SOURCES)
