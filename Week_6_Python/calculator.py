def addition(equation: str = "0"):
    numbers = [int(num.strip()) for num in equation.split("+")]
    result = sum(numbers)
    
    return result

def subtraction(equation: str = "0"):
    numbers = [int(num.strip()) for num in equation.split("-")]
    difference = numbers[0]
    result = difference
    for i in numbers[1:]:
        result -= i        

    return result

def division(equation: str = "0"):
    numbers = [int(num.strip()) for num in equation.split("/")]
    quotient = numbers[0]
    result = quotient
    for i in numbers[1:]:
        result /= i
        
    return int(result)

def multiplication(equation: str = "0"):
    numbers = [int(num.strip()) for num in equation.split("*")]
    product = numbers[0]
    result = product
    for i in numbers[1:]:
        result *= i
        
    return result

def main():
    operator = input("Choose operator [+, -, /, *]: ")
    equation = input("Problem: ")
    if operator == "+":
        result = addition(equation)
    elif operator == "-":
        result = subtraction(equation)
    elif operator == "/":
        result = division(equation)
    elif operator == "*":
        result = multiplication(equation)
    else:
        result = 0
        print("Incorrect operator.")
    
    print(f"Result: {result}")
    
if __name__ == "__main__":
    main()