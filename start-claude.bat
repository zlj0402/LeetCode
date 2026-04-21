@echo off
REM Claude Code startup script for Windows
REM Sets config directory to the project root's .claude folder
REM Usage: start-claude.bat [--install] [--uninstall]
REM   --install: permanently set CLAUDE_CONFIG_DIR in user environment, restart vscode
REM   --uninstall: remove CLAUDE_CONFIG_DIR from user environment

REM Get the directory where this script is located
set "SCRIPT_DIR=%~dp0"
REM Remove trailing backslash
set "SCRIPT_DIR=%SCRIPT_DIR:~0,-1%"

REM Set Claude config directory for current session
set "CLAUDE_CONFIG_DIR=%SCRIPT_DIR%\.claude"

REM Handle --install flag: permanently set user environment variable
if "%1"=="--install" (
    echo Installing CLAUDE_CONFIG_DIR to user environment...
    powershell -Command "[Environment]::SetEnvironmentVariable('CLAUDE_CONFIG_DIR', '%SCRIPT_DIR%\.claude', 'User')"
    echo Done. Restart VSCode/terminal to apply.
    goto :eof
)

REM Handle --uninstall flag: remove user environment variable
if "%1"=="--uninstall" (
    echo Removing CLAUDE_CONFIG_DIR from user environment...
    powershell -Command "[Environment]::SetEnvironmentVariable('CLAUDE_CONFIG_DIR', '', 'User')"
    echo Done.
    goto :eof
)

echo Claude config directory: %CLAUDE_CONFIG_DIR%

REM Find claude from npm global prefix
for /f "delims=" %%i in ('npm prefix -g') do set "NPM_PREFIX=%%i"
set "CLAUDE_BIN=%NPM_PREFIX%\claude.cmd"

echo Claude binary: %CLAUDE_BIN%

REM Start Claude Code
"%CLAUDE_BIN%" %*
