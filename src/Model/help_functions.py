from pathlib import Path
from ctypes import *
import datetime
from calendar import monthrange

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
