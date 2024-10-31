from colorama import Fore, Back, Style
import colorama

# Initialize colorama
colorama.init()

# Print some colored text
print(Fore.RED + "This is red text!")
print(Fore.GREEN + "This is green text!")
print(Fore.BLUE + "This is blue text!")
print(Style.RESET_ALL + "Back to normal text")
