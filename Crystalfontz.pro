TEMPLATE = subdirs

SUBDIRS += \
    cfa533 \
    consoleLibTester \
    tests \
    cfa533screens

cfa533screens.depends = cfa533
consoleLibTester.depends = cfa533 cfa533screens
