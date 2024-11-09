from pathlib import Path
from ctypes import *
import datetime
from calendar import monthrange

import Model.libcalculate as shared_fun


def day_in_this_year(year: int) -> int:
    days = 0
    if year % 4 != 0:
        days = 365
    elif year % 100 != 0:
        days = 366
    elif year % 400 != 0:
        days = 365
    else:
        days = 366
    return days


def is_valid_variable_str(var_str: str) -> bool:
    var_str = var_str.replace(",", ".")
    is_valid = True
    try:
        x_value: float = float(var_str)
        is_valid = is_valid and (
            var_str[0].isdigit() or var_str[0] in ['-', '+'])
    except ValueError:
        is_valid = False
    return is_valid


def is_valid_integer_varible_str(var_str: str) -> bool:
    return is_valid_variable_str(var_str) \
        and var_str.isdigit() \



def float_from_str(var_str: str) -> float:
    var_str = var_str.replace(",", ".")
    if not is_valid_variable_str(var_str):
        raise Exception("Getting value from incorrect string!")
    else:
        return float(var_str)


def is_valid_inputs(expression: str, x_input: str) -> bool:
    # so_file = str(Path(__file__).absolute())
    # so_file = so_file[:so_file.rfind('/') + 1] + "/libcalculate.so"
    # shared_fun = CDLL(so_file)

    arg_to_pass = expression.encode('ascii')
    is_valid = shared_fun.is_valid_input(arg_to_pass)
    is_valid = is_valid and is_valid_variable_str(x_input)

    return is_valid


def calculate_expr_at(expr: str, x: float) -> float:
    if not is_valid_inputs(expr, str(x)):
        raise Exception("Calculation on invalid string!")

    # so_file = str(Path(__file__).absolute())
    # so_file = so_file[:so_file.rfind('/') + 1] + "/libcalculate.so"
    # shared_fun = CDLL(so_file)

    # shared_fun.calculate.argtypes = [c_char_p, c_longdouble]
    # shared_fun.calculate.restype = c_longdouble  # c_longdouble  # c_double

    arg_to_pass = expr.encode('ascii')
    return shared_fun.calculate(arg_to_pass, x)
