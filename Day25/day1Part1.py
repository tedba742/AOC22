def snafu_to_decimal(snafu):
    """Convert a SNAFU number to a decimal number."""
    value_map = {'2': 2, '1': 1, '0': 0, '-': -1, '=': -2}
    decimal_value = 0
    place_value = 1
    
    for char in reversed(snafu):
        decimal_value += value_map[char] * place_value
        place_value *= 5
        
    return decimal_value

def decimal_to_snafu(decimal):
    """Convert a decimal number to a SNAFU number."""
    if decimal == 0:
        return "0"
    
    snafu_digits = []
    value_map = {2: '2', 1: '1', 0: '0', -1: '-', -2: '='}
    
    while decimal != 0:
        remainder = decimal % 5
        decimal //= 5
        
        if remainder > 2:
            remainder -= 5
            decimal += 1
        
        snafu_digits.append(value_map[remainder])
    
    return ''.join(reversed(snafu_digits))

def main():
    with open('input.txt', 'r') as file:
        snafu_numbers = file.read().strip().split('\n')
    
    total_decimal = sum(snafu_to_decimal(snafu) for snafu in snafu_numbers)
    
    result_snafu = decimal_to_snafu(total_decimal)
    
    print(f"The SNAFU number to supply to Bob's console is: {result_snafu}")

if __name__ == "__main__":
    main()
