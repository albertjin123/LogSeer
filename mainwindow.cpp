#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ThemeColors.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_aiClient = new LLMQore::OpenAIClient(
        "https://api.deepseek.com",   // DeepSeek API 地址
        "your api key",                       // 你的 API Key
        "deepseek-flash"
        );
    InitUi();
    lastDir = QDir::homePath();
    InitConnect();
    setupSplitter();

}

MainWindow::~MainWindow()
{
    // 先删 AI 客户端，避免它在 ui 析构后触发回调
    if (m_aiClient) {
        m_aiClient->setParent(nullptr);   // 断开父子关系
        delete m_aiClient;
        m_aiClient = nullptr;
    }
    delete ui;
}

void MainWindow::InitUi()
{
    //Init QTreeWidget Ui
    ui->FiletreeWidget->setColumnCount(3);
    ui->FiletreeWidget->setHeaderLabels({"文件名","大小","状态"});
    ui->FiletreeWidget->setRootIsDecorated(false);   // 不显示展开箭头
    ui->FiletreeWidget->setAlternatingRowColors(true);
    ui->FiletreeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->FiletreeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 列宽
    ui->FiletreeWidget->setColumnWidth(0, 140);   // 文件名
    ui->FiletreeWidget->setColumnWidth(1, 80);    // 大小
    ui->FiletreeWidget->setColumnWidth(2, 60);    // 状态
}

void MainWindow::InitConnect()
{
    connect(ui->actionThemeDark,&QAction::triggered,this,&MainWindow::onApplyDarkTheme);
    connect(ui->actionThemeLight,&QAction::triggered,this,&MainWindow::onApplyLightTheme);
    connect(ui->actionThemeSystem,&QAction::triggered,this,&MainWindow::onApplyDSystemTheme);
    connect(ui->actionAboutQt,&QAction::triggered,this,&MainWindow::aboutQt);
    connect(ui->actionAboutLogSeek,&QAction::triggered,this,&MainWindow::aboutLogSeer);
    // 工具栏按钮（假设 objectName 是 pushButton_6）
    connect(ui->openLogFile, &QPushButton::clicked, this, &MainWindow::onOpenLog);

    // 菜单项
    connect(ui->action_O, &QAction::triggered, this, &MainWindow::onOpenLog);
    connect(m_aiClient, &LLMQore::BaseClient::accumulatedReceived,
                    this, [this](const LLMQore::RequestID &, const QString &answer) {
                        ui->textBrowser->setPlainText(answer);
                    });

    // 请求完成
    connect(m_aiClient, &LLMQore::BaseClient::requestCompleted,
            this, [this](const LLMQore::RequestID &, const QString &) {
                qint64 ms = m_analyzeTimer.elapsed();
                double sec = ms/1000.0;
                QString timeText = (sec < 60)
                                       ? QString("%1 秒").arg(sec, 0, 'f', 2)
                                       : QString("%1 分 %2 秒").arg(ms / 60000).arg((ms % 60000) / 1000.0, 0, 'f', 1);
                ui->anyTime->setText(timeText);
                ToastManager::success(this, tr("分析完成"),
                                      tr("耗时 %1").arg(timeText));
            });

    // 请求失败
    connect(m_aiClient, &LLMQore::BaseClient::requestFailed,
            this, [this](const LLMQore::RequestID &, const QString &error) {
                ToastManager::error(this, tr("分析失败"), error);
            });
    connect(ui->StartAnalyze, &QPushButton::clicked, this, &MainWindow::onStartAnalyze);
    connect(ui->StopAnalyze, &QPushButton::clicked, this, &MainWindow::onStopAnalyze);
}

void MainWindow::onApplyDarkTheme()
{
    ThemeManager::instance().applyTheme(qApp,ThemeManager::Dark);
    qDebug()<<"1";
}

void MainWindow::onApplyLightTheme()
{
    ThemeManager::instance().applyTheme(qApp,ThemeManager::Light);
}

void MainWindow::onApplyDSystemTheme()
{
    // 暂未实现，先用暗色
    ThemeManager::instance().applyTheme(qApp, ThemeManager::Dark);
}

void MainWindow::aboutQt()
{
    QApplication::aboutQt();
}

