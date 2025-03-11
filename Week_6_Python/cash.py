def main():
    # Determines the amount of US coins needed to return for owed change
    
    # Accept only floating-point numbers above 0
    while True:
        try:
            change_owed = float(input("Change owed: ").strip())
            if change_owed < 0:
                continue
        except ValueError:
            continue
        else:
            break

    # Convert owed change from coins to dollars
    if change_owed:
        change_owed = int(change_owed * 100)
    else:
        change_owed = 0
    
    # Count amount of coins to total owed change    
    coin_amount = 0
    while change_owed > 0:
        coin_amount += change_owed // 25
        change_owed %= 25
        
        coin_amount += change_owed // 10
        change_owed %= 10
        
        coin_amount += change_owed // 5
        change_owed %= 5
        
        coin_amount += change_owed
        change_owed = 0
        
    print(coin_amount)


if __name__ == "__main__":
    main()