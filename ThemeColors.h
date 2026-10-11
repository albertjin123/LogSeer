#ifndef THEMECOLORS_H
#define THEMECOLORS_H

#include <QString>

struct Theme {
    // ===== 背景 =====
    QString background;         // 主背景
    QString panelBackground;    // 面板背景
    QString logBackground;      // 日志/输入区背景
    QString toolbarBackground;  // 工具栏背景
    QString statusBarBg;        // 状态栏背景

    // ===== 边框 =====
    QString border;

    // ===== 文字 =====
    QString textPrimary;        // 主文字
    QString textSecondary;      // 次要文字
    QString textOnAccent;       // 强调色上的文字（白）

    // ===== 强调色 =====
    QString accent;             // 强调色
    QString accentHover;        // 强调色悬停

    // ===== 状态色 =====
    QString success;
    QString warning;
    QString error;
    QString info;

    // ===== 按钮 =====
    QString buttonBg;           // 普通按钮背景
    QString buttonText;         // 普通按钮文字
    QString buttonHover;        // 悬停
    QString buttonPressed;      // 按下
    QString buttonBorder;       // 边框

    // ===== 主按钮 =====
    QString buttonPrimaryBg;
    QString buttonPrimaryText;
    QString buttonPrimaryHover;

    // ===== 禁用 =====
    QString buttonDisabledBg;
    QString buttonDisabledText;
};

namespace Themes {

// ============================================================
//  暗色主题
// ============================================================
inline const Theme Dark = {
    // 背景
    "#1E1E1E",  // background
    "#252526",  // panelBackground
    "#1A1A1A",  // logBackground
    "#2D2D30",  // toolbarBackground
    "#2D2D30",  // statusBarBg

    // 边框
    "#3C3C3C",  // border

    // 文字
    "#E0E0E0",  // textPrimary
    "#9E9E9E",  // textSecondary
    "#FFFFFF",  // textOnAccent

    // 强调色
    "#00B4D8",  // accent
    "#0096B7",  // accentHover

    // 状态色
    "#4CAF50",  // success
    "#FF9800",  // warning
    "#F44336",  // error
    "#2196F3",  // info

    // 普通按钮
    "#3C3C3C",  // buttonBg
    "#E0E0E0",  // buttonText
    "#4A4A4A",  // buttonHover
    "#2A2A2A",  // buttonPressed   ← 按下时更深
    "#4A4A4A",  // buttonBorder

    // 主按钮
    "#0086A8",  // buttonPrimaryBg
    "#FFFFFF",  // buttonPrimaryText
    "#00A3CC",  // buttonPrimaryHover

    // 禁用
    "#2A2A2A",  // buttonDisabledBg
    "#5A5A5A"   // buttonDisabledText
};

// ============================================================
//  亮色主题
// ============================================================
inline const Theme Light = {
    // 背景
    "#FFFFFF",  // background
    "#F5F5F5",  // panelBackground
    "#FAFAFA",  // logBackground
    "#E8E8E8",  // toolbarBackground
    "#E8E8E8",  // statusBarBg

    // 边框
    "#D0D0D0",  // border

    // 文字
    "#212121",  // textPrimary
    "#616161",  // textSecondary
    "#FFFFFF",  // textOnAccent

    // 强调色
    "#007ACC",  // accent
    "#005A9E",  // accentHover

    // 状态色
    "#4CAF50",  // success
    "#FF9800",  // warning
    "#F44336",  // error
    "#2196F3",  // info

    // 普通按钮
    "#E8E8E8",  // buttonBg
    "#212121",  // buttonText
    "#D8D8D8",  // buttonHover
    "#C8C8C8",  // buttonPressed   ← 按下时更深
    "#C0C0C0",  // buttonBorder

    // 主按钮
    "#007ACC",  // buttonPrimaryBg
    "#FFFFFF",  // buttonPrimaryText
    "#005A9E",  // buttonPrimaryHover

    // 禁用
    "#EFEFEF",  // buttonDisabledBg
    "#A0A0A0"   // buttonDisabledText
};

} // namespace Themes

#endif // THEMECOLORS_H