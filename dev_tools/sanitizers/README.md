# Sanitizers

`sanitizers` - це інструменти компілятора та рантайму, які допомагають знаходити помилки у C/C++ під час виконання програми.

Вони корисні для пошуку:
- виходу за межі масиву;
- use-after-free;
- витоків пам'яті;
- undefined behavior;
- гонок даних у багатопоточному коді.

У цій папці кожен sanitizer винесений в окремий маленький CMake-проєкт.

## Доступні прапори

### `-fsanitize=address`
AddressSanitizer (ASan) шукає помилки роботи з пам'яттю:
- heap/stack buffer overflow;
- use-after-free;
- double free;
- invalid free.

Приклад: `address/`

### `-fsanitize=leak`
LeakSanitizer (LSan) шукає витоки пам'яті, коли виділена пам'ять не була звільнена до завершення програми.

Приклад: `leak/`

### `-fsanitize=undefined`
UndefinedBehaviorSanitizer (UBSan) ловить типові ситуації з undefined behavior, наприклад:
- signed integer overflow;
- некоректні перетворення типів;
- порушення вирівнювання;
- вихід за допустимі межі деяких операцій.

Приклад: `undefined/`

### `-fsanitize=thread`
ThreadSanitizer (TSan) допомагає знаходити гонки даних та небезпечні одночасні доступи з різних потоків.

Приклад: `thread/`

## Швидкий запуск

Зібрати всі приклади:

```bash
make all
```

Зібрати окремий sanitizer:

```bash
make address
make leak
make undefined
make thread
```

Запустити приклад:

```bash
make run-address
make run-leak
make run-undefined
make run-thread
```

Очистити збірку:

```bash
make clean
```

## Примітки

- Для sanitizer-ів бажано збирати код з `-g` та без агресивної оптимізації.
- `ThreadSanitizer` не комбінується в одному білді з `AddressSanitizer`.
- Підтримка окремих sanitizer-ів залежить від компілятора та платформи. Найкраще вони працюють у Clang/LLVM та сучасному GCC.