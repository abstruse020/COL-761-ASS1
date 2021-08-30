#!/bin/sh
### Set the job name (for your reference)

#PBS -q low
#PBS -N fp_ap_comp
### Set the project name, your department code by default
#PBS -P cse
### Request email when job begins and ends, don't change anything on the below line
#PBS -m bea
### Specify email address to use for notification, don't change anything on the below line
#PBS -M $USER@iitd.ac.in
#### Request your resources, just change the numbers
#PBS -l select=2:ncpus=4:ngpus=0:mem=16G
### Specify "wallclock time" required for this job, hhh:mm:ss
#PBS -l walltime=00:05:00
#PBS -l software=jdk@8

# After job starts, must goto working directory.
# $PBS_O_WORKDIR is the directory from where the job is fired.
echo "==============================="
echo $PBS_JOBID
cat $PBS_NODEFILE
echo "==============================="
cd $PBS_O_WORKDIR
echo $PBS_O_WORKDIR
cd "HW 1"/fpgrowth/fpgrowth/src
make
#./makefile
echo "executed Successfully make"
cd $PBS_O_WORKDIR
cd "HW 1"/
python CompareFpAp.py
echo "Executed python program as well"
python --version
python3 --version

module () {
        eval `/usr/share/Modules/$MODULE_VERSION/bin/modulecmd bash $*`
}

source activate ~/myenv

module load pythonpackages/3.6.0/matplotlib/3.0.2/gnu
module load compiler/gcc/7.1.0/compilervars
module load compiler/python/3.6.0/ucs4/gnu/447
module load compiler/java/8.112/precompiled
#module load apps/anaconda/3
#module load apps/anaconda/3EnvCreation

# for pretrain change pbs filename,boolean arg is true(1), and last but one arg is previous epoch number - 1 

# First argument is the path of the model and second argument is the path of the training data
java -version
