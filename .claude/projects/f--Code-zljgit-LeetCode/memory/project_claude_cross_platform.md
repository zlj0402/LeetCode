---
name: claude-cross-platform-setup
description: 跨平台使用 Claude Code 的脚本和 VSCode 配置实现方式
type: project
originSessionId: 364fdba1-df1b-4d06-99b8-5e25c9a42a87
---
# Claude Code 跨平台同步配置

## 目标
在 Windows/Linux/macOS 三个平台上统一使用项目内的 `.claude` 目录作为 Claude 配置目录，实现记忆跨平台同步。

## 实现方式

### 1. 启动脚本

**Windows - start-claude.bat:**
- 使用 `%~dp0` 获取脚本所在目录
- 设置 `CLAUDE_CONFIG_DIR=%SCRIPT_DIR%\.claude`
- 支持 `--install` 通过 PowerShell 永久设置用户环境变量
- 支持 `--uninstall` 移除环境变量

**Linux/macOS - start-claude.sh:**
- 使用 `BASH_SOURCE[0]` 获取脚本路径
- 导出 `export CLAUDE_CONFIG_DIR="$SCRIPT_DIR/.claude"`
- 支持 `--install` 写入 shell profile（自动检测 bashrc/zshrc/profile）
- 支持 `--uninstall` 从所有 profile 中移除

### 2. VSCode 统一配置 (.vscode/settings.json)

```json
{
  "terminal.integrated.env.windows": {
    "CLAUDE_CONFIG_DIR": "${workspaceFolder}\\.claude"
  },
  "terminal.integrated.env.linux": {
    "CLAUDE_CONFIG_DIR": "${workspaceFolder}/.claude"
  },
  "terminal.integrated.env.osx": {
    "CLAUDE_CONFIG_DIR": "${workspaceFolder}/.claude"
  }
}
```

使用 `${workspaceFolder}` 变量，根据操作系统自动设置正确的路径分隔符。

### 3. .gitignore 配置

```gitignore
# Claude Code - 跨平台同步记忆
.claude/*
!.claude/projects/
!.claude/projects/*/
!.claude/projects/*/memory/
!.claude/projects/*/memory/**/
!.claude/projects/*/MEMORY.md
!.claude/settings.json.template
!.claude/README.md
# Ignore large conversation history files
.claude/projects/*.jsonl
.claude/projects/*/*.jsonl
```

**策略：** 默认忽略 `.claude/*`，然后逐级取消忽略需要同步的目录：
- `projects/<project-id>/memory/` - 记忆文件目录
- `projects/<project-id>/MEMORY.md` - 记忆索引
- `settings.json.template` - 配置模板
- `README.md` - 说明文档
- 排除 `*.jsonl` 对话历史文件（体积大，不同步）

## 使用方法

1. **VSCode 终端：** 直接打开终端，环境变量已自动设置
2. **命令行：** 运行 `./start-claude.bat` 或 `./start-claude.sh`
3. **永久安装：** 运行 `./start-claude.sh --install` 写入 shell profile