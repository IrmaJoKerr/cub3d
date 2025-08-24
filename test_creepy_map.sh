#!/bin/bash

# Test script for the creepy.cub map

MAP_PATH="maps/valid/creepy.cub"
EXECUTABLE="./cub3D"
LOGFILE="test_creepy_map.log"

# Check if the executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: Executable $EXECUTABLE not found. Please build the project first." | tee "$LOGFILE"
    exit 1
fi

# Run the test and pipe debug prints to the logfile
$EXECUTABLE $MAP_PATH > "$LOGFILE" 2>&1

# Capture the exit code
EXIT_CODE=$?

if [ $EXIT_CODE -eq 0 ]; then
    echo "Test passed successfully." | tee -a "$LOGFILE"
else
    echo "Test failed with exit code $EXIT_CODE." | tee -a "$LOGFILE"
fi

exit $EXIT_CODE
