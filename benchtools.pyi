from typing import Callable

def set_bench(f: Callable[[], None], name:str, fit:int) -> None:
    """Set a function to run in the benchmark run

    Args:
        f (Callable[[], None]): the function to call with no args, the return is ignored
        name (str): alias for the function
        fit (int): number of rounds to catch a average acurace bench to only one function
    """

def bench_round(log:bool = False) -> None:
    """Run the benchmark run for the added functions with set_bench()

    Args:
        log (bool, optional): defines with dump the execution to a csv file. Defaults to False.
    """

def clear_round() -> None:
    """Clear the benchmark round"""
