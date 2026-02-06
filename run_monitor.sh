#!/usr/bin/env bash
# Dynamic shebang for cross-platform portability

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
NC='\033[0m'  # No color (reset)

# Check if more than one argument is being passed
if [ "$#" -ne 1 ]; then
    echo -e "${YELLOW}USAGE: bash $0 /path/to/logs/${NC}"
    exit 1
fi

# Assign first argument to variable
LOG_D=$1

# Check if path exists & is NOT a directory
if [ ! -d "$LOG_D" ]; then
    echo -e "${RED}ERROR: Directory '$LOG_D' does not exist.${NC}"
    exit 1
fi

# Script info
echo -e "${GREEN}SCRIPT: $0 running with $# argument${NC}\n"
echo "Starting continuous monitoring..."
echo -e "${RED}(Exit with: ^C)${NC}\n"

# Report file path
RPT_F="monitor/reports/full_report.txt"

# Start infinite loop (iterative execution)
while true; do

    # Clear terminal
    clear

    # Print current timestamp
    echo -e "[$(date)] - Running analysis cycle...\n"

    # Initialize (overwrite) report file
    echo "-------------------------- SYSTEM MONITOR FULL REPORT --------------------------" > "$RPT_F"
    echo "Run @ $(date)" >> "$RPT_F"
    echo "--------------------------------------------------------------------------------" >> "$RPT_F"

    # Save current IFS for later restoration
    OLD_IFS=$IFS
    # Set IFS to "new line" for filenames w/ spaces to be handled correctly
    IFS=$'\n'

    # Use 'find' to get all .log files and loop through them one by one
    for file in $(find "$LOG_D" -name "*.log"); do

        # Extract filename from full path
        filename=$(basename "$file")

        # Check filename pattern to assign category label and add color
        case "$filename" in
            system.log)
                CATEGORY="[SYSTEM EVENT]"
                COLOR=$BLUE
                ;;
            network.log)
                CATEGORY="[NETWORK TRAFFIC]"
                COLOR=$CYAN
                ;;
            security.log)
                CATEGORY="[SECURITY ALERT]"
                COLOR=$RED
                ;;
            timestamps.log)
                CATEGORY="[TIME TRACKING]"
                COLOR=$MAGENTA
                ;;
            *)
                CATEGORY="[UNKNOWN LOG TYPE]" # Default case
                COLOR=$YELLOW
                ;;
        esac

        # Inform user about file's category
        echo -e "Analyzing:${COLOR} $CATEGORY: $filename${NC}..."

        # Append separator and file header to report
        echo "" >> "$RPT_F"
        echo "===================== $CATEGORY: $filename =====================" >> "$RPT_F"

        ANALYZER_EXEC="./analyze_log"

# Check if executable exists and is executable
        if [ -x "$ANALYZER_EXEC" ]; then
            # Run executable w/ the file as argument & append its output to report file
            "$ANALYZER_EXEC" "$file" >> "$RPT_F"

            # Store exit code
            EXIT_CODE=$?

            # Check execution status
            if [ $EXIT_CODE -ne 0 ]; then
                # Handle Errors/Warnings
                if [ $EXIT_CODE -eq 1 ]; then
                    echo "[X] ERROR: Cannot open file." >> "$RPT_F"
                    echo -e "${RED}   -> Cannot open file (Exit code 1)${NC}"
                elif [ $EXIT_CODE -eq 2 ]; then
                    echo "[!] NOTE: File is empty." >> "$RPT_F"
                    echo -e "${YELLOW}   -> File was empty (Exit code 2)${NC}"
                else
                    echo "[X] ERROR: Analysis failed." >> "$RPT_F"
                    echo -e "${RED}   -> Analysis failed (Unknown exit code $EXIT_CODE)${NC}"
                fi
            fi
        else
            # Exit if executable missing (aborts script)
            echo -e "${RED}ERROR: '$ANALYZER_EXEC' not found!${NC}"
            exit 1
        fi
        # Success Message (Exit Code 0)
        echo -e "${GREEN}   -> Analyzed successfully.${NC}"
    done

    # Restore original IFS
    IFS=$OLD_IFS

    # Inform user about report status
    echo -e "\n${GREEN}Report updated.${YELLOW} Waiting 60 seconds...${NC}\n"

    # Pause script for 60" before starting next loop
    sleep 60
done