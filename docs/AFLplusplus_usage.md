# Quickstart guide for AFL++

## Installation

Read the [official installation guide](https://github.com/AFLplusplus/AFLplusplus/blob/stable/docs/INSTALL.md).

Make sure you have the AFL binaries in your path.

## Fuzzing with AFL++

To begin with, the code snippets to be fuzzed should take in some sort of input either through a file or `stdin`.

It is possible to fuzz using commandline arguments, namely `argv` fuzzing. But it seems too complicated for what it's worth, see [here](https://github.com/AFLplusplus/AFLplusplus/blob/stable/utils/argv_fuzzing/README.md) for a guide on how to do `argv` fuzzing. So just make sure the code snippets generate take input through a file or the standard input.

### Compiling own source code
Since we have source code available, we can just compile the code using AFL's own compilers. There are a lot of different compilers to use, so refer to the following for which one to use. In general, if your system is not too old, `afl-clang-lto` is fine.

```bash
+--------------------------------+
| clang/clang++ 11+ is available | --> use LTO mode (afl-clang-lto/afl-clang-lto++)
+--------------------------------+     see [instrumentation/README.lto.md](instrumentation/README.lto.md)
    |
    | if not, or if the target fails with LTO afl-clang-lto/++
    |
    v
+---------------------------------+
| clang/clang++ 3.8+ is available | --> use LLVM mode (afl-clang-fast/afl-clang-fast++)
+---------------------------------+     see [instrumentation/README.llvm.md](instrumentation/README.llvm.md)
    |
    | if not, or if the target fails with LLVM afl-clang-fast/++
    |
    v
 +--------------------------------+
 | gcc 5+ is available            | -> use GCC_PLUGIN mode (afl-gcc-fast/afl-g++-fast)
 +--------------------------------+    see [instrumentation/README.gcc_plugin.md](instrumentation/README.gcc_plugin.md) and
                                       [instrumentation/README.instrument_list.md](instrumentation/README.instrument_list.md)
    |
    | if not, or if you do not have a gcc with plugin support
    |
    v
   use GCC mode (afl-gcc/afl-g++) (or afl-clang/afl-clang++ for clang)
```

For instance, if using `afl-clang-lto`, then you can compile the program using
```
afl-clang-lto [source_code] -o [program]
```
Basically the same way you would use `gcc`.

### Sanitizers

Do note that there is possibility to use sanitizers when fuzzing, see [this](https://github.com/AFLplusplus/AFLplusplus/blob/stable/docs/fuzzing_in_depth.md#c-selecting-sanitizers) for more details. In our case, we use mostly *ASAN* to detect buffer overflow vulnerabilities. So make sure to **always** `export AFL_USE_ASAN=1` before compiling the code, if you decide to use ASAN.

Recommended sanitizers: **ASAN** and **UBSCAN**.

### Fuzzing the code

Before you start with fuzzing, you need an input directory with at least one file containing **valid** inputs for the program. On the contrary, you do not need to have created an output directory. AFL will create it for you.

To fuzz, run the command:
```bash
afl-fuzz -i input -o output -- bin/target -someopt @@
```

Note that `@@` is not necessary if the program does not take input from a file, it used only to have afl-fuzz autogenerate a file name for you.

### General workflow

Assuming you have AFL++ installed and the binaries are in the path.

1. Activate ASAN and UBSAN by running the following commands:
   ```bash
   export AFL_USE_ASAN=1
   export AFL_USE_UBSAN=1
   ```
2. Compile the source code to be fuzzed by
   ```bash
   afl-clang-lto source_code.c -o [source_code]
   ```
3. Create a directory with at least one file containing a valid input to the program. I.e. A file `input/valid_input`. 
3. Run the fuzzer using the following commands (assuming the code reads input from `stdin`)
   ```bash
   afl-fuzz -i input -o output -- ./source_code
   ```
4. Fix any errors you have and rerun the corresponding steps.
5. Wait until satisfied and `ctrl+c`.

## Dealing with AFL++ fuzzer errors
Here are some of the problems I have encountered dealing with AFL++ fuzzer and solution to them.

#### Error: core dump notifications to an external utility

```bash
[-] Hmm, your system is configured to send core dump notifications to an
external utility. This will cause issues: there will be an extended delay
between stumbling upon a crash and having this information relayed to the
fuzzer via the standard waitpid() API.
If you're just testing, set 'AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1'.

To avoid having crashes misinterpreted as timeouts, please log in as root
and temporarily modify /proc/sys/kernel/core_pattern, like so:

echo core >/proc/sys/kernel/core_pattern

[-] PROGRAM ABORT : Pipe at the beginning of 'core_pattern'
Location : check_crash_handling(), src/afl-fuzz-init.c:2361
```

**Solution:**

Temporarily edit your `core_pattern` by
```bash
sudo -i # login as root
echo core >/proc/sys/kernel/core_pattern
exit
```


#### Error: on-demand CPU frequency scaling

```bash
[-] Whoops, your system uses on-demand CPU frequency scaling, adjusted
between 1171 and 3125 MHz. Unfortunately, the scaling algorithm in the
kernel is imperfect and can miss the short-lived processes spawned by
afl-fuzz. To keep things moving, run these commands as root:

cd /sys/devices/system/cpu
echo performance | tee cpu*/cpufreq/scaling_governor

You can later go back to the original state by replacing 'performance'
with 'ondemand' or 'powersave'. If you don't want to change the settings,
set AFL_SKIP_CPUFREQ to make afl-fuzz skip this check - but expect some
performance drop.

[-] PROGRAM ABORT : Suboptimal CPU scaling governor
Location : check_cpu_governor(), src/afl-fuzz-init.c:2470
```
**Solution:**

You can either
  - ignore this error, if you don't care about performance like me, by `export AFL_SKIP_CPUFREQ=1`,
  - or temporarily fix it by running the following commands, <sub>Note: I have not tested it</sub>
    ```bash
    sudo -i # login as root
    cd /sys/devices/system/cpu
    echo performance | tee cpu*/cpufreq/scaling_governor
    exit
    ```
  - or run `sudo afl-system-config` according to their official documentation.
