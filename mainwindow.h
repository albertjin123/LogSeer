#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ThemeManager.h"
#include <QDebug>
#include <QMessageBox>
#include <QSplitter>
#include <QMenu>
#include <QFileDialog>
#include <QFileInfo>
#include "ToastNotification.h"
#include <LLMQore/Clients>
#include <QElapsedTimer>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private:
    void InitUi();
    void InitConnect();
    void addLogFile(const QString &path);
    bool isLogFile(const QString &path) const;     // 判断是否是日志文件
    QString formatSize(qint64 bytes) const;        // 格式化文件大小
    QStringList collectLogFiles(const QString &dir, bool recursive) const;
private slots:
    void onApplyDarkTheme();
    void onApplyLightTheme();
    void onApplyDSystemTheme();
    void aboutQt();
    void aboutLogSeer();
     void setupSplitter();
    void onOpenLog();          // 统一入口
    void onOpenFiles();        // 选择文件
    void onOpenFolder();       // 选择文件夹
    void onStartAnalyze ();
    void onStopAnalyze();
private:
    Ui::MainWindow *ui;
    QString lastDir = "";
    LLMQore::OpenAIClient *m_aiClient = nullptr;

    LLMQore::RequestID m_currentRequest;
    QElapsedTimer m_analyzeTimer; //分析生命周期同软件，所以声明再MainWindow栈上
};
#endif // MAINWINDOW_H
