#!/usr/bin/env bash
# Dynamic shebang for cross-platform portability

# Check if more than one argument is being passed
if [ "$#" -ne 1 ]; then
    echo "USAGE: $0 /path/to/logs/"
    exit 1
fi

# Assign first argument to variable
LOG_D=$1

# Check if path exists & is NOT a directory
if [ ! -d "$LOG_D" ]; then
    echo "ERROR: Directory '$LOG_D' does not exist."
    exit 1
fi

# Script info
echo "SCRIPT: $0 running with $# argument"
echo "Starting continuous monitoring..."
echo "(Exit with: ^C)"

# Report file path
RPT_F="monitor/reports/full_report.txt"

# Start infinite loop (iterative execution)
while true; do

    # Print current timestamp
    echo "[$(date)] Running analysis cycle..."

    # Initialize (overwrite) report file
    echo "--- SYSTEM MONITOR FULL REPORT ---" > "$RPT_F"
    echo "Generated on: $(date)" >> "$RPT_F"
    echo "----------------------------------" >> "$RPT_F"

    # Save current IFS for later restoration
    OLD_IFS=$IFS
    # Set IFS to "new line" for filenames w/ spaces to be handled correctly
    IFS=$'\n'

    # Use 'find' to get all .log files and loop through them one by one
    # shellcheck disable=SC2044
    for file in $(find "$LOG_D" -name "*.log"); do

        # Extract filename from full path
        filename=$(basename "$file")

        # Check filename pattern to assign category label
        case "$filename" in
            system.log)
              CATEGORY="[SYSTEM EVENTS]"
              ;;
            network.log)
              CATEGORY="[NETWORK TRAFFIC]"
              ;;
            security.log)
              CATEGORY="[SECURITY ALERTS]"
              ;;
            *)
              CATEGORY="[UNKNOWN LOG TYPE]" # Default case
              ;;
        esac

        # Append separator and file header to report
        echo "" >> "$RPT_F"
        echo "=== $CATEGORY: $filename ===" >> "$RPT_F"

        ANALYZER_EXEC="./analyze_log"

        # Check if executable exists and is executable
        if [ -x "$ANALYZER_EXEC" ]; then
            # Run executable w/ the file as argument & append its output to report file
            "$ANALYZER_EXEC" "$file" >> "$RPT_F"
        else
            # Exit if executable missing
            echo "ERROR: '$ANALYZER_EXEC' not found!"
            exit 1
        fi
    done

    # Restore original IFS
    IFS=$OLD_IFS

    echo "Report updated. Waiting 10 seconds..."

    # Pause script for 10" before starting next loop
    sleep 10

done