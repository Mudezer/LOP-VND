#install.packages("dplyr") ## Uncomment this line if you don't have the package installed
library(dplyr)

rm(list=ls())
df <- read.csv("results/vnd/res_vnd.csv", sep=",", header = FALSE)


df <- data.frame(df)
colnames(df) <- c("Instance", "Algorithm","Size","AlgoClass","Pivot","Neighbour","Init","BestCost","BestKnown","Time","RelativeDev")
# print(df)

best.known <- read.table("assets/best_known/best_known.txt")
best.known <- data.frame(best.known)
colnames(best.known) <- c("Instance", "BestKnown")
# print(best.known)

# ensure that the columns are numeric
df$Time <- as.numeric(df$Time)
df$RelativeDev <- as.numeric(df$RelativeDev)
df$Size <- as.numeric(df$Size)
df$BestCost <- as.numeric(df$BestCost)
df$BestKnown <- as.numeric(df$BestKnown)
best.known$BestKnown <- as.numeric(best.known$BestKnown)

merged.df <- merge(df, best.known, by="Instance")

merged.df <- merged.df[,-which(names(merged.df) == "BestKnown.x")]
merged.df <- merged.df[,-which(names(merged.df) == "RelativeDev")]
colnames(merged.df)[which(names(merged.df) == "BestKnown.y")] <- "BestKnown"
Deviation <- 100*(merged.df$BestKnown - merged.df$BestCost)/merged.df$BestKnown
merged.df <- cbind(merged.df, Deviation)

# print(merged.df)

total.time <- merged.df %>%
  group_by(Algorithm,Size) %>%
  summarise(Time = sum(Time))
average.relative.deviation <- merged.df %>%
  group_by(Algorithm,Size) %>%
  summarise(Deviation = mean(Deviation))

new.df <- merge(total.time, average.relative.deviation, by=c("Algorithm","Size"))

sorted.df <- new.df %>% arrange(Size)

print(sorted.df)

write.table(sorted.df, file="src/Stats/outputs/vnd/general_vnd.csv", row.names = FALSE, quote=FALSE)