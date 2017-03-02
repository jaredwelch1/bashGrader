# ABOUT 

This is a small bash script designed to run numerous c files that include a main and functions, written by 2050 stuents.
There are also some directory files to be used for testing. 
The bash script is designed to take c files in, take a tester.cpp file, compile 
and run the tester, then output the results to REPORT.txt (the grade) and
pawprint_output.txt (a report of that students build and output).

# Usage

It is designed to work as follows:

Provided a directory of student files with naming convention pawprint_assignment.c, and a tests.cpp file (using gtest) designed 
to test the functions within the student files, run this script to compile and run the tester using the students code. The 
output from command line will go into pawprint_output.txt for each pawprint and one REPORT.TXT file will be created to contain
the scores, build failures, and seg faults for the given programs. 

# To Do

- Tweak script to use valgrind and output its contents
