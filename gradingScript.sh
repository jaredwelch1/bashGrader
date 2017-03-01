#!/user/local/bin/bash


#set -x

if [ "$#" -ne 2 ]; then
    echo "BAD PARAM COUNT! DIR FILE_GLOB"
    # Uhh, we won't be capturing this output anyway...
    exit 1
fi

# locate files to grade. Ideally, you have a bunch of folders whose name is their pawrint and contains the code to be graded directly inside it
# So something like waskd6/file.c
FILES=($(find "${1}" -type f -name "${2}" ))

#Example usage: ./file.sh directory *.c

# that will get us an array of paths to files (ex: ./waskd6/file.c)

# Let's assume you have a tester... tests.cpp
# Go steal an old tester, preferably the filesystem one. Note the environment setup and teardown stuff
# You'll either want a header that you can include (and don't forget to extern c!)
# or just declare what you're testing within the tester (also, extern c!)
# You'll need gtest 1.8

# this command probably won't work. I'm much too rusty.
# and I'm winging this. Not sure how it's going to work with missing implementation
# It may need to be compiled to an object and then linked with the student lib into an executeable later
# Actually, let's do that

# Compiled the tester, but not to a full program yet. Need to mix it with the student code
#g++ tests.cpp -c -o tests.o

# make gtest spit a report out for processing
export GTEST_OUTPUT="xml"

echo "NAME,SCORE" > REPORT.txt

for FILE_PATH in "${FILES[@]}"; do
	# grab pawprint from file path
	NAME="${FILE_PATH##*/}"
	NAME="${NAME%%_*}"

	# Figlet is just adorable, really.
	# figlet "${NAME}"

	# Uhhhhhhh you might need gcc... Not sure how it will treat the c file and if it'll try to C++ it	
	if ! (gcc "${FILE_PATH}" -c -o "${NAME}.o" && objcopy -N main -N _main "${NAME}.o" "${NAME}.o" && g++ -lgtest -pthread tests.cpp "${NAME}.o" -lgtest -o "${NAME}_test") ; then
		figlet "${NAME}"
		figlet "BUILD FAILED :("
		echo "${NAME},BUILD_FAIL" >> REPORT.txt 
	else
		# A smarter solution would be to compile a tester for each student
		# That way you don't magically lose it when we're done
		# ... let's do that
		# I have actually never done this. It probably works
		./"${NAME}_test"


		figlet "${NAME}"

		# backend stuff from the CI system from OS:
		if [ -e test_detail.xml ]; then
			RESULTS=$(fgrep -m 1 '<testsuites ' test_detail.xml)
			# eval echo is about the grosest thing you can ever do in a script
			eval $(echo ${RESULTS:12:-1})
			# bash math is ugly
			# FYI, counts disabled tests as failed You probably won't have disabled tests, so it won't matter
			(( passed = tests - failures - disabled ))
			(( failed = failures + disabled ))
			figlet "PASSED: ${passed}/${tests}"
			figlet "SCORE: ${points_given}/${points_total}"
			echo "${NAME},${points_given}/${points_total}" >> REPORT.txt
			rm -f test_detail.xml
		else
			# program segfaulted or something
			# Tyler REFUSED to learn what this meant and always acted like it was my fault somehow
			figlet "Report Not Available    :("
			echo "${NAME},DIED?" >> REPORT.txt
		fi
	fi 2>&1 | tee "${NAME}_output.txt"

	# get rid of this if you want. Should just make you hit enter before going to the next one
	# but we're capturing pretty much everything, so you can let it go and review files after the fact
	#read

done
