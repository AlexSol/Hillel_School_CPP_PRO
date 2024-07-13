
# Hillel_School_CPP_PRO

## Заняття 3
1. New C++ standarts: Smart Pointers
	- [std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr)
	- [std::shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr)
	- [std::weak_ptr](https://en.cppreference.com/w/cpp/memory/weak_ptr)
2. Константність та lambda
3. ДЗ

Посилання Smart Pointers:
- https://habr.com/ru/companies/piter/articles/706866/
- https://ravesli.com/urok-193-std-unique_ptr/#toc-9
- https://ravesli.com/urok-194-std-shared_ptr/
- https://ravesli.com/urok-195-std-weak_ptr-tsiklicheskaya-zavisimost-s-std-shared_ptr/

- Майерс, Скотт "Эффективный и современный С++_ 42 рекомендации по использованию C++11 и C++14" - `Розділ 4. Інтелектуальні вказівник` 

Відео:
- [Structured bindings. common_type, declval. unique_ptr](https://youtu.be/ynrrO_L3RyE?si=b2PqoAwxNzdiItCu)

- [Внутреннее устройство shared_ptr, weak_ptr](https://youtu.be/ogj3JI57BLM?si=C-IaYhqnpN6LOLie)


Посилання Lambda:


## 3. ДЗ

3.0 Практика використання:
- `std::unique_ptr`
- `std::shared_ptr`

3.1 Реалізувати власний спрощений варіант `std::unique_ptr`.
	
Потрібно реалізуват методи:
- конструктор, який приймає сирий вказівник T*
- деструктор
- `T& operator=( const T& r )`
- `T& operator*() const`
- `T* operator->() const`
- `T* get() const T* get() const`
- `explicit operator bool() const noexcept`

Саму реалізацію - покращуюйте необмеженно, я все заціню!

3.2 Реалізувати власний спрощений варіант `std::shared_ptr`.

Потрібно реалізуват методи:	
- конструктор, який приймає сирий вказівник T*
- деструктор
- копіюючий конструктор
- `T& operator=( const T& r )`
- `T& operator*() const`
- `T* operator->() const`
- `long use_count() const`
- `T* get() const T* get() const`
- `explicit operator bool() const noexcept`

Мета нашого классу в тому що я хочу використовувати його приблизно так:

```cpp
MySharedPtr<int> ptr1(new int(42));
MySharedPtr<int> ptr2 = ptr1;
*ptr2 = 100;
```

Клас бажано зробити шаблонним. Але якщо ви не працювали з ними - зробіть MySharedPtr для int. Оцінка за це не знижується.
Тоді використання буде

```cpp
MySharedPtr ptr1(new int(42));
MySharedPtr ptr2 = ptr1;
*ptr2 = 100;
```
Саму реалізацію - покращуюйте необмеженно, я все заціню!