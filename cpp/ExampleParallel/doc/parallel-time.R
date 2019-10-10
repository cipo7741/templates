setwd("~/workspace/CLionProjects/CellRain/doc/plot")

library(readr)
run_times_parallel_example <- read_csv("run-times-parallel-example.txt")

boxplot(run_times_parallel_example$time~run_times_parallel_example$threads, ylim=c(0,4), xlab="#threads", ylab = "time in seconds", title="example runtime with threads")


plot(run_times_parallel_example$time~run_times_parallel_example$threads, ylim=c(0,4), xlab="#threads", ylab = "time in seconds")
threads_1_mean = mean(run_times_parallel_example$time[run_times_parallel_example$time>3.5])
abline(threads_1_mean,0)
threads_3_mean = mean(run_times_parallel_example$time[run_times_parallel_example$time<1.5])
#abline(threads_3_mean,0)
threads_2_mean = mean(run_times_parallel_example$time[run_times_parallel_example$time>1.5&run_times_parallel_example$time<3.5])
#abline(threads_2_mean,0)
abline(threads_1_mean/2,0, col="red")
abline(threads_1_mean/8,0, col="red")

grid()

