#install.packages("dplyr") ## Uncomment this line if you don't have the package installed
library(dplyr)

rm(list=ls())
df <- read.csv("results/iter/res_iter.csv", sep=",", header = FALSE)
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
# print(df)

# print(unique(df$Algorithm))

## separation in 2 dataframes for each instance size
df150 <- filter(df, Size == 150)
df250 <- filter(df, Size == 250)

## comparison between initial solutions generation
### n= 150 and n=250
df.150.cw <- filter(df150, Init == "cw")
df.150.rnd <- filter(df150, Init == "random")
df.250.cw <- filter(df250, Init == "cw")
df.250.rnd <- filter(df250, Init == "random")

wilcoxon.init.150 <- data.frame(matrix(nrow=0, ncol= 5, dimnames = list(c(), c("CW","CW.Deviation","Random","Random.Deviation","p.value"))))
wilcoxon.init.250 <- data.frame(matrix(nrow=0, ncol= 5, dimnames = list(c(), c("CW","CW.Deviation","Random","Random.Deviation","p.value"))))

pivot_neighbour_combination <- with(df.150.cw, unique(paste(Pivot, Neighbour)))

for(combo in pivot_neighbour_combination){
  df_combo.150.cw <- filter(df.150.cw, paste(Pivot, Neighbour) == combo)
  df_combo.150.rnd <- filter(df.150.rnd, paste(Pivot, Neighbour) == combo)
  df_combo.250.cw <- filter(df.250.cw, paste(Pivot, Neighbour) == combo)
  df_combo.250.rnd <- filter(df.250.rnd, paste(Pivot, Neighbour) == combo)

  cw.algorithm.label.150 <- unique(df_combo.150.cw$Algorithm)
  cw.cost.150 <- mean(df_combo.150.cw$Deviation)
  cw.150.temp <- 100*(df_combo.150.cw$BestCost - df_combo.150.cw$BestKnown)/df_combo.150.cw$BestKnown
  rnd.algorithm.label.150 <- unique(df_combo.150.rnd$Algorithm)
  rnd.cost.150 <- mean(df_combo.150.rnd$Deviation)
  rnd.150.temp <- 100*(df_combo.150.rnd$BestCost - df_combo.150.rnd$BestKnown)/df_combo.150.rnd$BestKnown

  cw.algorithm.label.250 <- unique(df_combo.250.cw$Algorithm)
  cw.cost.250 <- mean(df_combo.250.cw$Deviation)
  cw.250.temp <- 100*(df_combo.250.cw$BestCost - df_combo.250.cw$BestKnown)/df_combo.250.cw$BestKnown
  rnd.algorithm.label.250 <- unique(df_combo.250.rnd$Algorithm)
  rnd.cost.250 <- mean(df_combo.250.rnd$Deviation)
  rnd.250.temp <- 100*(df_combo.250.rnd$BestCost - df_combo.250.rnd$BestKnown)/df_combo.250.rnd$BestKnown


  wilcoxon.init.150 <- rbind(wilcoxon.init.150, data.frame(
    "CW" = cw.algorithm.label.150,
    "CW.Deviation" = cw.cost.150,
    "Random" = rnd.algorithm.label.150,
    "Random.Deviation" = rnd.cost.150,
    "p.value" = wilcox.test(cw.150.temp, rnd.150.temp, paired = TRUE)$p.value
  ))

  wilcoxon.init.250 <- rbind(wilcoxon.init.250, data.frame(
    "CW" = cw.algorithm.label.250,
    "CW.Deviation" = cw.cost.250,
    "Random" = rnd.algorithm.label.250,
    "Random.Deviation" = rnd.cost.250,
    "p.value" = wilcox.test(cw.250.temp, rnd.250.temp, paired = TRUE)$p.value
  ))

}

# print(wilcoxon.init.150)
# print(wilcoxon.init.250)

write.table(wilcoxon.init.150, file="src/Stats/outputs/iterative/init_150.csv", row.names = FALSE, quote=FALSE)
write.table(wilcoxon.init.250, file="src/Stats/outputs/iterative/init_250.csv", row.names = FALSE, quote=FALSE)


## comparison between pivot algorithms
df.150.best <- filter(df150, Pivot == "best")
df.150.first <- filter(df150, Pivot == "first")
df.250.best <- filter(df250, Pivot == "best")
df.250.first <- filter(df250, Pivot == "first")

