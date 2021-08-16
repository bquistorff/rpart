# The `rpart` package <img src="man/figures/rpart.png" alt="Rpart logo" style="float:right;height:232.25px" align="right" height="232.25">


[![CRAN_STATUS_BADGE](http://www.r-pkg.org/badges/version/rpart)](https://CRAN.R-project.org/package=rpart)
[![Downloads](http://cranlogs.r-pkg.org/badges/rpart)](https://CRAN.R-project.org/package=rpart)
[![Travis-CI Build Status](https://travis-ci.org/bethatkinson/rpart.svg?branch=master)](https://travis-ci.org/bethatkinson/rpart)


This is the source code for the  `rpart` package, which is a recommended package in R.
It gets posted to the comprehensive R archive (CRAN) as needed after undergoing a thorough testing.


## Overview

The `rpart` code builds classification or regression models of a very
general structure using a two stage procedure; the resulting models can be
represented as binary trees. The package implements many of the ideas found
in the CART (Classification and Regression Trees) book and programs of
Breiman, Friedman, Olshen and Stone.  Because CART is the trademarked name
of a particular software implementation of these ideas and `tree` was used
for the Splus routines of Clark and Pregibon, a different acronym -
Recursive PARTitioning or rpart - was chosen.

### Two-sample changes
We renamed the package `rpart2` so it can be installed side-by-side with `rpart`. We require additional param `data_te` and allow params `minbucket_te` and `minsplit_te` so that there is a leaf size constraint for tree building that considers a second (test) sample. Currently we don't allow surrogate splits. See for `test_2s.R` for simple usage/test.

Later to do's:
- put in warning that I don't support subset param and no constraint is put in xpred.
- allow surrogates (partition.c, notesplit.c)?
- put constraint in xpred (currently having test be original data)?
- add back in the vignettes (couldn't get to build easily)?


## Development
- Can build a source package and then install with `install.packages("../rpart2_4.1-16.tar.gz", repos = NULL, type = "source")`.
- `devtools::install(".", build_vignettes = FALSE)` (I also deleted `build/vignette.rds` and renamed `vignettes` to make this more automatic.)

### Checking for memory leaks
Use R with Asan. This is easy with docker images ([info](http://dirk.eddelbuettel.com/code/sanitizers.html)). This image has a separate `R` (normal) and `Rdevel` (with ASAN). Make sure can reproduce the `sanitizer` pkg error.
- `docker run -v <host dir>/GitHub/:/mnt/GitHub -ti rocker/r-devel-san /bin/bash`. 
- Originally thought I had to manually set compile flags with `Makevars` (couldn't get `configure.args` param working in `install.packages()`) `fileConn<-file("~/.R/Makevars"); writeLines(c('LDFLAGS=-fsanitize=undefined', 'MAIN_LDFLAGS=-fsanitize=undefined','CFLAGS=-fsanitize=undefined -fno-omit-frame-pointer -g -O2 -Wall -pedantic -mtune=native'), fileConn); close(fileConn)`, but not needed.
- Then can, from `Rdevel` use `install.packages("/mnt/GitHub/rpart2_4.1-16.tar.gz", repos = NULL, type = "source")` or can use `Rdevel CMD INSTALL /mnt/GitHub/rpart2_4.1-16.tar.gz`.