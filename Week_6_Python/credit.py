import sys


def main():
    """ Validate a credit card number using Luhn's Algorithm.
    
    This function prompts user for a credit card number,
    processes it using checksum, and determines whether
    the card is valid or invalid, as well as card type.
    
    Returns:
        None: The result is printed to the console.
    """        
    
    # Uncomment lines 15:16 to accept formatted card numbers (i.e. XXXX-XXXX-XXXX)
    # card_num = input("Number: ")
    # card_num = card_num.replace('-', '')
    
    # Comment lines 19:26 if accepting formatted card numbers
    while True:
        try:
            card_num = int(input("Number: "))
            if card_num <= 0:
                continue
        except ValueError:
            continue
        else:
            card_num = str(card_num)
            break

    # Determine which card type
    is_valid = checksum(card_num)
    if is_valid:
        if card_num[:2] in ('34', '37') and len(card_num) == 15:
            print("AMEX")
        elif 51 <= int(card_num[:2]) <= 55 and len(card_num) == 16:
            print("MASTERCARD")
        elif card_num[0] == '4' and len(card_num) in (13, 16):
            print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")


def checksum(card_num: str = '0'):
    """Validates card number using Luhn's Algorithm.

    Args:
        card_num (str, optional): A string of representing a numeric card number. Defaults to '0'.

    Returns:
        bool: True if the computed checksum modulo 10 equals to 0, meaning the card number is valid. False otherwise.
    """
    
    # A list of int but twice each int per 2-interval starting from right
    alt_nums = [
        int(num) * 2 if index % 2 == 1 else int(num)
        for index, num in enumerate(reversed(card_num))
    ]
    
    # Sum all 2-digit int of their individual number
    alt_nums = [sum(int(num) for num in str(index)) for index in alt_nums]
    
    # Card number is valid if computed checksum ends with zero
    num_sum = sum(alt_nums)
    if num_sum % 10 == 0:
        return True
    else:
        return False


if __name__ == "__main__":
    main()