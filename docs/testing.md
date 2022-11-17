# More information about testing

## Google tests

All tests are written in `test.cpp`. More information about the tests themselves and how they can be written can be found in the google test documentation ([find link in main readme](../README.md)). This kind of testing will help you believe that part of the algorithm (the implemented function or structure) works correctly.  Example tests can be found [in the template folder](../TemplateForPrograms/test.cpp) (and in each implementation)

You can also run it manually with `./build/test_programm`.

## Main test

### Classic approach

After writing the code in `main.cpp`, the build will create the file `main_programm`, which is the executable file of your program. Testing is fairly straightforward:
1) run the file with the command `./build/main_programm` (or `./main_programm` if you are already in build directory). Input data, compare with expected output.
2) Create a file, write the input data into it. Execute the command `cat path_to_created_file | ./build/main_programm` (redirect the output of the file to our program)

### Other approach

Add next script at the end of `build_and_run_test`.

```sh
# create dir for test for main programm
if [ ! -d "./tests_results" ]
then
  mkdir tests_results
fi

for TEST in ../tests_for_main/test*
do
  # no tests in directory
  if [ ${TEST} == "../tests_for_main/test*" ]
  then 
    break;
  fi

  FILENAME=$(basename -- "$TEST")
  NUMBER_OF_TEST="${FILENAME##*_}"
  TEST_NAME="${FILENAME%_*}"

  # execute main
  cat $TEST | ./main_programm > tests_results/${NUMBER_OF_TEST}

  # check result
  if cmp -s tests_results/${NUMBER_OF_TEST} ../tests_for_main/res_${NUMBER_OF_TEST};
  then
    STATUS="OK"
  else
    STATUS="ERROR"
  fi
  echo "Test name is $FILENAME. Status is ${STATUS}"
  if [ ${STATUS} == "ERROR" ]
  then
    echo "Expected result"
    cat ../tests_for_main/res_${NUMBER_OF_TEST}
    echo "Program result is"
    cat tests_results/${NUMBER_OF_TEST}
  fi
done
```

Create directory `tests_for_main` near build script. Fill this directory with tests. Input data for tests should be put in file which name starts from `test_` and expected output should be in file with name which starts from `res_` (otherwise script will not work).