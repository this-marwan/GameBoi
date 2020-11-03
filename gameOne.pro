QT += widgets
QT += core

SOURCES += \
    killcovid.cpp \
    loginpage.cpp \
    main.cpp \
    scrollingbg.cpp \
    signupform.cpp \
    user.cpp \
    welcomepage.cpp

HEADERS += \
    killcovid.h \
    loginpage.h \
    scrollingbg.h \
    signupform.h \
    user.h \
    welcomepage.h

DISTFILES += \
    ../../Downloads/bg.png \
    users.json

RESOURCES += \
    static_images.qrc
