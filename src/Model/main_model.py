
import sys
import Model.libcalculate as shared_lib
import help_functions
class SmartCalcModel():
    def __init__(self) -> None:
        self.cpp_model = shared_lib.CalculatorModel()

    def is_valid_inputs(self, expression: str, x_input: str) -> bool:
        arg_to_pass = expression.encode('ascii')
        is_valid = shared_lib.is_valid_input(arg_to_pass)
        is_valid = is_valid and help_functions.is_valid_variable_str(x_input)

        return is_valid

    def calculate_expr_at(self, expr: str, x: float) -> float:
        if not self.is_valid_inputs(expr, str(x)):
            raise Exception("Calculation on invalid string!")
        arg_to_pass = expr.encode('ascii')
        return shared_lib.calculate(arg_to_pass, x)