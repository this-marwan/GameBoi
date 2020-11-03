QT += widgets
QT += core

SOURCES += \
    killcovid.cpp \
    loginpage.cpp \
    main.cpp \
    player.cpp \
    scrollingbg.cpp \
    signupform.cpp \
    user.cpp \
    vaccine.cpp \
    virus.cpp \
    welcomepage.cpp

HEADERS += \
    killcovid.h \
    loginpage.h \
    player.h \
    scrollingbg.h \
    signupform.h \
    user.h \
    vaccine.h \
    virus.h \
    welcomepage.h

DISTFILES += \
    ../../Downloads/bg.png \
    users.json

RESOURCES += \
    static_images.qrc
