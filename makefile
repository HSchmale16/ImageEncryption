# Image Encrypter Makefile
# RepoLoc: /
# Author: Henry J Schmale
# Date: March 3, 2015

# LaTeX Engine
LATEX_ENG=pdflatex

# Src Code Directory
SRC_DIR=src

# Article Src Dir
ARTICLE_SRC_DIR=article

# Project Root
PRO_ROOT_DIR=$(shell pwd)

# ***********************************************
# *                Build Targets                *
# ***********************************************

#Primary Build Target
#    Builds Everything in the project
all: code article

# Builds the source code of the project
#   and runs the test cases script
code:
	echo $(shell pwd)
	bash ./$(SRC_DIR)/testCase.sh
	cd $(PRO_ROOT_DIR)

# Builds the article
article:
	cd $(ARTICLE_SRC_DIR)
	$(LATEX_ENG) Encryption.tex

