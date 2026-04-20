@echo off
REM Claude Code startup script for Windows
REM Sets config directory to the project root's .claude folder

REM Get the directory where this script is located
set "SCRIPT_DIR=%~dp0"
REM Remove trailing backslash
set "SCRIPT_DIR=%SCRIPT_DIR:~0,-1%"

REM Set Claude config directory
set "CLAUDE_CONFIG_DIR=%SCRIPT_DIR%\.claude"

echo Claude config directory: %CLAUDE_CONFIG_DIR%

REM Start Claude Code
claude %*