# Quickstart guide for AFL++

## Installation

Read the [official installation guide](https://github.com/AFLplusplus/AFLplusplus/blob/stable/docs/INSTALL.md)
thoroughly.

## Fuzzing with AFL++

It seems to be rather complicated trying to get the fuzzers to fuzz commandline
arguments, so it probably is best to avoid any `argv` fuzzing shenaningans.

It's easiest to have your input from either a file or `stdin`.

Then create an input directory and add at least one file containing some valid
input. You don't need to create the output directory manually.

Before fuzzing, compile the source code using AFL++'s own compilers. As to which
to use, refer to the following guide.

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
afl-clang-lto [path_to_program] -o [program_name]
```
Basically the same way you would use `gcc`.

To fuzz, run the command `afl-fuzz -i input_dir -o output_dir ./your_program [...commandline stuff...]`.

## Dealing with AFL++ fuzzer errors
In general you can fix the errors by simply following the hints given in the
error messages.

Error:

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
Solution:

Temporarily edit your `core_pattern` by
```bash
sudo -i
echo core >/proc/sys/kernel/core_pattern
exit
```
Error:

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
Solution:

Follow the instructions in the error message.
