import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Please provide the file path of the csv file and the text file")
        sys.exit()
    else:
        reference = {}
        with open(sys.argv[1], "r") as file:
            reader = csv.DictReader(file)
            # Here we get all the types of STR excluding the fieldname of name
            types = reader.fieldnames[1:]
            # Here we get all the code of STRs for each individual in csv file
            for row in reader:
                # reference[row['name']] = ''.join(list(row.values())[1:])
                tmp = ''.join(list(row.values())[1:])
                reference[tmp] = row['name']

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as text_file:
        dna = text_file.read().strip()
        code = ""
        for type in types:
            code += str(longest_match(dna, type))

    # Here we get the final result given the code against the reference
    try:
        print(reference[code])
    except KeyError:
        print("No match")


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


if __name__ == "__main__":
    main()
