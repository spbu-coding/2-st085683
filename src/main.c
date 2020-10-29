#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "sort.h"
#include "utils.h"


enum error_codes {
    less_than_one_parameter_entered = -1,
    more_than_two_parameters_entered = -2,
    same_parameter_entered_more_than_once = -3,
    two_invalid_parameters_entered = -4,
    other_error_code = 1
};

enum parameter_types {
    invalid_type_parm ,
    type_parm_from,
    type_parm_to
};

static const char *const from_value = "--from=";
static const char *const to_value = "--to=";


enum parameter_types obtain_parm_type(char *variable_char);

int defined_parameters(long long **from_value, long long **to_value, char *variable_char, enum parameter_types variable_in_parm_types);


int analyze_of_parameters__and_param_accepted(long long **from_value, long long **to_value, char **variable_char2, size_t totality_of_variable_char2) {
    if (totality_of_variable_char2 < 1) return less_than_one_parameter_entered;
    if (totality_of_variable_char2 > 2) return more_than_two_parameters_entered;


    char *var_char_2_0 = totality_of_variable_char2 >= 1 ? variable_char2[0] : 0;
    char *var_char_2_1 = totality_of_variable_char2 >= 2 ? variable_char2[1] : 0;

    enum parameter_types var_char_2_0_variable_in_parm_types = obtain_parm_type(var_char_2_0);
    enum parameter_types var_char_2_1_variable_in_parm_types = obtain_parm_type(var_char_2_1);

    if (var_char_2_0_variable_in_parm_types == invalid_type_parm && var_char_2_1_variable_in_parm_types == invalid_type_parm) return two_invalid_parameters_entered;
    if (var_char_2_0_variable_in_parm_types == var_char_2_1_variable_in_parm_types) return same_parameter_entered_more_than_once;


    int exit_code = 0;
    exit_code = exit_code + defined_parameters(from_value, to_value, var_char_2_0, var_char_2_0_variable_in_parm_types);
    exit_code = exit_code + defined_parameters(from_value, to_value, var_char_2_1, var_char_2_1_variable_in_parm_types);
    if (exit_code != 0) {
        if (*from_value != 0) {
            free(*from_value);
            *from_value = 0;
        }
        if (*to_value != 0) {
            free(*to_value);
            *to_value = 0;
        }

        return more_than_two_parameters_entered;
    }

    return 0;
}

int about_integers_entered(long long *ints_ll_entrd) {
    char var_char_3;
    int quantity_ints_ll_entrd = 0;

    do {
        if (scanf("%lld%c", &ints_ll_entrd[quantity_ints_ll_entrd++], &var_char_3) != 2) {
            errprintf("Cannot read from_value stdin\n");
            return -1;
        }
    } while (isblank(var_char_3));

    return quantity_ints_ll_entrd;
}


int decreasing_numbers(long long *intg_ll_decreased, long long *ints_ll_entrd, size_t decr_num_quantity, long long *from_value, long long *to_value) {
    long long var_for_little_int_ll[decr_num_quantity];
    long long var_for_many_int_ll[decr_num_quantity];
    size_t overly_low_quantity = 0;
    size_t decreasing_quantity= 0;
    size_t overly_high_quantity = 0;

    long long decr_var_ll;
    bool num_int_ll_more_sufficient, num_int_ll_less_sufficient;
    for (size_t x = 0; x < decr_num_quantity; ++x) {
        decr_var_ll = ints_ll_entrd[x];
        num_int_ll_more_sufficient = from_value == 0 || *from_value < decr_var_ll;
        num_int_ll_less_sufficient = to_value == 0 || decr_var_ll < *to_value;

        if (!num_int_ll_more_sufficient) var_for_little_int_ll[overly_low_quantity++] = decr_var_ll;
        if (!num_int_ll_less_sufficient) var_for_many_int_ll[overly_high_quantity++] = decr_var_ll;
        if (num_int_ll_more_sufficient && num_int_ll_less_sufficient) intg_ll_decreased[decreasing_quantity++] = decr_var_ll;
    }

    if (fprintf_array_ll(stdout, var_for_little_int_ll, overly_low_quantity) < 0) return -1;
    if (fprintf_array_ll(stderr, var_for_many_int_ll, overly_high_quantity) < 0) return -1;

    return decreasing_quantity;
}

int appli_execution(long long *ints_ll_entrd, size_t decr_num_quantity, long long *from_value, long long *to_value) {
    long long intg_ll_decreased[decr_num_quantity];
    int decreasing_quantity = decreasing_numbers(intg_ll_decreased, ints_ll_entrd, decr_num_quantity, from_value, to_value);
    if (decreasing_quantity == -1) return other_error_code;

    if (decreasing_quantity == 0) return 0;

    long long var_release[decreasing_quantity];
    memcpy(var_release, intg_ll_decreased, sizeof(long long) * decreasing_quantity);

    sort(var_release, decreasing_quantity);

    int count_of_defference = 0;
    for (int x = 0; x < decreasing_quantity; ++x) {
        if (intg_ll_decreased[x] != var_release[x]) count_of_defference += 1;
    }

    return count_of_defference;
}


int main(int var_func_main_int, char *var_func_main_char[]) {
    long long *from_value = 0;
    long long *to_value = 0;

    int exit_code_main = analyze_of_parameters__and_param_accepted(&from_value, &to_value, var_func_main_char + 1, var_func_main_int - 1);
    if (exit_code_main != 0) return exit_code_main;

    long long ints_ll_entrd[100];
    int decr_num_quantity = about_integers_entered(ints_ll_entrd);
    if (decr_num_quantity == -1) return other_error_code;

    int app_output = appli_execution(ints_ll_entrd, decr_num_quantity, from_value, to_value);

    if (from_value != 0) free(from_value);
    if (to != 0) free(to_value);

    return app_output;
}


enum parameter_types obtain_parm_type(char *variable_char) {
    if (variable_char == 0) return invalid_type_parm;
    if (strstr(variable_char, from_value) == variable_char) return type_parm_from;
    if (strstr(variable_char, to_value) == variable_char) return type_parm_to;
    return invalid_type_parm;
}

int defined_parameters(long long **from_value, long long **to_value, char *variable_char, enum parameter_types variable_in_parm_types) {
    const long long length_from = strlen(from_value);
    const long long length_to = strlen(to_value);

    switch (variable_in_parm_types) {
        case type_parm_from:
            *from_value = malloc(sizeof **from_value);
            if (*from_value == 0) {
                errprintf("Cannot allocate memory for `from_value` variable_char\n");
                return -1;
            }
            **from_value = strtoll(variable_char + length_from, 0, 10);
            break;
        case type_parm_to:
            *to_value = malloc(sizeof **to_value);
            if (*to_value == 0) {
                errprintf("Cannot allocate memory for `to_value` variable_char\n");
                return -1;
            }
            **to_value = strtoll(variable_char + length_to, 0, 10);
            break;
        case invalid_type_parm:
            break;
    }

    return 0;
}

