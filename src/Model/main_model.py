
import Model.libcalculate as shared_lib
import Model.help_functions as help_functions

class MainModel():
    def __init__(self) -> None:
        self.calculatorModel = shared_lib.CalculatorModel()
        # self.creditModel = credit_model.CreditModel()
        # self.depositModel = deposit_model.DepositModel()

    # def set_credit_data(self, data: str):
    #     self.calculatorModel.set_data(data)

    # def set_deposit_data(self, data: str):
    #     self.calculatorModel.set_data(data)

    def set_calculator_data(self, data: str):
        self.calculatorModel.set_data(data)

    def is_valid_inputs(self, expression: str, x_input: str) -> bool:
        # arg_to_pass = expression.encode('ascii')
        self.set_calculator_data(expression)
        is_valid = self.calculatorModel.is_valid_input()
        is_valid = is_valid and help_functions.is_valid_variable_str(x_input)

        return is_valid

    def calculate_expr_at(self, expr: str, x: float) -> float:
        self.set_calculator_data(expr)
        if not self.is_valid_inputs(expr, str(x)):
            raise Exception("Calculation on invalid string!")
        # arg_to_pass = expr.encode('ascii')

        return self.calculatorModel.calculate(x)