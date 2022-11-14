from benchtools import *

def f1():
    for i in range(10000000):
        x = 22/22/22/22/22

def f2():
    for i in range(10000000):
        x = 22/22/22/22/22
        
def f3():
    for i in range(1000000000):
        x = 22/22
        
def f4():
    for i in range(100000):
        x = 22/22/22/22/22
        
def f5():
    for i in range(1000000):
        x = 22/22/22/22/22
        
def f6():
    for i in range(10000000):
        x = 22/22/22/22

set_bench(f1, "teste-1", 1)
set_bench(f2, "teste-2", 1)
#set_bench(f3, "teste-3", 1)
set_bench(f4, "teste-4", 1)
set_bench(f5, "teste-5", 1)
set_bench(f6, "teste-6", 1)
bench_round()
clear_round()
set_bench(f1, "teste-1", 1)
set_bench(f2, "teste-2", 1)
set_bench(f3, "teste-3", 1)
set_bench(f4, "teste-4", 1)
set_bench(f5, "teste-5", 1)
set_bench(f6, "teste-6", 1)
bench_round()
clear_round()

print("\n...\nfinsh test successful!")