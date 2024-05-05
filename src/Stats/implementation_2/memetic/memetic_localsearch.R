#install.packages("dplyr") ## Uncomment this line if you don't have the package installed
library(dplyr)

rm(list=ls())
df <- read.csv("results/memetic/res_memetic_localsearch.csv", sep=",", header = FALSE)
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

### local search study
df_subset <- merged.df[, c("Instance", "LocalSearch", "Deviation")]

# Split the data frame by LocalSearch type
list_df_perturbations <- split(df_subset, df_subset$LocalSearch)

# accessing each group using the LocalSearch type as the key
df_exch <- list_df_perturbations[["exchange"]]
df_insert <- list_df_perturbations[["insert"]]
df_transpose <- list_df_perturbations[["transpose"]]

localSearch <- merge(df_exch, df_insert, by="Instance")
localSearch <- merge(localSearch, df_transpose, by="Instance")

# print(localSearch)

localSearch <- localSearch %>% select(-LocalSearch.x, -LocalSearch.y, -LocalSearch)
colnames(localSearch) <- c("Instance", "Exchange", "Insert", "Transpose")

# print(localSearch)

mean_exchange <- mean(localSearch$Exchange, na.rm = TRUE)
mean_insert <- mean(localSearch$Insert, na.rm = TRUE)
mean_transpose <- mean(localSearch$Transpose, na.rm = TRUE)

# summary data frame with only the means
summ <- data.frame(Exchange = mean_exchange, Insert = mean_insert, Transpose = mean_transpose)

print(localSearch)
print(summ)

write.table(localSearch, file="src/Stats/outputs/memetic/local_search_study.csv",sep = ",", row.names = FALSE, quote=FALSE)
write.table(summ, file="src/Stats/outputs/memetic/local_search_summary.csv",sep = ",", row.names = FALSE, quote=FALSE)
