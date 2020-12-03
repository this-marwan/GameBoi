QT += widgets
QT += core
QT += multimedia

SOURCES += \
    Reversi.cpp \
    gameover.cpp \
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
    Reversi.h \
    gameover.h \
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
    static_images/reversi/Tokens.png \
    static_images/reversi/black_token.png \
    static_images/reversi/gameTwoMusic.wav \
    static_images/reversi/hint.png \
    static_images/reversi/tile.png \
    static_images/reversi/white_token.png \
    users.json

RESOURCES += \
    static_images.qrc
