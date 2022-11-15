from benchtools import set_bench, bench_round, clear_round
from unittest import TestCase, TestSuite, TextTestRunner

def benchF():
    for i in range(10000000):
        x = 22/22/22/22/22

def benchFHard():
    for i in range(1000000000):
        x = 22/22/22/22/22

class TestBenchmark(TestCase):
    
    def testSetOne(self):
        set_bench(benchF, "t-11", 1)
        
    def testSetAll(self):
        set_bench(benchF, "testetesteteste-12", 1)
        set_bench(benchF, "teste-14", 1)
        set_bench(benchF, "teste-15", 1)
        set_bench(benchF, "teste-16", 1)
        
    def testBench(self):
        bench_round()
    
    def testClear(self):
        clear_round()
        
    def testRebench(self):
        set_bench(benchF, "teste-22", 1)
        set_bench(benchFHard, "teste-24", 1)
        set_bench(benchF, "teste-25", 1)
        set_bench(benchF, "teste-26", 1)
        bench_round()
        clear_round()

def suite():
    suite = TestSuite()
    suite.addTest(TestBenchmark('testSetOne'))
    suite.addTest(TestBenchmark('testSetAll'))
    suite.addTest(TestBenchmark('testBench'))
    suite.addTest(TestBenchmark('testClear'))
    suite.addTest(TestBenchmark('testRebench'))
    return suite

if __name__ == '__main__':
    runner = TextTestRunner()
    runner.run(suite())