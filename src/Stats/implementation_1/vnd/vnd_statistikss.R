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
df <- cbind(merged.df, Deviation)



## separation in 2 dataframes for each instance size
df150 <- filter(df, Size == 150)
df250 <- filter(df, Size == 250)

# print(df150)

## comparison between the two different neighbourhoods sequences

### n= 150 and n=250
df.150.TEI <- filter(df150, Neighbour == "TEI")
df.150.TIE <- filter(df150, Neighbour == "TIE")
df.250.TEI <- filter(df250, Neighbour == "TEI")
df.250.TIE <- filter(df250, Neighbour == "TIE")

wilcoxon.neighbour.150 <- data.frame(matrix(nrow=0, ncol= 5, dimnames = list(c(), c("TEI","TEI.Deviation","TIE","TIE.Deviation","p.value"))))
wilcoxon.neighbour.250 <- data.frame(matrix(nrow=0, ncol= 5, dimnames = list(c(), c("TEI","TEI.Deviation","TIE","TIE.Deviation","p.value"))))

TEI.algorithm.label.150 <- unique(df.150.TEI$Algorithm)
TEI.cost.150 <- mean(df.150.TEI$Deviation)
TEI.150.temp <- 100*(df.150.TEI$BestCost - df.150.TEI$BestKnown)/df.150.TEI$BestKnown
TIE.algorithm.label.150 <- unique(df.150.TIE$Algorithm)
TIE.cost.150 <- mean(df.150.TIE$Deviation)
TIE.150.temp <- 100*(df.150.TIE$BestCost - df.150.TIE$BestKnown)/df.150.TIE$BestKnown

TEI.algorithm.label.250 <- unique(df.250.TEI$Algorithm)
TEI.cost.250 <- mean(df.250.TEI$Deviation)
TEI.250.temp <- 100*(df.250.TEI$BestCost - df.250.TEI$BestKnown)/df.250.TEI$BestKnown
TIE.algorithm.label.250 <- unique(df.250.TIE$Algorithm)
TIE.cost.250 <- mean(df.250.TIE$Deviation)
TIE.250.temp <- 100*(df.250.TIE$BestCost - df.250.TIE$BestKnown)/df.250.TIE$BestKnown

wilcoxon.neighbour.150 <- rbind(wilcoxon.neighbour.150, data.frame(
  "TEI" = TEI.algorithm.label.150,
  "TEI.Deviation" = TEI.cost.150,
  "TIE" = TIE.algorithm.label.150,
  "TIE.Deviation" = TIE.cost.150,
  "p.value" = wilcox.test(TEI.150.temp, TIE.150.temp, paired = TRUE)$p.value
))


wilcoxon.neighbour.250 <- rbind(wilcoxon.neighbour.250, data.frame(
  "TEI" = TEI.algorithm.label.250,
  "TEI.Deviation" = TEI.cost.250,
  "TIE" = TIE.algorithm.label.250,
  "TIE.Deviation" = TIE.cost.250,
  "p.value" = wilcox.test(TEI.250.temp, TIE.250.temp, paired = TRUE)$p.value
))

print(wilcoxon.neighbour.150)
print(wilcoxon.neighbour.250)

write.table(wilcoxon.neighbour.150, file="src/Stats/outputs/vnd/vnd_neighbour_150.csv", row.names = FALSE, quote=FALSE)
write.table(wilcoxon.neighbour.250, file="src/Stats/outputs/vnd/vnd_neighbour_250.csv", row.names = FALSE, quote=FALSE)


