HEADERS       = glwidget.h \
                imageviewer.h \
                sphere.h \
                window.h
SOURCES       = glwidget.cpp \
                imageviewer.cpp \
                main.cpp \
                sphere.cpp \
                window.cpp

RESOURCES     = textures.qrc

QT           += widgets

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/textures
INSTALLS += target
