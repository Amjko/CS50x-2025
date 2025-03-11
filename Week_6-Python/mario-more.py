def main():
    # Prints a pyramid with 2-wide gap in the middle depending on the height.
    
    # Accept values within the range of 1 - 8
    while True:
        try:
            height = int(input("Height: "))
            if not 1 <= height <= 8:
                continue
        except ValueError:
            continue
        else:
            break

    for i in range(0, height):
        # Spaces to align top hashtags
        print(" " * (height - 1 - i), end='')

        # First side of semi-pyramid
        print("#" * (1 + i), end='')

        # 2-wide gap
        print("  ", end='')

        # Opposite side of semi-pyramid
        print("#" * (1 + i), end='')

        print()


if __name__ == "__main__":
    main()
