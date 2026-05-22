# Compiler Flags Demo

Міні-проєкт показує, навіщо потрібні суворі параметри компіляції для GNU/Clang.

Що демонструє проєкт:
- суворі warning-прапори разом з Werror;
- як помилки в коді зупиняють збірку на ранньому етапі;
- різницю видимості символів при fvisibility=hidden;
- секціонування коду і даних через ffunction-sections та fdata-sections.

## Структура

- CMakeLists.txt: підключення прапорів для GNU/Clang;
- include/visibility_demo.hpp: API для shared library;
- src/visibility_demo.cpp: функції з керуванням visibility;
- src/main.cpp: стабільний приклад, який успішно збирається;
- src/warnings_bad.cpp: навмисно проблемний код для демонстрації warning-ів.

## Швидкий запуск

Перейти в папку:

```bash
cd dev_tools/compiler-flags-demo
```

Зібрати стабільний варіант:

```bash
make run
```

Подивитись експортовані символи з shared library:

```bash
make symbols
```

Запустити збірку навмисно проблемного прикладу (очікувано впаде через Werror):

```bash
make broken
```

Очистити build:

```bash
make clean
```

## Які прапори тут підсвічені

GNU:
- fno-extended-identifiers;
- fstrict-aliasing;
- Wall Wextra Werror та додаткові warning-и на shadow, conversion, switch, float-equal;
- duplicated-cond, duplicated-branches, restrict, null-dereference;
- ffunction-sections fdata-sections;
- fvisibility=hidden fvisibility-inlines-hidden.

Clang:
- Wall Wextra Werror;
- Wno-comment, Wno-final-dtor-non-final-class;
- ffunction-sections fdata-sections;
- fvisibility=hidden fvisibility-inlines-hidden.

Примітка: не всі warning-и детерміновано спрацьовують у будь-якій версії компілятора. Для стабільної демонстрації додано типові кейси (shadow, conversion, switch, float-equal, duplicated-cond).