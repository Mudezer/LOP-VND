#install.packages("dplyr") ## Uncomment this line if you don't have the package installed
library(dplyr)

rm(list=ls())

# Memetic data retrieval
memetic <- read.csv("results/memetic/res_memetic.csv", sep=",", header = FALSE)
memetic <- data.frame(memetic)
colnames(memetic) <- c("Instance","Algorithm","Size","AlgoClass","LocalSearch","MutationRate","PopInit","PopSize",
                  "BestCost","BestKnown","Time","RelativeDev")

best.known <- read.table("assets/best_known/best_known_150.txt")
best.known <- data.frame(best.known)
colnames(best.known) <- c("Instance", "BestKnown")

# ensure that the columns are numeric
memetic$Time <- as.numeric(memetic$Time)
memetic$RelativeDev <- as.numeric(memetic$RelativeDev)
memetic$Size <- as.numeric(memetic$Size)
memetic$PopSize <- as.numeric(memetic$PopSize)
memetic$MutationRate <- as.numeric(memetic$MutationRate)
memetic$BestCost <- as.numeric(memetic$BestCost)
memetic$BestKnown <- as.numeric(memetic$BestKnown)
best.known$BestKnown <- as.numeric(best.known$BestKnown)

merged.memetic <- merge(memetic, best.known, by="Instance")

### ensure that the best known are correctly noted in the dataframe
merged.memetic <- merged.memetic[,-which(names(merged.memetic) == "BestKnown.x")]
merged.memetic <- merged.memetic[,-which(names(merged.memetic) == "RelativeDev")]
colnames(merged.memetic)[which(names(merged.memetic) == "BestKnown.y")] <- "BestKnown"
Deviation <- 100*(merged.memetic$BestKnown - merged.memetic$BestCost)/merged.memetic$BestKnown
merged.memetic <- cbind(merged.memetic, Deviation)

print(merged.memetic)

# ILS data retrieval
ils <- read.csv("results/ils/res_ils.csv", sep=",", header = FALSE)
ils <- data.frame(ils)
colnames(ils) <- c("Instance", "Algorithm", "size", "AlgoClass", "Sequence", "Perturbation","Init",
                  "Moves","BestCost", "BestKnown","Time","RelativeDev")

best.known <- read.table("assets/best_known/best_known_150.txt")
best.known <- data.frame(best.known)
colnames(best.known) <- c("Instance", "BestKnown")

# ensure that the columns are numeric
# ensure that the columns are numeric
ils$Time <- as.numeric(ils$Time)
ils$RelativeDev <- as.numeric(ils$RelativeDev)
ils$size <- as.numeric(ils$size)
ils$Moves <- as.numeric(ils$Moves)
ils$BestCost <- as.numeric(ils$BestCost)
ils$BestKnown <- as.numeric(ils$BestKnown)
best.known$BestKnown <- as.numeric(best.known$BestKnown)

merged.ils <- merge(ils, best.known, by="Instance")

### ensure that the best known are correctly noted in the dataframe
merged.ils <- merged.ils[,-which(names(merged.ils) == "BestKnown.x")]
merged.ils <- merged.ils[,-which(names(merged.ils) == "RelativeDev")]
colnames(merged.ils)[which(names(merged.ils) == "BestKnown.y")] <- "BestKnown"
Deviation <- 100*(merged.ils$BestKnown - merged.ils$BestCost)/merged.ils$BestKnown
merged.ils <- cbind(merged.ils, Deviation)

print(merged.memetic)
print(merged.ils)


# reductions to only instance name and deviation
reduced_memetic <- merged.memetic[,c("Instance","Deviation")]
reduced_ils <- merged.ils[,c("Instance","Deviation")]

# merge the two dataframes
merged_algos <- merge(reduced_ils, reduced_memetic, by="Instance")
colnames(merged_algos) <- c("Instance", "Deviation_ILS", "Deviation_Memetic")
print(merged_algos)
#
# mean_deviation_ils <-
# mean_deviation_memetic <-

mean_merged_algos <- data.frame(ILS = mean(merged_algos$Deviation_ILS),
                        Memetic = mean(merged_algos$Deviation_Memetic))

print(mean_merged_algos)

write.table(merged_algos, "src/Stats/outputs/deviation_ils_memetic.csv", sep=",", row.names=FALSE)
write.table(mean_merged_algos, "src/Stats/outputs/mean_deviation_ils_memetic.csv", sep=",", row.names=FALSE)


wilcoxon_result <- wilcox.test(merged_algos$Deviation_ILS, merged_algos$Deviation_Memetic, paired=TRUE)$p.value
print(wilcoxon_result)

write.table(wilcoxon_result, "src/Stats/outputs/wilcoxon_ils_memetic.csv", sep=",", row.names=FALSE)

## correlation plot

ils.150 <- merged_algos$Deviation_ILS
memetic.150 <- merged_algos$Deviation_Memetic

#plot de result

plot(ils.150, memetic.150, pch=16, col="blue",
     xlab="Iterated Local Search Deviation (%)",
     ylab="Memetic Deviation (%)",
     main="Correlation Plot of Deviation")
fit.150 <- lm(memetic.150 ~ ils.150, data=data.frame(cbind(ils.150, memetic.150)))
abline(fit.150, col="black")
