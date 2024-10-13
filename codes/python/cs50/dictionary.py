words = set()

def load(dictionary):
    with open(dictionary, "r") as file:
        words.update(file.read().splitlines())
    return True

def check(word):
    return word.lower() in words

def size():
    return len(words)

def unload():
    return True

def main():
    # Load the dictionary
    dictionary_file = "test_dictionary.txt"
    if load(dictionary_file):
        print(f"Loaded {size()} words from {dictionary_file}")
    else:
        print("Failed to load dictionary")
        return

    # Test some words
    test_words = ["apple", "banana", "carrot", "DATE", "fig"]
    for word in test_words:
        if check(word):
            print(f"'{word}' is in the dictionary")
        else:
            print(f"'{word}' is NOT in the dictionary")

    # Unload the dictionary
    if unload():
        print("Dictionary unloaded successfully")
    else:
        print("Failed to unload dictionary")


# if __name__ == "__main__" `main()` is only called if the script is run directly (not imported as a module).
if __name__ == "__main__":
    main()


# touch dictionary_file.txt
# echo "apple" >> dictionary_file.txt
# echo "banana" >> dictionary_file.txt
# echo "cherry" >> dictionary_file.txt
# echo "date" >> dictionary_file.txt
# echo "elderberry" >> dictionary_file.txt
# echo "fig" >> dictionary_file.txt
# echo "grape" >> dictionary_file.txt
# echo "honeydew" >> dictionary_file.txt
