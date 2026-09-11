# Machine Learning Lab (MLL)

## Overview
The MLL directory contains hands-on Jupyter notebook exercises progressing from NumPy fundamentals, through data analysis/visualization, into core supervised machine learning algorithms implemented both from scratch and with scikit-learn. Each lab folder contains the notebook, lecture slides/handout PDFs, and any datasets (CSV) used in the exercises.

## Subdirectories

### Lab 1: NumPy
Fundamentals of array manipulation with NumPy.
- **Q1**: Convert a 1-D array into a 2-D array with 3 rows
- **Q2**: Replace all odd numbers in an array with -1
- **Q3**: Find positions where elements of `x` are greater than / equal to corresponding elements of `y`
- **Q4**: Extract the first four columns of a 2-D array
- **Q5**: Generate a 1-D array of 10 random integers between 30 and 40
- **Q6**: Matrix addition, subtraction, and other operations on two 3×3 matrices using NumPy

### Lab 2: Data Analysis and Visualization with Python
Plotting and data visualization with Matplotlib and Pandas.
- **Q1**: Create a figure with `plt.figure()` and add axes manually with `add_axes`
- **Q2**: Create a figure with two overlapping axes and plot data on both
- **Q3**: Line plot of total profit per month from the company sales dataset
- **Q4**: Styled line plot (dotted red line, legend, custom labels) of total profit per month
- Datasets: `company-sales.csv`, `company.csv`

### Lab 3: Data Preprocessing and Regression Techniques
Introduction to data cleaning and simple linear regression.
- **Sample**: Simple Linear Regression using Scikit-Learn
- **Q1**: Data preprocessing on the hepatitis dataset — drop unused columns, handle missing values, create dummy variables, convert to NumPy
- **Q2**: Build a study-hours-vs-score dataset and a regression model reporting intercept (B0), slope (B1), and RMSE
- Datasets: `hepatitis_csv.csv`, `studyhours_marks.csv`

### Lab 4: Polynomial and Multiple Regression
Polynomial and multiple linear regression with manual and library implementations.
- **Sample**: Polynomial Regression using Scikit-Learn
- **Q1**: Polynomial regression on the Yield dataset (yield vs. temperature) across 5 temperature levels
- **Q2**: Multiple linear regression on the Infarct Rate dataset — comparing manual (matrix formulation) vs. library coefficients, with visualization
- Datasets: `Yield.csv`, `Infarc_Rate.csv`

### Lab 5: Logistic Regression and Stochastic Gradient Descent (SGD)
Gradient-descent-based linear and logistic regression.
- **Sample**: Logistic Regression using Scikit-Learn
- **Q1**: Linear regression via gradient descent on a mother/daughter height dataset, compared against sklearn
- **Q2**: Logistic regression via gradient descent on a study-hours-vs-pass/fail dataset, compared against sklearn
- **Q3**: Logistic regression with two independent variables (X1, X2) modeling a binary dependent variable
- Datasets: `mother_daughter_height.csv`, `student_pass.csv`, `logistic_data.csv`
- Slides: `L7 Logistic Regression.pptx`, `Slides-week5.pptx`

### Lab 6: Cost Functions
Understanding and visualizing cost/loss functions used in gradient-based learning.
- Manual vs. Scikit-Learn (`SGDRegressor`) stochastic gradient descent, comparing coefficient convergence and error over iterations
- Visualization of log-loss (cross-entropy) cost curves for `y=1` and `y=0` cases in logistic regression
- Custom gradient descent implementation tracking slope and MSE across iterations, on positive- and negative-slope datasets
- Sigmoid function and log-loss computation for binary classification cost analysis
- Dataset: `exp_salary.csv`
- Slides: `Slides-week 6.pptx`

### Lab 7: Naïve Bayes Classifier
Bayesian classification, implemented both analytically and from scratch.
- **Q1**: Apply Bayes' Theorem to a hostel/day-scholar student performance probability problem
- **Q2**: Naïve Bayes classifier from scratch (no scikit-learn) to predict whether a buyer will purchase a computer, based on buyer attributes
- **Q3**: Naïve Bayes text classifier from scratch to determine whether a given sentence is about sports
- Datasets: `buys_computer.csv`, `sports_text.csv`

## Key Technologies
- **NumPy** — array manipulation and numerical computing
- **Pandas** — data loading, cleaning, and preprocessing
- **Matplotlib** — data visualization and plotting
- **Scikit-Learn** — regression models (`LinearRegression`, `SGDRegressor`), preprocessing utilities
- **Concepts covered**: array operations, data cleaning/preprocessing, simple/polynomial/multiple linear regression, logistic regression, gradient descent (manual and library-based), cost/loss functions (MSE, log-loss), and Naïve Bayes classification (numeric and text)

## Purpose
This directory is part of Semester 5 coursework building foundational and applied machine learning skills — starting from NumPy/data-handling basics, progressing through regression and gradient-descent techniques, and culminating in probabilistic classification with Naïve Bayes, with an emphasis on comparing from-scratch implementations against scikit-learn.
