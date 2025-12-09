# les-devoir-de-programmation-syst-mes-et-r-seaux
Devoir 1  - Options et arguments sur la ligne de commande
Maïssa MBAYE
Écrivez un programme qui prend en argument sur la ligne de commande des options suivantes :
-f entier : Cette option prend comme argument un entier n et calcule 2^n = f(n)
-g entier : Cette option prend comme argument un entier m et calcule 2*m = g(m)

Si les options sont enchaînées, le programme doit calculer la composition de fonction fog ou gof en fonction de l'ordre des options.
Exemple:
## Calcul de 2^3
./prog -p 3

## Calcul de 2*3
./prog -g 3

## Calcul de fog(3) = 2^3 * 2 = 8
./prog -f 3 -g

## Calcul de gof(3) = 2*(2^3) = 16
./prog -g 3 -f
