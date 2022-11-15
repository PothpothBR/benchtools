from benchtools import set_bench, bench_round, clear_round
from typing import Any

# create functions to bench
# all functions using this template

def myfuncName() -> None:
    "Your code here"
    
# no args, no return.
# if your execution recive args. encapsule it an parse the args properly.

def myfuncNameWithArgs(arg1, arg2, arg3) -> Any:
    "Your code here"

# example to encapsule
myfuncNameWithArgsCorrect = lambda : myfuncNameWithArgs('arg1', 'arg2', 'arg3')
    
# after it, you set the functions to bench table, make it calling set_bench
set_bench(myfuncName, "beatifull alias", 4)

# the first argument is your callable
# the second is an alias for view
# the third is an number of executions to get an average time, if 0 the function not is executed!

set_bench(myfuncNameWithArgsCorrect, "second beatifull alias", 1)
set_bench(myfuncNameWithArgsCorrect, "another beatifull alias", 0) # this not execute!
    
# after it, you like to benchmark, make it calling bench_round
bench_round()

# if you like to save the results, set True
bench_round(True)

# the file is benchmark.log.csv (comma separated, indexed)

# in the end, to reset the benchmark system call clear_round

clear_round()

# free to set new bench function