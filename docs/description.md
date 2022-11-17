# How to work with project

[generate_new_dir.sh](../generate_new_dir.sh) &mdash; generates copy of `TemplateForPrograms` directory (makes build easier).

If you want to implement your own code, create a `include` folder. All files from this folder will be added to `main.cpp` and `test.cpp` during build. ([Read more about tests](./testing.md))

To build and test just run the script `build_and_run_test`. It will build programm and format all files.

After running this script, the executable files `main_programm` and `test_programm` will lie in the `build` folder. `Main` is used to solve the problem you are facing. And the test is for checking the correctness of the implemented structure.

Additional build parameters:
* `ADDRESS=1` &mdash; enables ASan
* `UNDEFINED=1` &mdash; enables UBSan

These flags can be used together. 

__Example command to build with sanitizers__:

`./build_and_run_test ADDRESS=1 UNDEFINED=1`