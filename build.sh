# Build Script for this project
# Henry J Schmale
# March 3, 2015

# Define Pathes
projectDir=$(pwd)
articleDir="$(pwd)/article"
srcDir="$(pwd)/src"
latexEng=pdflatex

# Build the src code & test the exe on
# encryption and decryption
cd $srcDir
echo $(pwd)
./testCase.sh                          # Builds and tests the src code
cd $projectDir                         # Return to projectDir

# Article Builder
cd $articleDir
echo -n -e 'Making Article                          [\033[0;32m'
$latexEng Encryption.tex > /dev/null   # Silence a noisy command
echo -e    'Done\033[0m]'
