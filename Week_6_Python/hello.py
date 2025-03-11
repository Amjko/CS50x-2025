import re


def main():
    # Prompt user for a name then greet
    
    while True:
        name = input("What is your name? ")
        if bool(re.search(r"\d", name)) == True:
            continue
        else:
            break
        
    # Greet inputted name
    name = name.capitalize()
    print(f"hello, {name}")


if __name__ == "__main__":
    main()