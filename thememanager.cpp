#include "ThemeManager.h"
#include <QApplication>

ThemeManager& ThemeManager::instance()
{
    static ThemeManager inst;
    return inst;
}

ThemeManager::ThemeManager(QObject *parent) : QObject(parent) {}

void ThemeManager::applyTheme(QApplication *app, ThemeType type)
{
    m_current = type;
    const Theme &t = (type == Dark) ? Themes::Dark : Themes::Light;
    app->setStyleSheet(buildStyleSheet(t));
    emit themeChanged(type);
}

QString ThemeManager::buildStyleSheet(const Theme &t) const
{
    QString qss;

    // 主窗口
    qss += QString("QMainWindow, QWidget#centralWidget {"
                   "  background-color: %1;"
                   "  color: %2;"
                   "}")
               .arg(t.background, t.textPrimary);

    // 菜单栏
    qss += QString("QMenuBar {"
                   "  background-color: %1;"
                   "  color: %2;"
                   "}")
               .arg(t.toolbarBackground, t.textPrimary);

    qss += QString("QMenuBar::item:selected {"
                   "  background-color: %1;"
                   "  color: %2;"
                   "}")
               .arg(t.accent, t.textOnAccent);

    // 菜单下拉
    qss += QString("QMenu {"
                   "  background-color: %1;"
                   "  color: %2;"
                   "  border: 1px solid %3;"
                   "}")
               .arg(t.panelBackground, t.textPrimary, t.border);

    qss += QString("QMenu::item:selected {"
                   "  background-color: %1;"
                   "  color: %2;"
                   "}")
               .arg(t.accent, t.textOnAccent);

    // 工具栏
    qss += QString("QToolBar {"
                   "  background-color: %1;"
                   "  border: none;"
                   "  spacing: 6px;"
                   "}")
               .arg(t.toolbarBackground);

    // 左侧面板
    qss += QString("QWidget#leftPanel {"
                   "  background-color: %1;"
                   "  border-right: 1px solid %2;"
                   "}")
               .arg(t.panelBackground, t.border);

    // 日志预览
    qss += QString("QPlainTextEdit#textEditLog {"
                   "  background-color: %1;"
                   "  color: %2;"
                   "  border: 1px solid %3;"
                   "  font-family: 'Cascadia Code', 'Consolas', monospace;"
                   "}")
               .arg(t.logBackground, t.textPrimary, t.border);

    // 按钮
    qss += QString("QPushButton {"
                   "  background-color: %1;"
                   "  color: %2;"
                   "  border: 1px solid %3;"
                   "  border-radius: 4px;"
                   "  padding: 6px 16px;"
                   "}")
               .arg(t.buttonBg, t.buttonText, t.buttonBorder);

    qss += QString("QPushButton:hover {"
                   "  background-color: %1;"
                   "}")
               .arg(t.buttonHover);

    qss += QString("QPushButton:pressed {"
                   "  background-color: %1;"
                   "}")
               .arg(t.buttonPressed);

    qss += QString("QPushButton:disabled {"
                   "  background-color: %1;"
                   "  color: %2;"
                   "}")
               .arg(t.buttonDisabledBg, t.buttonDisabledText);

    // 工具栏按钮
    qss += QString("QToolButton {"
                   "  background-color: transparent;"
                   "  color: %1;"
                   "  border: 1px solid transparent;"
                   "  border-radius: 4px;"
                   "  padding: 6px 12px;"
                   "}")
               .arg(t.textPrimary);

    qss += QString("QToolButton:hover {"
                   "  background-color: %1;"
                   "}")
               .arg(t.buttonHover);

    // 状态栏
    qss += QString("QStatusBar {"
                   "  background-color: %1;"
                   "  color: %2;"
                   "  border-top: 1px solid %3;"
                   "}")
               .arg(t.toolbarBackground, t.textPrimary, t.border);

    qss += QString("QStatusBar QLabel {"
                   "  color: %1;"
                   "  padding: 0 8px;"
                   "}")
               .arg(t.textPrimary);

    // Label
    qss += QString("QLabel {"
                   "  color: %1;"
                   "  background: transparent;"
                   "}")
               .arg(t.textPrimary);

    // 输入框
    qss += QString("QLineEdit, QTextEdit, QPlainTextEdit {"
                   "  background-color: %1;"
                   "  color: %2;"
                   "  border: 1px solid %3;"
                   "  border-radius: 3px;"
                   "  padding: 4px 6px;"
                   "}")
               .arg(t.logBackground, t.textPrimary, t.border);

    // 下拉框
    qss += QString("QComboBox {"
                   "  background-color: %1;"
                   "  color: %2;"
                   "  border: 1px solid %3;"
                   "  border-radius: 3px;"
                   "  padding: 4px 6px;"
                   "}")
               .arg(t.logBackground, t.textPrimary, t.border);

    // 树/列表
    qss += QString("QTreeView, QListWidget, QListView, QTableView {"
                   "  background-color: %1;"
                   "  color: %2;"
                   "  border: 1px solid %3;"
                   "  outline: none;"
                   "  selection-background-color: %4;"
                   "  selection-color: %5;"
                   "}")
               .arg(t.logBackground, t.textPrimary, t.border,
                    t.accent, t.textOnAccent);

    qss += QString("QHeaderView::section {"
                   "  background-color: %1;"
                   "  color: %2;"
                   "  border: 1px solid %3;"
                   "  padding: 4px;"
                   "}")
               .arg(t.panelBackground, t.textPrimary, t.border);

    // 滚动条
    qss += QString("QScrollBar:vertical {"
                   "  background: %1;"
                   "  width: 10px;"
                   "  margin: 0;"
                   "  border: none;"
                   "}")
               .arg(t.background);

    qss += QString("QScrollBar::handle:vertical {"
                   "  background: %1;"
                   "  border-radius: 4px;"
                   "  min-height: 20px;"
                   "}")
               .arg(t.border);

    qss += QString("QScrollBar::handle:vertical:hover {"
                   "  background: %1;"
                   "}")
               .arg(t.accent);

    qss += QString("QScrollBar::add-line:vertical,"
                   "QScrollBar::sub-line:vertical {"
                   "  height: 0;"
                   "}");

    qss += QString("QScrollBar::add-page:vertical,"
                   "QScrollBar::sub-page:vertical {"
                   "  background: transparent;"
                   "}");

    qss += QString("QScrollBar:horizontal {"
                   "  background: %1;"
                   "  height: 10px;"
                   "  margin: 0;"
                   "  border: none;"
                   "}")
               .arg(t.background);

    qss += QString("QScrollBar::handle:horizontal {"
                   "  background: %1;"
                   "  border-radius: 4px;"
                   "  min-width: 20px;"
                   "}")
               .arg(t.border);

    qss += QString("QScrollBar::handle:horizontal:hover {"
                   "  background: %1;"
                   "}")
               .arg(t.accent);

    qss += QString("QScrollBar::add-line:horizontal,"
                   "QScrollBar::sub-line:horizontal {"
                   "  width: 0;"
                   "}");

    qss += QString("QScrollBar::add-page:horizontal,"
                   "QScrollBar::sub-page:horizontal {"
                   "  background: transparent;"
                   "}");

    // 分割器
    qss += QString("QSplitter::handle {"
                   "  background-color: %1;"
                   "}")
               .arg(t.border);

    qss += QString("QSplitter::handle:horizontal { width: 2px; }");
    qss += QString("QSplitter::handle:vertical { height: 2px; }");

    // 提示框
    qss += QString("QToolTip {"
                   "  background-color: %1;"
                   "  color: %2;"
                   "  border: 1px solid %3;"
                   "  padding: 4px 8px;"
                   "}")
               .arg(t.panelBackground, t.textPrimary, t.border);

    // 对话框
    qss += QString("QDialog {"
                   "  background-color: %1;"
                   "  color: %2;"
                   "}")
               .arg(t.panelBackground, t.textPrimary);

    qss += QString("QMessageBox {"
                   "  background-color: %1;"
                   "}")
               .arg(t.panelBackground);

    qss += QString("QMessageBox QLabel {"
                   "  color: %1;"
                   "}")
               .arg(t.textPrimary);

    qss += QString("QMessageBox QPushButton {"
                   "  background-color: %1;"
                   "  color: %2;"
                   "  border: 1px solid %3;"
                   "  border-radius: 4px;"
                   "  padding: 6px 24px;"
                   "  min-width: 70px;"
                   "}")
               .arg(t.accent, t.textOnAccent, t.accentHover);

    return qss;
}