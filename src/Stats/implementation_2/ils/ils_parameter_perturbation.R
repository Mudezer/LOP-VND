#install.packages("dplyr") ## Uncomment this line if you don't have the package installed
library(dplyr)

rm(list=ls())
df <- read.csv("results/ils/res_ils_perturbation_study.csv", sep=",", header = FALSE)
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

### perturbation study
df_subset <- merged.df[, c("Instance", "Perturbation", "Deviation")]

# Split the data frame by perturbation type
list_df_perturbations <- split(df_subset, df_subset$Perturbation)

# You can access each group using the perturbation type as the key
df_perturbation1 <- list_df_perturbations[["exchange"]]
df_perturbation2 <- list_df_perturbations[["insert"]]

# Merge the two data frames by the 'Instance' column
perturbated <- merge(df_perturbation1, df_perturbation2, by="Instance")
perturbated <- perturbated %>% select(-Perturbation.x, -Perturbation.y)
colnames(perturbated) <- c("Instance", "Exchange", "Insert")

# Calculate the mean of the 'Exchange' column
mean_exchange <- mean(perturbated$Exchange, na.rm = TRUE)

# Calculate the mean of the 'Insert' column
mean_insert <- mean(perturbated$Insert, na.rm = TRUE)

# Create a new data frame with these means : summary of the perturbation study
summ <- data.frame(Exchange = mean_exchange, Insert = mean_insert)

print(perturbated)
print(summ)

write.table(perturbated, file="src/Stats/outputs/ils/perturbation_study_instances.csv",sep = ",", row.names = FALSE, quote=FALSE)
write.table(summ, file="src/Stats/outputs/ils/perturbation_study_summary.csv",sep = ",", row.names = FALSE, quote=FALSE)



