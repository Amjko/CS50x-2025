def addition(equation: str = "0"):
    """Calculate the sum of numbers.

    Args:
        equation (str, optional): Is the provided problem. Defaults to "0".

    Returns:
        integer: Sum of numbers
    """    
    numbers = [int(num.strip()) for num in equation.split('+')]
    result = sum(numbers)
    
    return result

def subtraction(equation: str = "0"):
    """Calculate the difference of numbers.

    Args:
        equation (str, optional): Is the provided problem. Defaults to "0".

    Returns:
        integer: Difference of numbers.
    """    
    numbers = [int(num.strip()) for num in equation.split('-')]
    result = numbers[0]
    for num in numbers[1:]:
        result -= num
        
    return result

def division(equation: str = "0"):
    """Calculate the quotient of numbers.

    Args:
        equation (str, optional): Is the provided problem. Defaults to "0".

    Returns:
        float: Quotient of numbers.
    """    
    numbers = [int(num.strip()) for num in equation.split('/')]
    result = numbers[0]
    for num in numbers[1:]:
        result /= num
    
    return result

def multiplication(equation: str = "0"):
    """Calculate the product of numbers.

    Args:
        equation (str, optional): Is the provided problem. Defaults to "0".

    Returns:
        integer: Product of numbers.
    """    
    numbers = [int(num.strip()) for num in equation.split('*')]
    result = numbers[0]
    for num in numbers[1:]:
        result *= num
        
    return result

def main():
    operator = input("Choose operation [+, -, *, /]: ")
    equation = input("Problem: ")
    
    if operator == '+':
        result = addition(equation)
    elif operator == '-':
        result = subtraction(equation)
    elif operator == '/':
        result = division(equation)
        print(f"Rounded Result: {round(result)}")
    elif operator == '*':
        result = multiplication(equation)
    else:
        result = 0
        
    print(f"Result: {result}")

if __name__ == "__main__":
    main()