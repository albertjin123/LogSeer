#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include "ThemeColors.h"
class ThemeManager : public QObject
{
    Q_OBJECT

public:
    enum ThemeType {Dark,Light};
    static ThemeManager& instance();
    void applyTheme(QApplication* app,ThemeType type);
    ThemeType currentTheme() const { return m_current; }
    QString buildStyleSheet(const Theme &t) const;

signals:
    void themeChanged(ThemeType type);
private:
    explicit ThemeManager(QObject *parent = nullptr);
    ThemeType m_current = Dark;
};

#endif // THEMEMANAGER_H
