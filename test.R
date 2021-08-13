#library(rpart)
library(rpart2)
df = cars
#fit1 = rpart::rpart(speed~dist, df, minbucket=1, maxsurrogate=0)
fit2 = rpart(speed~dist, df, df, minbucket=1, minbucket_te=2, maxsurrogate=0)
