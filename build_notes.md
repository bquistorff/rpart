# Building on Windows: 
## Trying to build binary package
- Fails saying that <temp dir>/index.html doesn't exist. I can run `devtools::document()`. I tried `devtools::build_vignettes()`, but it errored about `Output(s) listed in 'build/vignette.rds' but not in package:`. I can open the Rnw's in Rstudio, try to build, they make .tex but then latex error. I can open the .tex in TexWorks and build fine (after installing R's texmf root in MikTex to find Sweave.sty : https://tex.stackexchange.com/questions/153193/)
## Trying to build source package
- Building worked fine, but then tried to install `install.packages("../rpart_4.1-16.tar.gz", type="source")` gave `Warning in install.packages : package ‘../rpart_4.1-16.tar.gz’ is not available for this version of R`. 
## Tried to build binary package
- Building with binary package, but renamed vignettes/ so it didn't build them. It built and installed fine.