void MainWindow::aboutLogSeer()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("关于 LogSeer"));
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setText(
        QString(
            "<h2>LogSeer</h2>"
            "<p style='color:#00B4D8;'><b>AI 驱动的智能日志诊断专家</b></p>"
            "<p>版本：v1.0.0</p>"
            "<p>基于 Qt %1 构建</p>"
            "<p>Copyright © 2026 Jeffrey</p>"
            "<p style='font-size:14px;'><b>本项目基于 MIT License 开源，允许商业使用和修改。</b></p>"
            "<p><a href='https://github.com/Jeffrey/LogSeer'>项目主页</a></p>"
            ).arg(QT_VERSION_STR)
        );

    msgBox.setFixedSize(420, 260);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::setupSplitter()
{
    // 1. 从旧布局中取出所有需要转移的控件
    ui->verticalLayout_3->removeWidget(ui->label_2);
    ui->verticalLayout_3->removeWidget(ui->FiletreeWidget);
    ui->verticalLayout_2->removeWidget(ui->textBrowser);

    // 2. 清空 horizontalLayout_4 里的旧 layout
    QLayoutItem *item;
    while ((item = ui->horizontalLayout_4->takeAt(0)) != nullptr) {
        delete item;
    }

    // 3. 创建左侧容器：放 label_2 + treeWidget
    QWidget *leftWidget = new QWidget(this);
    leftWidget->setObjectName("leftPanel");
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->setContentsMargins(4, 4, 4, 4);
    leftLayout->setSpacing(4);
    leftLayout->addWidget(ui->label_2);
    leftLayout->addWidget(ui->FiletreeWidget);

    // 4. 创建右侧容器：放 textBrowser
    QWidget *rightWidget = new QWidget(this);
    rightWidget->setObjectName("rightPanel");
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);
    rightLayout->setContentsMargins(4, 4, 4, 4);
    rightLayout->setSpacing(4);
    rightLayout->addWidget(ui->textBrowser);

    // 5. 创建 QSplitter
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setObjectName("splitterMain");
    splitter->setChildrenCollapsible(false);
    splitter->setHandleWidth(3);
    splitter->addWidget(leftWidget);
    splitter->addWidget(rightWidget);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 4);
    splitter->setSizes({250, 1000});

    // 6. 放回 horizontalLayout_4
    ui->horizontalLayout_4->addWidget(splitter);
}

void MainWindow::onOpenLog()
{
    QMenu menu(this);
    QAction *actFile   = menu.addAction(tr("📄 打开文件..."));
    QAction *actFolder = menu.addAction(tr("📁 打开文件夹..."));
    menu.addSeparator();
     QAction *actRecursive = menu.addAction(tr("📂 打开文件夹（含子目录）..."));
    actRecursive->setCheckable(false);
     QAction *chosen = menu.exec(QCursor::pos());
    if(chosen == actFile){
         onOpenFiles();
    }
    else if(chosen == actFolder){
        onOpenFolder();
    }
    else if(chosen == actRecursive){
        // 带递归的文件夹打开
        QString dir = QFileDialog::getExistingDirectory(
            this,tr("选择日志文件夹"),lastDir
            );
        if(dir.isEmpty())return;
        lastDir = dir;
        QStringList files = collectLogFiles(dir, true);
        if (files.isEmpty()) {
             ToastManager::error(this,"错误信息","该文件夹下面无Log文件");
            return;
        }
        for (const QString &f : files) {
            addLogFile(f);
        }
    }
}

void MainWindow::onOpenFiles()
{
    //打开对话框 选择一个文件 获取文件Name
    QStringList files = QFileDialog::getOpenFileNames(
        this,tr("选择日志文件"),  lastDir,
        tr("日志文件 (*.log *.txt *.out *.log.*);;所有文件 (*.*)")
        );
    if(files.isEmpty())return;
    lastDir = QFileInfo(files.first()).absolutePath();
    for(const QString &path:files){
        addLogFile(path);
    }

}

void MainWindow::onOpenFolder()
{
    QString dir = QFileDialog::getExistingDirectory(
        this,tr("选择一个文件夹"),lastDir
        );
    if(dir.isEmpty())return;
    lastDir = dir;
    QStringList files = collectLogFiles(dir,false);
    if(files.isEmpty()){
        ToastManager::error(this,"错误信息","该文件夹下面无Log文件");
        return;
    }
    for (const QString &f : files) {
        addLogFile(f);
    }

}

