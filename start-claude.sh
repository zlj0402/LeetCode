#!/bin/bash
# Claude Code startup script for Linux/Ubuntu
# Sets config directory to the project root's .claude folder

# Get the directory where this script is located
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Set Claude config directory
export CLAUDE_CONFIG_DIR="$SCRIPT_DIR/.claude"

echo "Claude config directory: $CLAUDE_CONFIG_DIR"

# Start Claude Code
claude "$@"