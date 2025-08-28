#!/bin/bash

# Colors for output
LOG_FILE="test_results.log"
echo "" > "$LOG_FILE"
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Counters
TOTAL_MAPS=0
PASSED_MAPS=0
FAILED_MAPS=0
TIMEOUT_MAPS=0

# Result arrays
PASSED_FILES=()
FAILED_FILES=()
TIMEOUT_FILES=()

echo -e "${BLUE}=== cub3D Map Testing Script ===${NC}"
echo -e "${BLUE}Testing all maps in /maps folder with 5s timeout each${NC}"
echo ""

# Function to test a single map
test_map() {
    local map_file="$1"
    local relative_path="${map_file#/home/bleow/Coding/Core/cub3d/}"
    
    echo -n "Testing: ${relative_path}... "
    
    # Run the game with 5-second timeout
    timeout 5s ./cub3D "$map_file" > tmp_run.log 2>&1
    local exit_code=$?
    cat tmp_run.log >> "$LOG_FILE"
    echo "==== $relative_path (exit code: $exit_code) ====" >> "$LOG_FILE"
    rm -f tmp_run.log
    
    if [[ $exit_code -eq 1 && $relative_path == maps/invalid/* ]]; then
        echo -e "${GREEN}PASSED (expected fail for invalid map)${NC}"
        PASSED_FILES+=("$relative_path")
        ((PASSED_MAPS++))
    elif [[ $exit_code -eq 0 || $exit_code -eq 124 ]]; then
        echo -e "${GREEN}PASSED${NC}"
        PASSED_FILES+=("$relative_path")
        ((PASSED_MAPS++))
    else
        echo -e "${RED}FAILED (exit code: $exit_code)${NC}"
        FAILED_FILES+=("$relative_path")
        ((FAILED_MAPS++))
    fi
    
    ((TOTAL_MAPS++))
}

# Build the project first
echo -e "${BLUE}Building cub3D...${NC}"
make > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo -e "${RED}Build failed! Cannot proceed with testing.${NC}"
    exit 1
fi
echo -e "${GREEN}Build successful!${NC}"
echo ""

# Find and test all .cub files
echo -e "${BLUE}Discovering maps...${NC}"
mapfile -t MAP_FILES < <(find maps -name "*.cub" | sort)

if [ ${#MAP_FILES[@]} -eq 0 ]; then
    echo -e "${RED}No .cub files found in maps directory!${NC}"
    exit 1
fi

echo -e "${BLUE}Found ${#MAP_FILES[@]} map files${NC}"
echo ""

# Test each map
echo -e "${BLUE}Starting tests...${NC}"
for map_file in "${MAP_FILES[@]}"; do
    test_map "$map_file"
done

echo ""
echo -e "${BLUE}=== TEST RESULTS SUMMARY ===${NC}"
echo -e "Total maps tested: ${TOTAL_MAPS}"
echo -e "${GREEN}Passed: ${PASSED_MAPS}${NC}"
echo -e "${RED}Failed: ${FAILED_MAPS}${NC}"
echo ""

# Detailed results
if [ ${#PASSED_FILES[@]} -gt 0 ]; then
    echo -e "${GREEN}=== PASSED MAPS (${#PASSED_FILES[@]}) ===${NC}"
    for file in "${PASSED_FILES[@]}"; do
        echo -e "${GREEN}✓${NC} $file"
    done
    echo ""
fi

if [ ${#FAILED_FILES[@]} -gt 0 ]; then
    echo -e "${RED}=== FAILED MAPS (${#FAILED_FILES[@]}) ===${NC}"
    echo -e "${RED}These maps failed to launch or crashed immediately${NC}"
    for file in "${FAILED_FILES[@]}"; do
        echo -e "${RED}✗${NC} $file"
    done
    echo ""
fi

# Calculate success rate
if [ $TOTAL_MAPS -gt 0 ]; then
    SUCCESS_RATE=$((PASSED_MAPS * 100 / TOTAL_MAPS))
    echo -e "${BLUE}=== ANALYSIS ===${NC}"
    echo -e "Functional maps (passed): ${PASSED_MAPS}/${TOTAL_MAPS} (${SUCCESS_RATE}%)"
    
    if [ $SUCCESS_RATE -eq 100 ]; then
        echo -e "${GREEN}🎉 All maps are functional!${NC}"
    elif [ $SUCCESS_RATE -ge 80 ]; then
        echo -e "${GREEN}Great job! Most maps are working.${NC}"
    elif [ $SUCCESS_RATE -ge 60 ]; then
        echo -e "${YELLOW}Good progress, but some maps need attention.${NC}"
    else
        echo -e "${RED}Many maps are failing. Review needed.${NC}"
    fi
fi

echo ""
echo -e "${BLUE}Testing completed!${NC}"

# Exit with appropriate code
if [ $FAILED_MAPS -eq 0 ]; then
    exit 0
else
    exit 1
fi
