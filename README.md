# OAIP_Labs-# Лабораторные работы ОАИП

## Содержание:

1. **[Лабораторная 1](#лабораторная-1)**
2. **[Лабораторная 2](#лабораторная-2)**
3. **[Лабораторная 3](#лабораторная-3)**
4. **[Лабораторная 4](#лабораторная-4)**
5. **[Лабораторная 5](#лабораторная-5)**


## Лабораторная 1

**[Задача](https://github.com/OlegSnytko/OAIP_Labs-/tree/main/src/LAB1Sem2)**. 
На 4-6
- Реализовать функцию для создания массива структур.
- Реализовать функцию для вывода массива структур на экран.
- Реализовать функцию для инициализации экземпляра структуры.
- Реализовать функции сортировки массива по каждому полю структуры. (Например, можно отсортировать студентов сначала по дате рождения, затем передумать и отсортировать по среднему баллу).
- Реализовать меню, для проверки функционала.

На 7-8
- Функции не должны привязываться к конкретному массиву: таковой должен передаваться в качестве аргумента.
- В качестве типа одного из полей структуры использовать enum (например, для цвета).
- Реализовать функцию для удаления структуры из массива.
- Реализовать сортировку по двум полям одновременно. (Например, отсортировать автомобили по цвету, на так чтобы все автомобили одного цвета шли в порядке года выпуска).

На 9-10
- Для заполнения структур распарсить html-файл любого списка или каталога.\

## Лабораторная 2
**[Задача]
Написать программу сжатия текстового файла по алгоритму: 
1.	Подсчет частоты встречи каждого слова в файле.
2.	Поиск самого популярного среди длинных слов (А).
3.	Поиск самого непопулярного среди коротких слов (В).
4.	Замена всех слов А и В друг на друга.
5.	Повтор пунктов 2-4 до тех пор, пока это имеет смысл.

На 4-6
- Программа должна сжать и разжать текстовый файл по приведенному выше алгоритму.
- В результате работы должно быть создано два файла: сжатый и разжатый. Последний должен полностью совпадать с исходным. Сжатый файл должен быть меньше исходного.
- При выборе слова А и В понятия «длинное слово» и «короткое слово» можно трактовать гибко. То есть, «длинное слово» не обязательно «самое длинное слово», главное, чтобы его использование имело положительный эффект.

ПРЕДУПРЕЖДЕНИЕ: чтение файла посимвольно (например, через fgetc) – быдлокод, так работает очень долго. Работайте со строками или словами!
ПРЕДУПРЕЖДЕНИЕ: Вычитывание ВСЕГО файла в строчку и работа только со строчкой – тоже быдлокод, так как убивает идеологию работы с файлами. Грамотно используйте функции из библиотеки stdio.
ПРЕДУПРЕЖДЕНИЕ: незакрытые хэндлы, отсутствие простейших проверок успешности файловых операций будут трактоваться как БАГИ.

На 7-8
	- Сжатие и разжатие файла реализовать двумя разными программами (два отдельных проекта).
	- Следовательно, в сжатый файл должны быть упакованы данные, необходимые для точного разжатия.

На 9-10
	- Для реализации пункта 1 алгоритма использовать собственный связный список (стек или очередь).\

## Лабораторная 3
**[Задача]
Написать программу обработки для bmp-изображений с сохранением результата в отдельный bmp файл. 

На 4-6
-Варианты обработки – перевод изображения в негатив, перевод изображения в черно-белые цвета.
-Название файла для обработки должно вводиться пользователем.
-Если файл не подходит для программы, программа должна сообщить об ошибке и корректно завершиться.
-Достаточно обрабатывать только структуры типа BITMAPINFOHEADER, только 24-bit изображения.
-Не использовать WINAPI, структуры описывать самостоятельно.
-Работу с пикселями реализовать через структуры.

На 7-8
	- Реализовать медианную фильтрацию.
	- Реализовать гамма-коррекцию.
	- Параметры преобразований изображений задаются в клавиатуры.

На 9-10
	- Реализовать поддержку 1-,2-,4-,16-,24-bit изображений.\
	
## Лабораторная 4
**[Задача]	
Программа должна определять загаданный пользователем объект. Для этого она должна управлять двоичным деревом, в котором хранится информация о загадываемых объектах. Работа проходит по следующему сценарию.

1)	Пользователь загадывает объект.
2)	Программа задает вопросы, на которые пользователь отвечает да/нет.
3)	Каждый ответ приводит к очередному вопросу из дерева. Так до тех пор, пока не будет достигнут конец (лист) с ответом.
4)	Если ответ неверный, программа должна предложить ввести данные о загаданном объекте (отличительный вопрос) и запомнить новый объект.
	
Примечание:	Программа становится осмысленнее, если работает с предметами какой-то ограниченной тематики, иначе вопросы в дереве будут странными и хаотичными. Тематику выбирайте сами.

На 4-6
- Описать отдельное API (библиотечку) для работы с двоичным деревом.
- Размер дерева не должен ограничиваться хардкодом (дефайнами, константами, максимальным размером, введенным с клавиатуры и т.п.), то есть дерево должно иметь возможность расти безгранично.

На 7-8
	- Реализовать функцию сохранения / загрузки базы данных об объектах (сохранение дерева в файл). Чтобы не вносить базу каждый раз заново. 
	- Подготовить тестовую базу на объектов 20.

На 9-10
	- Допилить какую-нибудь интересную фичу на свой вкус)

[как вариант, можно сделать логирование]
