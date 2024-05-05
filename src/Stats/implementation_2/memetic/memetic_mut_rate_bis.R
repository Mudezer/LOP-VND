#install.packages("dplyr") ## Uncomment this line if you don't have the package installed
library(dplyr)
library(tidyr)

rm(list=ls())
df <- read.csv("results/memetic/res_memetic_mut_rate.csv", sep=",", header = FALSE)
df <- data.frame(df)
colnames(df) <- c("Instance","Algorithm","Size","AlgoClass","LocalSearch","MutationRate","PopInit","PopSize",
                  "BestCost","BestKnown","Time","RelativeDev")
# print(df)

best.known <- read.table("assets/best_known/best_known_150.txt")
best.known <- data.frame(best.known)
colnames(best.known) <- c("Instance", "BestKnown")
# print(best.known)

# ensure that the columns are numeric
df$Time <- as.numeric(df$Time)
df$RelativeDev <- as.numeric(df$RelativeDev)
df$Size <- as.numeric(df$Size)
df$PopSize <- as.numeric(df$PopSize)
df$MutationRate <- as.numeric(df$MutationRate)
df$BestCost <- as.numeric(df$BestCost)
df$BestKnown <- as.numeric(df$BestKnown)
best.known$BestKnown <- as.numeric(best.known$BestKnown)

merged.df <- merge(df, best.known, by="Instance")

### ensure that the best known are correctly noted in the dataframe
merged.df <- merged.df[,-which(names(merged.df) == "BestKnown.x")]
merged.df <- merged.df[,-which(names(merged.df) == "RelativeDev")]
colnames(merged.df)[which(names(merged.df) == "BestKnown.y")] <- "BestKnown"
Deviation <- 100*(merged.df$BestKnown - merged.df$BestCost)/merged.df$BestKnown
merged.df <- cbind(merged.df, Deviation)

# print(merged.df)

# summary on the mutation rate
Mutation_summary <- merged.df %>%
  group_by(MutationRate) %>%
  summarise(Deviation = mean(Deviation, na.rm = TRUE))

temp <- data.frame(Instance = merged.df$Instance,
                   MutationRate = merged.df$MutationRate,
                   Deviation = merged.df$Deviation)

# study on the mutation rate
Mutation_study <- temp %>%
  pivot_wider(names_from = MutationRate, values_from = Deviation)

print(Mutation_summary)

print(Mutation_study)

# write.table(Mutation_summary, "src/Stats/outputs/memetic/mutation_summary_2.csv", sep = ",", row.names = FALSE, col.names = TRUE)
# write.table(Mutation_study, "src/Stats/outputs/memetic/mutation_study_2.csv", sep = ",", row.names = FALSE, col.names = TRUE)

