
import sys
from Model import help_functions
from Model.main_model import MainModel


class UserController():
    def __init__(self, main_model: MainModel) -> None:
        self.main_model = main_model

    def set_calculator_data(self, data: str):
        self.main_model.set_calculator_data(data)

    def calculate_expr_at(self, expr: str, x: float) -> float:
        return self.main_model.calculate_expr_at(expr, x)

    def is_valid_inputs(self, expr: str, x: str) -> bool:
        return self.main_model.is_valid_inputs(expr, x)

    def float_from_str(self, var_str: str) -> float:
        return help_functions.float_from_str(var_str)

    def is_valid_integer_varible_str(self, var_str: str) -> bool:
        return help_functions.is_valid_integer_varible_str(var_str)

    def is_valid_variable_str(self, var_str: str) -> bool:
        return help_functions.is_valid_variable_str(var_str)

    def day_in_this_year(self, year: int) -> int:
        return help_functions.day_in_this_year(year)

    # def credit_calculate(self,
    #                      sum_str: str, rate_str: str, time_str: str,
    #                      month_is_checked: bool, annuity_is_checked: bool) -> tuple[str, str, str]:
    #     return credit_model.credit_calculate(sum_str, rate_str, time_str,
    #                                          month_is_checked, annuity_is_checked)

    # def deposit_calculate(self, sum_str: str, rate_str: str, time_str: str,
    #                       tax_str: str, capitilization_checked: bool) -> tuple[str, str, str]:
    #     return deposit_model.calculate(sum_str, rate_str, time_str, tax_str, capitilization_checked)
