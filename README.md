# forkdebug

@michiwend: Here you go :).

This is a simple tool to check the functionality of the fork() syscall. It'll try to fork itself and log the result to the given file.

## Build instructions

```sh
clang -o forkdebug main.c
```
or
```sh
gcc -o forkdebug main.c
```

## Usage

Just setup a cronjob to schedule tests of 'fork()'. Invoke this tool as following:

```sh
./forkdebug {LOGFILE}
```