void MainWindow::onStartAnalyze()
{
    // 1. 检查是否已加载日志
    if (ui->FiletreeWidget->topLevelItemCount() == 0) {
        ToastManager::warning(this, tr("提示"), tr("请先打开日志文件。"));
        return;
    }

    // 2. 取当前选中文件，没选中就取第一个
    QTreeWidgetItem *cur = ui->FiletreeWidget->currentItem();
    if (!cur) cur = ui->FiletreeWidget->topLevelItem(0);

    QString path = cur->data(0, Qt::UserRole).toString();
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ToastManager::error(this, tr("打开失败"), tr("无法读取日志文件。"));
        return;
    }
    QTextStream in(&file);
    QString logContent = in.readAll();
    file.close();

    // 3. 截断过长日志（控制 Token）
    const int MAX_LINES = 800;
    QStringList lines = logContent.split('\n');
     ui->LogLineCount->setText(tr("%1 行").arg(lines.size()));
    if (lines.size() > MAX_LINES) {
        lines = lines.mid(lines.size() - MAX_LINES);   // 取最后 N 行
        ui->usedLinesCount->setText(tr("%1 行").arg(lines.size()));
        logContent = lines.join('\n');
    }

    // 4. 清空报告区
    ui->textBrowser->clear();
    ui->textBrowser->setPlainText(tr("🤖 正在分析日志，请稍候...\n"));

    ToastManager::info(this, tr("分析中"), tr("正在调用 DeepSeek API..."));

    LLMQore::Conversation conversation;
    conversation.addUser(
        "你是一个专业的系统日志分析专家。请分析以下日志，"
        "用简洁的中文回答，包含：\n"
        "1. 整体状态概述\n"
        "2. 严重等级（CRITICAL/HIGH/MEDIUM/LOW/INFO）\n"
        "3. 根本原因\n"
        "4. 主要异常模式\n"
        "5. 建议措施\n\n"
        "========== 日志内容 ==========\n" + logContent
        );
    // 6. 发送请求（流式）
    qDebug() << "开始发送请求，日志长度：" << logContent.size();
    m_currentRequest = m_aiClient->ask(conversation);
    qDebug() << "请求已发出";
    m_analyzeTimer.start();
    ui->anyStartTime->setText(tr("%1").arg(QDateTime::currentDateTime().toString()));
}

void MainWindow::onStopAnalyze()
{
    m_aiClient->cancelRequest(m_currentRequest);
    ToastManager::info(this, tr("已停止"), tr("分析已中断。"));
}

void MainWindow::addLogFile(const QString &path)
{
    QFileInfo info(path);
    QString absPath = info.absoluteFilePath();

    // 去重：已经在树里就跳过
    for (int i = 0; i < ui->FiletreeWidget->topLevelItemCount(); ++i) {
        QTreeWidgetItem *it = ui->FiletreeWidget->topLevelItem(i);
        if (it->data(0, Qt::UserRole).toString() == absPath) {
            return;
        }
    }

    QTreeWidgetItem *item = new QTreeWidgetItem(ui->FiletreeWidget);
    item->setText(0, info.fileName());
    item->setText(1, formatSize(info.size()));
    item->setText(2, tr("已加载"));
    item->setData(0, Qt::UserRole, absPath);
    item->setToolTip(0, absPath);
}

bool MainWindow::isLogFile(const QString &path) const
{
    QString endName = QFileInfo(path).fileName().toLower();
    static const QStringList exts = {".log", ".txt", ".out", ".err", ".trace"};
    for(const QString& ext : exts){
        if(endName.endsWith(ext)){
            return true;
        }
    }
    // 形如 app.log.1、app.log.2026-01-01 的轮转日志
    if (endName.contains(".log.")) return true;
    return false;
}

QString MainWindow::formatSize(qint64 bytes) const
{
    if (bytes < 1024)
        return QString("%1 B").arg(bytes);
    if (bytes < 1024 * 1024)
        return QString("%1 KB").arg(bytes / 1024.0, 0, 'f', 1);
    if (bytes < 1024LL * 1024 * 1024)
        return QString("%1 MB").arg(bytes / 1024.0 / 1024.0, 0, 'f', 1);
    return QString("%1 GB").arg(bytes / 1024.0 / 1024.0 / 1024.0, 0, 'f', 1);
}

QStringList MainWindow::collectLogFiles(const QString &dir, bool recursive) const
{
    QStringList result;

    QDir d(dir);
    QDir::Filters filters = QDir::Files | QDir::Readable | QDir::NoSymLinks;
    if (recursive) {
        filters |= QDir::Dirs;
    }

    QStringList nameFilters = {"*.log", "*.txt", "*.out", "*.log.*"};

    QFileInfoList entries = d.entryInfoList(
        nameFilters + QStringList{"*"},
        filters,
        QDir::Name | QDir::DirsLast
        );

    for (const QFileInfo &info : entries) {
        if (info.isFile()) {
            if (isLogFile(info.fileName())) {
                result << info.absoluteFilePath();
            }
        } else if (info.isDir() && recursive) {
            // 跳过 . 和 ..
            if (info.fileName() == "." || info.fileName() == "..") continue;
            result << collectLogFiles(info.absoluteFilePath(), true);
        }
    }

    return result;
}
