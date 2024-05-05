#install.packages("dplyr") ## Uncomment this line if you don't have the package installed
library(dplyr)

rm(list=ls())
df <- read.csv("results/ils/res_ils_init.csv", sep=",", header = FALSE)
df <- data.frame(df)
colnames(df) <- c("Instance", "Algorithm", "size", "AlgoClass", "Sequence", "Perturbation","Init",
                  "Moves","BestCost", "BestKnown","Time","RelativeDev")
# print(df)

best.known <- read.table("assets/best_known/best_known_150.txt")
best.known <- data.frame(best.known)
colnames(best.known) <- c("Instance", "BestKnown")
# print(best.known)

# ensure that the columns are numeric
df$Time <- as.numeric(df$Time)
df$RelativeDev <- as.numeric(df$RelativeDev)
df$size <- as.numeric(df$size)
df$Moves <- as.numeric(df$Moves)
df$BestCost <- as.numeric(df$BestCost)
df$BestKnown <- as.numeric(df$BestKnown)
best.known$BestKnown <- as.numeric(best.known$BestKnown)

merged.df <- merge(df, best.known, by="Instance")

## ensure that the best known are correctly noted in the dataframe
merged.df <- merged.df[,-which(names(merged.df) == "BestKnown.x")]
merged.df <- merged.df[,-which(names(merged.df) == "RelativeDev")]
colnames(merged.df)[which(names(merged.df) == "BestKnown.y")] <- "BestKnown"
Deviation <- 100*(merged.df$BestKnown - merged.df$BestCost)/merged.df$BestKnown
merged.df <- cbind(merged.df, Deviation)


# print(merged.df)

#retrieve only the instances with the initialization method and the respective deviations
df_subset <- merged.df[, c("Instance", "Init", "Deviation")]

# Split the data frame by initialization type
list_df_initializations <- split(df_subset, df_subset$Init)

# access each group using the initialization type as the key
df_init1 <- list_df_initializations[["cw"]]
df_init2 <- list_df_initializations[["random"]]

# Merge the two data frames by the 'Instance' column
initialized <- merge(df_init1, df_init2, by="Instance")
print(initialized)
initialized <- initialized %>% select(-Init.x, -Init.y)
colnames(initialized) <- c("Instance", "CW", "Random")

print(initialized)

# Calculate the mean of the 'Exchange' column
mean_cw <- mean(initialized$CW, na.rm = TRUE)

# Calculate the mean of the 'Insert' column
mean_random <- mean(initialized$Random, na.rm = TRUE)

# Create a new data frame with these means: summary of the initialization study
summ <- data.frame(CW = mean_cw, Random = mean_random)
print(summ)

# write.table(perturbated, "src/Stats/outputs/ils/init_study.csv", sep = ",", row.names = FALSE, col.names = TRUE)
write.table(summ, "src/Stats/outputs/ils/init_study_summary.csv", sep = ",", row.names = FALSE, col.names = TRUE)