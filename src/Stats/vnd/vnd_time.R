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

### ensure that the best known are correctly noted in the dataframe
merged.df <- merge(df, best.known, by="Instance")
merged.df <- merged.df[,-which(names(merged.df) == "BestKnown.x")]
merged.df <- merged.df[,-which(names(merged.df) == "RelativeDev")]
colnames(merged.df)[which(names(merged.df) == "BestKnown.y")] <- "BestKnown"
Deviation <- 100*(merged.df$BestKnown - merged.df$BestCost)/merged.df$BestKnown
merged.df <- cbind(merged.df, Deviation)

print(merged.df)

filtered.df <- df %>% filter(Size == 150)

average_time_df <- filtered.df %>%
  group_by(Instance) %>%
  summarise(AvgTime = mean(Time)*100)

print(average_time_df)

write.table(average_time_df, file="src/Stats/outputs/vnd/vnd_time.csv", row.names = FALSE, quote=FALSE, sep=",")