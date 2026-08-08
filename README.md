# Sem-5

A collection of Semester 5 course materials, lab notebooks, datasets and short programs. The repository is mostly Jupyter Notebooks with a small portion of C source code.

## Table of Contents
- [About](#about)
- [Repository structure](#repository-structure)
- [What the code & notebooks are for](#what-the-code--notebooks-are-for)
- [Notebooks — how to run](#notebooks---how-to-run)
- [C programs — how to compile & run](#c-programs---how-to-compile--run)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## About
This repo hosts Semester 5 coursework: interactive Jupyter Notebooks for labs and assignments, supporting PDFs and datasets, and some C programs used for programming/system exercises.

## Repository structure (high level)
- CCDL/ — course lab folder (README present; add content per lab)
- MLL/ — Machine Learning / Data Analysis lab materials (contains Lab 1 and Lab 2)
  - MLL/Lab 1/Lab1.ipynb
  - MLL/Lab 1/Week-01.pdf and WEEK-01-additional.pdf
  - MLL/Lab 2/Lab2.ipynb
  - MLL/Lab 2/Week-02-Data_Analysis_and_visualisation_with_Python-v2-aln.pdf
  - MLL/Lab 2/company-sales.csv, company.csv
- PCAPL/ — another course lab folder (contains Lab 1–3 subfolders)
- (possible C source files are present elsewhere in the repo — search for `*.c`)

Note: folder names reflect the current repo layout. Some README.md files inside folders are placeholders.

## What the code & notebooks are for
- MLL/Lab 1/Lab1.ipynb
  - Purpose: introductory notebook for Week 1 lab. It contains step-by-step exercises for the first lab session and accompanies Week-01 PDFs. Useful for learning notebook workflows and fundamental data handling examples.
  - Supporting files: `Week-01.pdf` and `WEEK-01-additional.pdf` provide lab instructions and reference material.

- MLL/Lab 2/Lab2.ipynb
  - Purpose: data analysis and visualization exercises. This notebook demonstrates data loading, cleaning, exploratory analysis, and common visualizations using Python libraries.
  - Datasets: `company-sales.csv` and `company.csv` used by the notebook for practice analyses and plotting.
  - Supporting file: `Week-02-Data_Analysis_and_visualisation_with_Python-v2-aln.pdf` contains the lab handout and detailed instructions.

- PCAPL/
  - Purpose: contains lab subfolders (Lab 1, Lab 2, Lab 3). These directories are intended for course-specific lab notebooks, exercises and any supporting code. Inspect each `PCAPL/Lab X/` folder to see the notebooks, code files and instructions for that lab.

- CCDL/
  - Purpose: course/lab directory (README currently empty). Add or open the CCDL subfolders to see course-specific notebooks and code.

- C programs (where present)
  - Purpose: short C source files typically implement assignment solutions, small system/algorithm experiments, or helper programs referenced by labs. Compile with gcc (see next section). If you want, I can list all `.c` files and add short descriptions for each file.

## Notebooks — how to run
1. Clone the repo:
   git clone https://github.com/paramshah2005/Sem-5.git
2. Create a virtual environment and install dependencies:
   python3 -m venv .venv
   source .venv/bin/activate
   pip install jupyterlab notebook numpy pandas matplotlib seaborn scipy
   (or install from requirements.txt if one is added)
3. Start Jupyter:
   jupyter lab
   or
   jupyter notebook
4. Open the notebooks (e.g., `MLL/Lab 1/Lab1.ipynb`, `MLL/Lab 2/Lab2.ipynb`) and run the cells. The datasets referenced (company-sales.csv, company.csv) are in the Lab 2 directory.

Tip: To run notebooks in Google Colab, use File → Open notebook → GitHub and paste the repository URL.

## C programs — how to compile & run
1. Locate C source files (search the repo for `*.c`). Example compile command:
   gcc -o program program.c
2. Run:
   ./program   # macOS/Linux
   program.exe # Windows

Check the top comments in each C file for specific usage, required flags, or input files.

## Contributing
- Add explanations or README content inside each course folder (CCDL, MLL, PCAPL) describing the lab objectives and the role of each file.
- Open issues for larger changes or datasets that should not be committed to the repo.
- Create PRs for fixes, improved notebooks, or adding a requirements.txt / LICENSE.

## License
If you want this content reused, add a LICENSE (MIT, Apache-2.0, etc.). I can add a recommended license on request.

## Contact
Owner: paramshah2005  
If you’d like, I can:
- commit this README to the repository,
- search the repo for every `.c` file and add one-line descriptions for each file,
- or expand the per-lab descriptions with short summaries pulled from each notebook.
