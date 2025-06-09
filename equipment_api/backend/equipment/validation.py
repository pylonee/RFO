import re

def validate_sn_by_mask(sn: str, mask: str) -> bool:
    # валидация серийника по маске

    # N – цифра от 0 до 9
    # A – прописная буква латинского алфавита
    # a – строчная буква латинскогоалфавита
    # X – прописная буква латинского алфавита либо цифра от 0 до 9
    # Z – символ из списка: “-“, “_”, “@”

    pattern = ""
    for char in mask:
        if char == 'N':
            pattern+=r'[0-9]'
        elif char == 'A':
            pattern+=r'[A-Z]'
        elif char == 'a':
            pattern += r'[a-z]'
        elif char == 'X':
            pattern += r'[A-Z0-9]'
        elif char == 'Z':
            pattern += r'[-_@]'

    return bool(re.fullmatch(pattern, sn))