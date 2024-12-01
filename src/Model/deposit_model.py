from Model.help_functions import *

class DepositModel():
    # deposit, time, rate, capitilization_checked = 0.0, 0, 0.0, False
    sum_str, rate_str, time_str, tax_str, capitilization_checked = "", "", "", "", False

    # def set_input_data(self, sum_str: str, rate_str: str, time_str: str, tax_str: str):
    #     self.sum_str = sum_str
    #     self.rate_str = rate_str
    #     self.time_str = time_str
    #     self.tax_str = tax_str

    def set_data(self, sum_str: str, rate_str: str, time_str: str, tax_str: str, capitilization_checked: bool):
        self.sum_str = sum_str
        self.rate_str = rate_str
        self.time_str = time_str
        self.tax_str = tax_str
        self.capitilization_checked = capitilization_checked

    def check_nums_input(self) -> bool:
        strs_inputs = [self.sum_str, self.rate_str, self.time_str,
                    self.tax_str]

        all_strs_correct = sum([is_valid_variable_str(var_str) for var_str in strs_inputs]) == len(strs_inputs) \
            and is_valid_integer_varible_str(self.time_str)

        all_nums_correct = all_strs_correct \
            and float_from_str(self.sum_str) > 0 \
            and 0 <= float_from_str(self.rate_str) <= 100 \
            and 0 <= float_from_str(self.tax_str) <= 100 \
            and float_from_str(self.time_str) > 0 \
            and float_from_str(self.time_str) <= 18250

        return all_nums_correct


    def process_charges_taxes(self, deposit: float, time: int, rate: float) -> tuple[int, int]:
        # (charges, taxes)
        KEY_BANK_PERCENT = 0.15

        charges, got_taxes = 0, 0
        got_last_year_taxes = 0
        date = datetime.datetime.now()
        now_year, now_month, now_day = date.year, date.month, date.day
        months_passed = 0
        start_day = now_day
        for i in range(time):
            days_in_month = monthrange(now_year, now_month)[1]
            days_in_year = day_in_this_year(now_year)

            if now_day > days_in_month:
                now_month += 1
                now_day = 1
                months_passed += 1

            if now_month > 12:
                got_taxes += max(got_last_year_taxes -
                                1_000_000 * KEY_BANK_PERCENT, 0)
                got_last_year_taxes = 0

                now_year += 1
                now_month = 1

            if self.capitilization_checked:
                day_payment = round(
                    (charges + deposit) * rate / (100 * days_in_year), 2)
            else:
                day_payment = round(
                    deposit * rate / (100 * days_in_year), 2)

            charges += day_payment
            got_last_year_taxes += day_payment

            now_day += 1

        got_taxes += max(got_last_year_taxes -
                        1_000_000 * KEY_BANK_PERCENT, 0)

        return (charges, got_taxes)


    def calculate(self) -> tuple[str, str, str]:
        tax_output, charges_output, final_sum_output = ("", "", "")
        all_nums_correct = self.check_nums_input()

        if all_nums_correct:
            deposit = float_from_str(self.sum_str)
            rate = float_from_str(self.rate_str)
            time = int(float_from_str(self.time_str))
            tax = float_from_str(self.tax_str)

            charges, got_taxes = self.process_charges_taxes(
                deposit, time, rate)

            charges_output = str(charges)
            final_sum_output = str(charges + deposit)
            tax_output = str(got_taxes * tax / 100)

        else:
            tax_output, charges_output, final_sum_output = ("Invalid input",) * 3

        return (tax_output, charges_output, final_sum_output)
