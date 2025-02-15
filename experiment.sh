#2020/3/21  ver 1.0

CPUID=7
ORIG_ASLR=`cat /proc/sys/kernel/randomize_va_space`
ORIG_GOV=`cat /sys/devices/system/cpu/cpu$CPUID/cpufreq/scaling_governor`
ORIG_TURBO=`cat /sys/devices/system/cpu/intel_pstate/no_turbo`

sudo bash -c "echo 0 > /proc/sys/kernel/randomize_va_space"
sudo bash -c "echo performance > /sys/devices/system/cpu/cpu$CPUID/cpufreq/scaling_governor"
sudo bash -c "echo 1 > /sys/devices/system/cpu/intel_pstate/no_turbo"

###### single kernel vs user test
# make clean
# make
# make client_test
# make unload
# make load
# sudo taskset -c 7 ./client_test > plot
# gnuplot scripts/plot-stats.gp
# make unload

###### single kernel vs user test
make clean
make
# make client_stat_measure
make client
make unload
make load
sudo taskset -c 7 ./client > plot
# sudo taskset -c 7 ./client_stat_measure > plot
gnuplot scripts/plot-stats.gp
make unload
# make clean

# restore the original system settings

sudo bash -c "echo $ORIG_ASLR >  /proc/sys/kernel/randomize_va_space"
sudo bash -c "echo $ORIG_GOV > /sys/devices/system/cpu/cpu$CPUID/cpufreq/scaling_governor"
sudo bash -c "echo $ORIG_TURBO > /sys/devices/system/cpu/intel_pstate/no_turbo"