wilcoxon.pivot.150 <- data.frame(matrix(nrow=0, ncol= 5, dimnames = list(c(), c("Best","Best.Deviation","First","First.Deviation","p.value"))))
wilcoxon.pivot.250 <- data.frame(matrix(nrow=0, ncol= 5, dimnames = list(c(), c("Best","Best.Deviation","First","First.Deviation","p.value"))))

init_neighbour_combination <- with(df.150.best, unique(paste(Init, Neighbour)))

for(combo in init_neighbour_combination){
  df_combo.150.best <- filter(df.150.best, paste(Init, Neighbour) == combo)
  df_combo.150.first <- filter(df.150.first, paste(Init, Neighbour) == combo)
  df_combo.250.best <- filter(df.250.best, paste(Init, Neighbour) == combo)
  df_combo.250.first <- filter(df.250.first, paste(Init, Neighbour) == combo)

  best.algorithm.label.150 <- unique(df_combo.150.best$Algorithm)
  best.cost.150 <- mean(df_combo.150.best$Deviation)
  best.deviation.150 <- 100*(df_combo.150.best$BestCost - df_combo.150.best$BestKnown)/df_combo.150.best$BestKnown
  first.algorithm.label.150 <- unique(df_combo.150.first$Algorithm)
  first.cost.150 <- mean(df_combo.150.first$Deviation)
  first.deviation.150 <- 100*(df_combo.150.first$BestCost - df_combo.150.first$BestKnown)/df_combo.150.first$BestKnown

  best.algorithm.label.250 <- unique(df_combo.250.best$Algorithm)
  best.cost.250 <- mean(df_combo.250.best$Deviation)
  best.deviation.250 <- 100*(df_combo.250.best$BestCost - df_combo.250.best$BestKnown)/df_combo.250.best$BestKnown
  first.algorithm.label.250 <- unique(df_combo.250.first$Algorithm)
  first.cost.250 <- mean(df_combo.250.first$Deviation)
  first.deviation.250 <- 100*(df_combo.250.first$BestCost - df_combo.250.first$BestKnown)/df_combo.250.first$BestKnown

  wilcoxon.pivot.150 <- rbind(wilcoxon.pivot.150, data.frame(
    "Best" = best.algorithm.label.150,
    "Best.Deviation" = best.cost.150,
    "First" = first.algorithm.label.150,
    "First.Deviation" = first.cost.150,
    "p.value" = wilcox.test(best.deviation.150, first.deviation.150, paired = TRUE)$p.value
  ))

  wilcoxon.pivot.250 <- rbind(wilcoxon.pivot.250, data.frame(
      "Best" = best.algorithm.label.250,
      "Best.Deviation" = best.cost.250,
      "First" = first.algorithm.label.250,
      "First.Deviation" = first.cost.250,
      "p.value" = wilcox.test(best.deviation.250, first.deviation.250, paired = TRUE)$p.value
  ))

}

# print(wilcoxon.pivot.150)
# print(wilcoxon.pivot.250)


write.table(wilcoxon.pivot.150, file="src/Stats/outputs/iterative/pivot_150.csv", row.names = FALSE, quote=FALSE)
write.table(wilcoxon.pivot.250, file="src/Stats/outputs/iterative/pivot_250.csv", row.names = FALSE, quote=FALSE)


## comparison between neighbour algorithms
df.150.exchange <- filter(df150, Neighbour == "exchange")
df.150.insertion <- filter(df150, Neighbour == "insert")
df.150.transpose <- filter(df150, Neighbour == "transpose")
df.250.exchange <- filter(df250, Neighbour == "exchange")
df.250.insertion <- filter(df250, Neighbour == "insert")
df.250.transpose <- filter(df250, Neighbour == "transpose")

wilcoxon.neighbour.150 <- data.frame(matrix(nrow=0, ncol= 9, dimnames = list(c(), c("Exch", "Exch.Dev", "Inse", "Inse.Dev", "Trans", "Trans.Dev", "exch.ins.p.value", "exch.trans.p.value", "trans.ins.p.value"))))
wilcoxon.neighbour.250 <- data.frame(matrix(nrow=0, ncol= 9, dimnames = list(c(), c("Exch", "Exch.Dev", "Inse", "Inse.Dev", "Trans", "Trans.Dev", "exch.ins.p.value", "exch.trans.p.value", "trans.ins.p.value"))))

init_pivot_combination <- with(df.150.exchange, unique(paste(Init, Pivot)))


