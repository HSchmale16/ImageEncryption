# Build Script for this project
# Henry J Schmale
# March 3, 2015

# Define Pathes
projectDir=$(pwd)
articleDir="$(pwd)/article"
srcDir="$(pwd)/src"
latexEng=pdflatex

# COLOR CONSTANTS
NC='\033[0m'                           # No Color
PASS='\033[0;32m'                      # Green, passed test
FAIL='\033[0;31m'                      # Red, failed test

# Build the src code & test the exe on
# encryption and decryption
cd $srcDir
echo $(pwd)
./testCase.sh                          # Builds and tests the src code
cd $projectDir                         # Return to projectDir

# Article Builder
cd $articleDir
echo -n -e 'Making Article                          ['
$latexEng Encryption.tex > /dev/null   # Silence a noisy command
bibtex *.aux > /dev/null
$latexEng Encryption.tex > /dev/null
if [ $? -eq 0 ] ; then
    echo -e "${PASS}PASS${NC}]"
else
    echo -e "${FAIL}FAIL${NC}]"
fi
