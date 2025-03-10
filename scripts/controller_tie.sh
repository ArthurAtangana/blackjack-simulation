#!/bin/bash

# Get the directory of the script
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Define the path to the executable
EXECUTABLE="$SCRIPT_DIR/../bin/controller_tie_test"

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: Executable not found at $EXECUTABLE"
    exit 1
fi

# Run executable and pass arguments if any
"$EXECUTABLE" "$@"

