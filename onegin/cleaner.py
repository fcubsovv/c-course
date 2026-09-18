import unicodedata

def is_greek(char):
    """Проверяет, относится ли символ к греческому алфавиту."""
    try:
        return 'GREEK' in unicodedata.name(char) or char == 'X' or char == "V" or char == "I" or char == "{" or char == "}"
    except ValueError:
        return False

def clean_text(text):
    # Оставляем символ, если это буква/пунктуация/пробел И это НЕ греческий символ
    return "".join(
        c for c in text
        if (unicodedata.category(c).startswith(('L', 'P')) or c.isspace()) and not is_greek(c)
    )

# 1. Читаем исходный файл
with open('zheka_washed.txt', 'r', encoding='utf-8') as f:
    lines = f.readlines()

cleaned_lines = []
for line in lines:
    # Очищаем строку от греческих символов и лишних знаков
    cleaned_line = clean_text(line)

    # Проверяем, не стала ли строка пустой (удаляем пробелы и переносы строк для проверки)
    if cleaned_line.strip():
        cleaned_lines.append(cleaned_line)

# 2. Записываем результат в новый файл
with open("zheka_washed.txt", "w", encoding="utf-8") as f:
    f.writelines(cleaned_lines)
