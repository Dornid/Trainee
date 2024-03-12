from Model.help_functions import *


def credit_calculate(sum_str: str, rate_str: str, time_str: str, month_is_checked: bool, annuity_is_checked: bool) \
        -> tuple[str, str, str]:
    year_is_checked = not month_is_checked

    str_payment: str = ""
    str_overpayment: str = ""
    str_total: str = ""

    all_strs_correct = is_valid_variable_str(sum_str) \
        and is_valid_integer_varible_str(time_str) \
        and is_valid_variable_str(rate_str)

    all_nums_correct = all_strs_correct \
        and float_from_str(sum_str) > 0 \
        and 0 <= float_from_str(rate_str) <= 1000 \
        and (month_is_checked and 1 <= float_from_str(time_str) <= 600
             or year_is_checked and 1 <= float_from_str(time_str) <= 50)

    if all_nums_correct:
        credit = float_from_str(sum_str)
        rate = float_from_str(rate_str)
        time = int(float_from_str(time_str))

        if year_is_checked:
            time *= 12

        p = rate / 1200
        if annuity_is_checked:
            payment = credit * p * (1 + p)**time / ((1 + p)**time - 1)
            payments = [payment] * time
            str_payment = str(payment)
        else:
            d = credit / time

            payments = [d + (credit - d * (month - 1)) *
                        p for month in range(1, time + 1)]
            str_payment = str(payments[0]) + " -> " + str(payments[-1])

        total = sum(payments)
        overpayment = total - credit

        str_overpayment = str(overpayment)
        str_total = str(total)

    else:
        str_payment = "Invalid input"
        str_overpayment = "Invalid input"
        str_total = "Invalid input"

    return (str_payment, str_overpayment, str_total)
