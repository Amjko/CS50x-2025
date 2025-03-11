import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py file.csv dna.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    try:
        with open(sys.argv[1], "r") as database:
            csv_reader = csv.DictReader(database)
            if csv_reader.fieldnames is None:
                print(".csv file is missing headers.")
                sys.exit(1)
            else:
                str_sequences = csv_reader.fieldnames[1:]
                csv_list = list(csv_reader)
                
    except OSError:
        print("Database file not found.")
        sys.exit(1)
    
    # TODO: Read DNA sequence file into a variable
    try:
        with open(sys.argv[2], "r") as dna_file:
            dna_reader = dna_file.read().strip()
            
    except OSError:
        print("DNA file not found.")
        sys.exit(1)

    # TODO: Find longest match of each STR in DNA sequence
    dna_str = [int(longest_match(dna_reader, str_)) for str_ in str_sequences]

    # TODO: Check database for matching profiles
    for row in csv_list:
        row_value = list(map(int, list(row.values())[1:]))
        if dna_str == row_value:
            print(f"{row['name']}")
            break
    else:
        print("No match.")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            
            # If there is no match in the substring
            else:
                break
        
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
