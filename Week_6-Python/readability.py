def main():
    """Determine the grade level of reading comprehension using Coleman-Liau formula.
    """
    text = input("Text: ")
    
    # Use Coleman-Liau formula to estimate grade level reading comprehension
    avg_letters = get_avg_letter(text)
    avg_sentences = get_avg_sentence(text)
    grade_index = (0.0588 * avg_letters) - (0.296 * avg_sentences) - 15.8
    
    # Output the approximate grade level
    if grade_index <= 1:
        print("Before Grade 1")
    elif grade_index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {int(round(grade_index))}")


def get_avg_letter(text: str = '0') -> float:
    """Compute the average number of letters present in text.

    Args:
        text (str, optional): A string of text. Defaults to '0'.

    Returns:
        float: The average number of letters.
    """    
    total_words = len(text.split())
    total_letters = sum(1 for char in text if char.isalpha())
    
    return (total_letters / total_words) * 100


def get_avg_sentence(text: str = '0') -> float:
    """Compute the average number of sentences present in text.

    Args:
        text (str, optional): A string of text. Defaults to '0'.

    Returns:
        float: The average number of sentences.
    """    
    total_words = len(text.split())
    total_sentences = sum(1 for char in text if char in ('.', '!', '?'))
    
    return (total_sentences / total_words) * 100


if __name__ == "__main__":
    main()