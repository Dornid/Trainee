
import sys
from Model import help_functions
sys.path.append('../Model/help_functions.py')


class UserController():
    def __init__(self) -> None:
        pass

    def calculate_expr_at(self, expr: str, x: float) -> float:
        return help_functions.calculate_expr_at(expr, x)

    def is_valid_inputs(self, expr: str, x: str) -> bool:
        return help_functions.is_valid_inputs(expr, x)

    def float_from_str(self, var_str: str) -> float:
        return help_functions.float_from_str(var_str)

    def is_valid_integer_varible_str(self, var_str: str) -> bool:
        return help_functions.is_valid_integer_varible_str(var_str)

    def is_valid_variable_str(self, var_str: str) -> bool:
        return help_functions.is_valid_variable_str(var_str)

    def convert_months_days(self, months: int) -> int:
        return help_functions.convert_months_days(months)

    def day_in_this_year(self, year: int) -> int:
        return help_functions.day_in_this_year(year)
