import Model.libcalculate as shared_lib
import Model.help_functions as help_functions
from  Model.credit_model import CreditModel
from  Model.deposit_model import DepositModel  # , #deposit_model

class MainModel():
    def __init__(self) -> None:
        self.calculatorModel = shared_lib.CalculatorModel()
        self.creditModel = CreditModel()
        self.depositModel = DepositModel()

    def set_calculator_data(self, data: str):
        self.calculatorModel.set_data(data)

    # def set_credit_data(self, sum_str: str, rate_str: str, time_str: str, 
    #                     month_is_checked: bool, annuity_is_checked: bool):
    #     self.credit_calculate.set_data(sum_str, rate_str, time_str,
    #                                    month_is_checked, annuity_is_checked)

    def set_credit_data(self, sum_str: str, rate_str: str, time_str: str, 
                 month_is_checked: bool, annuity_is_checked: bool):
        self.creditModel.set_data(sum_str, rate_str, time_str, 
                 month_is_checked, annuity_is_checked)

    def set_deposit_data(self, sum_str: str, rate_str: str, time_str: str, tax_str: str,
                capitilization_checked: bool):
        self.depositModel.set_data(sum_str, rate_str, time_str, tax_str,
                capitilization_checked)

    def is_valid_inputs(self, expression: str, x_input: str) -> bool:
        is_valid = self.calculatorModel.is_valid_input()
        is_valid = is_valid and help_functions.is_valid_variable_str(x_input)

        return is_valid

    def calculate_expr_at(self, expr: str, x: float) -> float:
        if not self.is_valid_inputs(expr, str(x)):
            raise Exception("Calculation on invalid string!")
        # arg_to_pass = expr.encode('ascii')

        return self.calculatorModel.calculate(x)

    def is_valid_inputs(self, expression: str, x_input: str) -> bool:
        is_valid = self.calculatorModel.is_valid_input()
        is_valid = is_valid and help_functions.is_valid_variable_str(x_input)

        return is_valid

    def credit_calculate(self) -> float:
        return self.creditModel.credit_calculate()

    def deposit_calculate(self) -> float:
        return self.depositModel.calculate()