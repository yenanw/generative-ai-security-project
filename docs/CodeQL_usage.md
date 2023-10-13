# CodeQL usage

It is recommended to read and follow the documentation of CodeQL CLI [here](https://docs.github.com/en/code-security/codeql-cli/getting-started-with-the-codeql-cli/setting-up-the-codeql-cli).

## Analyzing C code locally

Assuming CodeQL is installed and is on your path so that `codeql resolve qlpacks` and `codeql resolve languages` do not yield any error, then you are good to go.

1. To analyze a code snippet, we must first prepare a database for that code. To do that, use the following command:
   ```bash
   codeql database create [database_folder] --language=cpp --command=[build_command]
   ```
   Where `database_folder` is just an empty or non-existent folder that we are going to put the database in. The command is the build command for out code snippet. In the case of C, it can be something like
   ```bash
   clang -o snippet-XX snippet-XX.c
   ```
   Note that you need to wrap the command in quotes if it contains spaces like this: `--command='clang -o snippet-XX snippet-XX.c'`.
2. Then run the following command to analyze and generate a .sarif for the code snippet:
   ```bash
   codeql database analyze [database_folder] $CODEQL_SUITES_PATH/cpp-security-extended.qls --format=sarifv2.1.0 --output=[output_file].sarif
   ```

   Note that `$CODEQL_SUITES_PATH/cpp-security-extended.qls` is the path to the CodeQL test suite we intend to use, in this case we use the **security extended** version for max coverage in the security aspect.
   You can export the variable `CODEQL_SUITES_PATH` using the command `export CODEQL_SUITES_PATH=[path to your ql-suites]`.
