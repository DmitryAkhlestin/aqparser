# aqparser
Тестовое задание для кандидата на позицию разработчика на языке C

Задача:
Вам необходимо разработать программу, которая анализирует словарь английских слов и определяет, сколько из них могут быть набраны на QWERTY-клавиатуре с английским языком, передвигаясь только по смежным клавишам. 
При этом можно нажимать одну и ту же клавишу дважды подряд.

Условия:
 ∙ Входные данные: файл со списком английских слов (одно слово на строку).
 ∙ Раскладка клавиатуры: стандартная английская QWERTY.
 ∙ Клавиши считаются смежными, если они находятся горизонтально или вертикально рядом друг с другом. 
Диагональное расположение также считается смежным, но только для клавиш, имеющих общие грани. Так, 's' и 'w', а также 's' и 'z' считаются смежными, но 's' и 'q' - не считаются смежными.
 ∙ Каждую клавишу можно нажимать дважды подряд.

Ваша задача – посчитать и вывести количество английских слов, которые можно набрать, используя только смежные клавиши на QWERTY-клавиатуре.

![image](https://github.com/user-attachments/assets/30b5b511-1b44-4312-b8fd-56aa7b8126d0)

Для сборки необходимо make all, для очистки make clean, для запуска ./build/aqparser -f <text_file_name>
