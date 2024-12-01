
import sys
from Model import help_functions
from Model.main_model import MainModel


class UserController():
    def __init__(self, main_model: MainModel) -> None:
        self.main_model = main_model

    def set_calculator_data(self, data: str):
        self.main_model.set_calculator_data(data)

    def set_then_calculate(self, expr: str, x: float) -> float:
        self.set_calculator_data(expr)
        return self.main_model.calculate_expr_at(expr, x)

    def set_then_validate(self, expr: str, x: str) -> bool:
        self.set_calculator_data(expr)
        return self.main_model.is_valid_inputs(expr, x)

    def float_from_str(self, var_str: str) -> float:
        return help_functions.float_from_str(var_str)

    def is_valid_integer_varible_str(self, var_str: str) -> bool:
        return help_functions.is_valid_integer_varible_str(var_str)

    def is_valid_variable_str(self, var_str: str) -> bool:
        return help_functions.is_valid_variable_str(var_str)

    def day_in_this_year(self, year: int) -> int:
        return help_functions.day_in_this_year(year)

    def set_then_credit_calculate(self,
                         sum_str: str, rate_str: str, time_str: str,
                         month_is_checked: bool, annuity_is_checked: bool) -> tuple[str, str, str]:
        self.main_model.set_credit_data(sum_str, rate_str, time_str, 
                                        month_is_checked, annuity_is_checked)
        return self.main_model.credit_calculate()

    # def deposit_calculate(self, sum_str: str, rate_str: str, time_str: str,
    #                       tax_str: str, capitilization_checked: bool) -> tuple[str, str, str]:
    #     return deposit_model.calculate(sum_str, rate_str, time_str, tax_str, capitilization_checked)