for(combo in init_pivot_combination){

  df_combo.150.exch <- filter(df.150.exchange, paste(Init, Pivot) == combo)
  df_combo.150.ins <- filter(df.150.insertion, paste(Init, Pivot) == combo)
  df_combo.150.trans <- filter(df.150.transpose, paste(Init, Pivot) == combo)
  df_combo.250.exch <- filter(df.250.exchange, paste(Init, Pivot) == combo)
  df_combo.250.ins <- filter(df.250.insertion, paste(Init, Pivot) == combo)
  df_combo.250.trans <- filter(df.250.transpose, paste(Init, Pivot) == combo)


  exch.algorithm.label.150 <- unique(df_combo.150.exch$Algorithm)
  exch.cost.150 <- mean(df_combo.150.exch$Deviation)
  exch.150.temp <- 100*(df_combo.150.exch$BestCost - df_combo.150.exch$BestKnown)/df_combo.150.exch$BestKnown
  ins.algorithm.label.150 <- unique(df_combo.150.ins$Algorithm)
  ins.cost.150 <- mean(df_combo.150.ins$Deviation)
  ins.150.temp <- 100*(df_combo.150.ins$BestCost - df_combo.150.ins$BestKnown)/df_combo.150.ins$BestKnown
  trans.algorithm.label.150 <- unique(df_combo.150.trans$Algorithm)
  trans.cost.150 <- mean(df_combo.150.trans$Deviation)
  trans.150.temp <- 100*(df_combo.150.trans$BestCost - df_combo.150.trans$BestKnown)/df_combo.150.trans$BestKnown


  exch.algorithm.label.250 <- unique(df_combo.250.exch$Algorithm)
  exch.cost.250 <- mean(df_combo.250.exch$Deviation)
  exch.250.temp <- 100*(df_combo.250.exch$BestCost - df_combo.250.exch$BestKnown)/df_combo.250.exch$BestKnown
  ins.algorithm.label.250 <- unique(df_combo.250.ins$Algorithm)
  ins.cost.250 <- mean(df_combo.250.ins$Deviation)
  ins.250.temp <- 100*(df_combo.250.ins$BestCost - df_combo.250.ins$BestKnown)/df_combo.250.ins$BestKnown
  trans.algorithm.label.250 <- unique(df_combo.250.trans$Algorithm)
  trans.cost.250 <- mean(df_combo.250.trans$Deviation)
  trans.250.temp <- 100*(df_combo.250.trans$BestCost - df_combo.250.trans$BestKnown)/df_combo.250.trans$BestKnown


  wilcoxon.neighbour.150 <- rbind(wilcoxon.neighbour.150, data.frame(
    "Exch" = exch.algorithm.label.150,
    "Exch.Dev" = exch.cost.150,
    "Inse" = ins.algorithm.label.150,
    "Inse.Dev" = ins.cost.150,
    "Trans" = trans.algorithm.label.150,
    "Trans.Dev" = trans.cost.150,
    "exch.ins.p.value" = wilcox.test(exch.150.temp, ins.150.temp, paired = TRUE)$p.value,
    "exch.trans.p.value" = wilcox.test(exch.150.temp, trans.150.temp, paired = TRUE)$p.value,
    "trans.ins.p.value" = wilcox.test(trans.150.temp, ins.150.temp, paired = TRUE)$p.value
  ))

  wilcoxon.neighbour.250 <- rbind(wilcoxon.neighbour.250, data.frame(
    "Exch" = exch.algorithm.label.250,
    "Exch.Dev" = exch.cost.250,
    "Inse" = ins.algorithm.label.250,
    "Inse.Dev" = ins.cost.250,
    "Trans" = trans.algorithm.label.250,
    "Trans.Dev" = trans.cost.250,
    "exch.ins.p.value" = wilcox.test(exch.250.temp, ins.250.temp, paired = TRUE)$p.value,
    "exch.trans.p.value" = wilcox.test(exch.250.temp, trans.250.temp, paired = TRUE)$p.value,
    "trans.ins.p.value" = wilcox.test(trans.250.temp, ins.250.temp, paired = TRUE)$p.value
  ))

}


# print(wilcoxon.neighbour.150)
# print(wilcoxon.neighbour.250)


write.table(wilcoxon.neighbour.150, file="src/Stats/outputs/iterative/neighbour_150.csv", row.names = FALSE, quote=FALSE)
write.table(wilcoxon.neighbour.250, file="src/Stats/outputs/iterative/neighbour_250.csv", row.names = FALSE, quote=FALSE)
