# Sorting_Robot
Program układający plan pracy dźwigu sortującego kulki na pochylni. Dźwig może przenosić wyłącznie 3 sąsiadujące kulki naraz.

## Problem:
    Na pochylni są ułożone w przypadkowej kolejności kulki w trzech kolorach: czerwone, zielone i niebieskie. 
    Dźwig może przenosić wyłącznie 3 sąsiadujące kulki na koniec, za kulki leżące powyżej, 
    które stoczą się pod własnym ciężarem w dół, wypełniając lukę. 
    Należy ułożyć planu pracy dźwigu tak, aby za pomocą jak najmniejszej ilości ruchów posortować kulki tak, 
    aby najniżej znalazły się czerwone, potem zielone, a najwyżej niebieskie.
    
## Algorytmy:
    Program zawiera 3 różne algorytmy rozwiązujące ten problem:
    1) Algorytm brutalny przeszukujący całą przestrzeń możliwych ruchów.
    2) Algorytm naiwny w pętli skupiający się na przeniesieniu pojedynczej kulki na właściwe miejsce. 
    3) Algorytm wydzielania list opierający się na obserwacji, że jeśli wydzielimy pewne obszary wśród kulek takie, 
      że tylko wśród nich pozwalamy dźwigowi podnosić kulek to te kulki, które nie są zawarte w tych obszarach 
      po pewnym czasie pracy dźwigu opadną na sam dół.


## Możliwe polecenia aktywacji programu:
    W argumentach wywołania należy podać literę związaną z wybranym algorytmem:
        b dla algorytmu brutalnego
        n dla algorytmu naiwnego
        l dla algorytmu wydzielania list

    Program może być aktywowany w trzech trybach:
        1) Dane dostarczone ze standarwego strumienia wejściowego
            Strumień ten można oczywiście przekierować.
            Przykłady:
            1 b
            1 n <<in.txt >>out.txt

        2) Dane generowane losowo
            Należy podać:
                -pożądany rozmiar problemu
            Przykład:
             2 b 100

        3) Cała procedura testowania z pomiarami czasu uwzgledniajacymi wiele powtórzeń
            Należy podać kolejno:
                -liczbę startową rozmiaru problemu
                -ilość badanych rozmiarów
                -krok między każdymi kolejnymi rozmiarami
                -ilość powtórzeń, które zostaną uśrednione
            Przykład:
            3 l 5000 3 1000 30
            Czyli wykonanie  po 30 powtórzeń dla problemów o rozmiarach 5000, 6000, 7000;


## Konwencja danych wejściowych:
    Dane wejściowe mogą zawierać dowolną liczbę instancji problemu o dowolnej długości.
    Zaczynają się od liczby oznaczającej ilość instancji do przetworzenia.
    Jedna linijka tekstu złożonego z samych liter odpowiadającym kolorom kulek jest jedną instancją.
    Przykładowe dane wejściowe składające się z dwóch instancji problemu mogą wyglądać następująco:
        2
        nczzccnnncnncz
        cnnnz

## Dekompozycja programu na moduły źródłowe:
    Program jest podzielony na dwie główne wartswy: warstwę algorytmiczną i wartstwę interfejsu użytkownika.
    Warstwa algorytmiczna nie zawiera żadnych funkcji wejścia-wyjścia, więc np. w razie zmiany koncepcji prezentacji
    wyników warstwa algorytmiczna nie będzie wymagała modyfikacji
        Warstwa interfejsu jest realizowana przez plik main.cpp.
        Warstwa algorytmiczna jest realizowana przez pozostałe pliki.

    Warstwa algorytmiczna jest podzielona na kilka plików.
        list_algoritm
        naive_algorithm
        brute_algorithm
        utilities
    Są to pliki realizujące każdy z trzech algorytmów oraz plik "utilities" zawierający różne funkcje pomocnicze, z
    których korzystają wymienione algorytmy - nie dotyczą one tylko jednego algorytmu, więc posiadają oddzielny plik.
