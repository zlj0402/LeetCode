#!/bin/bash
# Claude Code startup script for Linux/macOS
# Sets config directory to the project root's .claude folder
# Usage: start-claude.sh [--install] [--uninstall]
#   --install: permanently set CLAUDE_CONFIG_DIR in shell profile, then restart vscode
#   --uninstall: remove CLAUDE_CONFIG_DIR from shell profile

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Set Claude config directory for current session
export CLAUDE_CONFIG_DIR="$SCRIPT_DIR/.claude"

# Handle --install flag: add to shell profile
if [ "$1" == "--install" ]; then
    echo "Installing CLAUDE_CONFIG_DIR to shell profile..."
    # Detect which shell profile to use
    if [ -f "$HOME/.bashrc" ]; then
        PROFILE="$HOME/.bashrc"
    elif [ -f "$HOME/.zshrc" ]; then
        PROFILE="$HOME/.zshrc"
    else
        PROFILE="$HOME/.profile"
    fi
    # Add export line if not already present
    if ! grep -q "CLAUDE_CONFIG_DIR.*LeetCode" "$PROFILE" 2>/dev/null; then
        echo "" >> "$PROFILE"
        echo "# Claude Code config for LeetCode project" >> "$PROFILE"
        echo "export CLAUDE_CONFIG_DIR=\"$SCRIPT_DIR/.claude\"" >> "$PROFILE"
        echo "Added to $PROFILE. Restart terminal or run: source $PROFILE"
    else
        echo "Already configured in $PROFILE"
    fi
    exit 0
fi

# Handle --uninstall flag: remove from shell profile
if [ "$1" == "--uninstall" ]; then
    echo "Removing CLAUDE_CONFIG_DIR from shell profiles..."
    for PROFILE in "$HOME/.bashrc" "$HOME/.zshrc" "$HOME/.profile"; do
        if [ -f "$PROFILE" ]; then
            sed -i '/CLAUDE_CONFIG_DIR.*LeetCode/d' "$PROFILE"
            sed -i '/# Claude Code config for LeetCode project/d' "$PROFILE"
        fi
    done
    echo "Done."
    exit 0
fi

echo "Claude config directory: $CLAUDE_CONFIG_DIR"

# Find claude from npm global prefix
CLAUDE_BIN="$(npm config get prefix 2>/dev/null)/claude"

# Start Claude Code
"$CLAUDE_BIN" "$@"