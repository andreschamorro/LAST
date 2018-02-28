#!/bin/bash
#SBATCH --job-name=<job name>
#SBATCH --mail-user=<your email address>
#SBATCH --mail-type=ALL
#SBATCH --error=<error filename>
#SBATCH --output=<output filename>

#This script simply prints out current clock time in 12-hour format

/bin/date +%r
