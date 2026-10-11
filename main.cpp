#include "mainwindow.h"

#include <QApplication>
#include "thememanager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // 应用默认暗色主题
    ThemeManager::instance().applyTheme(&a, ThemeManager::Dark);
    w.resize(1500, 900);
    w.show();
    return QApplication::exec();
}
