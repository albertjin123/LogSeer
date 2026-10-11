<div align="center">

# 🛡️ LogGuardian

**AI 驱动的智能日志诊断专家**

[![Qt](https://img.shields.io/badge/Qt-6.12-41CD52?logo=qt&logoColor=white)](https://www.qt.io/)
[![C++](https://img.shields.io/badge/C++-20-00599C?logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.21+-064F8C?logo=cmake&logoColor=white)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)]()

*让日志分析变得简单、高效、智能*

[功能特性](#-功能特性) · [快速开始](#-快速开始) · [使用指南](#-使用指南) · [技术架构](#-技术架构) · [贡献](#-贡献指南)

</div>

---

## 📖 项目简介

**LogGuardian** 是一款基于 **Qt 6** 和 **C++20** 开发的跨平台桌面日志分析工具，集成 **DeepSeek 大语言模型**，能够自动分析系统日志、应用日志、设备日志，快速定位异常根因并给出可执行的修复建议。

告别肉眼逐行排查，让 AI 帮你读懂日志。

> 💡 **一句话概括**：把日志文件拖进来，点击"开始分析"，AI 告诉你哪里出了问题、为什么出问题、怎么修。

---

## ✨ 功能特性

### 🔍 智能日志加载
- 📂 支持**单文件 / 多文件 / 文件夹 / 递归文件夹**四种加载方式
- 🎯 自动识别 `.log`、`.txt`、`.out`、`.err`、`.trace` 及轮转日志（`app.log.1`、`app.log.2026-01-01`）
- 🔁 文件去重，重复加载自动跳过
- 📊 实时显示文件大小与加载状态

### 🤖 AI 智能分析
- 🧠 集成 **DeepSeek** 大语言模型，流式输出分析结果
- 🎯 自动识别 **严重等级**（CRITICAL / HIGH / MEDIUM / LOW / INFO）
- 🔬 精准定位**根本原因**，避免表面现象误导
- 📋 结构化输出**异常模式**与**修复建议**
- ⏱️ 实时显示分析耗时与 Token 消耗

### 🎨 现代化界面
- 🌗 **暗色 / 亮色**双主题无缝切换
- 🪟 可拖拽分割器，自由调整布局比例
- 💬 精致的 Toast 通知，替代传统弹窗
- 🔤 全局 QSS 主题管理，一处修改全局生效

### ⚙️ 灵活配置
- 🔌 支持多 AI 提供商（DeepSeek / OpenAI / Ollama / Claude）
- 💾 配置持久化，重启自动恢复
- 🔐 API Key 本地加密存储

---

## 🚀 快速开始

### 环境要求

| 依赖 | 版本要求 |
|---|---|
| **操作系统** | Windows 10+ / Linux / macOS |
| **Qt** | 6.5 或更高（推荐 6.12） |
| **C++ 标准** | C++20 |
| **CMake** | 3.21+ |
| **编译器** | MSVC 2022 / GCC 10+ / Clang 14+ |

### 编译步骤

```bash
# 1. 克隆项目
git clone https://github.com/albertjin123/LogSeer.git
cd LogSeer

# 2. 拉取子模块（LLMQore）
git submodule update --init --recursive

# 3. 配置 CMake
cmake -B build -DCMAKE_PREFIX_PATH="/path/to/Qt/6.12.0/msvc2022_64"

# 4. 构建
cmake --build build --config Release

# 5. 运行
./build/Release/LogGuardian.exe
```

### 打包发布

```bash
# Windows：使用 windeployqt 自动收集依赖
windeployqt --release build/Release/LogGuardian.exe

# 然后用 Inno Setup 或 NSIS 制作安装包
```

---

## 📘 使用指南

### 1️⃣ 配置 API Key

首次启动后，点击菜单 **设置 → API 配置**，填入你的 DeepSeek API Key。

> 🔑 **获取 API Key**：访问 [platform.deepseek.com/api_keys](https://platform.deepseek.com/api_keys) 注册并创建。

### 2️⃣ 加载日志

点击工具栏 **📂 打开日志**，选择：

- **打开文件** — 支持多选
- **打开文件夹** — 加载当前目录下所有日志
- **打开文件夹（含子目录）** — 递归扫描

加载后，左侧树会显示文件名、大小、状态。

### 3️⃣ 开始分析

1. 在左侧列表中**双击**选中要分析的日志文件
2. 点击工具栏 **▶ 开始分析**
3. 右侧面板将**流式显示** AI 分析结果

### 4️⃣ 查看结果

分析完成后，界面会显示：

| 项目 | 说明 |
|---|---|
| **严重等级** | CRITICAL / HIGH / MEDIUM / LOW / INFO |
| **根本原因** | AI 推断的问题根源 |
| **异常模式** | 识别出的异常及出现次数 |
| **建议措施** | 可执行的修复步骤 |
| **分析耗时** | 本次分析总用时 |

### ⌨️ 快捷键

| 快捷键 | 功能 |
|---|---|
| `Ctrl+O` | 打开日志 |
| `F5` | 开始分析 |
| `Shift+F5` | 停止分析 |
| `Ctrl+E` | 导出报告 |
| `Ctrl+,` | 打开设置 |
| `Ctrl+T` | 切换主题 |
| `F1` | 使用手册 |
| `F11` | 全屏切换 |

---

## 🏗️ 技术架构

### 技术栈

```
┌─────────────────────────────────────────┐
│              应用层 (UI)                 │
│      Qt Widgets + QSS 主题系统           │
├─────────────────────────────────────────┤
│              业务层                      │
│   日志加载 · 筛选 · 分析调度 · 主题管理    │
├─────────────────────────────────────────┤
│              通信层                      │
│      LLMQore · QNetworkAccessManager     │
├─────────────────────────────────────────┤
│              数据层                      │
│      QSettings · JSON 配置 · SQLite      │
└─────────────────────────────────────────┘
```

| 组件 | 技术 |
|---|---|
| **UI 框架** | Qt 6 Widgets |
| **编程语言** | C++20 |
| **构建系统** | CMake + FetchContent |
| **AI 集成** | [LLMQore](https://github.com/Palm1r/llmqore) |
| **网络通信** | QNetworkAccessManager + SSE |
| **数据持久化** | QSettings + JSON |
| **主题系统** | 全局 QSS + 动态切换 |

### 项目结构

```
LogGuardian/
├── src/
│   ├── main.cpp
│   ├── mainwindow.h / .cpp        # 主窗口
│   ├── settingsdialog.h / .cpp    # 设置对话框
│   ├── thememanager.h / .cpp      # 主题管理器
│   ├── ThemeColors.h              # 主题色定义
│   ├── ToastNotification.h / .cpp # Toast 通知组件
│   └── *.ui                       # Qt Designer 界面文件
├── config/
│   └── ai_providers.json          # AI 提供商配置
├── resources/                     # 图标、QSS 等资源
├── CMakeLists.txt
└── README.md
```

---

## 🎯 应用场景

| 场景 | 价值 |
|---|---|
| **运维排障** | 快速定位线上服务异常根因 |
| **开发调试** | 分析测试环境日志，缩短排查时间 |
| **工业设备监控** | 解析设备日志，提前预警故障 |
| **安全审计** | 识别异常访问模式与潜在威胁 |
| **教学演示** | 学习 Qt + AI 集成的完整案例 |

---

## 🤝 贡献指南

欢迎提交 Issue 和 Pull Request！

```bash
# 1. Fork 本仓库
# 2. 创建特性分支
git checkout -b feature/AmazingFeature

# 3. 提交更改
git commit -m "Add some AmazingFeature"

# 4. 推送到分支
git push origin feature/AmazingFeature

# 5. 提交 Pull Request
```

### 提交规范

| 类型 | 说明 |
|---|---|
| `feat:` | 新功能 |
| `fix:` | 修复 Bug |
| `docs:` | 文档更新 |
| `style:` | 代码格式调整 |
| `refactor:` | 重构 |
| `perf:` | 性能优化 |

---

## 📄 开源协议

本项目基于 **MIT License** 开源，允许商业使用和修改。

详见 [LICENSE](LICENSE) 文件。

---

## 🙏 致谢

- [Qt](https://www.qt.io/) — 跨平台应用开发框架
- [LLMQore](https://github.com/Palm1r/llmqore) — Qt/C++ LLM 客户端库
- [DeepSeek](https://www.deepseek.com/) — 大语言模型服务

---

<div align="center">

**⭐ 如果这个项目对你有帮助，请给个 Star ⭐**

Made with ❤️ by [Jeffrey](https://github.com/albertjin123)

</div>
