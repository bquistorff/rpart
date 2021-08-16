#library(rpart)
library(rpart2)
df = cars
df2 = cbind(df, df)
#fit1 = rpart::rpart(speed~dist, df, minbucket=1, maxsurrogate=0)
fit2a = rpart(speed~dist, df, df, minbucket=1, minbucket_te=2)
fit2b = rpart(speed~dist, df2, df, minbucket=1, minbucket_te=2)
fit2c = rpart(speed~dist, df, df2, minbucket=1, minbucket_te=2)
