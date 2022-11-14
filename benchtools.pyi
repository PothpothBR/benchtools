from typing import Callable

def set_bench(f: Callable[[], None], name:str, fit:int) -> None:
    """Seta uma função para ser executada na rodada de benchmark"""

def bench_round() -> None:
    """Executa a rodada de benchmark para as funcoes adicionadas com set_bench()"""

def clear_round() -> None:
    """Limpa a rodada de benchmark"""